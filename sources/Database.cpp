// Copyright 2020 Your Name <your_email>

#include <Database.hpp>

std::queue<Element> elements;

//creates db with given cf_names and path
void Database::create_db(std::string &path,
                         std::vector<std::string> &family_names)
{
  //open db
  rocksdb::Options options;
  options.create_if_missing = true;
  rocksdb::DB *db;
  rocksdb::Status s = rocksdb::DB::Open(options, path, &db);
  assert(s.ok());

  //create column_family
  rocksdb::ColumnFamilyHandle *h1;
  for (auto &iter : family_names) {
    s = db->CreateColumnFamily
        (rocksdb::ColumnFamilyOptions(), iter, &h1);
    delete h1;
  }
  delete db;
  assert(s.ok());
}

//opens db
void Database::open_db() {
  rocksdb::DB::Open(rocksdb::DBOptions(), _way, _column_families,
                    &_handles, &_db);
}

void Database::close_db() {
  delete _db;
}

//fills _column_families_names
void Database::fill_vector(int &num) {
  for (int i = 0; i != num; i++) {
    _column_families_names.push_back("fam"+ std::to_string(i));
  }
}

//copies _column_families_names to _column_families
void Database::parse(std::string &way_to_db){
  _way = way_to_db;
  rocksdb::Status s;

   s = rocksdb::DB::ListColumnFamilies(rocksdb::DBOptions(),
                                      way_to_db,
                                      &_column_families_names);
  assert(s.ok());
  for (auto a : _column_families_names) {
    _column_families.emplace_back(a,
                                  rocksdb::ColumnFamilyOptions());
  }
}

//writes value to db
void Database::put_value(Element &element) {
  m2.lock();
  std::vector<std::string>::iterator it =
      std::find(_column_families_names.begin(),
             _column_families_names.end(), element._family_name);
  if (it != _column_families_names.end()){
    rocksdb::Status s;
    s = _db ->Put(rocksdb::WriteOptions(),
  _handles[std::distance(_column_families_names.begin(), it)],
             element._key,
      picosha2::hash256_hex_string(element._key + element._value));
    assert(s.ok());
  }
  m2.unlock();
}

//gets value from db
Element Database::get_value(std::string &key, std::string &column_family_name) {
  std::vector<std::string>::iterator
      it = std::find(_column_families_names.begin(),
               _column_families_names.end(), column_family_name);
  if (it != _column_families_names.end()){
    rocksdb::Status s;
    std::string value;
    s = _db->Get(rocksdb::ReadOptions(),
  _handles[std::distance(_column_families_names.begin(), it)],
                     key, &value);
    assert(s.ok());
    Element tmp(key, value, column_family_name);
    return tmp;
  }  else {
    return Element();
  }
}

//prints cf and values
void Database::print() {
  for (const auto iter : _handles) {
    std::cout << "family " + iter->GetName() << std::endl;
    rocksdb::Iterator *it = _db->NewIterator
        (rocksdb::ReadOptions(), iter);
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
      std::cout << it->key().ToString() << ": "
                << it->value().ToString() << std::endl;
    }
    assert(it->status().ok());
    delete it;
  }
}

//prints trivial log
void Database::print_trivial_log(Element &element){
  BOOST_LOG_TRIVIAL(info) << " :" << element._key << " "
                          << element._value << std::endl;
}

//fills new db with values from queue
void Database::fill_db() {
  bool status = true;
  while (status) {
    m1.lock();
    if (!elements.empty())
    {
      Element tmp = elements.front();
      put_value(tmp);
      elements.pop();
      print_trivial_log(tmp);
      m1.unlock();
    } else {
      status = false;
      m1.unlock();
    }
  }
}


//fills the queue with values from given db
void Database::read_db() {
  for (const auto iter : _handles) {
    rocksdb::Iterator *it = _db->NewIterator(rocksdb::ReadOptions(), iter);
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
      Element tmp(it->key().ToString(), it->value().ToString(),
                  iter->GetName());
      elements.push(tmp);
    }
    assert(it->status().ok());
    if (!elements.empty()) delete it;
  }
}

void Database::logger(std::string &level) {
  boost::log::register_simple_formatter_factory<boost::log
  ::trivial::severity_level, char>(level);
  const std::string format =
      "%TimeStamp% <%Severity%> (%ThreadID%): %Message%";
  boost::log::add_file_log(
      boost::log::keywords::file_name = "logs/log_trace_%N.log",
      boost::log::keywords::rotation_size = _256_MiB,
      boost::log::keywords::format = format);
  boost::log::add_console_log(
      std::clog,
      boost::log::keywords::format =
          format);
  boost::log::add_common_attributes();
}
