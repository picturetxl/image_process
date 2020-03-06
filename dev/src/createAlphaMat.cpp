
#include "../include/Header.h"


// ������alphaͨ����Mat
void createAlphaMat(Mat& mat)
{
	for (size_t i = 0; i < mat.rows; i++)
	{
		for (size_t j = 0; j < mat.cols; j++)
		{
			Vec4b& rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / (((float)mat.cols) * UCHAR_MAX));
			rgba[1] = saturate_cast<uchar>((float(mat.rows - j)) / (((float)mat.rows) * UCHAR_MAX));
			rgba[2] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}


//����һ������alphaͨ����ͼ��
int create_alpha_img()
{
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int> compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	//����д�����
	try
	{
		imwrite("alpha.png", mat, compression_params);
		imshow("alpha", mat);
		cout << "saved" << endl;
		waitKey(0);

	}
	catch (const std::exception & ex)
	{
		cerr << ex.what();
		return 1;
	}

}
