#include "maths.h"
#include <cmath>

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

void applyActivation(double** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			mat[i][j] = sigmoid(mat[i][j]);
}
// resultMatrix_(MxN) = aMatrix_(MxK) * bMatrix_(KxN)
void matMul(double** aMatrix, double** bMatrix, double** resultMatrix, int M, int K, int N) {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			resultMatrix[i][j] = 0;
			for (int k = 0; k < K; k++)
				resultMatrix[i][j] += aMatrix[i][k] * bMatrix[k][j];
		}
}
