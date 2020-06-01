#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

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
  string os,Version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> Version>> kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  float mem_total,mem_free;
  int i=0;
  string value,key,unit,line;
  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key>>value>>unit)
      {
		if(key=="MemTotal")
        {
            mem_total=stof(value);
         	i++;
        }
        else if(key=="MemFree")
        {
        	mem_free=stof(value);
            i++;
        }
        if(i==2)
        {
        	return  (mem_total-mem_free)/mem_total;
            std::istringstream linestream(line);

        }
      }

    }
  }
    return 0;
}

/*float LinuxParser::MemoryUtilization() 
{
  float mem_total,mem_free;
  int i=0;
  string unit,line;
  vector<string> key {};
  vector<string> value {};
  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while(linestream >> key[i]>>value[i]>>unit)
        {
            
            if(i==2)
            {
                mem_total=stof(value[0]);
 				mem_free=stof(value[1]);
              	return  (mem_total-mem_free)/mem_total;
            }
           i++;
         }
     }

   }  
  return  0.0;
}*/

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  string line,str1_uptime,str2_idle ;
  long  uptime_Sec ;
  
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if (stream.is_open()) 
  {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> str1_uptime>>str2_idle;
      uptime_Sec=stol(str1_uptime);
    
  }
  return uptime_Sec; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line,key,kPidDirectory;
  kPidDirectory=to_string(pid);
  vector<string>  values ;
  long utime,stime,cutime,cstime;
  std::ifstream stream(kProcDirectory+kPidDirectory+kStatFilename);
   if (stream.is_open()) 
  {
    std::getline(stream, line);
    std::istringstream linestream(line); 
    
    while(linestream>>key)
    {
    	 values.push_back(key);
    } 
     
  }
  utime=stol(values[13]);
  stime=stol(values[14]);
  cutime=stol(values[15]);
  cstime=stol(values[16]);

  return utime+stime+cutime+cstime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{
    string line,key;
  	vector<string> values;
  	std::ifstream stream(kProcDirectory+kStatFilename);
	if (stream.is_open()) 
  	{
       std::getline(stream, line);
       std::istringstream linestream(line);
       linestream>>key;
       while(linestream>>key)
       {
         values.emplace_back(key);
       }
    }  
  return values; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line,key,value;
  int Tot_Processes;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if (stream.is_open()) 
  {
    
     while(std::getline(stream, line))
     {
        std::istringstream linestream(line);
        while(linestream >> key>>value)
        {
			if(key=="processes")
            {
              Tot_Processes=stoi(value);
              return Tot_Processes;
            }
      
        }
       
     }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
  string line,key,value;
  int Run_Processes;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if (stream.is_open()) 
  {
    
     while(std::getline(stream, line))
     {
        std::istringstream linestream(line);
        while(linestream >> key>>value)
        {
			if(key=="procs_running")
            {
              Run_Processes=stoi(value);
              return Run_Processes;
            }
      
        }
       
     }
  }
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line,kPidDirectory;
  kPidDirectory=to_string(pid);
  std::ifstream stream(kProcDirectory+kPidDirectory+kCmdlineFilename);
  if (stream.is_open()) 
  {
    std::getline(stream, line);
    return line;
  }

  return "";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  long size_MG;
  string line,key,vmSize,unit,kPidDirectory;
  kPidDirectory=to_string(pid);
  std::ifstream stream(kProcDirectory+kPidDirectory+kStatusFilename);

  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
		std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
      	while(linestream>>key>>vmSize>>unit)
        {
          if(key=="VmSize")
          {
            size_MG=(stol(vmSize))/1024;
           	return to_string(size_MG);
          }
        }
    }
  }

  return ""; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) 
{ 
  string line,key,UID,kPidDirectory;
  kPidDirectory=to_string(pid);
  std::ifstream stream(kProcDirectory+kPidDirectory+kStatusFilename);
  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
		std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
      	while(linestream>>key>>UID)
        {
          if(key=="Uid")
          {
           	return UID;
          }
        }


    }
  }

  return ""; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{
  string line ,kPidDirectory,user,value,uid;
  kPidDirectory=to_string(pid);
  uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
	  while(linestream>>user>>value>>value)
      {
        if(value==uid)
          return user;
      }
    }
  }
  return {}; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line,value,kPidDirectory;
  long start_time ,up_time;
  kPidDirectory=to_string(pid);
  std::ifstream stream(kProcDirectory+kPidDirectory+kStatFilename);
  if (stream.is_open()) 
  {
    std::getline(stream, line);
   	std::istringstream linestream(line);
    for( int count=0;count<22;count++){
    	linestream>>value ;
    }
    
    start_time =stol(value)/sysconf(_SC_CLK_TCK);
    up_time=LinuxParser::UpTime() -start_time;
    return up_time;
  }

  return 0; 
}