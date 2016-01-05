#include "Array.h"
#include "Cmplx.h"
#include "FFT.h"
#include <math.h>

const long int SAMPLE_RATE = 44100;
void write_ifft(float(*myfunc)(float), float duration, char * const filename) {
   const long int samples = duration*SAMPLE_RATE;
   Array<Cmplx> ifft_me(samples); 
   const float norm = static_cast<float>(inf2(ifft_me.len));
   for(int i=0; i<samples; ++i) {
      float x = static_cast<float>(i)/SAMPLE_RATE;
      ifft_me.data[i] = Cmplx(myfunc(x), 0.0) * norm;
   }
   Array<Cmplx> time_domain(inf2(ifft_me.len));
   IFFT(ifft_me, time_domain);
   Array<short> write_me(time_domain);
   write_me.write_to(filename);
}

float testfunc(float f) {
   return 32000*440.0 / f; //sin(f * 400/sin(f));
}
#include <stdlib.h>
int main(int argc, char** argv) {
   write_ifft(&testfunc, atof(argv[1]), argv[2]);
   return 0;
}
