#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>
class Processor {
 public:
  float Utilization(); 
  Processor() :pre_jiff(10, 0), current_jiff(10, 0) {}  
 private:
  std :: vector<long> pre_jiff;
  std :: vector<long> current_jiff;
};

#endif