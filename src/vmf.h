#pragma once

#include <opencv2/core/core.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

namespace vmf {


	int calcDistanceMatrix(int* window, int size, int c) {

		double *distanceMatrix = new double[size*size]();
		double *rp, *cp;
		rp = distanceMatrix; //distance matrix columns pointer
		cp = distanceMatrix; //distance matrix rows pointer
		int *wp; //window pointer
		wp = window;
		int start[3] = { 0 };

		for (int i = 0; i < size; i++) {
			rp = rp + i + 1;
			cp = cp + size * (i + 1);

			for (int k = 0; k < c; k++) {
				start[k] = *wp;
				*wp++;
			}

			for (int j = 0; j < size - i - 1; j++) {
				double sum = 0;
				for (int l = 0; l < c; l++) {
					sum += pow(start[l] - (*wp), 2);
					wp++;
				}
				double dist = sqrt(sum);
				*rp = dist;
				*cp = dist;

				rp++;
				cp += size;
			}
			wp = &window[(i + 1)*c];
			cp = &distanceMatrix[i + 1];
		}

		cout << endl << endl;
		for (int i = 1; i <= size*size; i++) {
			cout << distanceMatrix[i - 1] << " ";
			if (i % 9 == 0) cout << endl;
		}

		delete[] distanceMatrix;
		return 1;

	}

	int calcPixelsWindow(unsigned char *p, int *window, int rows, int cols, int c, int n) {
		if (rows < n || cols < n || n < 1) {
			return -1;
		}
		int *wp; //window pointer
		wp = window;

		for (int i = 0; i < rows - (n - 1); i++) {
			for (int j = 0; j < cols - (n - 1); j++) {
				for (int k = 0; k < n; k++) {
					for (int l = 0; l < n; l++) {
						for (int m = 0; m < c; m++) {
							//cout << (int)*p << " ";
							*wp = (int)*p;
							wp++;
							p++; //grayscale or rgb values
						}
						p = p - c; //return after above changes
						p = p + cols * c;  // rows of window
					}
					p = p - n * cols * c + c; // columns of window
				}
				wp = &window[0];
				p = p - (n - 1) * c; // columns of matrix
			}
			p = p + (n - 1) * c; // rows of matrix
		}
		return 1;
	}

	void createPixelsWindow(Mat image, unsigned int size) {

		unsigned char *p = (unsigned char*)(image.data);
		const int c = image.channels();
		const int n = size;
		int* window = new int[n*n*c];
		calcPixelsWindow(p, window, image.rows, image.cols, c, n);
		for (int a = 0; a < n*n*c; a++) {
			cout << window[a] << " ";
		}
		delete[] window;
	}


	int vmfFilter(Mat image) {
		return -1;
	}

}