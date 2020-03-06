
#include "../include/Header.h"


void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();  //不作用在原图上且对图片数据部分处理=>拷贝,不能简单的赋值
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols * outputImage.channels();  //列数 x 通道数=每一行元素的个数

	for (int i = 0; i < rowNumber; i++)  //行循环
	{
		uchar* data = outputImage.ptr<uchar>(i);  //获取第i行的首地址
		//接下来就相当于数组操作了
		for (int j = 0; j < colNumber; j++)   
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}



void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();  //不作用在原图上且对图片数据部分处理=>拷贝,不能简单的赋值
	//迭代器
	//typedef Vec<uchar, 3> Vec3b;//含有三个uchar的元素的向量
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //指向的是第一行,第一列的三个通道的指针
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();//指向的是最后一行,最后一列的三个通道的指针

	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;//B
		(*it)[1] = (*it)[1] / div * div + div / 2;//G
		(*it)[2] = (*it)[2] / div * div + div / 2;//R
	}
}



void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();  //不作用在原图上且对图片数据部分处理=>拷贝,不能简单的赋值
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols;  //列数

	//和迭代器类似,也是指向了三通道的像素,只是表示形式不同
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  //蓝色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  //绿色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  //红是通道
		}      
	}
}
