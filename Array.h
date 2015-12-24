#ifndef VECTOR_TYPES_H
#define VECTOR_TYPES_H

#include "Cmplx.h"
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

#include "ArrayWavIO.cpp"

#endif//VECTOR_TYPES_H

