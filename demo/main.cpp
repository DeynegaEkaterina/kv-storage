#include <Database.hpp>
#include <iostream>
int main() {
  std::string path("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db");
  Database db1;
  db1.fill_vector(5);
  db1.create_db(path, db1._column_families_names);
  db1.parse(path);
  db1.open_db();
  db1.print();

}