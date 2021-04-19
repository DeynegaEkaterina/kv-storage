// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <PicoSHA.hpp>
#include "boost/log/trivial.hpp"
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <rocksdb/table.h>
class Database{
 public:
  Database() = default;
  void create_db(std::string way);
  std::vector <std::string> _column_families_names;
};


#endif // INCLUDE_HEADER_HPP_
