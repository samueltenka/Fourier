#include "Cmplx.h"
#include <iostream>

void print(const Cmplx &a) {
   std::cout << a.re << "+" << a.im << "i\n";
}

int main(int argc, char** argv) {
   Cmplx a(0.7071067, 0.7071067);
   Cmplx b(0, 2.0);

   //1. Test print functions
   std::cout << "Test print functions..." << "\n";
   print(a);   //0.707107+0.707107i
   print(b);   //0+2i

   //2. Test basic arithmetic
   std::cout << "Test basic arithmetic..." << "\n";
   print(a*a); //0+1i
   print(a*b); //-1.41421+1.41421i
   print(a+b); //0.707107+2.707107i
   print(~a);  //0.707107+-0.707107i
   std::cout << (a+a).mag2() << "\n";
   std::cout << (a+a).mag() << "\n";

   //3. Precision test using distributive law
   std::cout << "Precision Test using distributive law..." << "\n";
   Cmplx conjunctive((~a+a)*(b-~b));
   Cmplx disjunctive(~a*b + a*b - ~a*~b - a*~b);
   print(conjunctive); //0+5.65685i 
   print(disjunctive); //0+5.65685i
   print(conjunctive-disjunctive);//0+0i

   //4. Test phase-factor computations 
   std::cout << "Test phase factor computations..." << "\n";
   print(unit(0.0));   //1+0i
   print(unit(-tau/4));//6.12323e-17+-1i
   print(unit(-tau));  //1+-0i
   print(unit(2*tau)); //1+0i
   print(unit(tau));   //1+0i
   print(unit(tau/2)); //-1+1.22465e-16i
   print(unit(tau/3)); //-0.5+0.866026i
   print(unit(tau/4)); //6.1232e-17+1i
   print(unit(tau/5)); //0.309017+0.951056i
   print(unit(tau/6)); //0.5+0.866025i
   print(unit(tau/8)); //0.707107+0.707107i
   return 0;
}
