// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_DATABASE_HPP_
#define INCLUDE_DATABASE_HPP_
#include "Element.hpp"


#include <boost/log/trivial.hpp>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <rocksdb/table.h>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace rocksdb;

class Database{
 public:
  Database() = default;

  void create_db(std::string path, std::vector<std::string> family_names);
  void open_db();
  void parse(std::string way_to_db);
  void put_value(Element element);
  Element get_value(std::string key, std::string column_family_name);
  void print();
  void fill_vector(int num);
  void fill_db();
  void read_db();

  std::vector<std::string> _column_families_names;
  rocksdb::DB *_db;
  std::vector<rocksdb::ColumnFamilyHandle *> _handles;
  std::string _way;
  std::vector<rocksdb::ColumnFamilyDescriptor> _column_families;
  std::queue<Element> elements;
};


#endif // INCLUDE_DATABASE_HPP_
