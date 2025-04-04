/*
-------------------------------------------------------------------------------------
File name       = main.cpp
Creation date   = 4/4/2025
-------------------------------------------------------------------------------------
Author          = Leo Cabezas Amigo (KUID 3109786)
Class           = EECS 348
Lab #           = 9
-------------------------------------------------------------------------------------
*/

#include "matrices.hpp"

void test_SqIntMatrix(std::ifstream& file){
    m_int_2tuple matrices = SqIntMatrix::read_matrices(file);   // Reads both matrices and their sizes from the file.
    SqIntMatrix A = std::get<0>(matrices);  // Initializes the first matrix (A).
    SqIntMatrix B = std::get<1>(matrices);  // Initializes the second matrix (B).
    
    SqIntMatrix AplusB = A + B;     // Calculates the sum of A and B.
    SqIntMatrix AtimesB = A * B;    // Calculates the product of A and B.
    
    std::cout << "================================= QUESTION 1 =================================\n";
    std::cout << "------------ FIRST MATRIX (A) ------------\n";
    std::cout << "A.size = " << A.size << "\n";
    std::cout << "A.array = \n";
    A.display_matrix(); // Prints A to std::cout.
    std::cout << "\n";

    std::cout << "------------ SECOND MATRIX (B) ------------\n";
    std::cout << "B.size = " << A.size << "\n";
    std::cout << "B.array = \n";
    B.display_matrix();  // Prints B to std::cout.
    std::cout << "\n";

    std::cout << "================================= QUESTION 2 =================================\n";
    std::cout << "------------ SUM OF A AND B ------------\n";
    std::cout << "AplusB.array = \n";
    AplusB.display_matrix();     // Prints A + B to std::cout.
    std::cout << "\n";

    std::cout << "================================= QUESTION 3 =================================\n";
    std::cout << "------------ PRODUCT OF A AND B ------------\n";
    std::cout << "AtimesB.array = \n";
    AtimesB.display_matrix();    // Prints A * B to std::cout.
    std::cout << "\n";

    std::cout << "================================= QUESTION 4 =================================\n";
    std::cout << "------------ DIAGONAL SUMS OF A ------------\n";
    std::cout << "A's main diagonal sum = " << A.main_diag_sum() << "\n";
    std::cout << "A's secondary diagonal sum = " << A.secondary_diag_sum() << "\n";
    std::cout << "\n";

    std::cout << "------------ DIAGONAL SUMS OF B ------------\n";
    std::cout << "B's main diagonal sum = " << B.main_diag_sum() << "\n";
    std::cout << "B's secondary diagonal sum = " << B.secondary_diag_sum() << "\n";
    std::cout << "\n";

    std::cout << "================================= QUESTION 5 =================================\n";
    std::cout << "------------ SWAPPING ROWS OF A ------------\n";
    std::size_t row1A = 0, row2A = 2;
    A.swap_rows(row1A, row2A);
    std::cout << "===> Swapped rows " << row1A << " and " << row2A << " of A.\n";
    std::cout << "A.array = \n";    // Prints A after row swapping to std::cout.
    A.display_matrix();
    std::cout << "\n";

    std::cout << "------------ SWAPPING ROWS OF B ------------\n";
    std::size_t row1B = 1, row2B = 3;
    B.swap_rows(row1B, row2B);
    std::cout << "===> Swapped rows " << row1B << " and " << row2B << " of B.\n";
    std::cout << "B.array = \n";    // Prints B after row swapping to std::cout.
    B.display_matrix();
    std::cout << "\n";
    
    std::cout << "================================= QUESTION 6 =================================\n";
    std::cout << "------------ SWAPPING COLUMNS OF A ------------\n";
    std::size_t col1A = 1, col2A = 2;
    A.swap_columns(col1A, col2A);
    std::cout << "===> Swapped columns " << col1A << " and " << col2A << " of A.\n";
    std::cout << "A.array = \n";    // Prints A after column swapping to std::cout.
    A.display_matrix();
    std::cout << "\n";
    
    std::cout << "------------ SWAPPING COLUMNS OF B ------------\n";
    std::size_t col1B = 0, col2B = 3;
    B.swap_columns(col1B, col2B);
    std::cout << "===> Swapped columns " << col1B << " and " << col2B << " of B.\n";
    std::cout << "B.array = \n";    // Prints B after column swapping to std::cout.
    B.display_matrix();
    std::cout << "\n";

    std::cout << "================================= QUESTION 7 =================================\n";
    std::cout << "------------ UPDATING ELEMENTS OF A ------------\n";
    std::size_t rowA = 2, colA = 1;
    int new_elemA = 1633;
    std::cout << "A[" << rowA << "][" << colA << "] before updating = " << A.get_value(rowA, colA) << "\n";
    A.set_value(rowA, colA, new_elemA);
    std::cout << "===> Updated value of A[" << rowA << "][" << colA << "] to " << A.get_value(rowA, colA) << "\n",
    std::cout << "A.array = \n";    // Prints A after element updating to std::cout.
    A.display_matrix();
    std::cout << "\n";

    std::cout << "------------ UPDATING ELEMENTS OF B ------------\n";
    std::size_t rowB = 0, colB = 3;
    int new_elemB = 1483;
    std::cout << "B[" << rowB << "][" << colB << "] before updating = " << B.get_value(rowB, colB) << "\n";
    B.set_value(rowB, colB, new_elemB);
    std::cout << "===> Updated value of B[" << rowB << "][" << colB << "] to " << B.get_value(rowB, colB) << "\n",
    std::cout << "B.array = \n";    // Prints B after element updating to std::cout.
    B.display_matrix();
    std::cout << "\n";
    return;
}

int main(int argc, char** argv){
    std::ifstream file;
    if (argc > 1){  // If a filepath is specified (argv[1]).
        file.open(argv[1]);     // Opens file specified by runtime args.
        if (!file.is_open()){
            std::cerr << "Error in 'main()': Could not open specified file.\n";
            return 1;
        }
    } else {        // If no filepath is specified.
        file.open("Lab8_Test_File.txt");
        if (!file.is_open()){
            std::cerr << "Error in 'main()': Could not open default file 'Lab8_Test_File.txt'.\n";
            return 1;
        }
    }

    test_SqIntMatrix(file); // Displays the results of all methods of the SqIntMatrix class given the input text file.
    file.close();           // Closes the file after data is read.
    return 0;
}