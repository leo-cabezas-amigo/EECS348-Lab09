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

template <typename type>
void test_SqTypeMatrix(SqTypeMatrix<type>& A, SqTypeMatrix<type>& B){
    SqTypeMatrix<type> AplusB = A + B;     // Calculates the sum of A and B.
    SqTypeMatrix<type> AtimesB = A * B;    // Calculates the product of A and B.
    
    std::cout << "================================= TYPE FLAGS =================================\n";
    std::cout << "(type_flag == 0) -------> int\n";
    std::cout << "(type_flag == 1) -------> double\n";
    std::cout << "\n";

    std::cout << "================================= QUESTION 1 =================================\n";
    std::cout << "------------ FIRST MATRIX (A) ------------\n";
    std::cout << "A.size = " << A.size << "\n";
    std::cout << "A.type_flag = " << A.type_flag << "\n";
    std::cout << "A.array = \n";
    A.display_matrix(); // Prints A to std::cout.
    std::cout << "\n";

    std::cout << "------------ SECOND MATRIX (B) ------------\n";
    std::cout << "B.size = " << A.size << "\n";
    std::cout << "B.type_flag = " << B.type_flag << "\n";
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
        file.open("Lab9_Test_File.txt");
        if (!file.is_open()){
            std::cerr << "Error in 'main()': Could not open default file 'Lab9_Test_File.txt'.\n";
            return 1;
        }
    }
    
    // Retreives the corresponding hyper_tuple and type flag read from the file (see matrices.cpp, matrices.hpp for an in-depth explanation).
    std::tuple<hyper_tuple, std::size_t> global_tuple = init_read_matrices(file);   
    hyper_tuple hyp_tuple = std::get<0>(global_tuple);
    std::size_t type_flag = std::get<1>(global_tuple);
    
    // Retreives all entries of the hyper_tuple. Only the entry corresponding to the parsed type flag will be employed. The rest are placeholders.
    SqTypeMatrix<int>::m_type_2tuple m_int_tuple = std::get<0>(hyp_tuple);
    SqTypeMatrix<double>::m_type_2tuple m_double_tuple = std::get<1>(hyp_tuple);

    switch (type_flag){     // Calls the appropriate type instance of test_SqTypeMatrix<type>() according to the type flag.
        case 0:     // Case type == int.
            // Displays the results of all methods of the SqTypeMatrix<int> class when applied to the parsed matrices.
            // A = std::get<0>(m_int_tuple) [first matrix in the file]; B = std::get<1>(m_int_tuple) [second matrix in the file].
            test_SqTypeMatrix<int>(std::get<0>(m_int_tuple), std::get<1>(m_int_tuple));     
            break;
        case 1:     // Case type == double.
            // Displays the results of all methods of the SqTypeMatrix<double> class when applied to the parsed matrices.
            // A = std::get<0>(m_double_tuple) [first matrix in the file]; B = std::get<1>(m_double_tuple) [second matrix in the file].
            test_SqTypeMatrix<double>(std::get<0>(m_double_tuple), std::get<1>(m_double_tuple));
            break;
        default:    // Other type flag values are considered invalid.
            std::cerr << "Error in 'main()': Undefined matrix type flag.\n";
    }

    file.close();   // Closes the file after all data is read.
    return 0;
}