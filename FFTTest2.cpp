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
  Cmplx c[len];
  for(int j=0; j<len; ++j) {
     //float th=(tau/len)*j * 2;
     c[j] = /*Cmplx(cos(th),sin(th));*/Cmplx(naive_random(),naive_random());
  }

  //1. Analyze white noise
  Cmplx f[len];
  FFT(c,len,f);

  //2. Synthesize white noise
  Cmplx c2[len];
  IFFT(f,len,c2);

  //3. Compare
  for(int j=0; j<len; ++j) {
     print(c2[j]*(1.0/len) - c[j]);
  }

  return 0;
}
