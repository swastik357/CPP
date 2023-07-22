#include <string>
#include "format.h"

using std::string;


//Convert long int measuring seconds into HH:MM:SS format
string Format::ElapsedTime(long seconds) {
  string time = "00:00:00";
  long time_calc = 0;
  
  if (seconds > 0) {
    time_calc = seconds / 3600; //hours
    time = TimeToString(time_calc) + ":";
    time_calc = (seconds / 60) % 60; //minutes
    time += TimeToString(time_calc) + ":";
    time_calc = seconds % 60; //seconds
    time += TimeToString(time_calc);
  }
  return time;
}

//If hours or minutes or seconds in HH:MM:SS are in single digit, append a zero before them
std::string Format::TimeToString(long time) {
  if (time < 10)
    return "0" + std::to_string(time);
  else
    return std::to_string(time);
}