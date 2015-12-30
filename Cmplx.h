#ifndef CMPLX_H
#define CMPLX_H

#include <math.h>
const float tau=6.283185;


struct Cmplx {
   float re,im;
   Cmplx() {}
   Cmplx(const short re_): re(static_cast<float>(re_)), im(0.0) {}
   operator short () { return static_cast<short>(re); }
   Cmplx(const float re_): re(re_), im(0.0) {}
   operator float() {return static_cast<float>(re); }
   Cmplx(const float re_, const float im_): re(re_), im(im_) {}
   Cmplx(const Cmplx &other):re(other.re), im(other.im) {}
   Cmplx operator=(const Cmplx &rhs) {
      re=rhs.re; im=rhs.im;
      return *this;
   }

   Cmplx operator+(const Cmplx &rhs) const { return Cmplx(re+rhs.re, im+rhs.im); }
   Cmplx operator-(const Cmplx &rhs) const { return Cmplx(re-rhs.re, im-rhs.im); }
   Cmplx operator*(const Cmplx &rhs) const { return Cmplx(re*rhs.re - im*rhs.im,
                                                          im*rhs.re + re*rhs.im);}
   Cmplx operator*(const float &rhs) const { return Cmplx(re*rhs, im*rhs); }
   Cmplx operator~() const { return Cmplx(re, -im); } //complex conjugation
   float mag2() const { return re*re+im*im; }
   float mag() const {return sqrt(mag2());}
   float phase() const {
      if(im>0) {return tau/4+atan(-re/im);}
      else if(im<0) {return -tau/4+atan(re/-im);}
      else {return re>0 ? 0.0 : -tau/2;}
   }
};



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
   return polygon * static_cast<float>(1.0/m);
}


#endif//CMPLX_H
