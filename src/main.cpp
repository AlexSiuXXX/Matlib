#include "Mat.h"
#include "Vec.h"
#include "Ft.h"

#include <chrono>

using namespace std::chrono;


void MatTest() {
  
   Matrix<double> m(8, 8);
   m.Random();
   m.PrintMat();

   Matrix<double> m2(8, 8);
   m2.Random();
   m2.PrintMat();

   auto start = high_resolution_clock::now();
   std::cout << "\n==============================================\n\n";
      
   Matrix<double> resm = m * m2;
   resm.PrintMat();

   Matrix<double> resa = m + m2;
   resa.PrintMat();

   Matrix<double> ress = m - m2;
   ress.PrintMat();

   std::cout << "Sum: " << ress.sum() << "\n";
   std::cout << "Max: " << ress.maxx() << "\n";
   std::cout << "Min: " << ress.minn() << "\n";
   std::cout << "trace: " << ress.trace() << "\n";
   std::cout << "Mean: " << ress.mean() << "\n";

   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
 
   std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

   Matrix<double> w(3, 3);
   w.Random();
   w.PrintMat();

   Vector<double> vw(3);
   vw.RandomV();
   vw.PrintVec();

   Matrix<double> wrs = w.mul_MatVec(vw);
   std::cout << "==================================\n\n\n";
   wrs.PrintMat(); 

}
 
void VecTest() {
   auto start = high_resolution_clock::now();
   Vector<double> v(164000);
   v.RandomV();

   Vector<double> w(164000);
   w.RandomV();

   Vector<double> resv = v * w;
   // resv.PrintVec();

   Vector<double> resva = v + w;
   // resva.PrintVec();

   Vector<double> resvs = v - w;
   // resvs.PrintVec();
   double d = v.dot(w);
   std::cout << d << "\n"; 


   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
 
   std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}



int main() {
  
   DiscreteFourierTransform<double> dft(13);
  
   std::pair<Vector<double>, Vector<double>> pft = dft.compute_dft1d(13);
   pft.first.PrintVec();
   pft.second.PrintVec();

   Vector<double> ip = dft.compute_idft1d(pft, 13);
   ip.PrintVec();

   return 0;
}