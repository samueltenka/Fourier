#ifndef VECTOR_TYPES_H
#define VECTOR_TYPES_H

//#include "Cmplx.h"

template<typename T>
struct Array {
   T* const a;
   const unsigned int len;

   Array(unsigned int l): len(l), a(nullptr) {
      //following line gets around the constness of a
      //TODO: Question: is there a nicer way to do this?
      *(const_cast<T**>(&a)) = new T[len];
   }
   Array(const Array &other) {
      len=other.len;
      a = new T[len];
      for(int i=0; i<len; ++i) {
         a[i] = other.a[i];
      }
   }
   ~Array() {
      delete[] a;
   }
};

// Implemented in ArrayWavIO.h
struct Array<Cmplx> {
   Array<Cmplx>(const char* filename);
   void write_to(const char* filename);
}

#endif//VECTOR_TYPES_H

