#include "WavReader.h"
#include <iostream>
#include "FFT.h"

void print(const Cmplx &a) {
   std::cout << a.re << "\t+\t" << a.im << "i\n";
}

float frequency_of(const char* filename, float duration) {
   int len =static_cast<int>(duration*44100);
   int len2=1; while(len2<len) {len2*=2;} len2/=2;
   Cmplx* c = new Cmplx[len];
   wav_read(filename, c);

   Cmplx* f = new Cmplx[len2];
   FFT(c,len2,1,f);
   
   //find kindex of maximum amplitude^2.
   int bestk=-1; float max_m2=-1.0;
   for(int k=1; k<len2-1; ++k) {
      float m2=f[k].mag2();
      if(max_m2>=m2) {continue;}
      max_m2=m2;
      bestk=k;
   }

   delete[] c;
   delete[] f;
   return bestk/duration;
}

/* Reads 
 *
 *
 */
int main() {
   float f1000 = frequency_of("Audio/sine1000.wav", 3.0);
   float f0440 = frequency_of("Audio/sine0440.wav", 3.0);
   std::cout << "frequency " << f1000 << " Hz\n";
   std::cout << "frequency " << f0440 << " Hz\n";
   return 0;
}