#ifndef __MATHS_H__
#define __MATHS_H__

// 시그모이드 함수
double sigmoid(double x);

// 행렬 전체 성분에 대해 시그모이드 함수 적용
void applyActivation(double** mat, int rows, int cols);

// 행렬 곱 함수
// resultMatrix_(MxN) = aMatrix_(MxK) * bMatrix_(KxN)
void matMul(double** aMatrix, double** bMatrix, double** resultMatrix, int M, int K, int N);

#endif
