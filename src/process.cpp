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

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  vector<string> stats = LinuxParser::Process::CpuUtilization(pid_);
  if (stats.size() == 5) {
    this->stat_.utime = std::stol(stats[0]);
    this->stat_.stime = std::stol(stats[1]);
    this->stat_.cutime = std::stol(stats[2]);
    this->stat_.cstime = std::stol(stats[3]);
    this->stat_.starttime = std::stol(stats[4]);

    long total_time = this->stat_.utime + this->stat_.stime +
                      this->stat_.cutime + this->stat_.cstime;
    long Hertz = sysconf(_SC_CLK_TCK);
    float seconds =
        LinuxParser::Process::UpTime(pid_) - (this->stat_.starttime / Hertz);

    return (total_time / Hertz) / seconds;
  } else {
    return 0;
  }
}

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Process::Command(pid_); }

// DONE: Return this process's memory utilization
string Process::Ram() {
  std::string vsize = LinuxParser::Process::Ram(pid_);
  double r = std::stoll(vsize) / (double)1000;

  std::ostringstream out;
  out.precision(2);
  out << std::fixed << r;
  return out.str();
}

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::Process::User(pid_); }

// DONE: Return the age of this process (in seconds)
long long unsigned int Process::UpTime() {
  long Hertz = sysconf(_SC_CLK_TCK);
  long long unsigned ut = LinuxParser::Process::UpTime(pid_);
  return ut / Hertz;
}

// Check to see if a process is running
bool Process::Running() {
  string state = LinuxParser::Process::State(pid_);
  return state == "R";
};

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process& a) {
  float aC = a.CpuUtilization();
  float bC = this->CpuUtilization();
  return aC < bC;
}