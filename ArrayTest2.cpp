#include "Array.h"
#include "Cmplx.h"
#include <iostream>

template<typename T>
void print(const Array<T> &a) {
   for(int i=0; i<a.len; ++i) {
      std::cout << a.data[i] << " ";
   }
}
template<>
void print(const Array<Cmplx> &a) {
   for(int i=0; i<a.len; ++i) {
      std::cout << "("<<a.data[i].re<< "," <<a.data[i].im<<") ";
   }
}

const int LEN=30;
int main(int argc, char** argv) {
   //TODO: write not a time test, but a 6way type-conversion test and a Array<short> file read-write-read-compare test.
   Array<float> floats(LEN);
   for(int i=0; i<floats.len; ++i) {
      floats.data[i] = i;
   }
   Array<Cmplx> cmplxs(floats);
   Array<short> shorts(cmplxs);
   shorts.write_to("ArrayTest2.wav");
   Array<short> shorts2("ArrayTest2.wav");
   Array<float> floats2(shorts2);
   Array<Cmplx> cmplxs2(floats2);
   print(cmplxs2); 
   return 0;
}
