#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Declare a 5 ∗ 7 ∗ 12 ∗ n View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View
  	int n;
	std::cout << "what do you want n to be:" << std::endl;
	std::cin >> n;
  	Kokkos::View<int****> B("num3", 5,7,12,n);
  // print name
  	std::cout  << "name: " <<  B.label() << " Dim 1: " << B.extent(0) << " Dim 2: " <<  B.extent(1) << " Dim 3: " <<  B.extent(2) << " Dim 4: " <<  B.extent(3) << std::endl;
  
  }
  Kokkos::finalize();
}
