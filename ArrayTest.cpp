#include "Array.h"
#include <iostream>
const int HUGE = 1000*1000*1000;
int main(int argc, char** argv) {
   Array<int> a(HUGE);
   int* const aa = a.data;
   for(int i=0; i<a.len; ++i) {
      aa[i] = i;
   }
   std::cout << "completed: filled Array<int> of len " << a.len << "\n";
   return 0;
}
