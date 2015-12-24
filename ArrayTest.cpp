#include "Array.h"
#include <iostream>
#include <ctime>
const int HUGE = 1000*1000*1000;

float dur(const clock_t &a, const clock_t &b) {
   return static_cast<float>((unsigned int)(b-a))/(1000*1000);
}

int main(int argc, char** argv) {
   clock_t AAA=clock();
   int*const ar = new int[HUGE];
  clock_t BBB=clock();
   for(int i=0; i<HUGE; ++i) {
      ar[i] = i;
   }
  clock_t CCC=clock();
   std::cout << "completed: filled int[] of len " << HUGE << " in " << dur(AAA,BBB) << " plus " << dur(BBB,CCC) << " seconds\n";
   delete[] ar;

 clock_t AA=clock();
   Array<int> a(HUGE);
   int* const aa = a.data;
  clock_t BB=clock();
   for(int i=0; i<a.len; ++i) {
      aa[i] = i;
   }
  clock_t CC=clock();
   std::cout << "completed: filled Array<int> of len " << a.len << " in " << dur(AA,BB) << " plus " << dur(BB,CC) << " seconds\n";

   return 0;
}
