#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>


int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
 
	double result;
	int N = 10; 
	Kokkos::View<int*> A("A", N);
	for(int i =0; i < N; i++){
	       A(i) = i;
	}	       

	Kokkos::View<int*> partial_sum("partial_sum", N);
	Kokkos::Timer timer;

	Kokkos::parallel_scan("PrefixSum", N, KOKKOS_LAMBDA(const int i, int& update, const bool final){
			update += A(i);
			if(final){
				partial_sum(i) = update;
			}
		});
	Kokkos::fence();
	for(int i = 0; i < N; i++) {
		std::cout << "Partial sum[ " << i << "] = " << partial_sum(i) << std::endl;
	}
	std::cout << "Time taken: " << timer.seconds() << " seconds" << std::endl;



  }
  Kokkos::finalize();
  return 0;

}
