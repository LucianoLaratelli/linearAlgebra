//
// Created by l on 4/19/19.
//

#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <numeric>
#include <iostream>
#include <iomanip>
#include <utility>
#include "vector.hpp"

enum matrixType {lower, upper};

class Matrix {
 public:
    Matrix(unsigned rows, unsigned cols);
    Matrix(const Matrix & other);
    ~Matrix();

    //functions that return doubles
    double &operator()(unsigned row, unsigned col);
    double operator()(unsigned row, unsigned col) const;
    double smallestValue() const;

    //functions that return matrices
    Matrix &operator=(Matrix&& other) noexcept;
    Matrix &operator=(const Matrix & other);
    Matrix operator*(const Matrix &m);
    Matrix transpose() const;
    Matrix getTriangular(matrixType mt);

    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;

    Vector colVecFromMatrix(unsigned column) const;
    void insertColumnVector(Vector v, unsigned column);

    unsigned rowCount() const;
    unsigned colCount() const;

    //friend std::ostream &operator<<(std::ostream &stream, const Matrix &m);
    friend std::ostream &operator<<(std::ostream &stream, Matrix m);


 private:
    unsigned rows_, cols_;
    double ** data_;
};


#endif //MATRIX_MATRIX_HPP
