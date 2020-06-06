#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid){};
  std::string User();          // DONE: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
};

#endif