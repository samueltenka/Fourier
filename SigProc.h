#ifndef SIGPROC_H
#define SIGPROC_H
//Fourier-based Tricks! :)

//#include <vector>
#include "Array.h"
#include "Cmplx.h"
#include "rand.h"
#include "FFT.h"
#include <iostream>

const int SAMPLE_RATE=44100;

float frequency_of(const Array<Cmplx> &xs);
float frequency_of(const char* filename);
void phase_align(const Array<Cmplx> &in, Array<Cmplx> &out) {
   Array<Cmplx> f(in.len);
   FFT(in,f); Cmplx* const fa=f.data;
   for(int k=0; k<in.len; ++k) {
      fa[k]=Cmplx(fa[k].mag(),0.0);
   }
   IFFT(f,out);
}
void phase_randomize(const Array<Cmplx> &in, Array<Cmplx> &out) {
   Array<Cmplx> f(in.len);
   FFT(in,f); Cmplx* const fa=f.data;
   float factor=0.0;
   for(int k=0; k<in.len/2; ++k) {
      factor += randfloat()*tau/10.0;
      Cmplx phase=unit(factor);
      fa[k] = fa[k] * phase;
      fa[in.len-1-k] = fa[in.len-1-k] * (~phase);
   }
   IFFT(f,out);
}
void print_phases(const Array<Cmplx> &in) {
   Array<Cmplx> f(in.len);
   FFT(in,f); Cmplx* const fa=f.data;
   for(int k=0; k<in.len; ++k) {
      std::cout << k << ", " << fa[k].im/fa[k].re << "\n";
   }
}

//void to_frequency(const float* in, Cmplx* out);
//void convolve(const std::vector<const float*> ins, int len, float* out); //faster: multiplication in fourier space, no need to take logs.
//void to_quenvolvency(const float* in, float* out);
//void convolve(const std::vector<std::pair<const float*, float> > ins, int len, float* out);
//void to_quefrency(const float* in, float* out);

/*TODO: QUESTION:
 * why doesn't this work 
 * when the following is in a .cpp?
 */
float frequency_of(const Array<Cmplx> &xs) {
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

#endif//SIGPROC_H
