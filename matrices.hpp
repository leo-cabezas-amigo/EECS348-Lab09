/*
-------------------------------------------------------------------------------------
File name       = matrices.hpp
Creation date   = 4/4/2025
-------------------------------------------------------------------------------------
Author          = Leo Cabezas Amigo (KUID 3109786)
Class           = EECS 348
Lab #           = 9
-------------------------------------------------------------------------------------
*/

#include <iostream> // Implements basic C++ I/O functionality.
#include <fstream>  // Implements file streams.
#include <sstream>  // Implements string streams.
#include <string>   // Implements the std::string class.
#include <vector>   // Implements the std::vector class.
#include <tuple>    // Implements the std::tuple class.
#include <climits>  // Implements INT_MIN.
#include <iomanip>  // Implements std::setw (for SqIntMatrix::display_matrix()).

class SqIntMatrix;  // Stands for "square integer matrix". Class declaration.

typedef std::vector<std::vector<int>> m_int;                // Stands for "integer matrix".
typedef std::tuple<SqIntMatrix, SqIntMatrix> m_int_2tuple;  // Stands for "2-element tuple of integer matrices".

class SqIntMatrix { // Class definition with its attributes, constructors, and methods.
    public:
        m_int array;    // Contains the elements of the matrix.
        std::size_t size;    // Size of the square matrix.

        SqIntMatrix();  // Default constructor.

        SqIntMatrix(std::stringstream& sstream);    // Initializes a matrix given a stringstream containing its elements.
        
        void load_matrix(std::stringstream& sstream);   // Rewrites the matrix array given a stringstream containing the new elements.

        static m_int_2tuple read_matrices(std::ifstream& file); // Reads two matrices of identical size from a text file (as per the lab instruction).

        SqIntMatrix operator + (const SqIntMatrix& B);  // Computes the sum of two matrices of equal size.

        SqIntMatrix operator * (const SqIntMatrix& B);  // Computes the product of two matrices of equal size.

        int main_diag_sum();    // Computes the sum of the matrix elements in the main diagonal.

        int secondary_diag_sum();   // Computes the sum of the matrix elements in the secondary diagonal.

        void swap_rows(std::size_t row1, std::size_t row2); // Swaps the rows of the matrix given by the input indices.

        void swap_columns(std::size_t col1, std::size_t col2);  // Swaps the columns of the matrix given by the input indices.

        int get_value(std::size_t i, std::size_t j);    // Returns the element located at (i, j) in the matrix.

        void set_value(std::size_t i, std::size_t j, int new_val);  // Sets the (i, j) entry of the matrix to new_val

        void display_matrix();  // Prints the contents of the matrix to std::cout
};
