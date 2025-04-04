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

SqIntMatrix::SqIntMatrix(){
    this->size = 0; // Set size to 0 for the default constructor (signifies empty array).
    return;
}

SqIntMatrix::SqIntMatrix(std::stringstream& sstream){
    this->load_matrix(sstream); // Initializes the matrix instance with the SqIntMatrix::load_matrix() method.
    return;
}

void SqIntMatrix::load_matrix(std::stringstream& sstream){
    sstream >> this->size;  // Get the matrix size from the stringstream.
    if (this->size == 0){   // Cannot read size 0 matrices (no elements to be read).
        std::cerr << "Error in 'SqIntMatrix::load_matrix()': Can't load a size 0 matrix.\n";
        return;
    }

    this->array.clear();    // Erases the contents of this->array (in case it was already populated).

    int elem_buffer;                // Temporarily holds integer values read from sstream.
    std::vector<int> row_buffer;    // Temporarily holds entire rows read from sstream.
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

m_int_2tuple SqIntMatrix::read_matrices(std::ifstream& file){
    m_int_2tuple matrices;  // 2-tuple to store the two matrices that will be read.
    
    std::size_t matrix_size;    // Holds the size value read from the file.
    int buffer_int;             // Temporarily holds integer values read from the file.
    std::string matrix_string1, matrix_string2; // Strings that will be used to generate the stringstreams.
    std::stringstream sstream1, sstream2;       // Stringstreams that will be used to initialize the matrices.

    file >> matrix_size;    // Reads the matrix size from the file.
    matrix_string1 += std::to_string(matrix_size) + " ";    // Appends the matrix size to matrix_string1
    matrix_string2 += std::to_string(matrix_size) + " ";    // Appends the matrix size to matrix_string2
    
    // Reads every element corresponding to the first matrix, and appends it to matrix_string1
    for (int i = 0; i < matrix_size * matrix_size; i++){
        file >> buffer_int;
        matrix_string1 += std::to_string(buffer_int) + " ";
    }

    // Reads every element corresponding to the second matrix, and appends it to matrix_string2
    for (int j = 0; j < matrix_size * matrix_size; j++){
        file >> buffer_int;
        matrix_string2 += std::to_string(buffer_int) + " ";
    }

    sstream1.str(matrix_string1);   // Populates the stringstream sstream1 with matrix_string1
    sstream2.str(matrix_string2);   // Populates the stringstream sstream2 with matrix_string2

    SqIntMatrix A(sstream1);    // Initializes the first matrix with sstream1 (calls SqIntMatrix::load_matrix())
    SqIntMatrix B(sstream2);    // Initializes the second matrix with sstream2 (calls SqIntMatrix::load_matrix())
    matrices = std::make_tuple(A, B);   // Assigns the 2-tuple containing A and B to 'matrices'.

    return matrices;    // Returns the 2-tuple containing the read matrices.
}

SqIntMatrix SqIntMatrix::operator + (const SqIntMatrix& B){
    if (this->size != B.size){  // Can't add matrices of different sizes.
        std::cerr << "Error in 'SqIntMatrix::operator + ()': Can't add matrices of different sizes.\n";
        return SqIntMatrix();   // Returns an empty matrix to end function exection.
    }

    SqIntMatrix AplusB;         // Stores the result of A + B.
    AplusB.size = this->size;   // The size of A + B is the same as that of A (or B).
    
    std::vector<int> row_buffer;    // Temporarily holds entire rows computed when performing addition.
    for (int i = 0; i < AplusB.size; i++){      // Iterates over the matrices' rows.
        for (int j = 0; j < AplusB.size; j++){  // Iterates over the matrices' columns.
            row_buffer.push_back(this->array[i][j] + B.array[i][j]);    // Appends the result of adding A(i,j) to B(i,j) to the row buffer.
        }
        AplusB.array.push_back(row_buffer);     // Appends the i-th row to AplusB once all of its elements are computed.
        row_buffer.clear();     // Erases the row buffer before calculating the next row.
    }
    return AplusB;  // Returns the result of A + B (SqIntMatrix).
}

SqIntMatrix SqIntMatrix::operator * (const SqIntMatrix& B){
    if (this->size != B.size){  // Can't multiply square matrices of different sizes.
        std::cerr << "Error in 'SqIntMatrix::operator * ()': Can't multiply matrices of different sizes.\n";
        return SqIntMatrix();   // Returns an empty matrix to end function execution.
    }

    SqIntMatrix AtimesB;        // Stores the result of A * B.
    AtimesB.size = this->size;  // The size of A * B is the same as that of A (or B), since these are square matrices.

    int elem_buffer = 0;            // Temporarily holds the result of multiplying a row of A by a column of B.
    std::vector<int> row_buffer;    // Temporarily holds entire rows computed when performing multiplication.
    for (int i = 0; i < AtimesB.size; i++){
        for (int j = 0; j < AtimesB.size; j++){
            // Computes the (i, j)-th element of A * B.
            for (int k = 0; k < AtimesB.size; k++){
                elem_buffer += this->array[i][k] * B.array[k][j];
            }
            row_buffer.push_back(elem_buffer);  // Appends the result of the computation to the row buffer.
            elem_buffer = 0;    // Resets elem_buffer for the next computation.
        }
        AtimesB.array.push_back(row_buffer);    // Appends the i-th row to AtimesB once all of its elements are computed.
        row_buffer.clear();     // Erases the row buffer before calculating the next row.
    }
    return AtimesB; // Returns the result of A * B (SqIntMatrix).
}

int SqIntMatrix::main_diag_sum(){
    int main_diag_sum = 0;  // Initializes the result to 0.
    // Adds all diagonal elements of the matrix to main_diag_sum.
    for (int i = 0; i < this->size; i++){
        main_diag_sum += this->array[i][i];
    }
    return main_diag_sum;   // Returns the main diagonal sum.
}

int SqIntMatrix::secondary_diag_sum(){
    int secondary_diag_sum = 0; // Initializes the result to 0.
    // Adds all secondary-diagonal elements of the matrix to main_diag_sum.
    for (int i = 0; i < this->size; i++){
        secondary_diag_sum += this->array[this->size - 1 - i][i];
    }
    return secondary_diag_sum;  // Returns the secondary diagonal sum.
}

void SqIntMatrix::swap_rows(std::size_t row1, std::size_t row2){
    if (row1 >= this->size || row2 >= this->size){  // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqIntMatrix::swap_rows()': Indices out of range.\n";
        return; // Ends function execution.
    }
    // Swaps row1 with row2 (trivial implementation).
    std::vector<int> temp_row;  // Temporary variable for swapping.
    temp_row = this->array[row1];
    this->array[row1] = this->array[row2];
    this->array[row2] = temp_row;
    return;
}

void SqIntMatrix::swap_columns(std::size_t col1, std::size_t col2){
    if (col1 >= this->size || col2 >= this->size){  // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqIntMatrix::swap_columns()': Indices out of range.\n";
        return; // Ends function execution.
    }
    
    int temp_int;   // Temporary variable for swapping.
    for (int i = 0; i < this->size; i++){
        // Individually swaps every element of the columns.
        temp_int = this->array[i][col1];
        this->array[i][col1] = this->array[i][col2];
        this->array[i][col2] = temp_int;
    }
    return;
}

int SqIntMatrix::get_value(std::size_t i, std::size_t j){   
    if (i >= this->size || j >= this->size){    // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqIntMatrix::get_value()': Indices out of range.\n";
        return INT_MIN; // Returns INT_MIN when the indices are invalid, ending function execution.
    }

    return this->array[i][j];   // Returns the (i, j)-th element of the matrix.
}

void SqIntMatrix::set_value(std::size_t i, std::size_t j, int new_val){
    if (i >= this->size || j >= this->size){    // If either of the indices are out of bounds.
        // This ALSO accounts for negative numbers! (std::size_t converts negatives to extremely large positive numbers).
        std::cerr << "Error in 'SqIntMatrix::set_value()': Indices out of range.\n";
        return; // Ends function execution.
    }

    this->array[i][j] = new_val;    // Sets the (i, j)-th element of the matrix to the new value.
    return;
}

void SqIntMatrix::display_matrix(){
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
            std::cout << std::setw(max_width) << this->array[i][j]; // Prints the (i, j)-th element with proper spacing.
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
