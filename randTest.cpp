#include "rand.h"
#include <iostream>

const int num_bins=100;
const int num_samples=1000000;
int main(int argc, char** argv) {
   int bins[num_bins];
   for(int i=0; i<num_bins; ++i) {
      bins[i]=0;
   }
   for(int i=0; i<num_samples; ++i) {
      bins[static_cast<int>(randfloat()*num_bins)]+=1;
   }
   for(int i=0; i<num_bins; ++i) {
      std::cout << i << "\t" << static_cast<float>(bins[i] * num_bins)/num_samples << "\n";
   }
}
