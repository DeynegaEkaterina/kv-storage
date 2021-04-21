#include <Database.hpp>
#include <iostream>
int main() {
  std::string path("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db1");
  Database db1;
  db1.fill_vector(5);
  db1.create_db(path, db1._column_families_names);
  db1.parse(path);
  db1.open_db();
  for(int i = 0; i <= 4; i++) {
    for (int z = 0; z != 11; z++) {
      Element tmp("key" + std::to_string(z),
                  "value" + std::to_string(z),
                  "fam" + std::to_string(i));
      db1.put_value(tmp);
    }
  }

  db1.print();

}