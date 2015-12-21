#include "SigProc.h"
#include "rand.h"

void phase_align(const float* in, int len, float* out) {
   Cmplx* f = new Cmplx[len];
   FFT(in,len,f);
   for(int k=0; k<len; ++k) {
      f[k]=Cmplx(f[k].mag(),0.0);
   }
   IFFT(f,len,out);
   delete[] f;
}
void phase_randomize(const float* in, int len float out) {
   Cmplx* f = new Cmplx[len];
   FFT(in,len,f);
   for(int k=0; k<len; ++k) {
      f[k] *= unit(randfloat()*tau);
   }
   IFFT(f,len,out);
   delete[] f;
}


