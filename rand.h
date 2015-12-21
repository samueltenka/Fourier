#ifndef RAND_H
#define RAND_H

#include <limits>
static const int MAX = std::numeric_limits<int>::max();
static const int MIN = std::numeric_limits<int>::min();
static const float RANGE = static_cast<float>(MAX)-MIN;
static int x=0xAB343F74,
           y=0x072C4307,
           z=0x537928C2,
           t=0x48033E61,
           w=0xF914DA7E;

int randint() {
   x^=y-z+w;
   y^=z-(t>>1);
   z^=t-(x>>2);
   t^=x-(y>>3);
   return x^y^z;
}

float randfloat() {
   return (static_cast<float>(randint())-MIN)/RANGE;
}

#endif//RAND_H
