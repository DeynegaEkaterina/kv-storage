#include <Database.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include <thread>

namespace po = boost::program_options;
std::string path_in("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db1");
std::string path_out("/home/ekaterina/CLionProjects/lab-10-kv-storage/cmake-build-debug/db2");
const size_t _256_MiB = 1024 * 256 * 1024;

int main(int argc, char* argv[]) {

  po::options_description descr("Usage");
  po::options_description desc("Options");
  desc.add_options()("log_level <string>",po::value<std::string>(), "= \"info\"|\"warning\"|\"error\"\n= default: \"Error\"\n")(
      "thread_count <number>", po::value<size_t>(), "= default: count of logical core\n")(
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
    log_level = "Error";
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


 /* boost::log::register_simple_formatter_factory<boost::log
  ::trivial::severity_level, char>(log_level);
  const std::string format =
      "%TimeStamp% <%Severity%> (%ThreadID%): %Message%";
  boost::log::add_file_log(
      boost::log::keywords::file_name = "logs/log_trace_%N.log",
      boost::log::keywords::rotation_size = _256_MiB,
      boost::log::keywords::format = format);
  boost::log::add_console_log(
      std::cout,
      boost::log::keywords::format =
          format);
  boost::log::add_common_attributes();*/

  Database db1;
  db1.parse(path_in);
  db1.open_db();
  db1.read_db();


  Database db2;
  db2.create_db(path_out, db1._column_families_names);
  db2.parse(path_out);
  db2.open_db();
  db2.fill_db();
  db2.print();
}