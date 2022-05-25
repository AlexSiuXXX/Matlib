#ifndef MAT_H
#define MAT_H

#include "Vec.h"

#include <iostream>
#include <random>
#include <vector>
#include <cassert>

template <typename _MTp>
class Matrix {
public:
    
    /**
     * @brief Construct a new Matrix object
     * Assume All the matrix loop in row major
     */
    Matrix() {};
    Matrix(int r, int c);
    Matrix(int Sq);
    ~Matrix();


    /**
     * @brief 
     * Fill matrix with spec value
     * @param x 
     */
    void fill(const _MTp &x);
    void eyes();
    void zeros();


    void PrintMat();
    
    /**
     * @brief 
     * Generate Random Number given row and col size
     */
    void Random();

    /**
     * @brief 
     * Overloading Matrix-Matrix Addition, Subtraction, Multiplication
     * @param Rhs 
     * @return Matrix 
     */
    Matrix operator+(const Matrix& Rhs);
    Matrix operator-(const Matrix& Rhs);
    Matrix operator*(const Matrix& Rhs);
    /**
     * @brief 
     * Overloading Matrix-scalar Addition, Subtraction, Multiplication
     * @param Rhs 
     * @return Matrix 
     */
    Matrix operator+(const _MTp& scalar);
    Matrix operator-(const _MTp& scalar);
    Matrix operator*(const _MTp& scalar);

    

    unsigned rows() const { return Rows; }
    unsigned cols() const { return Cols; }
    unsigned size() const { return Rows * Cols; }

    /**
     * @brief 
     * Exchange whole row with row index r1 and r1, means row1 == row2 and row2 == row1
     * Exchange whole col with col index c1 and c1, means col1 == col2 and col2 == col1
     * @param r1 
     * @param r2 
     */
    void SwapRow(int r1, int r2);
    void SwapCol(int c1, int c2);

    /**
     * @brief 
     * Some utility function of matrix
     * @return _MTp 
     */
    _MTp sum();
    _MTp prod();
    _MTp trace();
    _MTp mean();
    _MTp maxx();
    _MTp minn();

    /**
     * @brief 
     * return position of 1d array given row index and col index
     * Mat[i][j] = Arr[i*Cols+j] in row-major style 
     * @param i 
     * @param j 
     * @return int 
     */
    int index(int i, int j) {
        return i*Cols+j; 
    }
    
    _MTp coeff(int i, int j) {
        return m_Mat[index(i, j)];
    }


    bool isSquare() {
        return Rows == Cols;
    }
    bool isSymmetric();

    Matrix mul_MatVec(Vector<_MTp> &Rhs) {
        Matrix<_MTp> resv(1, Cols);
       
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                resv.m_Mat[i] = m_Mat[i*Cols+j] * Rhs.v_Vec[j];
            }
        }
        return resv;
    }

    Matrix transpose();
    
public:
    std::vector<_MTp> m_Mat;
    int Rows;
    int Cols;
    
};


template <typename _MTp>
Matrix<_MTp>::Matrix(int r, int c): Rows(r), Cols(c) {
    m_Mat.resize(Rows*Cols); // dynamically allocate memory matrix with different size
}

template <typename _MTp>
Matrix<_MTp>::Matrix(int Sq): Rows(Sq), Cols(Sq) {
   
     m_Mat.resize(Rows*Cols); // dynamically allocate memory matrix, assume square matrix
}

template <typename _MTp>
Matrix<_MTp>::~Matrix() {
    
}

template <typename _MTp>
void Matrix<_MTp>::fill(const _MTp &x) {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = x;
        }
    }
}

template <typename _MTp>
void Matrix<_MTp>::zeros() {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = 0.0;
        }
    }
}

template <typename _MTp>
void Matrix<_MTp>::eyes() {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            if (i == j) {
                m_Mat[i*Cols+j] = 1.0;
            }
        }
    }
}

template <typename _MTp>
void Matrix<_MTp>::PrintMat() {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            std::cout << m_Mat[i*Cols+j] << "               ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}

template <typename _MTp>
void Matrix<_MTp>::Random() {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_real_distribution<double> dist(2.0, 15.0);

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[index(i, j)] = dist(rng);
        }
    }
    
}

