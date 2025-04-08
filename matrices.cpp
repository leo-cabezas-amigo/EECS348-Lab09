/*
-------------------------------------------------------------------------------------
File name       = matrices.cpp
Creation date   = 4/4/2025
-------------------------------------------------------------------------------------
Author          = Leo Cabezas Amigo (KUID 3109786)
Class           = EECS 348
Lab #           = 9
-------------------------------------------------------------------------------------
*/

#include "matrices.hpp"

std::tuple<hyper_tuple, std::size_t> init_read_matrices(std::ifstream& file){
    // Declares the output hyper_tuple and its to-be entry elements.
    hyper_tuple hyp_tuple;
    SqTypeMatrix<int>::m_type_2tuple m_int_2tuple;          // int instance of m_type_2tuple, first entry.
    SqTypeMatrix<double>::m_type_2tuple m_double_2tuple;    // double instance of m_type_2tuple, second entry.

    std::size_t matrix_size;    // Holds the parsed matrix size.
    std::size_t type_flag;      // Holds the parsed type flag.
    
    file >> matrix_size;        // Parses the matrix size from the file.
    file >> type_flag;          // Parses the type flag from the file.
    file.clear();                   // Clear any error flags (if any; probably unnecessary).
    file.seekg(0, std::ios::beg);   // Return to the beginning of the file before calling SqTypeMatrix<type>::read_matrices().

    switch(type_flag){  // Calls the appropriate type instance of SqTypeMatrix<type>::read_matrices() according to the type flag.
        case 0:     // Case type == int.
            m_int_2tuple = SqTypeMatrix<int>::read_matrices(file);
            break;
        case 1:     // Case type == double.
            m_double_2tuple = SqTypeMatrix<double>::read_matrices(file);
            break;
        default:    // Other type flag values are considered invalid.
            std::cerr << "Error in 'init_read_matrices()': Undefined matrix type flag.\n";
    }

    // Generates the hyper_tuple containing all m_type_2tuple variations. Only one type instance of m_type_2tuple contains
    // the parsed matrices, since the switch statement only calls SqTypeMatrix<type>::read_matrices() for the appropriate
    // data type according to the type flag. The other m_type_2tuple instances are placeholders, and are unused.
    hyp_tuple = std::make_tuple(m_int_2tuple, m_double_2tuple);     

    return std::make_tuple(hyp_tuple, type_flag);   // Returns a tuple containing the hyper_tuple and the type flag.
}

template <typename type>    // This method belongs to a templated class.
SqTypeMatrix<type>::SqTypeMatrix(){
    this->size = 0; // Set size to 0 for the default constructor (signifies empty array).
    return;
}

template <typename type>    // This method belongs to a templated class.
SqTypeMatrix<type>::SqTypeMatrix(std::stringstream& sstream){
    this->load_matrix(sstream); // Initializes the matrix instance with the SqTypeMatrix<type>::load_matrix() method.
    return;
}

template <typename type>    // This method belongs to a templated class.
void SqTypeMatrix<type>::load_matrix(std::stringstream& sstream){
    sstream >> this->size;  // Get the matrix size from the stringstream. 
    if (this->size == 0){   // Cannot read size 0 matrices (no elements to be read).
        std::cerr << "Error in 'SqTypeMatrix<type>::load_matrix()': Can't load a size 0 matrix.\n";
        return;
    }
    sstream >> this->type_flag;     // Gets the type flag from the stringstream.

    this->array.clear();    // Erases the contents of this->array (in case it was already populated).

    type elem_buffer;                // Temporarily holds type values read from sstream.
    std::vector<type> row_buffer;    // Temporarily holds entire rows read from sstream.
    for (int i = 0; i < this->size; i++){           // Iterates over the matrix rows.
        for (int j = 0; j < this->size; j++){       // Iterates over the matrix columns.
            sstream >> elem_buffer;             // Reads the next element from sstream.
            row_buffer.push_back(elem_buffer);  // Appends the element to the current row.
        }
        this->array.push_back(row_buffer);  // Once built, append the current row to the array.
        row_buffer.clear();                 // Erases the row buffer before the next row is read.
    }
    return;
}

