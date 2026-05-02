#include <iostream>
#include "maths.h"

using namespace std;

int main() {
	// 소수점 자리수 고정 (소수점 밑으로 3자리까지 나오도록)
	cout << fixed;
	cout.precision(3);

	// 신경망 층 수 입력받기
	int layerCount;
	cout << "신경망 층 수 입력: ";
	cin >> layerCount;

	// 각 층별 뉴런 수 입력받기
	int* neuronCount = new int[layerCount];
	cout << "각 층의 뉴런 수 입력: ";
	for (int i = 0; i < layerCount; i++)
		cin >> neuronCount[i];

	cout << endl;

	// 가중치 입력받기
	double*** weights = new double** [layerCount - 1]; // (layerCount - 1) by nextNeuronCount by currentNeuronCount
	for (int i = 0; i < layerCount - 1; i++) {
		int nextNeuronCount = neuronCount[i + 1], currentNeuronCount = neuronCount[i];
		cout << 'W' << i + 1 << " 가중치 입력 (" << nextNeuronCount << "x" << currentNeuronCount << "):" << endl;

		weights[i] = new double* [nextNeuronCount]; // nextNeuronCount by currentNeuronCount
		for (int j = 0; j < nextNeuronCount; j++) {
			weights[i][j] = new double [currentNeuronCount];

			for (int k = 0; k < currentNeuronCount; k++)
				cin >> weights[i][j][k];
		}

		cout << endl;
	}

	cout << "입력값 입력 (" << neuronCount[0] << "개):" << endl;
	double** inputMatrix = new double* [neuronCount[0]]; // neuronCount[0] by 1
	for (int i = 0; i < neuronCount[0]; i++) {
		inputMatrix[i] = new double[1];
		cin >> inputMatrix[i][0];
	}

	// 층별 계산하기
	int _rows = -1;
	for (int i = 0; i < layerCount - 1; i++) {
		int rows = neuronCount[i + 1], cols = neuronCount[i];
		_rows = rows;
		double** weightMatrix = weights[i]; // rows by cols

		double** resultMatrix = new double* [rows]; // rows by 1
		for (int j = 0; j < rows; j++)
			resultMatrix[j] = new double[1];

		// 행렬 곱 연산 및 활성화 함수 적용
		matMul(weightMatrix, inputMatrix, resultMatrix, rows, cols, 1);
		applyActivation(resultMatrix, rows, 1);


		// 기존 배열 해제
		for (int j = 0; j < cols; j++)
			delete[] inputMatrix[j];
		delete[] inputMatrix;

		// 새로운 input 배열 할당
		inputMatrix = new double* [rows]; // rows by 1
		for (int j = 0; j < rows; j++) {
			inputMatrix[j] = new double[1];
			inputMatrix[j][0] = resultMatrix[j][0];
		}

		// 출력
		if (i + 1 < layerCount - 1) {
			cout << endl << "은닉층 출력:" << endl;
			for (int j = 0; j < rows; j++)
				cout << "O_hidden[" << j << "] = " << inputMatrix[j][0] << endl;
		}

		// 해제
		// 기존 배열 해제
		for (int j = 0; j < rows; j++) {
			delete[] resultMatrix[j];
		}
		delete[] resultMatrix;
	}

	// 출력층 출력
	cout << endl << "출력층 출력:" << endl; // _rows by 1
	for (int i = 0; i < _rows; i++)
		cout << "O_output[" << i << "] = " << (int) inputMatrix[i][0] << ".xxx" << endl;

	// 해제
	// weights 먼저 해제
	for (int i = 0; i < layerCount - 1; i++) {
		int nextNeuronCount = neuronCount[i + 1];
		for (int j = 0; j < nextNeuronCount; j++)
			delete[] weights[i][j];
		delete[] weights[i];
	}
	delete[] weights;

	// inputMatrix 해제
	for (int i = 0; i < _rows; i++)
		delete[] inputMatrix[i];
	delete[] inputMatrix;

	// 마지막에 neuronCount
	delete[] neuronCount;
}
