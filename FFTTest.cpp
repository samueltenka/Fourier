#include "FFT.h"
#include <iostream>
#include <iomanip>
#include "Array.h"

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

void analyze(const Array<Cmplx> &c) {
   Array<Cmplx> f(inf2(c.len));
   FFT(c,f);
   for(int k=0; k<f.len; ++k) {
      print(f.data[k]);
   }
}

int main(int argc, char** argv) {
  std::cout.precision(3); std::cout<<std::fixed;
  
  //1. Analyze constant signal
  std::cout << "Analyzing constant signal...\n";
  Array<Cmplx> c(8);
  for(int i=0; i<8; ++i) {
     c.data[i] = Cmplx(1.0,0.0);
  }
  analyze(c);
  
  //2. Analyze 1st excited mode
  std::cout << "Analyzing 1st excited mode...\n";
  Array<Cmplx> c2(8);
  Cmplx ph=Cmplx(1.0,0.0);
  for(int i=0; i<8; ++i) {
     c2.data[i]=ph;
     ph = ph*unit(tau/8);
  }
  analyze(c2);

  //2.5. Analyze 1st stationary mode
  std::cout << "Analyzing 1st stationary mode...\n";
  Array<Cmplx> c25(8);
  Cmplx ph1=Cmplx(1.0,0.0),
        ph2=Cmplx(1.0,0.0);
  for(int i=0; i<8; ++i) {
     c25.data[i]=ph1+ph2;
     ph1 = ph1*unit(tau/8);
     ph2 = ph2*unit(-tau/8);
  }
  analyze(c25); 

  std::cout << "Analyzing phase shifted stationary...\n";
  Array<Cmplx> f25(8);
  FFT(c25,f25);
  for(int i=1; i<8/2; ++i) {
     f25.data[i] = f25.data[i] * unit(tau/4);
     f25.data[f25.len-i] = f25.data[f25.len-i] * (~unit(tau/4));
  }
  Array<Cmplx> c275(8);
  IFFT(f25,c275);
  analyze(c275);

  //3. Analyze linear combination
  std::cout << "Analyzing linear combination...\n";
  Array<Cmplx> c3(8);
  for(int j=0; j<8; ++j) {
     c3.data[j]=c.data[j]+c2.data[j];
  }
  analyze(c3);

  //4. Analyze delta function
  std::cout << "Analyzing delta function...\n";
  Array<Cmplx> c4(16);
  for(int j=0; j<16; ++j) {
      c4.data[j]=Cmplx(0.0,0.0);
  } c4.data[0]=Cmplx(1.0,0.0);
  analyze(c4);

  //5. Analyze shifted delta
  std::cout << "Analyzing translated delta function...\n";
  Array<Cmplx> c5(16);
  for(int j=0; j<16; ++j) {
      c5.data[j]=Cmplx(0.0,0.0);
  } c5.data[15]=Cmplx(1.0,0.0);
  analyze(c5);

  return 0;
}
