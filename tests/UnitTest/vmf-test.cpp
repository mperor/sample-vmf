#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../src/vmf.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSampleVMF
{
	TEST_CLASS(UnitTestSampleVMF)
	{
	public:

		TEST_METHOD(TestCalcPixelsWindow_Window2by2InMatrix5by5_ExpectedWindow)
		{
			Mat example_image_5by5 = (Mat_<unsigned char>(5, 5) <<
				11, 12, 13, 14, 15,
				21, 22, 23, 24, 25,
				31, 32, 33, 34, 35,
				41, 42, 43, 44, 45,
				51, 52, 53, 54, 55);

			unsigned int expected_window[4] = { 44, 54, 45, 55 };
			const int window_size = 2;
			
			unsigned char *p = (unsigned char*)(example_image_5by5.data);
			const int c = example_image_5by5.channels();
			
			unsigned int* window = new unsigned int[window_size*window_size*c];

			vmf::calcPixelsWindow(p, window, example_image_5by5.rows, example_image_5by5.cols, c, window_size);
			for (int i = 0; i < window_size*window_size*c; i++) {
				Assert::AreEqual(expected_window[i], window[i]);
			}

			delete[] window;
			delete[] expected_window;
		}

		TEST_METHOD(TestCalcPixelsWindow_Window4by4InMatrix3by3_ReturnMinus1)
		{
			Mat example_image_3by3 = (Mat_<unsigned char>(3, 3) <<
				11, 12, 13,
				21, 22, 23,
				31, 32, 33);

			const int window_size = 4;
			unsigned char *p = (unsigned char*)(example_image_3by3.data);
			const int c = example_image_3by3.channels();

			unsigned int* window = new unsigned int[window_size*window_size*c];

			int result = vmf::calcPixelsWindow(p, window, example_image_3by3.rows, example_image_3by3.cols, c, window_size);
			Assert::AreEqual(-1, result);

			delete[] window;
		}

		TEST_METHOD(TestCalcPixelsWindow_WindowSize0InMatrix3by3_ReturnMinus1)
		{
			Mat example_image_3by3 = (Mat_<unsigned char>(3, 3) <<
				11, 12, 13,
				21, 22, 23,
				31, 32, 33);

			const int window_size = 0;
			unsigned char *p = (unsigned char*)(example_image_3by3.data);
			const int c = example_image_3by3.channels();

			unsigned int* window = new unsigned int[window_size*window_size*c];

			int result = vmf::calcPixelsWindow(p, window, example_image_3by3.rows, example_image_3by3.cols, c, window_size);
			Assert::AreEqual(-1, result);

			delete[] window;
		}

		TEST_METHOD(TestCalcPixelsWindow_Window2by2InMatrix2by2_ExpectedWindow)
		{
			Mat example_image_2by2 = (Mat_<unsigned char>(2, 2) <<
				11, 12, 
				21, 22);

			unsigned int expected_window[4] = { 11, 21, 12, 22 };
			const int window_size = 2;

			unsigned char *p = (unsigned char*)(example_image_2by2.data);
			const int c = example_image_2by2.channels();

			unsigned int* window = new unsigned int[window_size*window_size*c];

			vmf::calcPixelsWindow(p, window, example_image_2by2.rows, example_image_2by2.cols, c, window_size);
			for (int i = 0; i < window_size*window_size*c; i++) {
				Assert::AreEqual(expected_window[i], window[i]);
			}

			delete[] window;
			delete[] expected_window;
		}

		TEST_METHOD(TestCalcPixelsWindow_Window1by1InMatrix2by2_ExpectedWindow)
		{
			Mat example_image_2by2 = (Mat_<unsigned char>(2, 2) <<
				11, 12,
				21, 22);

			unsigned int expected_window[1] = { 22 };
			const int window_size = 1;

			unsigned char *p = (unsigned char*)(example_image_2by2.data);
			const int c = example_image_2by2.channels();

			unsigned int* window = new unsigned int[window_size*window_size*c];

			vmf::calcPixelsWindow(p, window, example_image_2by2.rows, example_image_2by2.cols, c, window_size);
			for (int i = 0; i < window_size*window_size*c; i++) {
				Assert::AreEqual(expected_window[i], window[i]);
			}

			delete[] window;
			delete[] expected_window;
		}

		TEST_METHOD(TestCalcPixelsWindow_Window2by2InRgbMatrix2by2_ExpectedWindow)
		{
			Mat example_rgb_image_2by2(2, 2, CV_8UC3, Scalar(1, 100, 255));

			unsigned int expected_window[4*3] = { 1, 100, 255, 1, 100, 255, 1, 100, 255, 1, 100, 255 };
			const int window_size = 2;

			unsigned char *p = (unsigned char*)(example_rgb_image_2by2.data);
			const int c = example_rgb_image_2by2.channels();

			unsigned int* window = new unsigned int[window_size*window_size*c];

			vmf::calcPixelsWindow(p, window, example_rgb_image_2by2.rows, example_rgb_image_2by2.cols, c, window_size);
			for (int i = 0; i < window_size*window_size*c; i++) {
				Assert::AreEqual(expected_window[i], window[i]);
			}

			delete[] window;
			delete[] expected_window;
		}

	};
}