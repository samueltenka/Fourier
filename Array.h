#ifndef ARRAY_H
#define ARRAY_H

#include "stdio.h"

template<typename T>
struct Array {
   //order matters, e.g. see Array<short>(FILE*) constructor.
   const unsigned int len;
   T* const data;

   Array(unsigned int l): len(l), data(new T[len]) {}
   template<typename S>
   Array(const Array<S> &other): len(other.len), data(new T[len]) {
      for(int i=0; i<len; ++i) { data[i] = other.data[i]; }
   }
   ~Array() { delete[] data; }

   Array(FILE* file);
   Array(const char* filename);
   void write_to(const char* filename);
};

// Implemented in ArrayWavIO.h
/*template <>
Array<short>::Array(FILE* file);
template <>
Array<short>::Array(const char* filename);
template <>
void Array<short>::write_to(const char* filename);*/

#include <stdio.h>
#include <iostream>

/* Thanks to soundfile.sapp.org/doc/WaveFormat/ */

static int get_len(FILE* file) {
   fseek(file, 40, SEEK_SET);
   int s[2];  fread(s, 2, 2, file);
   return ((s[1]<<(8+8)) + s[0])/2;
}
template<>
Array<short>::Array(FILE* file): len(get_len(file)), data(new short[len]) {
   std::cout << "reading " << len << " amplitudes\n";
   fread(data, 2, len, file);
}

static FILE* file;
template<>
Array<short>::Array(const char* filename): Array(file=fopen(filename,"rb")) {
   fclose(file);
}




static void write_header(FILE* file, unsigned int len);

template<>
void Array<short>::write_to(const char* filename) {
   FILE* file = fopen(filename, "wb");
   write_header(file, len);
   std::cout << "writing " << len << " amplitudes\n";
   fwrite(data, 2, len, file);
   fclose(file);
}



inline void write_bigendian(const int x, FILE* file) {
   int s[4] = { x>>(8+8+8),
               (x>>(8+8))%256,
               (x>>8)%256,
                x%256         };
   fwrite(s,1,4,file); //TODO: does this do what we want?
}

static void write_header(FILE* file, unsigned int len) {
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

   
   write_bigendian(ChunkID, file);
   fwrite(&ChunkSize,4,1,file);
   write_bigendian(Format, file);

   write_bigendian(Subchunk1ID, file);
   fwrite(&Subchunk1Size,4,1,file);
   fwrite(&AudioFormat,2,1,file);
   fwrite(&NumChannels,2,1,file);
   fwrite(&SampleRate,4,1,file);
   fwrite(&ByteRate,4,1,file);
   fwrite(&BlockAlign,2,1,file);
   fwrite(&BitsPerSample,2,1,file);

   write_bigendian(Subchunk2ID, file);
   fwrite(&Subchunk2Size,4,1,file);
}

#endif//ARRAY_H

