#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  unsigned long long int previdle,previowait;
  unsigned long long int prevuser , prevnice;
  unsigned long long int  prevsystem , previrq , prevsoftirq , prevsteal;

};

#endif