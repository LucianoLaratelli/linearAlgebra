//
// Created by l on 4/19/19.
//

#ifndef MATRIX_VECTOR_HPP
#define MATRIX_VECTOR_HPP

#include <numeric>
#include <iostream>
#include <functional>
#include <cmath>


class Vector {
 public:
    explicit Vector(unsigned size);
    Vector(const Vector & other);

    ~Vector();

    double &operator[](unsigned index);
    double operator[](unsigned index) const;

    Vector &operator=(Vector&& other) noexcept;
    Vector &operator=(const Vector & other);

    double operator*(const Vector &v) const;
    Vector operator*(double n) const;
    Vector operator-(Vector v);
    void operator-=(const Vector &v);

    bool operator==(const Vector &rhs) const;
    bool operator!=(const Vector &rhs) const;

    double norm() const;
    Vector unitize() const;
    Vector projectOnBasis(const Vector& v);

    unsigned size() const;
    double * getData() const;

    friend std::ostream &operator<<(std::ostream &stream, Vector v);

 private:
    unsigned size_;
    double * data_;

};


#endif //MATRIX_VECTOR_HPP
