#ifndef WAV_READER_H
#define WAV_READER_H

#include <stdio.h>
#include <iostream>
#include "Cmplx.h"

void wav_read(const char* filename, Cmplx* amplitudes) {
   FILE* file = fopen(filename, "rb");
   fseek(file, 40, SEEK_SET);
   int s1,s2;
   fread(&s1, 2, 1, file);
   fread(&s2, 2, 1, file);
   const int size=s2*256*256 + s1;
   std::cout << "reading " << size/2 << " amplitudes\n";
   int a, b;
   for(int i=0; i<size/2; ++i) {
      fread(&a, 2, 1, file);
      //fread(&b, 1, 1, file);
      amplitudes[i] = Cmplx(a-256*128,0.0);
   }
   fclose(file);
}
void wav_write(const char* filename, const float* amplitudes) {
   //FILL IN!
}

#endif//WAV_READER_H
