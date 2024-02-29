#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Do simple parallel reduce to output the maximum element in a View
struct max{
	using value_type = int;
	KOKKOS_INLINE_FUNCTION 
	void operator()(const int i, int& lmax) const{
		if( i > lmax)
		       lmax = i;	
	}
};


int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
	  int n = 8;
  // Make View and create values
  	Kokkos::View<int*> A("4", n); 
	for(int i = 0; i < n; i++) {
		A(i) = i + 2;
	        std::cout << "A" << i << " Value " <<  A(i) << std::endl;	
	}
	int max_value = std::numeric_limits<int>::min(); // initalize max val to smalles val poss
  
  // Do a parallel reduction
  	Kokkos::parallel_reduce("Parallel max", A.extent(0), KOKKOS_LAMBDA(const int& i , int& lmax) {
			max functor;
			functor(A(i), lmax);
		}, Kokkos::Max<int>(max_value));
		std::cout << "Max value: " << max_value << std::endl;
  
  }
  Kokkos::finalize();
  return 0;
}
