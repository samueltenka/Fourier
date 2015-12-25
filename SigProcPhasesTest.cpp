#include "SigProc.h"
#include "Array.h"
#include "Cmplx.h"

int main(int argc, char** argv) {
   Array<short> shorts("Audio/oooh0148.wav");
   Array<Cmplx> cmplxs(shorts);
   //print_phases(cmplxs);

   Array<Cmplx> cmplxs2(cmplxs.len);
   phase_randomize(cmplxs, cmplxs2);
   Array<Cmplx> cmplxs3(cmplxs.len);
   phase_align(cmplxs, cmplxs3);

   Array<short> shorts2(cmplxs2);
   shorts2.write_to("Audio/oooh0148.randomized.wav");
   Array<short> shorts3(cmplxs3);
   shorts3.write_to("Audio/oooh0148.aligned.wav");
   return 0;
}
