#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>


#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  float memTotal = 0.0;
  float memFree = 0.0;
  string line;
  string key;
  string value;

  // Parse /proc/meminfo and use sstrem to extract values for keys MemTotal and MemFree
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        // search for key memTotal
        if (key == "MemTotal") {
          memTotal = std::stof(value);
        }
        // search for key memFree
        else if (key == "MemFree") {
          memFree = std::stof(value);
          break;
        }
      }
    }
  }
  // Total used memory = (memTotal - MemFree) / memTotal
  return ((memTotal - memFree) / memTotal);
}

//parse and return uptime using istringstream
long int LinuxParser::UpTime() {
  string line;
  string uptimeString;
  std::ifstream filestream(kProcDirectory + kUptimeFilename); 
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptimeString;
  }
  long uptime = stol(uptimeString);
  return uptime;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          try {
            return std::stol(value);
          } catch (const std::invalid_argument& arg) {
            return 0;
          }
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          try {
            return std::stol(value);
          } catch (const std::invalid_argument& arg) {
            return 0;
          }
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of jiffies for the system
long int LinuxParser::Jiffies() {
  return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
//long int LinuxParser::ActiveJiffies(int pid) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long int LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long int LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuValues{};
  string line;
  string key;
  string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> user >> nice >> system >> idle >>
             iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
        if (key == "cpu") {
          cpuValues.push_back(user);
          cpuValues.push_back(nice);
          cpuValues.push_back(system);
          cpuValues.push_back(idle);
          cpuValues.push_back(iowait);
          cpuValues.push_back(irq);
          cpuValues.push_back(softirq);
          cpuValues.push_back(steal);
          cpuValues.push_back(guest);
          cpuValues.push_back(guest_nice);
          return cpuValues;
        }
      }
    }
  }
  return {};
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string cmd = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, cmd);
    return cmd;
  }
  return cmd;
}


// Read and return the CPU usage of a process
// return the values in seconds
        // CPU time spent in user mode - utime #14
        // CPU time spent in kernel mode - stime #15
        // Waited for children's CPU time spent in user mode #16
        // Waited for children's CPU time spent in kernel mode #17
        // the time when process started  #22
vector<float> LinuxParser::CpuUtilization(int pid) {
  vector<float> cpuValues{};
  string line;
  float time = 0;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for (int i = 1; i <= 22; i++) {
        linestream >> value;
        if (i == 14 || i == 15 || i == 16 || i == 17 ||
            i == 22) {
          time = std::stof(value) / sysconf(_SC_CLK_TCK);
          cpuValues.push_back(time);
        }
      }
    }
  }
  return cpuValues;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string value = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value="";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::replace(line.begin(),line.end(),':',' ');   
      std::istringstream linestream(line);
      while(linestream>>key>>value)
      {
       if(key=="Uid")
       {
         return value;
       }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{ 
  string uid=Uid(pid);
  string line;
  string key;
  string value="";
  string other;
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      while(linestream>>value>>other>>key)
      {
        if(key==uid)
        {
          return value;
        }
    }
  }
}
return value;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) 
{ 
  string line;
  long uptime=0;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      for(int i=1;i<=22;i++)
      {
        linestream>>value;
        if(i==22)
        {
          try
          {
            uptime=std::stol(value)/sysconf(_SC_CLK_TCK);
            return uptime;
          }
          catch (const std::invalid_argument& arg)
          {
            return 0;
          }
        }
      }
    }
  }
  return uptime;          
}
