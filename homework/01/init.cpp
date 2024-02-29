#include <Kokkos_Core.hpp>
#include <iostream>
#include <cstdio>

// Problem: Link and run program with Kokkos where you initialize a View and print out its name with the $.label()$ method.

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
	  Kokkos::View<int*> J("first_view", 3);

	  std::cout << J.label() << std::endl;
  }
  Kokkos::finalize();
}
