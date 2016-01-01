#ifndef CEPSTRUM_H
#define CEPSTRUM_H
#include "Array.h"
#include "Cmplx.h"
#include "FFT.h"

typedef const char* filename;

void extract_essence(Array<filename> &ins, filename out) {
   Array<short> first(ins.data[0]); //TODO: sorta wasteful, just to get len...
   Array<Cmplx> avg(inf2(first.len));
   for(int i=0; i<ins.len; ++i) {
      Array<short> next(ins.data[i]);
      Array<Cmplx> summand(inf2(next.len));
      FFT(next,summand);
      for(int j=0; j<avg.len; ++j) {
         summand.data[j] = log(summand.data[j]);
      }
      for(int j=0; j<avg.len; ++j) {
         avg.data[j] = avg.data[j] + summand.data[j];
      }
   }
   for(int j=0; j<avg.len; ++j) {
      avg.data[j] = avg.data[j] * (1.0/ins.len);
   }
   for(int j=0; j<avg.len; ++j) {
      avg.data[j] = exp(avg.data[j]);
   }
   Array<Cmplx> outarray(inf2(avg.len));
   IFFT(avg,outarray);
   Array<short> shorts(outarray);
   shorts.write_to(out);
}

#endif//CEPSTRUM_H
