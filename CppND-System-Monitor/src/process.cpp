#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : processId_(pid) {
  calculateCpuUtilization();
  setCommand();
  setRam();
  setUptime();
  setUser();
}
// TODO: Return this process's ID
int Process::Pid() { return processId_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// calculate the CPU utilization of this process and save in cpuUsage_
void Process::calculateCpuUtilization() {
  long int uptime = LinuxParser::UpTime();
  vector<float> vec = LinuxParser::CpuUtilization(Pid());
  // only if the values could be read sucessfully
  if (vec.size() == 5) {
    
    float timesum =vec[0] + vec[1] + vec[2] + vec[3];
    float seconds = uptime - vec[4];
    cpuUtilization_ = timesum / seconds;
  } else
    cpuUtilization_ = 0;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a) const { return CpuUtilization() < a.CpuUtilization(); }
bool Process::operator<(Process &a) {
  return CpuUtilization() < a.CpuUtilization();
}

// set user_ to username that generated this process
void Process::setUser() { user_ = LinuxParser::User(Pid()); }
// set command_ to command that generated this process
void Process::setCommand() { command_ = LinuxParser::Command(Pid()); }
// set ram_ to memory utilization of the process
void Process::setRam() {
  // read kB value from file
  string kB = LinuxParser::Ram(Pid());
  // convert into MB
  try {
    long int mB = std::stol(kB) / 1000;
    ram_ = std::to_string(mB);
  } catch (const std::invalid_argument& arg) {
    ram_ = "0";
  }
}
// set uptime_ to age of this process
void Process::setUptime() {
  uptime_ = LinuxParser::UpTime(Pid());
}

