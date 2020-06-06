#include "format.h"

#include <string>

#include "math.h"

using std::floor;
using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  seconds = floor(seconds);
  int minutes = seconds / 60;
  int hours = minutes / 60;
  // hours %= 24;
  minutes %= 60;
  seconds %= 60;
  return (hours < 10 ? "0" : "") + std::to_string(hours) + ":" +
         (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
         (seconds < 10 ? "0" : "") + std::to_string(seconds);
}