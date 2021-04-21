#include <Database.hpp>
#include <iostream>
int main() {
  std::string path("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db");
  Database db1;

  db1.parse(path);
  /*db1.open_db();
  Element el1("key1", "value1", "family1");
  Element el2("key2", "value2", "family2");
  db1.put_value(el1);
  db1.put_value(el2);
  db1.get_value("key1", "family1");
  db1.print();*/
}