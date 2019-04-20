//
// Created by l on 4/19/19.
//

#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <numeric>
#include <iostream>
#include <iomanip>
#include "vector.hpp"


class Matrix {
public:
    Matrix(unsigned rows, unsigned cols);
    Matrix(const Matrix & other);

    ~Matrix();

    double &operator()(unsigned row, unsigned col);
    double operator()(unsigned row, unsigned col) const;

    Matrix &operator=(Matrix&& other) noexcept;
    Matrix &operator=(const Matrix & other);
    Matrix operator*(Matrix &m);
    Matrix transpose();

    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;

    Vector colVecFromMatrix(unsigned column);
    void insertColumnVector(Vector v, unsigned column);
    unsigned rowCount() const;
    unsigned colCount() const;


    friend std::ostream &operator<<(std::ostream &stream, Matrix m);

private:
    unsigned rows_, cols_;
    double ** data_;
};


#endif //MATRIX_MATRIX_HPP
