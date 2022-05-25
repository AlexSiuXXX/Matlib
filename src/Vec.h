#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <random>
#include <vector>

template <typename _VTp>
class Vector {
public:
    Vector();
    Vector(int s);

    /**
     * @brief 
     * Print Vector
     */

    void PrintVec() {
        for (int i = 0; i < Size; i++) {
            if (i % 10 == 0) std::cout << "\n";
            std::cout << v_Vec[i] << "    ";
            
        }
        std::cout << "\n";
    }

    /**
     * @brief 
     * Generate Random Number given Size
     */
    void RandomV();
    /**
     * @brief 
     * Overloading Vector-Vector Addition, Subtraction, Multiplication
     * @param Rhs 
     * @return Matrix 
     */
    Vector operator+(const Vector& Rhs);
    Vector operator-(const Vector& Rhs);
    Vector operator*(const Vector& Rhs);

    /**
     * @brief 
     * Overloading Vector-Scalar Addition, Subtraction, Multiplication
     * @param Rhs 
     * @return Matrix 
     */
    Vector operator+(const _VTp& scalar);
    Vector operator-(const _VTp& scalar);
    Vector operator*(const _VTp& scalar);


    /**
     * @brief 
     * return value after dot product of two vector
     */
    _VTp dot(const Vector& Rhs);



public:
    std::vector<_VTp> v_Vec;
    int Size;
    
};

template <typename _VTp>
Vector<_VTp>::Vector()
{
}

template <typename _VTp>
Vector<_VTp>::Vector(int s): Size(s) {
    v_Vec.resize(Size);
}

template <typename _VTp>
void Vector<_VTp>::RandomV() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dist(1.0, 2.0);

    for (int i = 0; i < Size; i++) {
        v_Vec[i] = dist(rng);
    }
}

template <typename _VTp>
Vector<_VTp> Vector<_VTp>::operator+(const Vector& Rhs) {
    for (int i = 0; i < Size; i++) {
        v_Vec[i] = v_Vec[i] + Rhs.v_Vec[i];
    }
    return *this;
}

template <typename _VTp>
Vector<_VTp> Vector<_VTp>::operator-(const Vector& Rhs) {
    for (int i = 0; i < Size; i++) {
        v_Vec[i] = v_Vec[i] - Rhs.v_Vec[i];
    }
    return *this;
}

template <typename _VTp>
Vector<_VTp> Vector<_VTp>::operator*(const Vector& Rhs) {
    for (int i = 0; i < Size; i++) {
        v_Vec[i] = v_Vec[i] * Rhs.v_Vec[i];
    }
    return *this;
}

template <typename _VTp>
Vector<_VTp> Vector<_VTp>::operator+(const _VTp& scalar) {
    for (int i = 0; i < Size; i++) {
        v_Vec[i] = v_Vec[i] * scalar;
    }
    return *this;
}

template <typename _VTp>
Vector<_VTp> Vector<_VTp>::operator-(const _VTp& scalar) {
    for (int i = 0; i < Size; i++) {
        v_Vec[i] = v_Vec[i] - scalar;
    }
    return *this;
}

template <typename _VTp>
Vector<_VTp> Vector<_VTp>::operator*(const _VTp& scalar) {
    for (int i = 0; i < Size; i++) {
        v_Vec[i] = v_Vec[i] * scalar;
    }
    return *this;
}


template <typename _VTp>
_VTp Vector<_VTp>::dot(const Vector& Rhs) {
    _VTp resDot = 0.0;

    for (int i = 0; i < Size; i++) {
        resDot += v_Vec[i] * Rhs.v_Vec[i];
    }

    return resDot;
}

#endif