#include "process.h"

#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  vector<string> stats = LinuxParser::Process::CpuUtilization(pid_);
  if (stats.size() == 5) {
    this->stat_.utime = std::stol(stats[0]);
    this->stat_.stime = std::stol(stats[1]);
    this->stat_.cutime = std::stol(stats[2]);
    this->stat_.cstime = std::stol(stats[3]);
    this->stat_.starttime = std::stol(stats[4]);

    int total_time = this->stat_.utime + this->stat_.stime +
                     this->stat_.cutime + this->stat_.cstime;
    int Hertz = sysconf(_SC_CLK_TCK);
    float seconds = LinuxParser::UpTime() - (this->stat_.starttime / Hertz);

    return std::max((float)0, 100 * (total_time / Hertz) / seconds);
  } else {
    return 0;
  }
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// DONE: Return this process's memory utilization
string Process::Ram() {
  std::string vsize = LinuxParser::Process::Ram(pid_);
  return std::to_string(std::stol(vsize) / (long)1024);
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::Process::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process& a) {
  float aC = a.CpuUtilization();
  float bC = this->CpuUtilization();
  return aC < bC;
}