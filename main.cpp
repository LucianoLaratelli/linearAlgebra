#include <cassert>
#include "matrix.hpp"
#include "vector.hpp"
#include <vector>

Matrix buildQ(Matrix &start) {
    auto Q = Matrix(start.rowCount(), start.colCount());

    std::vector<Vector> aVectors;
    std::vector<Vector> uVectors;

    for(unsigned i = 0; i < start.colCount(); ++i) {
        aVectors.push_back(start.colVecFromMatrix(i));
    }

    for(unsigned i = 0; i < start.colCount(); ++i) {
        auto currentUVector = aVectors[i];
        for(unsigned j = 0; j < i; ++j) {
            currentUVector -= aVectors[i].projectOnBasis(uVectors[j]);
        }
        uVectors.push_back(currentUVector);
        Q.insertColumnVector(currentUVector.unitize(), i);
        std::cout << "BOINK" << std::endl;
    }

    return Q;
}

Matrix buildU(Matrix &start) {
    auto U = Matrix(start.rowCount(), start.colCount());

    std::vector<Vector> aVectors;
    std::vector<Vector> uVectors;

    for(unsigned i = 0; i < start.colCount(); ++i) {
        aVectors.push_back(start.colVecFromMatrix(i));
    }

    for(unsigned i = 0; i < start.colCount(); ++i) {
        auto currentUVector = aVectors[i];
        for(unsigned j = 0; j < i; ++j) {
            currentUVector -= aVectors[i].projectOnBasis(uVectors[j]);
        }
        uVectors.push_back(currentUVector);
        U.insertColumnVector(currentUVector, i);
    }

    return U;
}


int main(int argc, char ** argv) {
    unsigned long n = (argc < 3) ? 3 : std::stoul(argv[1]);
    unsigned long m = (argc < 3) ? 3 : std::stoul(argv[2]);
    auto N = static_cast<unsigned>(n);
    auto M = static_cast<unsigned>(m);
    Matrix A(N, M);
    A(0, 0) = 12.0;
    A(0, 1) = -51.0;
    A(0, 2) = 4.0;
    A(1, 0) = 6.0;
    A(1, 1) = 167.0;
    A(1, 2) = -68.0;
    A(2, 0) = -4.0;
    A(2, 1) = 24.0;
    A(2, 2) = -41.0;

    auto oldA = A;
    std::cout << "OLDA:\n " << A << std::endl;
    auto Q = buildQ(oldA);
    std::cout << "Q:\n " << Q << std::endl;
    auto oldU = buildU(oldA);
    std::cout << "OLDU:\n " << oldU << std::endl;
    auto R = Q.transpose() * oldA;
    std::cout << "R:\n " << R << std::endl;
    auto newA = R * Q;
    auto newU = oldU * Q;

    return 0;
}

