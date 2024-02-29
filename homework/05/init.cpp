#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Create a program that compares a parallel for loop and a standard for loop for summing rows of a View with Kokkos Timer.

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
 	int n = 8;
	int m = 8;

        Kokkos::View<double**> A("4", n, m);
        Kokkos::parallel_for("init", n, KOKKOS_LAMBDA(const int i) {
			for(int j =0; j < m; j++) {
			   A(i,j) = i + j;
			}
	});
  // sum loops 
	Kokkos::Timer timer_serial;
	//serial sum
	for(int i = 0; i < n; i++ ) {
		double sumFor = 0.0;
		for(int j =0; j < m; j++) {
			sumFor += A(i,j);
		}
		std::cout << "Sum For  row:  " << i << " is: " << sumFor << std::endl;
	}
	double serial_time = timer_serial.seconds();
        timer_serial.reset();
	Kokkos::Timer timer_parallel;
        Kokkos::parallel_for("Loop i", n, KOKKOS_LAMBDA(const int i)  {
           double sumPAR = 0.0;
           for(int j = 0; j < m; j++) {
	   	sumPAR += A(i,j);
	   }
	   std::cout << "Sum for row: " << i << " is: " << sumPAR << std::endl;
	});
        double parallel_time = timer_parallel.seconds();
	timer_parallel.reset();
	std::cout << "Parallel sum time: " << parallel_time << " seconds" << std::endl;
	std::cout << "Serial sum time: " << serial_time << " seconds" << std::endl;

  }
  Kokkos::finalize();
  return 0; 
}

