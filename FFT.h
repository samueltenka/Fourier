#ifndef FFT_H
#define FFT_H

#include "Cmplx.h"
#include "Array.h"
#include <iostream>

static void FFT_(Cmplx const* const xs, int len, int skip, Cmplx* ys);
static void IFFT_(Cmplx const* const ys, int len, int skip, Cmplx* xs);

int inf2(int i) {
   //returns largest power of 2 not more than i.
   int x=2;
   while(x<=i) {x*=2;}
   return x/2;
}

void FFT(const Array<Cmplx> &xs, Array<Cmplx> &ys) {
   FFT_(xs.data, inf2(xs.len), 1, ys.data);
}
void IFFT(const Array<Cmplx> &ys, Array<Cmplx> &xs) {
   IFFT_(ys.data, inf2(ys.len), 1, xs.data);
   const float norm=1.0/ys.len;//WARNING: assumes ys' length is a power of 2
   Cmplx* const xsa = xs.data;
   for(int i=0; i<xs.len; ++i) {
      xsa[i] = xsa[i]*norm;
   }
}

static void FFT_(Cmplx const* const xs, int len, int skip, Cmplx* ys) {
   int size=len/skip;
   if(size==1) {ys[0]=xs[0]; return;}

   int half=size/2;
   Cmplx* y1s = new Cmplx[half],
        * y2s = new Cmplx[half];
   FFT_(xs, len, skip*2, y1s);
   FFT_(xs+skip, len, skip*2, y2s);

   const Cmplx c = unit(-tau/size);
   Cmplx coef = Cmplx(1.0,0.0);
   for(int k=0; k<size; ++k) {
      ys[k] = y1s[k%half] + coef*y2s[k%half];
      coef = coef*c;
   }
   delete[] y1s; delete[] y2s;
}

// IFFT is just FFT, but complex-conjugated:
static void IFFT_(Cmplx const* const ys, int len, int skip, Cmplx* xs) {
   /*FFT(ys,len,skip,xs);
   for(int j=0; j<len; ++j) {
      xs[j] = ~xs[j];
   }*/
   int size=len/skip;
   if(size==1) {xs[0]=ys[0]; return;}

   int half=size/2;
   Cmplx* x1s = new Cmplx[half],
        * x2s = new Cmplx[half];
   IFFT_(ys, len, skip*2, x1s); //aha! bug was that we accidentally wrote FFT instead of IFFT
   IFFT_(ys+skip, len, skip*2, x2s);
   
   const Cmplx c = unit(tau/size);
   Cmplx coef = Cmplx(1.0,0.0);
   for(int k=0; k<size; ++k) {
      xs[k] = x1s[k%half] + coef*x2s[k%half];
      coef = coef*c;
   }
   delete[] x1s; delete[] x2s;
}

#endif//FFT_H
