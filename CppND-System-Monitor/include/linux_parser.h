#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"}; 

// System
std::string OperatingSystem();
std::string Kernel();
std::vector<int> Pids();
float MemoryUtilization();
long int UpTime();
int TotalProcesses();
int RunningProcesses();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
  
long int Jiffies();
//long int ActiveJiffies(int pid);
long int ActiveJiffies();
long int IdleJiffies();
std::vector<std::string> CpuUtilization();
  
// Processes
std::string Command(int pid);
std::vector<float> CpuUtilization(int pid);//read and return in percent the cpu usage of a process
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif