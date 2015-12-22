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
   //Array<Cmplx>(const char* filename);
   Array<Cmplx>(const Array<float> &other);
   Array<Cmplx>(const Array<short> &other);
   //void write_to(const char* filename);
}
struct Array<float> {
   Array<float>(const Array<short> &other);
   Array<float>(const Array<Cmplx> &other);
}
struct Array<short> {
   Array<short>(const char* filename);
   Array<short>(const Array<Cmplx> &other);
   Array<short>(const Array<float> &other);
   void write_to(const char* filename);
}

#endif//VECTOR_TYPES_H

