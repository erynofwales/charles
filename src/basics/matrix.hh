/* matrix.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_MATRIX_HH__
#define __BASICS_MATRIX_HH__

#include <cassert>
#include <cstring>
#include <type_traits>

#include "basics/types.hh"


namespace charles {
namespace basics {

/**
 * A generic, templated Matrix class taking two template parameters. `N` is the
 * number of rows. `M` is the number of columns.
 */
template<uint N, uint M>
struct Matrix
{
    /** Construct an N x M matrix of zeros. */
    static Matrix<N,M> Zero();

    /** Construct an N x M identity matrix. */
    static Matrix<N,M> Identity();

    /** Value accessor. Get the ij'th item. */
    Double& operator(uint i, uint j);

    /** Scalar multiplication */
    Matrix<N,M> operator*(const Double& lhs) const;

    /** Matrix multiplication */
    template<uint P>
    Matrix<N,P> operator*(Matrix<M,P> lhs) const;

    const Double* CArray() const;

private:
    /** The matrix data, stored in row-major format. */
    Double mData[N * M];
};


/** Scalar multiplication, scalar factor on the left. */
template<uint N, uint M>
Matrix<N,M> operator*(const Double& lhs, const Matrix<N,M>& rhs);


/*
 * charles::basics::Matrix<>::Zero --
 */
template<uint N, uint M>
Matrix<N,M>
Matrix<N,M>::Zero()
{
    Matrix<N,M> m;
    bzero(m.mData, sizeof(Double) * N * M);
    return m;
}


/*
 * charles::basics::Matrix<>::Identity --
 */
template<uint N, uint M>
Matrix<N,M>
Matrix<N,M>::Identity()
{
    static_assert(N == M, "Identity matrices must be square.");

    auto m = Matrix<N,M>::Zero();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j) {
                m(i,j) = 1.0;
            }
        }
    }
    return m;
}


/*
 * charles::basics::Matrix<>::operator() --
 */
template<uint N, uint M>
Double&
Matrix<N,M>::operator()(uint i, uint j)
{
    assert(i < N && j < M);
    return mData[i * N + j];
}


/*
 * charles::basics::Matrix<>::operator* --
 */
template<uint N, uint M>
Matrix<N,M>
Matrix<N,M>::operator*(const Double& lhs)
    const
{
    Matrix<N,M> result;
    for (int i = 0; i < N*M; i++) {
        result.mData = mData[i] * lhs;
    }
    return result;
}


/*
 * charles::basics::Matrix<>::operator* --
 */
template<uint N, uint M>
template<uint P>
Matrix<N,P>
Matrix<N,M>::operator*(Matrix<M,P> lhs)
    const
{
    Matrix<N,P> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            /* Each cell is Sigma(k=0, M)(lhs[ik] * rhs[kj]) */
            const int ij = i*N + j;
            mCells[ij] = 0.0;
            for (int k = 0; k < M; k++) {
                result.mCells[ij] += mCells[i*N + k] * rhs.mCells[k*P + j];
            }
        }
    }
    return result;
}


/*
 * charles::basics::Matrix<>::CArray --
 */
template<uint N, uint M>
const Double*
Matrix<N,M>::CArray()
    const
{
    return mData;
}


/*
 * charles::basics::operator* --
 */
template<uint N, uint M>
Matrix<N,M>
operator*(const Double& lhs,
          const Matrix<N,M>& rhs)
{
    return rhs * lhs;
}

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_MATRIX_HH__ */
