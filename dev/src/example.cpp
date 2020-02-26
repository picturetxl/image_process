#include <opencv2/opencv.hpp>//包含了众多模块 一劳永逸

using namespace std;
using namespace cv;

/*
 *@function:opencv_1_1
 *@desc:读取图像,显示图像
 *@param:
**/
void opencv_1_1()
{
	Mat srcImage = imread("1.jpg");
	imshow("1", srcImage);
	waitKey(0);
}

/*
 *@function:opencv_1_2
 *@desc:腐蚀图像
 *@param:
**/
void opencv_1_2()
{
	Mat srcImage = imread("1.jpg");
	imshow("1", srcImage);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat destImg;
	erode(srcImage, destImg, element);
	imshow("腐蚀", destImg);

	waitKey(0);
}
/*
 *@function:opencv_1_3
 *@desc:均值滤波
 *@param:
**/
void opencv_1_3()
{
	Mat srcImage = imread("1.jpg");
	imshow("1", srcImage);

	Mat destImg;
	blur(srcImage, destImg, Size(7, 7));
	imshow("均值滤波", destImg);

	waitKey(0);
}
/*
 *@function:opencv_1_4
 *@desc:边缘检测
 *@param:
**/
void opencv_1_4()
{
	Mat srcImage = imread("fruits.jpg");
	imshow("1", srcImage);

	Mat destImage;
	Mat edge;
	Mat grayImage;
	//创建和原图同类型和大小的矩阵
	destImage.create(srcImage.size(), srcImage.type());
	//转换为灰度图像
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	//先使用3*3内核来降噪
	blur(grayImage, edge, Size(3, 3));
	//运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	imshow("Canny边缘检测", edge);


	waitKey(0);

}
/*
 *@function:opencv_1_5
 *@desc:读取视频
 *@param:
**/
void opencv_1_5()
{
	VideoCapture capture("1.avi");
	//capture.open("1.avi"); 和流一样

	while (true)
	{
		Mat frame;
		capture >> frame;
		imshow("读取视频", frame);
		waitKey(30);//延时30ms
	}
	waitKey(0);

}

/*
 *@function:opencv_1_6
 *@desc:读取摄像头
 *@param:
**/
void opencv_1_6()
{
	VideoCapture capture(0);//0表示摄像头

	while (true)
	{
		Mat frame;
		capture >> frame;
		imshow("读取视频", frame);
		waitKey(30);//延时30ms
	}
	waitKey(0);

}

/*
 *@function:opencv_1_7
 *@desc:读取摄像头并进行边缘检测
 *@param:
**/
void opencv_1_7()
{
	VideoCapture capture(0);//0表示摄像头
	Mat edges;
	while (true)
	{
		Mat frame;
		capture >> frame;
		//转换为灰度图像
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		//先使用3*3内核来降噪
		blur(edges, edges, Size(7, 7));
		//运行Canny算子
		Canny(edges, edges, 0, 30, 3);

		imshow("canny后的视频", edges);
		waitKey(30);
	}

}

/*
 *@function:print_opencv_version
 *@desc:打印版本
 *@param:
**/
void print_opencv_version()
{
	printf("version:" CV_VERSION);

}

int main()
{
    //测试每个函数
	print_opencv_version();

	return 0;
}