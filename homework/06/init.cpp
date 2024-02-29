#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
#include <iomanip>

// Create a program that does matrix addition between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions

bool checkShape( int rowm , int colm,  int rowv  );

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
	bool flag = false;
	int numRowsMatrix;
	int numRowsVector;
	int numColumnsMatrix;
	int num;
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
	Kokkos::View<int**> C("sum", numRowsMatrix, numColumnsMatrix);
  //	for(int i = 0; i < numRowsMatrix; i++) {
//		for(int j = 0 ; j < numColumnsMatrix; j++){
//			A(i,j) =( i * j) + 5;
//			std::cout << " A's Values are: " << "i: " << i << " j: " << j << " makes the value "<<   (A(i,j)) << std::endl;
//		}
//	}	

//	for(int i = 0; i < numRowsVector; i++){
//		B(i) = i * 3;
//		std::cout << "B's Values are: " << "i: " << i <<  " makes the value " <<   (B(i)) << std::endl;
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


  // Do a matrix add
	Kokkos::parallel_for("Loop i", numRowsMatrix, KOKKOS_LAMBDA(const int i)  {

           for(int j = 0; j < numColumnsMatrix; j++) {
		C(i,j) = A(i,j) + B(j);
           }
        });
  	
  
  // Output addition 
	for(int i = 0; i < numRowsMatrix; i++) {
                for(int j = 0 ; j < numColumnsMatrix; j++){
                        std::cout << "   " << C(i,j);
                }
		std::cout << std::endl;
        }       
  }
  Kokkos::finalize();
}


bool checkShape(int fm, int sm, int fv ) {
	if(sm == fv){
		return true;
	}else{
		return false;
	}

	



}
