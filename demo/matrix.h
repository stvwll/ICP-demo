#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#ifndef _MSC_VER
#include <stdint.h>
#else
typedef signed __int8     int8_t;//typedef已有数据类型起别名,typedef 旧名  新名；
typedef signed __int16    int16_t;
typedef signed __int32    int32_t;
typedef signed __int64    int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;
#endif

#define endll endl << endl //宏定义，用endll代替字符串endl<<endl

typedef double FLOAT;
//typedef float  FLOAT;    

class Matrix {

public:

	Matrix();                                                  // init empty 0x0 matrix
	Matrix(const int32_t m, const int32_t n);                   // init empty mxn matrix
	Matrix(const int32_t m, const int32_t n, const FLOAT* val_); // init mxn matrix with values from array 'val'
	Matrix(const Matrix &M);                                   // creates deepcopy of M
	~Matrix();


	Matrix& operator= (const Matrix &M);//重载操作符=


	void getData(FLOAT* val_, int32_t i1 = 0, int32_t j1 = 0, int32_t i2 = -1, int32_t j2 = -1);


	Matrix getMat(int32_t i1, int32_t j1, int32_t i2 = -1, int32_t j2 = -1);
	void   setMat(const Matrix &M, const int32_t i, const int32_t j);


	void setVal(FLOAT s, int32_t i1 = 0, int32_t j1 = 0, int32_t i2 = -1, int32_t j2 = -1);


	void setDiag(FLOAT s, int32_t i1 = 0, int32_t i2 = -1);


	void zero();


	Matrix extractCols(std::vector<int> idx);


	static Matrix eye(const int32_t m);
	void          eye();


	static Matrix ones(const int32_t m, const int32_t n);


	static Matrix diag(const Matrix &M);


	static Matrix reshape(const Matrix &M, int32_t m, int32_t n);


	static Matrix rotMatX(const FLOAT &angle);
	static Matrix rotMatY(const FLOAT &angle);
	static Matrix rotMatZ(const FLOAT &angle);


	Matrix  operator+ (const Matrix &M); // add matrix
	Matrix  operator- (const Matrix &M); // subtract matrix
	Matrix  operator* (const Matrix &M); // multiply with matrix
	Matrix  operator* (const FLOAT &s);  // multiply with scalar
	Matrix  operator/ (const Matrix &M); // divide elementwise by matrix (or vector)
	Matrix  operator/ (const FLOAT &s);  // divide by scalar
	Matrix  operator- ();                // negative matrix
	Matrix  operator~ ();                // transpose转置
	FLOAT   l2norm();                   // euclidean norm (vectors) / frobenius norm (matrices)
	FLOAT   mean();                     // mean of all elements in matrix

	static Matrix cross(const Matrix &a, const Matrix &b);    // cross product of two vectors
	static Matrix inv(const Matrix &M);                       // invert matrix M
	bool   inv();                                             // invert this matrix
	FLOAT  det();                                             // returns determinant of matrix
	bool   solve(const Matrix &M, FLOAT eps = 1e-20);            // solve linear system M*x=B, replaces *this and M
	bool   lu(int32_t *idx, FLOAT &d, FLOAT eps = 1e-20);        // replace *this by lower upper decomposition
	void   svd(Matrix &U, Matrix &W, Matrix &V);                 // singular value decomposition *this = U*diag(W)*V^T

	friend std::ostream& operator<< (std::ostream& out, const Matrix& M);

	FLOAT   **val;
	int32_t   m, n;

private:

	void allocateMemory(const int32_t m_, const int32_t n_);
	void releaseMemory();
	inline FLOAT pythag(FLOAT a, FLOAT b);

};

#endif // MATRIX_H
