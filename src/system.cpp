#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


Processor& System::Cpu()
{
  return cpu_;
}

vector<Process>& System::Processes() 
{
	vector<int> l_pids ;
	l_pids = LinuxParser::Pids();
	for(unsigned int i=0; i< (l_pids.size()); i++)
	{
		Process l_process(l_pids[i]);
		processes_.push_back(l_process);
	} 
	std::sort(processes_.begin(), processes_.end());
	std::reverse(processes_.begin(), processes_.end());
	return processes_; 
}


std::string System::Kernel()
 { 
     return LinuxParser::Kernel(); 
 }


float System::MemoryUtilization()
 { 
     return LinuxParser::MemoryUtilization() ; 
 }


std::string System::OperatingSystem()
 { 
     return LinuxParser::OperatingSystem(); 
 }


int System::RunningProcesses() 
{ 
    return LinuxParser::RunningProcesses(); 
}


int System::TotalProcesses() 
{ 
    return LinuxParser::TotalProcesses() ;
}


long int System::UpTime() 
{ 
    return LinuxParser::UpTime(); 
}