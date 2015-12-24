#include "SigProc.h"
#include "Array.h"
#include "Cmplx.h"

int main(int argc, char** argv) {
   Array<short> shorts("Audio/oooh0148.wav");
   Array<Cmplx> cmplxs(shorts);

   Array<Cmplx> cmplxs2(cmplxs.len);
   phase_randomize(cmplxs, cmplxs2);

   Array<short> shorts2(cmplxs2);
   shorts2.write_to("Audio/oooh0148.randomized.wav");
   return 0;
}
