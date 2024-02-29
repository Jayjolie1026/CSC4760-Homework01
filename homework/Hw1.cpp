#include <Kokkos_Core.hpp>
#include <iostream>


int main (int argc, char** argv) {
     Kokkos::initialize(argc,argv);
     {  

          View<int*> J("first_view", 8);
	  std:: cout << J.label()

     }  
     Kokkos::finalize();
     return 0;
}


