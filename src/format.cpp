#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long UpTime)
{
    long hours ;
    long minutes;
    string res="";
    hours = UpTime / 3600;
    UpTime %= 3600; 
    minutes = UpTime / 60;
    UpTime %= 60;
  
    res += to_string(hours);
    res += ":";
    res += to_string(minutes);
    res += ":";
    res += to_string(UpTime);

    // Ensure two digits for each component
    if (hours < 10) {
        res.insert(0, "0"); 
    }
    if (minutes < 10) {
        res.insert(3, "0"); 
    }
    if (UpTime < 10) {
        res.insert(6, "0"); 
    }
  
  return res;

}