#ifndef PROCESSOR_H
#define PROCESSOR_H

struct Stat {
  int user;
  int nice;
  int system;
  int idle;
  int iowait;
  int irq;
  int softirq;
  int steal;
  int guest;
  int guest_nice;
};

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  struct Stat stat_ {};
  struct Stat stat_prev_ {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };
};

#endif