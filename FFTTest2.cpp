#include "FFT.h"
#include <iostream>
#include <math.h>

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

int naive_random() {
   static int s = 12345;
   static int t = 67890;
   s -= t; t += 1; s ^= t;
   if((t>>6)%2) {s*=3;}
   if((s>>7)%2) {t*=5;}
   return (t>>4)%2 - (s>>5)%2;
}

const int len = 4096;

int main(int argc, char** argv) {
  std::cout.precision(4); std::cout<<std::fixed;
  //0. Generate white noise
  Array<Cmplx> c(len);
  Cmplx* const ca = c.data;
  for(int j=0; j<len; ++j) {
     ca[j] = Cmplx(naive_random(),0); //real-valued white noise
  }

  //1. Analyze white noise
  Array<Cmplx> f(len);
  FFT(c,f);
  for(int i=0; i<f.len/2; ++i) {
     float dph=f.data[f.len-i].phase() + f.data[i].phase();
     if(dph!=0.0) {std::cout << "dph " << dph << "\n";}
  }

  //2. Synthesize white noise
  Array<Cmplx> c2(len);
  IFFT(f,c2);

  //3. Compare
  Cmplx* const c2a = c2.data;
  for(int j=0; j<len; ++j) {
     print(c2a[j]*(1.0/len) - ca[j]);
  }

  return 0;
}
