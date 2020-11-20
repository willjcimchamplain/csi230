/*
@file week11.cpp
@brief displays my ability to use external libraries
  I import 2 libraries (program options, and timer) and call each of them in this program
@author Will Im
@credit boost.timer: https://theboostcpplibraries.com/boost.timer
@credit boost.program_options: https://theboostcpplibraries.com/boost.program_options
@assignment Lab 11.2
@date 11/19/2020
*/

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace boost::program_options;

void on_age(int age)
{
  std::cout << "On age: " << age << '\n';
}

int main(int argc, const char *argv[])
{
  std::cout << "Starting timer for code\n";
  boost::timer::cpu_timer timer;
  std::cout << timer.format() << "\n";

  try
  {
    options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("pi", value<float>()->default_value(3.14f), "Pi")
      ("age", value<int>()->notifier(on_age), "Age")
      ("file", value<std::string>(), "File");
    boost::timer::cpu_timer timer;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("file")){
      std::ofstream fout;
      fout.open(vm["file"].as<std::string>().c_str());
      if (fout.is_open()){
        if (vm.count("help"))
          fout << desc << '\n';
        else if (vm.count("age"))
          fout << "Age: " << vm["age"].as<int>() << '\n';
        else if (vm.count("pi"))
          fout << "Pi: " << vm["pi"].as<float>() << '\n';
      }
      else{
        std::cout << vm["file"].as<std::string>() << " not accepted!\n";
      }
      fout.close();
    }
    else{
      if (vm.count("help"))
        std::cout << desc << '\n';
      else if (vm.count("age"))
        std::cout << "Age: " << vm["age"].as<int>() << '\n';
      else if (vm.count("pi"))
        std::cout << "Pi: " << vm["pi"].as<float>() << '\n';
    }
  }
  catch (const error &ex)
  {
    std::cerr << ex.what() << '\n';
  }

  std::cout << "\nEnding timer for code\n";
  timer.stop();
  std::cout << timer.format() << "\n";
}