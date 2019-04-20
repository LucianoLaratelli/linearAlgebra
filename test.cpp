#define CATCH_CONFIG_MAIN
#include "catch2/single_include/catch2/catch.hpp"
#include "matrix.hpp"
#include "vector.hpp"

bool compareVectors(Vector lhs, Vector rhs) {
    auto x = lhs.getData();
    auto y = rhs.getData();
    auto N = lhs.size();
    bool result = true;
    for(int i = 0; i < N; i++) {
        if(x[i] != Approx(y[i])) {result = false; break;}
    }
    return result;
}

TEST_CASE("vector class") {
    auto v = Vector(5);
    auto w = Vector(5);
    REQUIRE(v.size() == 5);
    SECTION("vector equality operator") {
        REQUIRE(v == w);
    }
    for(int i = 0; i < 5; ++i) { v[i] = i * i; }
    SECTION("vector inequality operator") {
        REQUIRE(v != w);
    }
    for(int i = 0; i < 5; ++i) { w[i] = i * i * i;}
    SECTION("vector subtraction") {
        auto x = w - v;
        auto answer = Vector(5);
        answer[0] = 0;
        answer[1] = 0;
        answer[2] = 4;
        answer[3] = 18;
        answer[4] = 48;
        REQUIRE(x == answer);
    }
    SECTION("multiply vector by scalar") {
        auto x = w * 2;
        auto answer = Vector(5);
        answer[0] = 0;
        answer[1] = 2;
        answer[2] = 16;
        answer[3] = 54;
        answer[4] = 128;
        REQUIRE(x == answer);
    }
    SECTION("make unit vector") {
        auto x = w.unitize();
        auto answer = Vector(5);
        answer[0] = 0.0;
        answer[1] = 1.0/std::sqrt(4890);
        answer[2] = 4.0 * std::sqrt(2.0/2445);
        answer[3] = 9.0 * std::sqrt(3.0/1630);
        answer[4] = 32.0 * std::sqrt(2.0/2445.0);
        REQUIRE(compareVectors(x, answer));
    }
    SECTION("vector norm") {
        auto x = w.norm();
        REQUIRE(x == Approx(69.9285));
    }
    SECTION("vector pojection") {
        auto w = Vector(5);
        auto v = Vector(5);
        for(int i = 0; i < 5; ++i) { w[i] = i * i * i;}
        for(int i = 0; i < 5; ++i) { v[i] = i * i;}
        auto x = w.projectOnBasis(v);
        auto answer = Vector(5);
        answer[0] = 0.0;
        answer[1] = 650.0 / 177.0;
        answer[2] = 2600.0/177.0;
        answer[3] = 1950.0/59.0;
        answer[4] = 10400.0/177.0;
        REQUIRE(x == answer);
    }
}

TEST_CASE("matrix class") {
    SECTION("equality operator") {
        Matrix m(2,2);
        Matrix n(2,2);
        m(0,0) = 2;
        m(0,1) = 8;
        m(1,0) = -10;
        m(1,1) = 20;

        n(0,0) = 2;
        n(0,1) = 8;
        n(1,0) = -10;
        n(1,1) = 20;
        REQUIRE(m == n);
    }
    SECTION("transpose works for square matrix") {
        Matrix m(3,3);
        m(0,0) = 0;
        m(0,1) = 1;
        m(0,2) = 2;
        m(1,0) = 3;
        m(1,1) = 4;
        m(1,2) = 5;
        m(2,0) = 6;
        m(2,1) = 7;
        m(2,2) = 8;
        Matrix mT(3,3);
        mT(0,0) = 0;
        mT(0,1) = 3;
        mT(0,2) = 6;
        mT(1,0) = 1;
        mT(1,1) = 4;
        mT(1,2) = 7;
        mT(2,0) = 2;
        mT(2,1) = 5;
        mT(2,2) = 8;
        REQUIRE(m.transpose() == mT);
    }

    SECTION("transpose works for non-square matrix") {
        Matrix m(3,2);
        m(0,0) = 0;
        m(0,1) = 1;
        m(1,0) = 2;
        m(1,1) = 3;
        m(2,0) = 4;
        m(2,1) = 5;
        Matrix mT(2,3);
        mT(0,0) = 0;
        mT(0,1) = 2;
        mT(0,2) = 4;
        mT(1,0) = 1;
        mT(1,1) = 3;
        mT(1,2) = 5;
        REQUIRE(m.transpose() == mT);
    }
    SECTION("multiply square matrices") {
        Matrix a(2,2);
        a(0,0) = 1;
        a(0,1) = 2;
        a(1,0) = 3;
        a(1,1) = 4;
        Matrix b(2,2);
        b(0,0) = 5;
        b(0,1) = 6;
        b(1,0) = 7;
        b(1,1) = 8;
        Matrix expected(2,2);
        expected(0,0) = 19;
        expected(0,1) = 22;
        expected(1,0) = 43;
        expected(1,1) = 50;

        auto answer = a * b;

        REQUIRE(answer == expected);
    }
    SECTION("multiply non-square matrices") {
        Matrix a(2,3);
        a(0,0) = 1;
        a(0,1) = 2;
        a(0,2) = 3;
        a(1,0) = 4;
        a(1,1) = 3;
        a(1,2) = 4;
        Matrix b(3,2);
        b(0,0) = 5;
        b(1,0) = 6;
        b(2,0) = 7;
        b(0,1) = 8;
        b(1,1) = 3;
        b(2,1) = 4;

        Matrix expected(2,2);
        expected(0,0) = 38;
        expected(0,1) = 26;
        expected(1,0) = 66;
        expected(1,1) = 57;
        auto answer = a * b;

        REQUIRE(answer == expected);
    }
    SECTION("column vectors retrieved properly") {
        Matrix m(3,3);
        m(0,0) = 0;
        m(0,1) = 1;
        m(0,2) = 2;
        m(1,0) = 3;
        m(1,1) = 4;
        m(1,2) = 5;
        m(2,0) = 6;
        m(2,1) = 7;
        m(2,2) = 8;
        Vector v(3);
        v = m.colVecFromMatrix(0);
        Vector expected(3);
        expected[0] = 0;
        expected[1] = 3;
        expected[2] = 6;
        REQUIRE(v == expected);
    }
}



