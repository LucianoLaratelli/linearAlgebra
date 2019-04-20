#include <vector>
#include "matrix.hpp"
#include "vector.hpp"

std::pair<Matrix, Matrix> buildQAndR(const Matrix& start) {
    Matrix Q = Matrix(start.rowCount(), start.colCount());
    Matrix U = Matrix(start.rowCount(), start.colCount());

    std::vector<Vector> aVectors;
    std::vector<Vector> uVectors;

    for (unsigned i = 0; i < start.colCount(); ++i) {
        aVectors.push_back(start.colVecFromMatrix(i));
    }

    for (unsigned i = 0; i < start.colCount(); ++i) {
        auto currentUVector = aVectors[i];
        for (unsigned j = 0; j < i; ++j) {
            currentUVector -= aVectors[i].projectOnBasis(uVectors[j]);
        }
        uVectors.push_back(currentUVector);
        Q.insertColumnVector(currentUVector.unitize(), i);
        U.insertColumnVector(currentUVector, i);
    }

    return std::pair<Matrix, Matrix>(Q, U);
}

Matrix QRDecomposition(const Matrix &start) {
    auto oldA = start;
    auto QU = buildQAndR(oldA);
    auto Q = QU.first;
    auto oldU = QU.second;
    auto R = Q.transpose() * oldA;
    auto newA = R * Q;
    auto newU = oldU * Q;
    oldU = newU;
    oldA = newA;
    for (int i = 0; i < 1000; ++i) {
        QU = buildQAndR(oldA);
        Q = QU.first;
        oldU = QU.second;
        R = Q.transpose() * oldA;
        newA = R * Q;
        newU = oldU * Q;
        oldU = newU;
        oldA = newA;
    }
    return newA;
}

int main(int argc, char ** argv) {
    int64_t n = (argc < 3) ? 3 : std::stoul(argv[1]);
    int64_t m = (argc < 3) ? 3 : std::stoul(argv[2]);
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
    std::cout << QRDecomposition(A) << std::endl;
}

