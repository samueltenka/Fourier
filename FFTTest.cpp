#include "FFT.h"
#include <iostream>
#include <iomanip>

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

void analyze(Cmplx* c, int len) {
   Cmplx* f = new Cmplx[len];
   FFT(c,len,f);
   for(int k=0; k<len; ++k) {
      print(f[k]);
   }
   delete[] f;
}

int main(int argc, char** argv) {
  std::cout.precision(3); std::cout<<std::fixed;
  
  //1. Analyze constant signal
  std::cout << "Analyzing constant signal...\n";
  Cmplx c[8] = {Cmplx(1.0,0.0),
                Cmplx(1.0,0.0),
                Cmplx(1.0,0.0),
                Cmplx(1.0,0.0),
                Cmplx(1.0,0.0),
                Cmplx(1.0,0.0),
                Cmplx(1.0,0.0),
                Cmplx(1.0,0.0)};
  analyze(c, 8);
  
  //2. Analyze 1st excited mode
  std::cout << "Analyzing 1st excited mode...\n";
  const float sqrt2=0.7071069;
  Cmplx c2[8] = {Cmplx(1.0,0.0),
                Cmplx(sqrt2,sqrt2),
                Cmplx(0.0,1.0),
                Cmplx(-sqrt2,sqrt2),
                Cmplx(-1.0,0.0),
                Cmplx(-sqrt2,-sqrt2),
                Cmplx(0.0,-1.0),
                Cmplx(sqrt2,-sqrt2)};
  analyze(c2, 8);

  //3. Analyze linear combination
  std::cout << "Analyzing linear combination...\n";
  Cmplx c3[8];
  for(int j=0; j<8; ++j) {
     c3[j]=c[j]+c2[j];
  }
  analyze(c3, 8);

  //4. Analyze delta function
  std::cout << "Analyzing delta function...\n";
  Cmplx c4[16];
  for(int j=0; j<16; ++j) {
      c4[j]=Cmplx(0.0,0.0);
  } c4[0]=Cmplx(1.0,0.0);
  analyze(c4, 16);

  //5. Analyze shifted delta
  std::cout << "Analyzing delta function...\n";
  Cmplx c5[16];
  for(int j=0; j<16; ++j) {
      c5[j]=Cmplx(0.0,0.0);
  } c5[15]=Cmplx(1.0,0.0);
  analyze(c5, 16);

  return 0;
}
