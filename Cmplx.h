#ifndef CMPLX_H
#define CMPLX_H

struct Cmplx {
   float re,im;
   Cmplx() {}
   Cmplx(const float re_, const float im_):
      re(re_), im(im_) {}
   Cmplx(const Cmplx &other):
      re(other.re), im(other.im) {}
   Cmplx operator=(const Cmplx &rhs) {
      re=rhs.re; im=rhs.im;
      return *this;
   }
   Cmplx operator+(const Cmplx &rhs) const {
      return Cmplx(re+rhs.re, im+rhs.im);
   }
   Cmplx operator-(const Cmplx &rhs) const {
      return Cmplx(re-rhs.re, im-rhs.im);
   }
   Cmplx operator*(const Cmplx &rhs) const {
      return Cmplx(re*rhs.re - im*rhs.im,
                   im*rhs.re + re*rhs.im);
   }
   Cmplx operator*(const float &rhs) const {
      return Cmplx(re*rhs, im*rhs);
   }
   Cmplx operator~() const { //complex conjugation
      return Cmplx(re, -im);
   }
   float mag2() {
      return re*re+im*im;
   }
};



const float tau=6.283185;
#include "expi_table.h"
inline Cmplx unit(float phase) {
   //returns exp(i*phase) for 0<=phase<tau
   if(phase<0) {return ~unit(-phase);} //negatives round toward 0 (wrong way!)
   float stretch = expi::size*phase/tau;
   int bucket = static_cast<int>(expi::size * phase/tau);
   Cmplx c1=expi::table[bucket % expi::size],
         c2=expi::table[(bucket+1)%expi::size];
   float extra = stretch-bucket;
   Cmplx polygon = c1*(1-extra) + c2*extra;
   float m = (1.0+polygon.mag2())/2; //approximates magnitude
   return polygon * (1.0/m);
}


#endif//CMPLX_H
