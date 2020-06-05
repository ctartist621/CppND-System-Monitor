#include "../include/processor.h"

#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::vector;

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<string> stats = LinuxParser::CpuUtilization();
  this->stat_.user = std::stoi(stats[0]);
  this->stat_.nice = std::stoi(stats[1]);
  this->stat_.system = std::stoi(stats[2]);
  this->stat_.idle = std::stoi(stats[3]);
  this->stat_.iowait = std::stoi(stats[4]);
  this->stat_.irq = std::stoi(stats[5]);
  this->stat_.softirq = std::stoi(stats[6]);
  this->stat_.steal = std::stoi(stats[7]);
  this->stat_.guest = std::stoi(stats[8]);
  this->stat_.guest_nice = std::stoi(stats[9]);

  int prev_idle = this->stat_prev_.idle + this->stat_prev_.iowait;
  int idle = this->stat_.idle + this->stat_.iowait;

  int prev_non_idle = this->stat_prev_.user + this->stat_prev_.nice +
                      this->stat_prev_.system + this->stat_prev_.softirq +
                      this->stat_prev_.steal;
  int non_idle = this->stat_.user + this->stat_.nice + this->stat_.system +
                 this->stat_.softirq + this->stat_.steal;

  int prev_total = prev_idle + prev_non_idle;
  int total = idle + non_idle;

  // differentiate: actual value minus the previous one
  int totald = total - prev_total;
  int idled = idle - prev_idle;

  this->stat_ = this->stat_prev_;
  return (totald - idled) / (float)totald;
};