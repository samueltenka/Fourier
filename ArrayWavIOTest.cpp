#include "Array.h"
#include <iostream>
#include "FFT.h"
#include "Cmplx.h"
//#include "SigProc.h"

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

void copy(const char* filename_in, const char* filename_out) {
   std::cout << "!"; std::cout.flush();
   Array<short> shorts(filename_in);
   std::cout << "!@"; std::cout.flush();
   Array<Cmplx> cmplxs(shorts);
   std::cout << "!*"; std::cout.flush();
   const int len2=inf2(cmplxs.len);
   std::cout << "!#"<<cmplxs.data[0].re; std::cout.flush();

   Array<Cmplx> fourier(len2);
   std::cout << "!&"<<fourier.len; std::cout.flush();
   FFT(cmplxs,fourier);
   std::cout << "!$"<<fourier.data[0].re; std::cout.flush();
   Array<Cmplx> cmplxs2(len2);
   std::cout << "!~"; std::cout.flush();
   IFFT(fourier,cmplxs2);
  
   std::cout << "!%"; std::cout.flush();
   Array<float> floats(cmplxs2);
   Array<short> shorts2(floats); 
   shorts2.write_to(filename_out);
}


int main() {
   //float f1000 = frequency_of("Audio/sine1000.wav");
   //float f0440 = frequency_of("Audio/sine0440.wav");
   //std::cout << "frequency " << f1000 << " Hz\n";
   //std::cout << "frequency " << f0440 << " Hz\n";
   copy("Audio/sine0440.wav", "Audio/sine0440.copy.wav");
   return 0;
}
