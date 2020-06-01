#include "format.h"
#include <string>

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  string  format,hrs ,mins,secs;
  long hours=seconds/3600 ;
  long seconds_remaining=seconds%3600;
  long minutes =seconds_remaining/60;
  seconds_remaining=seconds_remaining%60;
  
  hrs=to_string(hours);
  if(hours<10)
  {

       hrs="0"+hrs;
  
  }
  mins=to_string(minutes);
  if(minutes<10)
  {
    mins="0"+mins;
  }
  secs=to_string(seconds_remaining);
  if(seconds_remaining<10)
  {
    secs="0"+secs;
  }
  
  format = hrs+":"+mins+":"+secs;
  return format;
}