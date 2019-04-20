#include "matrix.hpp"
#include <string>
#include <stdexcept>

Matrix::Matrix(unsigned rows, unsigned cols)
    : rows_(rows), cols_(cols)
{
    if(!rows || !cols) {
        throw std::out_of_range("Can't make matrix with " + std::to_string(rows) +
                                " rows and " + std::to_string(cols) + " cols.");
    }
    data_ = new double*[rows]();
    for(unsigned i = 0; i < rows; ++i) {
        data_[i] = new double[cols]();
    }
}

Matrix::Matrix(const Matrix &other)
    : rows_(other.rows_), cols_(other.cols_){
    this->data_ = new double*[other.rows_]();
    for(unsigned i = 0; i < other.rows_; ++i) {
        this->data_[i] = new double[other.cols_]();
        for(unsigned j = 0; j < other.cols_; ++j) {
            this->data_[i][j] = other.data_[i][j];
        }
    }
}

Matrix::~Matrix() {
    for(unsigned i = 0; i < rows_; i++) {
        delete[] data_[i];
    }
    delete[] data_;
}

double &Matrix::operator()(unsigned row, unsigned col) {
    return data_[row][col];
}


double Matrix::operator()(unsigned row, unsigned col) const {
    return data_[row][col];
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
    using std::swap;
    swap(rows_, other.rows_);
    swap(cols_, other.cols_);
    swap(data_, other.data_);
    return *this;
}

Matrix &Matrix::operator=(const Matrix &other) {
    if(this != &other) {
        auto ** newData = new double*[other.rows_]();
        for(unsigned i = 0; i < other.rows_; ++i) {
            newData[i] = new double[other.cols_]();
            for(int j = 0; j < other.cols_; ++j){
                newData[i][j] = other(i,j);
            }
        }
        data_ = newData;
        rows_ = other.rows_;
        cols_ = other.cols_;
    }
    return *this;
}

Matrix Matrix::operator*(Matrix &m) {
    Matrix result(rows_, m.cols_);
    auto mTranspose = m.transpose();
    for (unsigned i = 0; i < rows_; ++i) {
        for (unsigned j = 0; j < m.cols_; ++j) {
            result.data_[i][j] = std::inner_product(data_[i], data_[i] + cols_, mTranspose.data_[j], 0.0);
        }
    }
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(cols_, rows_);

    for (int i = 0; i < cols_; i++) {
        for (int j = 0; j < rows_; j++) {
            result(i, j) = (*this)(j, i);
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix &rhs) const {
    if(rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        return false;
    }
    bool equal = true;
    for(int i = 0; i < rows_; ++i) {
        for(int j = 0; j < cols_; ++j) {
            if((*this)(i,j) != rhs(i,j)) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}

bool Matrix::operator!=(const Matrix &rhs) const {
    return !((*this) == rhs);
}

Vector Matrix::colVecFromMatrix(unsigned column) {
    Vector v(rows_);
    for(unsigned i = 0; i < rows_; ++i) {
        v[i] = data_[i][column];
    }
    std::cout << v << std::endl;
    return v;
}

void Matrix::insertColumnVector(Vector v, unsigned column) {
    for(unsigned i = 0; i < rows_; ++i) {
        data_[i][column] = v[i];
    }

}

unsigned Matrix::rowCount() const {
    return rows_;
}

unsigned Matrix::colCount() const {
    return cols_;
}


std::ostream &operator<<(std::ostream &stream, Matrix m) {
    for (int i = 0; i < m.rows_; i++) {
        for (int j = 0; j < m.cols_; j++) {
            if(std::abs(m(i,j)) < 10e-8) {
                stream << std::setw(12) << 0.0 << " ";
            } else {
                stream << std::setw(12) << m(i, j) << " ";
            }
        }
        stream << std::endl;
    }
    return stream;
}



