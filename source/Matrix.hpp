#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <initializer_list>
#include <memory>
#include <ostream>
#include <iomanip>

/*
 * @brief A class representing a matrix with arbitrary data type.
 *
 * @tparam MatrixType The type of elements in the matrix.
 */
template <class MatrixType>
class Matrix{
	public:
		/*
		 * @brief Default constructor creating an empty matrix.
		 */
		Matrix() : rows(0), columns(0), data(nullptr){

		}

		/*
		 * @brief Constructor creating a matrix with specified dimensions and filled with a value.
		 *
		 * @param rows The number of rows in the matrix.
		 * @param columns The number of columns in the matrix.
		 * @param value The value to fill the matrix with.
		 */
		Matrix(std::size_t rows, std::size_t columns, MatrixType value)
			: Matrix(){
			assert(rows > 0 && columns > 0);

			this->rows = rows;
			this->columns = columns;

			std::size_t size = rows * columns;
			if(size > 0){
				data = std::make_unique<MatrixType[]>(size);
				for(std::size_t i = 0; i < size; ++i){
					data[i] = value;
				}
			}else{
				this->rows = 0;
				this->columns = 0;
			}
		}

		/*
		 * @brief Constructor creating a matrix from an initializer list of rows.
		 *
		 * @param elements The initializer list of rows, where each row is an initializer list of MatrixType elements.
		 */
		Matrix(std::initializer_list<std::initializer_list<MatrixType>> elements){
			std::size_t rows = elements.size();
			if (rows == 0) {
				columns = 0;
				data = nullptr;
				return;
			}

			std::size_t maxColumns = 0;
			for(const auto& row : elements){
				maxColumns = std::max(maxColumns, row.size());
			}

			std::size_t size = rows * maxColumns;
			data = std::make_unique<MatrixType[]>(size);
			std::size_t rowIndex = 0;
			for(const auto& row : elements){
				std::copy(row.begin(), row.end(), data.get() + rowIndex * maxColumns);
				std::fill(data.get() + rowIndex * maxColumns + row.size(), data.get() + (rowIndex + 1) * maxColumns, MatrixType());
				rowIndex++;
			}

			this->rows = rows;
			this->columns = maxColumns;
		}

		/*
		 * @brief Copy constructor creating a matrix as a copy of another matrix.
		 *
		 * @param matrix The matrix to copy.
		 */
		Matrix(const Matrix& matrix)
			: Matrix(){
			rows = matrix.rows;
			columns = matrix.columns;

			std::size_t size = rows * columns;

			if(size > 0){
				data = std::make_unique<MatrixType[]>(size);
				std::copy(matrix.data.get(), matrix.data.get() + (rows * columns), data.get());
			}
		}

		/*
		 * @brief Assignment operator for assigning one matrix to another.
		 *
		 * @param rhs The matrix to assign.
		 *
		 * @return A reference to the assigned matrix.
		 */
		Matrix& operator=(const Matrix& rhs){
			if(this == &rhs){
				return *this;
			}

			if(rows != rhs.rows || columns != rhs.columns){
				auto newData = std::make_unique<MatrixType[]>(rhs.rows * rhs.columns);
				std::copy(rhs.data.get(), rhs.data.get() + (rhs.rows * rhs.columns), newData.get());
				data = std::move(newData);
				rows = rhs.rows;
				columns = rhs.columns;
			}else{
				std::copy(rhs.data.get(), rhs.data.get() + (rows * columns), data.get());
			}

			return *this;
		}

		/*
		 * @brief Returns the number of rows in the matrix.
		 *
		 * @return The number of rows.
		 */
		std::size_t getRows() const{
			return rows;
		}

		/*
		 * @brief Returns the number of columns in the matrix.
		 *
		 * @return The number of columns.
		 */
		std::size_t getColumns() const{
			return columns;
		}

		/*
		 * @brief Accesses the element at the specified row and column in the matrix for modification.
		 *
		 * @param i The row index.
		 * @param j The column index.
		 *
		 * @return A reference to the element at the specified position.
		 */
		MatrixType& operator()(std::size_t i, std::size_t j){
			//assert(i * columns + j < rows * columns);
			return data[i * columns + j];
		}

		/*
		 * @brief Accesses the element at the specified row and column in the matrix for read-only access.
		 *
		 * @param i The row index.
		 * @param j The column index.
		 *
		 * @return The element at the specified position.
		 */
		MatrixType operator()(std::size_t i, std::size_t j) const{
			//assert(i * columns + j < rows * columns);
			return data[i * columns + j];
		}

	private:
		std::size_t rows;					///< The number of rows in the matrix.
		std::size_t columns;				///< The number of columns in the matrix.
		std::unique_ptr<MatrixType[]> data;	///< The underlying data storage for the matrix.
};

/*
 * @brief Output stream operator for displaying a matrix.
 *
 * @tparam MatrixType The type of elements in the matrix.
 *
 * @param os The output stream.
 * @param matrix The matrix to display.
 *
 * @return The output stream.
 */
template <typename MatrixType>
std::ostream& operator<<(std::ostream& os, const Matrix<MatrixType>& matrix){
    std::size_t rows = matrix.getRows();
    std::size_t cols = matrix.getColumns();

    int maxElementWidth = 0;
    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            int elementWidth = std::to_string(matrix(i, j)).length();
            if(elementWidth > maxElementWidth){
                maxElementWidth = elementWidth;
            }
        }
    }

    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            os << std::setw(maxElementWidth) << matrix(i, j) << ' ';
        }
        os << '\n';
    }

    os << std::setw(0);

    return os;
}

#endif /* MATRIX_HPP */
