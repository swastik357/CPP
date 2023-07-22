#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();
  Processor();

 private:
  float pTotalCpuTime;// previous total cpu time since boot
  float pIdleCpuTime;// previous idle time since boot 
  vector<long> ToLong(vector<string> sVector);// convert the given string vector into a long vector
};

#endif