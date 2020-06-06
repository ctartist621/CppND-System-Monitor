#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
struct Process_Stat {
  long utime;
  long stime;
  long cutime;
  long cstime;
  long starttime;
};

class Process {
 public:
  Process(int pid) : pid_(pid){};
  int Pid();               // DONE: See src/process.cpp
  std::string Command();   // DONE: See src/process.cpp
  float CpuUtilization();  // DONE: See src/process.cpp
  std::string Ram();       // DONE: See src/process.cpp
  std::string User();      // DONE: See src/process.cpp
  bool Running();
  long long unsigned UpTime();  // DONE: See src/process.cpp
  bool operator<(Process& a);   // DONE: See src/process.cpp

  // DONE: Declare any necessary private members
 private:
  int pid_;
  Process_Stat stat_{0, 0, 0, 0, 0};
};

#endif