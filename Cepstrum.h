#ifndef CEPSTRUM_H
#define CEPSTRUM_H
#include "Array.h"
#include "Cmplx.h"

typedef const char* filename;

void extract_essence(Array<filename> &ins, filename out) {
   Array<short> first(ins.data[0]); //TODO: sorta wasteful, just to get len...
   Array<Cmplx> avg(first.len);
   for(int i=0; i<ins.len; ++i) {
      Array<short> next(ins.data[i]);
      Array<Cmplx> summand(next);
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
   Array<short> outarray(avg);
   outarray.write_to(out);
}

#endif//CEPSTRUM_H
