#include <vector>

/* Conclusion:
 *vector construct/destruct and array allocate/deallocate are comparable.
 *but vector access is ~2wice as slow as array access.
 */

const int HUGE = 1000*1000*1000;

void huge_vector() {
   std::vector<int> v(HUGE);
   for(int i=0; i<HUGE; ++i) {
      v[i]=i;
   }
}
void huge_array() {
   int* a = new int[HUGE];
   for(int i=0; i<HUGE; ++i) {
      a[i]=i;
   }
   delete[] a;
}

int main(int argc, char** argv) {
   huge_array();
   return 0;
}
