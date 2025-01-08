#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process (int p) : pid_(p){}
  int Pid();                               
  void Pid(int pid);
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const ;   
  
 private:
  int pid_= 0;
  float CpuUtil_=0.0;
};
#endif