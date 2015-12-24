#ifndef SIGPROC_H
#define SIGPROC_H
//Fourier-based Tricks! :)

//#include <vector>
#include "Array.h"
#include "Cmplx.h"

const int SAMPLE_RATE=44100;

float frequency_of(const Array<Cmplx> xs);
float frequency_of(const char* filename);
//void phase_align(const float* in, int len, float* out);
//void phase_randomize(const float* in, int len, float out);

//void to_frequency(const float* in, Cmplx* out);
//void convolve(const std::vector<const float*> ins, int len, float* out); //faster: multiplication in fourier space, no need to take logs.
//void to_quenvolvency(const float* in, float* out);
//void convolve(const std::vector<std::pair<const float*, float> > ins, int len, float* out);
//void to_quefrency(const float* in, float* out);

#endif//SIGPROC_H
