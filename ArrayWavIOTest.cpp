#include "Array.h"
#include <iostream>
#include "FFT.h"
#include "Cmplx.h"
//#include "SigProc.h"

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

void copy(const char* filename_in, const char* filename_out) {
   Array<short> shorts(filename_in);
   Array<Cmplx> cmplxs(shorts);
   const int len2=inf2(cmplxs.len);

   Array<Cmplx> fourier(len2);
   FFT(cmplxs,fourier);
   Array<Cmplx> cmplxs2(len2);
   IFFT(fourier,cmplxs2);
  
   Array<short> shorts2(cmplxs); 
   shorts2.write_to(filename_out);
}

#include "SigProc.h"

int main() {
   float f1000 = frequency_of("Audio/sine1000.wav");
   float f0440 = frequency_of("Audio/sine0440.wav"); //TODO: write fileexception handling in Array's file io!
   std::cout << "frequency " << f1000 << " Hz\n";    // (we wasted like 15 minutes on a stupid bug in which sine0440 was spelled sine440)!
   std::cout << "frequency " << f0440 << " Hz\n";
   copy("Audio/sine1000.wav", "Audio/sine1000.copy.wav");
   float f1000_= frequency_of("Audio/sine1000.wav");
   std::cout << "frequency " << f1000_ <<" Hz\n";
   return 0;
}
