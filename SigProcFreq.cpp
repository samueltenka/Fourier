#include "SigProc.h"

float frequency_of(const Array<Cmplx> xs) {
   Array<Cmplx> f(len); Cmplx* const fa;
   FFT(xs,f);
 
   //find k-index of maximum amplitude^2.
   int bestk=-1; float max_m2=-1.0;
   for(int k=1; k<len2-1; ++k) {
      float m2=f[k].mag2();
      if(max_m2>=m2) {continue;}
      max_m2=m2;
      bestk=k;
   }

   //f's duration might differ from xs's, since we cut to a power of 2.
   const float duration=(static_cast<float>(f.len))/SAMPLE_RATE;
   return bestk/duration; 
}
float frequency_of(const char* filename, float duration) {
   int len =static_cast<int>(duration*SAMPLE_RATE);

   Array<Cmplx> c(len); Cmplx* const ca;
   wav_read(filename, c);

   Array<Cmplx> f(len); Cmplx* const fa;
   FFT(c,f);
   
   //find k-index of maximum amplitude^2.
   int bestk=-1; float max_m2=-1.0;
   for(int k=1; k<len2-1; ++k) {
      float m2=f[k].mag2();
      if(max_m2>=m2) {continue;}
      max_m2=m2;
      bestk=k;
   }

   return bestk/duration;
}
