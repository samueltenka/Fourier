#include "Cmplx.h"
#include <math.h>

const float step = 1.0/(1024*1024);
int main(int argc, char** argv) {
   //1. For timing:
   for(float phase=0.0; phase<tau; phase+=step) {
      unit(phase);
      //Cmplx(cos(phase),sin(phase));
   }
}