template <typename _MTp>
Matrix<_MTp> Matrix<_MTp>::operator+(const Matrix<_MTp> &Rhs) {
    assert(Rows == Rhs.Rows && Cols == Rhs.Cols && "dim");
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = m_Mat[i*Cols+j] + Rhs.m_Mat[i*Cols+j];
        }
    }
    return *this;
}

template <typename _MTp>
Matrix<_MTp> Matrix<_MTp>::operator-(const Matrix<_MTp> &Rhs) {
    assert(Rows == Rhs.Rows && Cols == Rhs.Cols);
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = m_Mat[i*Cols+j] - Rhs.m_Mat[i*Cols+j];
        }
    }

    return *this;
}

template <typename _MTp>
Matrix<_MTp> Matrix<_MTp>::operator*(const Matrix<_MTp> &Rhs) {
    
    if (Cols != Rhs.Rows) std::cout << "Dim mismatch\n";
    
    Matrix<_MTp> res(Rows, Rhs.Cols);
    std::cout << " Dim: " << Rows << "   " << Rhs.Cols << "\n";
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Rhs.Cols; j++) {
            _MTp sum = 0.0;
            for (int k = 0; k < Rhs.Rows; k++) {
                sum += m_Mat[i*Cols+k] * Rhs.m_Mat[k*Rhs.Cols+j];   
            }
            res.m_Mat[i*Rhs.Cols+j] = sum;
        }
    }
    return res;
}

template <typename _MTp>
Matrix<_MTp> Matrix<_MTp>::operator+(const _MTp& scalar) {
    // if (Rows != Cols) std::cout << "Dim mismatch\n";
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = scalar + m_Mat[i*Cols+j];
        }
    }
    return *this;
}

template <typename _MTp>
Matrix<_MTp> Matrix<_MTp>::operator-(const _MTp& scalar) {
    // if (Rows != Cols) std::cout << "Dim mismatch\n";
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = scalar - m_Mat[i*Cols+j];
        }
    }

    return *this;
}

template <typename _MTp>
Matrix<_MTp> Matrix<_MTp>::operator*(const _MTp& scalar) {
    // if (Rows != Cols) std::cout << "Dim mismatch\n";
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            m_Mat[i*Cols+j] = scalar * m_Mat[i*Cols+j];
        }
    }

    return *this;
}



template <typename _MTp>
void Matrix<_MTp>::SwapRow(int r1, int r2) {
    _MTp tmp;
    for (int i = 0; i < Cols; i++) {
        tmp = m_Mat[index(r1, i)];
        m_Mat[index(r1, i )] = m_Mat[index(r2, i)];
        m_Mat[index(r2, i)] = tmp;
    }
}

template <typename _MTp>
void Matrix<_MTp>::SwapCol(int c1, int c2) {
    _MTp tmp;
    for (int i = 0; i < Rows; i++) {
        tmp = m_Mat[index(i, c1)];
        m_Mat[index(i, c1 )] = m_Mat[index(i, c2)];
        m_Mat[index(i ,c2)] = tmp;
    }
}


template <typename _MTp>
_MTp Matrix<_MTp>::sum() {
    _MTp N = 0.0;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            N += m_Mat[index(i, j)];
        }
    }

    return N;
}

template <typename _MTp>
_MTp Matrix<_MTp>::prod() {
    _MTp N = 1.0;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            N *= m_Mat[index(i, j)];
        }
    }

    return N;
}

template <typename _MTp>
_MTp Matrix<_MTp>::trace() {
    _MTp N = 1.0;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            if (i == j) {
                N += m_Mat[index(i, j)];
            }
        }
    }

    return N;
}


template <typename _MTp>
_MTp Matrix<_MTp>::mean() {
    return sum() / size();
}

template <typename _MTp>
_MTp Matrix<_MTp>::maxx() {
    _MTp maxEle = std::numeric_limits<_MTp>::min();
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            if (m_Mat[index(i, j)] > maxEle) {
                maxEle = m_Mat[index(i, j)];
            }
        }
    }

    return maxEle;

}

template <typename _MTp>
_MTp Matrix<_MTp>::minn() {
    _MTp minEle = std::numeric_limits<_MTp>::max();
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            if (m_Mat[index(i, j)] < minEle) {
                minEle = m_Mat[index(i, j)];
            }
        }
    }

    return minEle;
}



#endif