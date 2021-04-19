// Copyright 2020 Your Name <your_email>

#include <Database.hpp>


void Database::create_db(std::string way) {
  //open db
  rocksdb::Options options;
  options.create_if_missing = true;
  rocksdb::DB *db;
  rocksdb::Status s = rocksdb::DB::Open(options, way, &db);
  assert(s.ok());

  //create cf
  rocksdb::ColumnFamilyHandle *h1;
    s = db->CreateColumnFamily
        (rocksdb::ColumnFamilyOptions(), "new_cf", &h1);
  assert(s.ok());

  // close DB
  s = db->DestroyColumnFamilyHandle(h1);
  assert(s.ok());
  delete db;

}