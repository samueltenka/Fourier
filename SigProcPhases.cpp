#include "SigProc.h"
#include "rand.h"

void phase_align(const Array<Cmplx> &in, Array<Cmplx> &out) {
   Array<Cmplx> f(len);
   FFT(in,f); Cmplx* const fa=f.a;
   for(int k=0; k<in.len; ++k) {
      fa[k]=Cmplx(fa[k].mag(),0.0);
   }
   IFFT(f,out);
}
void phase_randomize(const Array<Cmplx> &in, Array<Cmplx> &out) {
   Array<Cmplx> f(len);
   FFT(in,f); Cmplx* const fa=f.a;
   for(int k=0; k<in.len; ++k) {
      fa[k] *= unit(randfloat()*tau);
   }
   IFFT(f,out);
}


