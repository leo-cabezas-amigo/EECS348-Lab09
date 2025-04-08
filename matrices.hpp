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
#include <limits>   // Implements std::numeric_limits<type>::min().
#include <iomanip>  // Implements std::setw (for SqTypeMatrix<type>::display_matrix()).

#ifndef __MATRICES_HPP__
#define __MATRICES_HPP__

template <typename type>    // Beginning of SqTypeMatrix<type> class template
class SqTypeMatrix { // Class definition with its attributes, constructors, and methods.
    public:
        typedef std::vector<std::vector<type>> m_type;                              // Stands for "type matrix".
        typedef std::tuple<SqTypeMatrix<type>, SqTypeMatrix<type>> m_type_2tuple;   // Stands for "2-element tuple of type matrices".
        
        m_type array;           // Contains the elements of the matrix.
        std::size_t size;       // Size of the square matrix.
        std::size_t type_flag;  // Type flag for the matrix (0: int; 1: double).

        SqTypeMatrix();  // Default constructor.

        SqTypeMatrix(std::stringstream& sstream);    // Initializes a matrix given a stringstream containing its elements.
        
        void load_matrix(std::stringstream& sstream);   // Rewrites the matrix array given a stringstream containing the new elements.

        static m_type_2tuple read_matrices(std::ifstream& file); // Reads two matrices of identical size from a text file (as per the lab instructions).

        SqTypeMatrix<type> operator + (const SqTypeMatrix<type>& B);  // Computes the sum of two matrices of equal size (operator overloading).

        SqTypeMatrix<type> operator * (const SqTypeMatrix<type>& B);  // Computes the product of two matrices of equal size (operator overloading).

        type main_diag_sum();    // Computes the sum of the matrix elements in the main diagonal.

        type secondary_diag_sum();   // Computes the sum of the matrix elements in the secondary diagonal.

        void swap_rows(std::size_t row1, std::size_t row2); // Swaps the rows of the matrix given by the input indices.

        void swap_columns(std::size_t col1, std::size_t col2);  // Swaps the columns of the matrix given by the input indices.

        type get_value(std::size_t i, std::size_t j);    // Returns the element located at (i, j) in the matrix.

        void set_value(std::size_t i, std::size_t j, const type new_val);  // Sets the (i, j) entry of the matrix to new_val

        void display_matrix();  // Prints the contents of the matrix to std::cout
};

// Defines a tuple type capable of storing all possible type-instances of m_type_2_tuple (int, double).
typedef std::tuple<SqTypeMatrix<int>::m_type_2tuple, SqTypeMatrix<double>::m_type_2tuple> hyper_tuple;

// Bootstraps the file parsing process. Determines the type flag, and calls SqTypeMatrix<type>::read_matrices(file)
// according to the type flag detected. Returns both a hyper_tuple --- one of whose tuple members contains the desired
// generated matrices, and the others are unused --- and the type flag as a tuple. Returning the type flag is needed
// to determine which entry of hyper_tuple to access to retreive the generated matrices, and to know their type.
// There might be simpler ways to achieve this kind of behavior, but I am not acquainted enough with templates to know.
std::tuple<hyper_tuple, std::size_t> init_read_matrices(std::ifstream& file);   

#endif // __MATRICES_HPP__