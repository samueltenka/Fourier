#ifndef WAV_READER_H
#define WAV_READER_H

#include <stdio.h>
#include <iostream>
#include "Cmplx.h"

Array<Cmplx>* wav_read(const char* filename) {
   FILE* file = fopen(filename, "rb");
   fseek(file, 40, SEEK_SET);
   int s1,s2;
   fread(&s1, 2, 1, file);
   fread(&s2, 2, 1, file);
   const int size=s2*256*256 + s1;
   const int len=size/2;

   std::cout << "reading " << len << " amplitudes\n";
   Array<Cmplx>* amplitudes = new Array<Cmplx>(len);
   short a; Cmplx* const aa = amplitudes->a;
   for(int i=0; i<size/2; ++i) {
      fread(&a, 2, 1, file);
      aa[i] = Cmplx(a,0.0); //unsigned 16-bit short interpreted literally
   }
   fclose(file);
   return amplitudes;
}

inline void write_bigendian(const int x, FILE* file) {
   int s1=x>>(8+8+8),
       s2=(x>>(8+8))%256,
       s3=(x>>8)%256,
       s4=x%256;
   fwrite(&s1,1,1,file);
   fwrite(&s2,1,1,file);
   fwrite(&s3,1,1,file);
   fwrite(&s4,1,1,file);
}
inline int to_littleendian(int x) {
   int s1=x>>(8+8+8),
       s2=(x>>(8+8))%256,
       s3=(x>>8)%256,
       s4=x%256;
   return (s1<<(8+8+8)) + (s2<<(8+8)) + (s3<<8) + s4;
}
void wav_write(const char* filename, const Array<Cmplx> amplitudes) {
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

   std::cout << "writing " << len << " amplitudes\n";
   short* as = new short[size]; Cmplx* const aa=amplitudes.a;
   for(int i=0; i<amplitudes.len; ++i) {
      as[i] = static_cast<short>(aa[i].re);
      fwrite(&as[i], 2, 1, file);
   }
   //fwrite(as, 2, size/2, file);
   delete[] as;
   fclose(file);
}

#endif//WAV_READER_H
