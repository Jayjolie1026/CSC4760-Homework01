#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

bool checkShape( int rowm , int colm,  int rowv );

int main(int argc, char* argv[]) {

  Kokkos::initialize(argc, argv);

  {

        bool flag = false;
        int numRowsMatrix;
        int numRowsVector;
        int numColumnsMatrix;
        do{
        std::cout << " Please enter your number of rows  for your matrix: ";
        std::cin >> numRowsMatrix;
	std::cout << std::endl;
        std::cout << " Please enter your number of columns  for your matrix: ";
        std::cin >> numColumnsMatrix;
        std::cout << std::endl;
        std::cout << " Please enter your number of rows for your vector: ";
        std::cin >> numRowsVector;
        std::cout << std::endl;
        std::cout << "Checking dimensions..." << std::endl;
        flag = checkShape(numRowsMatrix,numColumnsMatrix, numRowsVector);
        if(!flag){
                std::cout << "That is not correct dimensions! Please try again!" << std::endl;
        }
        }while(!flag);
  // Make View and add values
        Kokkos::View<int*> B("vector", numRowsVector);
        Kokkos::View<int**> A("matrix", numRowsMatrix,numColumnsMatrix);
        Kokkos::View<int*> C("multiply", numRowsMatrix);
      //  for(int i = 0; i < numRowsMatrix; i++) {
        //        for(int j = 0 ; j < numColumnsMatrix; j++){
          //              A(i,j) =( i * j) + 10;
            //            std::cout << " A's Values are: " << "i: " << i << " j: " << j << " makes the value "<<   (A(i,j)) << std::endl;
              //  }
       // }
       // for(int i = 0; i < numRowsVector; i++){
         //       B(i) = i * 4;
           //     std::cout << "B's Values are: " << "i: " << i <<  " makes the value " <<   (B(i)) << std::endl;
//	}
	
	 for (int i = 0; i < numRowsMatrix; i++){
                for(int j = 0; j < numColumnsMatrix; j++) {
                        std::cout << "Enter value for the matrix's row " << i+1 << " ,column " << j + 1 << ": ";
                        std::cin >> A(i,j);
                }
        }

        for(int i = 0; i < numRowsVector; i++) {
                 std::cout << "Enter value for the vector's row " << i+1 << " " ;
                 std::cin >> B[i];
        }
	Kokkos::parallel_for("Loop i", numRowsMatrix, KOKKOS_LAMBDA(const int i)  {
	   long total = 0;
           for(int j = 0; j < numColumnsMatrix; j++) {
                total += A(i,j) * B(j);
           }
	   C(i) = total;
        });
  // Output addition 
  	std::cout << "C's values are: " << std::endl;
        for(int i = 0; i < numRowsMatrix; i++) {
                
             std::cout << std::endl <<  (C(i)) << " " ;
               
        }
  }
  Kokkos::finalize();
  return 0;
}

bool checkShape(int fm, int sm, int fv ) {
        if(sm == fv){
                return true;
        }else{
                return false;
        }
}