template <typename type>    // This static method belongs to a templated class.
typename SqTypeMatrix<type>::m_type_2tuple SqTypeMatrix<type>::read_matrices(std::ifstream& file){
    SqTypeMatrix<type>::m_type_2tuple matrices;  // 2-tuple to store the two matrices that will be read.
    
    std::size_t matrix_size;    // Holds the size value read from the file.
    std::size_t type_flag;      // Holds the type flag value read from the file (unused in this function).
    type elem_buffer;           // Temporarily holds type values read from the file.
    std::string matrix_string1, matrix_string2; // Strings that will be used to generate the stringstreams.
    std::stringstream sstream1, sstream2;       // Stringstreams that will be used to initialize the matrices.

    file >> matrix_size;    // Reads the matrix size from the file.
    file >> type_flag;      // Reads the type flag from the file.

    matrix_string1 += std::to_string(matrix_size) + " ";    // Appends the matrix size to matrix_string1.
    matrix_string2 += std::to_string(matrix_size) + " ";    // Appends the matrix size to matrix_string2.
    matrix_string1 += std::to_string(type_flag) + " ";      // Appends the matrix type flag to matrix_string1.
    matrix_string2 += std::to_string(type_flag) + " ";      // Appends the matrix type flag to matrix_string2.
    
    // Reads every element corresponding to the first matrix, and appends it to matrix_string1.
    for (int i = 0; i < matrix_size * matrix_size; i++){
        file >> elem_buffer;
        matrix_string1 += std::to_string(elem_buffer) + " ";
    }

    // Reads every element corresponding to the second matrix, and appends it to matrix_string2.
    for (int j = 0; j < matrix_size * matrix_size; j++){
        file >> elem_buffer;
        matrix_string2 += std::to_string(elem_buffer) + " ";
    }

    sstream1.str(matrix_string1);   // Populates the stringstream sstream1 with matrix_string1.
    sstream2.str(matrix_string2);   // Populates the stringstream sstream2 with matrix_string2.

    SqTypeMatrix<type> A(sstream1);     // Initializes the first matrix with sstream1 (calls SqTypeMatrix<type>::load_matrix()).
    SqTypeMatrix<type> B(sstream2);     // Initializes the second matrix with sstream2 (calls SqTypeMatrix<type>::load_matrix()).
    matrices = std::make_tuple(A, B);   // Assigns the 2-tuple containing A and B to 'matrices'.

    return matrices;    // Returns the 2-tuple containing the read matrices.
}

template <typename type>    // This method belongs to a templated class.
SqTypeMatrix<type> SqTypeMatrix<type>::operator + (const SqTypeMatrix<type>& B){
    if (this->size != B.size){  // Can't add matrices of different sizes.
        std::cerr << "Error in 'SqTypeMatrix<type>::operator + ()': Can't add matrices of different sizes.\n";
        return SqTypeMatrix<type>();   // Returns an empty matrix to end function exection.
    }

    SqTypeMatrix<type> AplusB;      // Stores the result of A + B.
    AplusB.size = this->size;       // The size of A + B is the same as that of A (or B).
    AplusB.type_flag = this->type_flag;  // The type flag of A + B is the same as that of A (or B).

    std::vector<type> row_buffer;    // Temporarily holds entire rows computed when performing addition.
    for (int i = 0; i < AplusB.size; i++){      // Iterates over the matrices' rows.
        for (int j = 0; j < AplusB.size; j++){  // Iterates over the matrices' columns.
            row_buffer.push_back(this->array[i][j] + B.array[i][j]);    // Appends the result of adding A(i,j) to B(i,j) to the row buffer.
        }
        AplusB.array.push_back(row_buffer);     // Appends the i-th row to AplusB once all of its elements are computed.
        row_buffer.clear();     // Erases the row buffer before calculating the next row.
    }
    return AplusB;  // Returns the result of A + B (SqTypeMatrix<type>).
}

template <typename type>    // This method belongs to a templated class.
SqTypeMatrix<type> SqTypeMatrix<type>::operator * (const SqTypeMatrix<type>& B){
    if (this->size != B.size){  // Can't multiply square matrices of different sizes.
        std::cerr << "Error in 'SqTypeMatrix<type>::operator * ()': Can't multiply matrices of different sizes.\n";
        return SqTypeMatrix<type>();   // Returns an empty matrix to end function execution.
    }

    SqTypeMatrix<type> AtimesB;     // Stores the result of A * B.
    AtimesB.size = this->size;      // The size of A * B is the same as that of A (or B), since these are square matrices.
    AtimesB.type_flag = this->type_flag; // The type flag of A * B is the same as that of A (or B).

    type elem_buffer = (type)0;           // Temporarily holds the result of multiplying a row of A by a column of B.
    std::vector<type> row_buffer;   // Temporarily holds entire rows computed when performing multiplication.
    for (int i = 0; i < AtimesB.size; i++){
        for (int j = 0; j < AtimesB.size; j++){
            // Computes the (i, j)-th element of A * B.
            for (int k = 0; k < AtimesB.size; k++){
                elem_buffer += this->array[i][k] * B.array[k][j];
            }
            row_buffer.push_back(elem_buffer);  // Appends the result of the computation to the row buffer.
            elem_buffer = (type)0;    // Resets elem_buffer for the next computation.
        }
        AtimesB.array.push_back(row_buffer);    // Appends the i-th row to AtimesB once all of its elements are computed.
        row_buffer.clear();     // Erases the row buffer before calculating the next row.
    }
    return AtimesB; // Returns the result of A * B (SqTypeMatrix<type>).
}

