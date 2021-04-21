#include <Database.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include <thread>
namespace po = boost::program_options;
std::string path_in("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db1");
std::string path_out("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db2");

int main(int argc, char* argv[]) {
  po::options_description descr("Usage");
  po::options_description desc("Options");
  desc.add_options()("log-level <string>",po::value<std::string>(), "= \"info\"|\"warning\"|\"error\"\n= default: \"Severity\"\n")(
      "thread-count <number>", po::value<size_t>(), "= default: count of logical core\n")(
      "input <path>", po::value<std::string>(), "= <path/to/input/storage.db>\n= default: /home/.../cmake-build-debug/db1\n")(
      "output <path>", po::value<std::string>(), "= <path/to/output/storage.db>\n= default: /home/.../cmake-build-debug/db2\n")(
      "help", "optional information\n");

  po::variables_map vm; // хранит ключи
  po::store(po::parse_command_line(argc, argv, desc), vm);

  if (vm.count("help")) {
    std::cout << descr;
    std::cout << "  dbcs [options] <path/to/input/storage.db>\n" << std::endl;
    std::cout << desc << std::endl;
    return 0;
  }

  std::string log_level;
  size_t thread_count;
  std::string  input;
  std::string output;


  if (vm.count("log-level")) {
    log_level = vm["log-level"].as<std::string>();
    std::cout << "log-level:" << log_level << std::endl;
  } else {
    log_level = "Severity";
    std::cout << "log-level:" << log_level << std::endl;
  }
  if (vm.count("thread-count")) {
    thread_count = vm["thread-count"].as<int>();
    std::cout << "threads:" << thread_count << std::endl;
  } else {
    thread_count = std::thread::hardware_concurrency();
    std::cout << "threads:" << thread_count << std::endl;
  }
  if (vm.count("output")) {
    output = vm["output"].as<std::string>();
    std::cout << "output:" << output << std::endl;
  } else {
    output = path_out;
    std::cout << "output:" << output << std::endl;
  }
  if (vm.count("input")) {
    input = vm["input"].as<std::string>();
    std::cout << "input:" << input << std::endl;
  } else {
    input = path_in;
    std::cout << "input:" << input << std::endl;
  }




 /* std::string path_in("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db1");
  Database db1;
  db1.parse(path_in);
  db1.open_db();
  db1.read_db();



  std::string path_out("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db2");
  Database db2;
  db2.create_db(path_out, db1._column_families_names);
  db2.parse(path_out);
  db2.open_db();
  db2.fill_db();
  db2.print();*/
}