#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : pTotalCpuTime(0.0), pIdleCpuTime(0.0){};

// Return the aggregate CPU utilization
float Processor::Utilization() {
  // current cpu values 
  vector<long> cpuValues = ToLong(LinuxParser::CpuUtilization());
  // total cpu time since boot 
  float totalCpuTime = cpuValues[LinuxParser::kUser_]+cpuValues[LinuxParser::kNice_]+cpuValues[LinuxParser::kSystem_]+                              cpuValues[LinuxParser::kIdle_]+cpuValues[LinuxParser::kIOwait_]+cpuValues[LinuxParser::kIRQ_]+
                       cpuValues[LinuxParser::kSoftIRQ_]+cpuValues[LinuxParser::kSteal_];
  // idle time since boot 
  float idleCpuTime =cpuValues[LinuxParser::kIdle_]+cpuValues[LinuxParser::kIOwait_];
  // cpu usage since last update
  float dIdle = idleCpuTime - pIdleCpuTime;
  float dTotal = totalCpuTime - pTotalCpuTime;
  float dUsage = (dTotal - dIdle) / dTotal;
  // remember the total and idle times for next check
  pIdleCpuTime = idleCpuTime;
  pTotalCpuTime = totalCpuTime;
  return dUsage;
}

// convert the given string vector into a long vector
vector<long> Processor::ToLong(vector<string> sVector) { 
  vector<long> lVector{};
  for (int i = 0; i < (int)sVector.size(); i++) {
    try {
      lVector.push_back(std::stol(sVector[i]));
    } catch (const std::invalid_argument& arg) {
      lVector.push_back((long)0);
    }
  }
  return lVector;
}