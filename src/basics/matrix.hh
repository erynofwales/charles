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
 * number of rows. `M` is the number of columns. If `M` is not specified, the
 * matrix will be square.
 */
template<UInt N, UInt M = N>
struct Matrix
{
    /** Construct an N x M matrix of zeros. */
    static Matrix<N,M> Zero();

    /**
     * Construct an N x M identity matrix. Identity matrices are always square.
     * It is a (compile time) error to call Identity on a Matrix class where
     * N != M.
     */
    static Matrix<N,M> Identity();

    Matrix();
    Matrix(const Double data[N*M]);
    Matrix(const Matrix<N,M>& rhs);

    Matrix<N,M>& operator=(const Matrix<N,M>& rhs);

    bool operator==(const Matrix<N,M>& rhs) const;
    bool operator!=(const Matrix<N,M>& rhs) const;

    /** Value accessor. Get the ij'th item. */
    Double& operator()(UInt i, UInt j);

    /**
     * @defgroup Scalar multiplication
     * @{
     */
    Matrix<N,M> operator*(const Double& rhs) const;
    Matrix<N,M>& operator*=(const Double& rhs);
    Matrix<N,M> operator/(const Double& rhs) const;
    Matrix<N,M>& operator/=(const Double& rhs);
    /** @} */

    /** Matrix multiplication */
    template<UInt P>
    Matrix<N,P> operator*(Matrix<M,P> rhs) const;

    /** Get the underlying C array */
    const Double* CArray() const;

protected:
    /** The matrix data, stored in row-major format. */
    Double mData[N * M];
};


/** Scalar multiplication, scalar factor on the left. */
template<UInt N, UInt M>
Matrix<N,M> operator*(const Double& lhs, const Matrix<N,M>& rhs);


/** A standard 4x4 matrix. */
typedef Matrix<4> Matrix4;


/**
 * Create a translation matrix that will translate a vector to the given
 * coordinates.
 */
Matrix4 TranslationMatrix(const Double& x, const Double& y, const Double& z);

#pragma mark Static Methods

/*
 * charles::basics::Matrix<>::Zero --
 */
template<UInt N, UInt M>
/* static */ Matrix<N,M>
Matrix<N,M>::Zero()
{
    Matrix<N,M> m;
    bzero(m.mData, sizeof(Double) * N * M);
    return m;
}


/*
 * charles::basics::Matrix<>::Identity --
 */
template<UInt N, UInt M>
/* static */ Matrix<N,M>
Matrix<N,M>::Identity()
{
    static_assert(N == M, "Identity matrices must be square.");

    auto m = Matrix<N,M>::Zero();
    for (size_t i = 0; i < N; i++) {
        m(i,i) = 1.0;
    }
    return m;
}

#pragma mark Instance Methods

/*
 * charles::basics::Matrix<>::Matrix --
 */
template<UInt N, UInt M>
Matrix<N,M>::Matrix()
    : mData()
{ }


/*
 * charles::basics::Matrix<>::Matrix --
 */
template<UInt N, UInt M>
Matrix<N,M>::Matrix(const Double data[N*M])
{
    memcpy(mData, data, sizeof(Double) * N * M);
}


/*
 * charles::basics::Matrix<>::Matrix --
 */
template<UInt N, UInt M>
Matrix<N,M>::Matrix(const Matrix<N,M>& rhs)
    : Matrix(rhs.mData)
{ }


/*
 * charles::basics::Matrix<>::operator= --
 */
template<UInt N, UInt M>
Matrix<N,M>&
Matrix<N,M>::operator=(const Matrix<N,M>& rhs)
{
    memcpy(mData, rhs.mData, sizeof(Double) * N * M);
    return *this;
}


/*
 * charles::basics::Matrix<>::operator== --
 */
template<UInt N, UInt M>
bool
Matrix<N,M>::operator==(const Matrix<N,M>& rhs)
    const
{
    for (int i = 0; i < N*M; i++) {
        /* TODO: Use NearlyEqual. */
        if (mData[i] != rhs.mData[i]) {
            return false;
        }
    }
    return true;
}


/*
 * charles::basics::Matrix<>::operator!= --
 */
template<UInt N, UInt M>
bool
Matrix<N,M>::operator!=(const Matrix<N,M>& rhs)
    const
{
    return !(*this == rhs);
}


/*
 * charles::basics::Matrix<>::operator() --
 */
template<UInt N, UInt M>
Double&
Matrix<N,M>::operator()(UInt i, UInt j)
{
    assert(i < N && j < M);
    return mData[i * N + j];
}


/*
 * charles::basics::Matrix<>::operator* --
 */
template<UInt N, UInt M>
Matrix<N,M>
Matrix<N,M>::operator*(const Double& rhs)
    const
{
    return Matrix<N,M>(*this) *= rhs;
}


template<UInt N, UInt M>
Matrix<N,M>&
Matrix<N,M>::operator*=(const Double& rhs)
{
    for (size_t i = 0; i < N*M; i++) {
        mData[i] *= rhs;
    }
    return *this;
}


template<UInt N, UInt M>
Matrix<N,M>
Matrix<N,M>::operator/(const Double& rhs)
    const
{
    return Matrix<N,M>(*this) /= rhs;
}


template<UInt N, UInt M>
Matrix<N,M>&
Matrix<N,M>::operator/=(const Double& rhs)
{
    return *this *= (1.0 / rhs);
}


/*
 * charles::basics::Matrix<>::operator* --
 */
template<UInt N, UInt M>
template<UInt P>
Matrix<N,P>
Matrix<N,M>::operator*(Matrix<M,P> rhs)
    const
{
    Matrix<N,P> result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            /* Each cell is Sigma(k=0, M)(lhs[ik] * rhs[kj]) */
            const int ij = i*N + j;
            mData[ij] = 0.0;
            for (int k = 0; k < M; k++) {
                result.mData[ij] += mData[i*N + k] * rhs.mData[k*P + j];
            }
        }
    }
    return result;
}


/*
 * charles::basics::Matrix<>::CArray --
 */
template<UInt N, UInt M>
const Double*
Matrix<N,M>::CArray()
    const
{
    return mData;
}


/*
 * charles::basics::operator* --
 */
template<UInt N, UInt M>
Matrix<N,M>
operator*(const Double& lhs,
          const Matrix<N,M>& rhs)
{
    return rhs * lhs;
}

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_MATRIX_HH__ */
