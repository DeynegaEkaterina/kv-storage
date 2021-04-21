// Copyright 2020 Your Name <your_email>

#include <Database.hpp>


//creates db with given cf_names and path
void Database::create_db(std::string path,
                         std::vector<std::string> family_names)
{
  //open db
  Options options;
  options.create_if_missing = true;
  DB *db;
  Status s = DB::Open(options, path, &db);
  assert(s.ok());

  //create column_family
  rocksdb::ColumnFamilyHandle *h1;
  for (auto &iter : family_names) {
    s = db->CreateColumnFamily
        (ColumnFamilyOptions(), iter, &h1);
    delete h1;
  }
  delete db;
  assert(s.ok());
}

//opens db
void Database::open_db() {
  DB::Open(DBOptions(), _way, _column_families, &_handles, &_db);
}


//fills _column_families_names
void Database::fill_vector(int num) {
  for (int i = 0; i != num; i++) {
    _column_families_names.push_back("fam"+ std::to_string(i));
  }
}

//copies _column_families_names to _column_families
void Database::parse(std::string way_to_db){
  _way = way_to_db;
  Status s;

   s = DB::ListColumnFamilies(DBOptions(),
                                      way_to_db,
                                      &_column_families_names);
  assert(s.ok());
  for (auto a : _column_families_names) {
    _column_families.emplace_back(a,
                                  rocksdb::ColumnFamilyOptions());
  }
}

//writes value to db
void Database::put_value(Element element) {
  std::vector<std::string>::iterator it =
      std::find(_column_families_names.begin(),
             _column_families_names.end(), element._family_name);
  if (it != _column_families_names.end()){
    Status s;
    s = _db ->Put(WriteOptions(),
  _handles[std::distance(_column_families_names.begin(), it)],
             element._key, element._value);
    assert(s.ok());
  }
}

//gets value from db
Element Database::get_value(std::string key, std::string column_family_name) {
  std::vector<std::string>::iterator
      it = std::find(_column_families_names.begin(),
               _column_families_names.end(), column_family_name);
  if (it != _column_families_names.end()){
    Status s;
    std::string value;
    s = _db->Get(ReadOptions(),
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
