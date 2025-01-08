#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "process.h"
#include "linux_parser.h"
#include "format.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() 
{
 	 return this->pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{
	vector<long> CpuUtil(5,0) ;
	long Total_time;
    long Seconds;
	long UP_time ;
    float Util;
    UP_time = LinuxParser::UpTime();
	CpuUtil = LinuxParser:: Cpu_utilization(this->pid_);
    Total_time = CpuUtil[cpu_states ::kUtime_ ] + CpuUtil[cpu_states ::kStime_] ;
    Total_time += (CpuUtil[cpu_states :: kCutime_ ] + CpuUtil[cpu_states :: kCstime_ ]) ;
    Seconds =  UP_time - CpuUtil[cpu_states :: kUptime_] ; 
    Util = ( (float)( Total_time/sysconf(_SC_CLK_TCK) ) / Seconds ) ;               
    CpuUtil_= Util;
    return Util ; 
}

// TODO: Return the command that generated this process
string Process::Command() 
{
  string cmd =LinuxParser::Command(this->pid_);
  return cmd; 
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{
 string ram = LinuxParser::Ram(this->pid_);
  return ram; 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{
  string name = LinuxParser::User(this->pid_);
  return name; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{
  long int UpT = LinuxParser::UpTime(this->pid_); 
  return UpT; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{
 return (  CpuUtil_ < a.CpuUtil_) ;
}