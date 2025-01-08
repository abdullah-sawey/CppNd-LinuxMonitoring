#include "processor.h"

#include <vector>

#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
	pre_jiff =current_jiff;
	long Prev_Ideal =0, Ideal =0 ,Prev_Nonideal=0, Nonideal=0 ,Prev_Total=0 ,Total =0;
	long Total_res =0 ,Ideal_Res =0;
	float utilization =0.0;
  
	current_jiff = LinuxParser :: CpuUtilization();
	Prev_Ideal = pre_jiff[CPUStates :: kIdle_ ] + pre_jiff[CPUStates :: kIOwait_];
	Ideal = current_jiff[CPUStates :: kIdle_ ] + current_jiff[CPUStates :: kIOwait_];

	Prev_Nonideal = pre_jiff[CPUStates :: kUser_ ] + pre_jiff[CPUStates :: kNice_] + pre_jiff[CPUStates :: kSystem_];
	Prev_Nonideal += (pre_jiff[CPUStates :: kIRQ_ ] + pre_jiff[CPUStates :: kSoftIRQ_] + pre_jiff[CPUStates :: kSteal_]);

	Nonideal = current_jiff[CPUStates :: kUser_ ] + current_jiff[CPUStates :: kNice_] + current_jiff[CPUStates :: kSystem_];
	Nonideal += (current_jiff[CPUStates :: kIRQ_ ] + current_jiff[CPUStates :: kSoftIRQ_] + current_jiff[CPUStates :: kSteal_]);

	Prev_Total = Prev_Ideal + Prev_Nonideal;
	Total = Ideal + Nonideal ;
 
	Total_res = Total - Prev_Total;
	Ideal_Res = Ideal - Prev_Ideal;
  
	utilization =(float)(Total_res - Ideal_Res)/(Total_res) ;

	return utilization;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                