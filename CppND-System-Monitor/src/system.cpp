#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<Process> presentProcesses{};
  // read process IDs from file system and generate Vector
  vector<int> processIds = LinuxParser::Pids();
  
  for (int p : processIds) {
    Process process{p};
    presentProcesses.push_back(process);
  }

  // sort the processes according to their CPU usage
  sort(presentProcesses.begin(), presentProcesses.end(),mySort);
  // update list of processes
  processes_ = presentProcesses;

  return processes_;
}

bool System::mySort(Process& a, Process& b)
{
  return b.CpuUtilization() < a.CpuUtilization();
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }