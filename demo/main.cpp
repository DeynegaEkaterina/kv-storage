#include <Database.hpp>
#include <iostream>
int main() {
  std::string path_in("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db1");
  Database db1;
  db1.parse(path_in);
  db1.open_db();
  db1.read_db(); //queue elements is full



  std::string path_out("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db2");
  Database db2;
  db2.create_db(path_out, db1._column_families_names);
  db2.parse(path_out);
  db2.open_db();
  db2.fill_db();
  db2.print();
}