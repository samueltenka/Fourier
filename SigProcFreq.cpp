#include "SigProc.h"
#include "FFT.h"
#include "Cmplx.h"

float frequency_of(const Array<Cmplx> xs) {
   const int len2=inf2(xs.len);
   Array<Cmplx> fourier(inf2(xs.len));
   FFT(xs,fourier);
 
   //find k-index of maximum amplitude^2.
   int bestk=-1; float max_m2=-1.0;
   for(int k=1; k<len2-1; ++k) {
      float m2=fourier.data[k].mag2();
      if(max_m2>=m2) {continue;}
      max_m2=m2;
      bestk=k;
   }

   //f's duration might differ from xs's, since we cut to a power of 2.
   const float duration=(static_cast<float>(fourier.len))/SAMPLE_RATE;
   return bestk/duration; 
}
float frequency_of(const char* filename) {
   Array<short> shorts(filename);
   Array<Cmplx> cmplxs(shorts);

   return frequency_of(cmplxs);
}
