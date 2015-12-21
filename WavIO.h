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
   int a;
   for(int i=0; i<size/2; ++i) {
      fread(&a, 2, 1, file);
      amplitudes[i] = Cmplx(a-256*128,0.0);
   }
   fclose(file);
}
void wav_write(const char* filename, const Cmplx* amplitudes, const int len) {
   const int bytes_per_sample=2;
   const int size=len*bytes_per_sample;
   const int ChunkID=0x52494646, //RIFF
             ChunkSize=36+size,
             Format=0x57415645; //WAVE
   const int Subchunk1ID=0x666d7420, //fmt 
             Subchunk1Size=16,
             AudioFormat=1,
             NumChannels=1,
             SampleRate=44100,
             ByteRate=SampleRate*NumChannels*bytes_per_sample,
             BlockAlign=NumChannels*bytes_per_sample,
             BitsPerSample=bytes_per_sample*8;
   const int Subchunk2ID=0x64617461, //data
             Subchunk2Size=size;


   FILE* file = fopen(filename, "wb");
   fwrite(&ChunkID,4,1,file);
   fwrite(&ChunkSize,4,1,file);
   fwrite(&Format,4,1,file);

   fwrite(&Subchunk1ID,4,1,file);
   fwrite(&Subchunk1Size,4,1,file);
   fwrite(&AudioFormat,2,1,file);
   fwrite(&NumChannels,2,1,file);
   fwrite(&SampleRate,4,1,file);
   fwrite(&ByteRate,4,1,file);
   fwrite(&BlockAlign,2,1,file);
   fwrite(&BitsPerSample,2,1,file);

   fwrite(&Subchunk2ID,4,1,file);
   fwrite(&Subchunk2Size,4,1,file);

   std::cout << "writing " << len << " amplitudes\n";
   int* as = new int[size];
   for(int i=0; i<size/2; ++i) {
      as[i] = static_cast<int>(amplitudes[i].re);
   }
   fwrite(as, 2, size/2, file);
   delete[] as;
   fclose(file);
}

#endif//WAV_READER_H
