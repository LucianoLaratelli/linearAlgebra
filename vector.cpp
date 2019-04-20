//
// Created by l on 4/19/19.
//

#include <utility>
#include "vector.hpp"

Vector::Vector(unsigned size)
    : size_(size) {
    data_ = new double[size]();
}

Vector::Vector(const Vector &other)
    : size_(other.size_) {
    this->data_ = new double[other.size_]();
    for (unsigned i = 0; i < other.size_; ++i) {
        this->data_[i] = other[i];
    }
}

Vector::~Vector() {
    delete[] data_;
}

double &Vector::operator[](unsigned index) {
    return data_[index];
}

double Vector::operator[](unsigned index) const {
    return data_[index];
}

Vector &Vector::operator=(Vector &&other) noexcept {
    using std::swap;
    swap(size_, other.size_);
    swap(data_, other.data_);
    return *this;
}

Vector &Vector::operator=(const Vector &other) {
    if (this != &other) {
        auto * newData = new double[other.size_]();
        for (unsigned i = 0; i < other.size_; ++i) {
            newData[i] = other[i];
        }
        data_ = newData;
        size_ = other.size_;
    }
    return *this;
}

double Vector::operator*(const Vector &v) const {
    return std::inner_product(data_, data_+size_, v.data_, 0.0);
}

Vector Vector::operator*(double n) const {
    Vector result(size_);
    for (unsigned i = 0; i < size_; ++i) {
        result[i] = data_[i] * n;
    }
    return result;
}

Vector Vector::operator-(Vector v) {
    Vector result(size_);
    for (unsigned i = 0; i < size_; ++i) {
        result[i] = data_[i] - v[i];
    }
    return result;
}

void Vector::operator-=(const Vector &v) {
    if (v.size_ != size_) {
        throw std::out_of_range("Trying to -= a vector with size (LHS) " + std::to_string(size_) +
                                " and a vector with size (RHS) " + std::to_string(v.size_));
    }
    (*this) = (*this) - v;
}

bool Vector::operator==(const Vector &rhs) const {
    if (size_ != rhs.size_) { return false; }
    bool equal = true;
    for (unsigned i = 0; i < size_; ++i) {
        if (data_[i] != rhs.data_[i]) {
            equal = false;
            break;
        }
    }
    return equal;
}

bool Vector::operator!=(const Vector &rhs) const {
    return !((*this) == rhs);
}

double Vector::norm() const {
    return std::sqrt(std::inner_product(data_, data_+size_, data_, 0.0));
}

Vector Vector::unitize() const {
    // return new vector that is old vector divided by its norm -- this is a "unit vector" since it has a difference
    // of one, so we say we're "unitizing"
    auto result = Vector(size_);
    auto norm = this->norm();
    for (int i = 0; i < size_; i++) {
        result[i] = this->data_[i] / norm;
    }

    return result;
}


Vector Vector::projectOnBasis(const Vector& v) {
    return v * ((*this*v)/(v*v));
}

unsigned Vector::size() const {
    return size_;
}

double *Vector::getData() const {
    return data_;
}

std::ostream &operator<<(std::ostream &stream, Vector v) {
    for (unsigned i = 0; i < v.size_; ++i) {
        stream << v[i] << " ";
    }
    stream << std::endl;
    return stream;
}



