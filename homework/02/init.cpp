#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // set n and m, you can change these values
       int n= 16;
       int m = 16;
  // Make View
       Kokkos::View<int**> A("test",n,m);
  // set values to 1000 * i * j;
       Kokkos::parallel_for("Loop i", A.extent(0), KOKKOS_LAMBDA (const int i) {
		       Kokkos::parallel_for("Loop j", A.extent(1), KOKKOS_LAMBDA (const int j) {
			      A(i,j) = i*j*1000;
			      
                       });
       });
       for(int i = 0; i < n ; i++) {
	       for(int j = 0; j < m; j++) {
		       std::cout << "for i value: " << i << " and j value: " << j << " we get: " <<  A(i,j) << std::endl;
	       }
       }

  }
  Kokkos::finalize();
  return 0;
}
