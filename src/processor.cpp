#include "processor.h"
#include "linux_parser.h"

#include <string>     // std::string, std::stoll
#include <vector>

using std::string ;
using std::vector;
using std::stoll ;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{
  vector<string> values= LinuxParser::CpuUtilization();
  unsigned long long int user, nice, system, idle;
  unsigned long long int ioWait, irq, softIrq, steal, guest, guestnice;
  user=stoll(values[0]);
  nice=stoll(values[1]);
  system=stoll(values[2]);
  idle=stoll(values[3]);
  ioWait=stoll(values[4]);
  irq=stoll(values[5]);
  softIrq=stoll(values[6]);
  steal=stoll(values[7]);
  guest=stoll(values[8]);
  guestnice=stoll(values[9]);
  
  
  unsigned long long int PrevIdle = previdle + previowait;
  unsigned long long int Idle=idle + ioWait;
  unsigned long long int PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
  unsigned long long int NonIdle=user+nice+system+irq+softIrq+steal;
  unsigned long long int PrevTotal=PrevIdle+PrevNonIdle;
  unsigned long long int  Total = Idle + NonIdle;
  
  unsigned long long int totald = Total - PrevTotal;
  unsigned long long int idled = Idle - PrevIdle;
  
  float CPU_Percentage = (totald - idled)/(float)totald ;

  prevuser=user;
  prevnice=nice;
  prevsystem=system;
  previdle=idle;
  previowait=ioWait;
  previrq=irq;
  prevsoftirq=softIrq;
  prevsteal=steal;
  return CPU_Percentage;
}