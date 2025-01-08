#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
	string line;
	string key;
	string value;
	std::ifstream filestream(kOSPath);
	if (filestream.is_open())
    {
        while (std::getline(filestream, line)) 
        {
            std::replace(line.begin(), line.end(), ' ', '_'); //to integrate key in single string
            std::replace(line.begin(), line.end(), '=', ' '); // to sepreate key away from value
            std::replace(line.begin(), line.end(), '"', ' '); // to remove " " from value
            std::istringstream linestream(line);
            while (linestream >> key >> value) 
            {
                if (key == "PRETTY_NAME")
                {
                    std::replace(value.begin(), value.end(), '_', ' '); // to correct key value
                    return value;
                }
            }
        }
    }
return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
	string os, version, kernel;
	string line;
	std::ifstream stream(kProcDirectory + kVersionFilename);
	if (stream.is_open())
    {
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  string line;
  string key;
  string value;
  float Memu=0;
  long  MemT=0 ,MemF=0 ;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
       while( linestream >> key )
       {
        if (key == "MemTotal:")
        {
          linestream >> value;
          MemT=std::stol(value);
        }
        else if(key == "MemFree:")
        {
          linestream >> value;
          MemF =std::stol(value);
          break;
        }
       }
      }
  }
   Memu = (MemT - MemF) / (float)MemT;
  return  Memu;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
	string UpT;
	long value;
	string line;
	std::ifstream stream(kProcDirectory + kUptimeFilename);
	if (stream.is_open())
	{
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >>UpT ;
		value = std::stol(UpT);
	}
	return value;
}
// TODO: Read and return CPU utilization
std::vector<long> LinuxParser::CpuUtilization() 
{  
  string line;
  string key;
  long value ;
  vector<long>jiff;
  std::ifstream filestream(kProcDirectory + kStatFilename );
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key ) {
        if (key == "cpu")
        {
          for(int i=0 ;i< Max_CpuStates ;i++)
          {
              linestream >> value;
              jiff.push_back(value);
          }
          return jiff;
         }
      }
    }
  }
  return jiff;
}
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  string line;
  string key;
  int value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename );
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{ 
 string line;
  string key;
  int value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename );
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
       std::istringstream linestream(line);
       while (linestream >> key >> value) {
        if (key == "procs_running") 
        {
        	return value;
        }
      }
    }
  }
  return  value;
}


string LinuxParser::Command(int pid) 
{ 
  string path = std :: to_string(pid);
  string line;
  std::ifstream filestream(kProcDirectory + path + kCmdlineFilename );
 if (filestream.is_open())
 {
    std::getline(filestream, line);
  }
  return line;

}

string LinuxParser::Ram(int pid) { 
  string path = std :: to_string(pid); 
  string res ;
  string line;
  string key;
  int value=0;
  std::ifstream filestream(kProcDirectory + path + kStatusFilename );
  if (filestream.is_open()) 
  {
  	while (std::getline(filestream, line))
    {
  		std::istringstream linestream(line);
  		while (linestream >> key >> value) 
        {
            if (key == "VmSize:") 
            {
                res= std :: to_string(value / 1024);
                return res;
            }
  		}
  	}
  
 }
  return res;
}

string LinuxParser::Uid(int pid)
{
  string path = std :: to_string(pid); 
  string res ;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + path + kStatusFilename );
  if (filestream.is_open()) 
  {
  	while (std::getline(filestream, line)) 
  	{
  		std::istringstream linestream(line);
        while (linestream >> key >> value)
        {
        	if (key == "Uid:") 
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
	string UID = LinuxParser::Uid(pid); 
	string line;
	string key;
	string value;
	string der;
	std::ifstream filestream(kPasswordPath);
	if (filestream.is_open()) {
	while (std::getline(filestream, line)) {
	std::replace(line.begin(), line.end(), ':', ' '); //to seprate username away from uid
	std::istringstream linestream(line);
	while (linestream >> key >> der >> value)
    {
		if (value == UID)
		{
			return key;	
		}
	}
}
}
return key;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{

  string path = std :: to_string(pid); 
  long res =0;
  string line;
  string value;
  int goal =21;
  int index =0;
  std::ifstream filestream(kProcDirectory + path + kStatFilename );
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> value) {
        if (index == goal) {
         res = std :: stol(value);
         res/= sysconf(_SC_CLK_TCK);
         return res ;
        }
        else
        {
          index ++;
        }
        
      }
    }
  }
  return res ;
}
std::vector<long> LinuxParser:: Cpu_utilization(int pid)
{
 string path = std :: to_string(pid); 
  std::vector<long> Utilizaion;
  string line;
  string value;
  int goal =13;
  int goalf=16;
  int index =0;
  std::ifstream filestream(kProcDirectory + path + kStatFilename );
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> value) {
        if ((index >= goal)&&(index <= goalf))
        {
         Utilizaion.push_back(std :: stol(value));
        }
        index ++;
      }
    }
  }
    Utilizaion.push_back(LinuxParser::UpTime(pid));
     return Utilizaion;
} 