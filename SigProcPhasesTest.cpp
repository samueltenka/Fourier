#include "SigProc.h"
#include "Array.h"
#include "Cmplx.h"
#include <iostream>

void try_brownian_constant(const Array<Cmplx> &in, float drift_speed, const char* filename) {
   Array<Cmplx> out(inf2(in.len));
   phase_randomize(in, out, drift_speed);
   Array<short> shorts(out);
   //print_phases(out);
   shorts.write_to(filename);
}

int main(int argc, char** argv) {
   Array<short> shorts("Audio/sine1000.wav");//"Audio/oooh0148.wav");
   Array<Cmplx> cmplxs(shorts);
   //print_phases(cmplxs);

   Array<Cmplx> cmplxs3(cmplxs.len);
   phase_align(cmplxs, cmplxs3);
   Array<short> shorts3(cmplxs3);
   shorts3.write_to("Audio/sine1000.aligned.wav");

   char fnm[] = "Audio/sine1000.randomized.brown00100.wav";
   /*for(float i=10.0; i<100000.0; i*=1.5) {
      int ii=static_cast<int>(i);
      for(int j=5-1; j>=0;--j) {
         fnm[31+j]='0'+(ii%10);
         ii/=10;
      }
      std::cout << "writing " << fnm << " ...\n";
      try_brownian_constant(cmplxs, i, fnm);
   }*/
   try_brownian_constant(cmplxs,100.0,fnm);
   return 0;
}
