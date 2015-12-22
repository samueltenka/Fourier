#include "WavIO.h"
#include <iostream>
#include "FFT.h"
#include "SigProc.h"

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

float frequency_of(const char* filename, float duration) {
   int len = static_cast<int>(duration*44100);
   Array<Cmplx> c(len); Cmplx* const ca;
   wav_read(filename, c);
   return find_frequency(c);
}

void copy(const char* filename_in, const char* filename_out, float duration) {
   int len =static_cast<int>(duration*44100);
   int len2=1; while(len2<len) {len2*=2;} len2/=2;
   Array<Cmplx> c(len);
   filename_in = wav_read(c);
   for(int i=0; i<100; ++i) {
      print(c[i]);
   }

   Array<Cmplx> f(len2);
   FFT(c,f);
   Array<Cmplx> c2(len2);
   IFFT(f,c2);
   wav_write(filename_out, c2, len2);
}


int main() {
   float f1000 = frequency_of("Audio/sine1000.wav", 3.0);
   float f0440 = frequency_of("Audio/sine0440.wav", 3.0);
   std::cout << "frequency " << f1000 << " Hz\n";
   std::cout << "frequency " << f0440 << " Hz\n";
   copy("Audio/sine1000.wav", "Audio/sine1000.copy.wav", 3.0);
   return 0;
}