template <typename type>    // This method belongs to a templated class.
type SqTypeMatrix<type>::main_diag_sum(){
    type main_diag_sum = (type)0;  // Initializes the result to 0.
    // Adds all diagonal elements of the matrix to main_diag_sum.
    for (int i = 0; i < this->size; i++){
        main_diag_sum += this->array[i][i];
    }
    return main_diag_sum;   // Returns the main diagonal sum.
}

template <typename type>    // This method belongs to a templated class.
type SqTypeMatrix<type>::secondary_diag_sum(){
    type secondary_diag_sum = (type)0; // Initializes the result to 0.
    // Adds all secondary-diagonal elements of the matrix to main_diag_sum.
    for (int i = 0; i < this->size; i++){
        secondary_diag_sum += this->array[this->size - 1 - i][i];
    }
    return secondary_diag_sum;  // Returns the secondary diagonal sum.
}

template <typename type>    // This method belongs to a templated class.
void SqTypeMatrix<type>::swap_rows(std::size_t row1, std::size_t row2){
    if (row1 >= this->size || row2 >= this->size){  // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqTypeMatrix<type>::swap_rows()': Indices out of range.\n";
        return; // Ends function execution.
    }
    // Swaps row1 with row2 (trivial implementation).
    std::vector<type> temp_row;  // Temporary variable for swapping.
    temp_row = this->array[row1];
    this->array[row1] = this->array[row2];
    this->array[row2] = temp_row;
    return;
}

template <typename type>    // This method belongs to a templated class.
void SqTypeMatrix<type>::swap_columns(std::size_t col1, std::size_t col2){
    if (col1 >= this->size || col2 >= this->size){  // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqTypeMatrix<type>::swap_columns()': Indices out of range.\n";
        return; // Ends function execution.
    }
    
    type elem_temp;     // Temporary variable for swapping.
    for (int i = 0; i < this->size; i++){
        // Individually swaps every element of the columns.
        elem_temp = this->array[i][col1];
        this->array[i][col1] = this->array[i][col2];
        this->array[i][col2] = elem_temp;
    }
    return;
}

template <typename type>    // This method belongs to a templated class.
type SqTypeMatrix<type>::get_value(std::size_t i, std::size_t j){   
    if (i >= this->size || j >= this->size){    // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqTypeMatrix<type>::get_value()': Indices out of range.\n";
        return std::numeric_limits<type>::min(); // Returns INT_MIN when the indices are invalid, ending function execution.
    }

    return this->array[i][j];   // Returns the (i, j)-th element of the matrix.
}

template <typename type>    // This method belongs to a templated class.
void SqTypeMatrix<type>::set_value(std::size_t i, std::size_t j, const type new_val){
    if (i >= this->size || j >= this->size){    // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqTypeMatrix<type>::set_value()': Indices out of range.\n";
        return; // Ends function execution.
    }

    this->array[i][j] = new_val;    // Sets the (i, j)-th element of the matrix to the new value.
    return;
}

template <typename type>    // This method belongs to a templated class.
void SqTypeMatrix<type>::display_matrix(){
    int max_width = 0;
    // Finds the maximum digit length of a matrix element (for column formatting).
    for (int i = 0; i < this->size; i++) {  
        for (int j = 0; j < this->size; j++) {
            int num_width = std::to_string(this->array[i][j]).length();
            if (num_width > max_width) {    // If current width is higher than the largest recorded,
                max_width = num_width;      // set current width as the new largest.
            }
        }
    }
    
    std::cout << "[";   // Denotes the beginning of the matrix.
    for (int i = 0; i < this->size; i++){       // Iterates over the matrix's rows.
        if (i != 0){    // Prints a " "except for the first row.
            std::cout << " ";
        }
        std::cout << "[";   // Denotes the beginning of a row.
        for (int j = 0; j < this->size; j++){   // Iterates over the matrix's columns.
            std::cout << std::setw(max_width) << std::fixed << this->array[i][j];   // Prints the (i, j)-th element with proper spacing.
            if (j != this->size - 1){   // Prints a ", " except for the last column elements.
                std::cout << ", ";
            }
        }
        std::cout << "]"; // Denotes the end of a row.
        if (i != this->size - 1){   // Prints ",\n" except for the last row.
            std::cout << ",\n"; 
        }
    }
    std::cout << "]\n"; // Denotes the end of the matrix.
    return;
}

// Ensures the linker is able to find all possible type declarations of SqTypeMatrix when compiling (or something along these lines).
// Compilation fails without including these template statements at the end of matrices.cpp. 
template class SqTypeMatrix<int>;
template class SqTypeMatrix<double>;