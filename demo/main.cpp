#include <Database.hpp>
#include <iostream>
int main() {
  std::string path("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db1");
  Database db2;
  db2.parse(path);
  db2.open_db();
  db2.read_db();


}