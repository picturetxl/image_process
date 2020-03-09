#include "../include/Header.h"

extern int g_nContrastValue; //对比度值
extern int g_nBrightValue;  //亮度值

//改变亮度和对比度的回调函数
void ContrastAndBright(int, void*usrdata)
{
	//解析回调函数的
	Mat srcImage = *((Mat *)usrdata);
	Mat dstImage = *(((Mat *)usrdata)+1);


	// 三个for循环，执行运算 dstImage(i,j) = a*srcImage(i,j) + b
	for (int i = 0; i < srcImage.rows; i++)
	{
		for (int j = 0; j < srcImage.cols; j++)
		{
			for (int c = 0; c < 3; c++)//RGB 三个通道
			{//乘以0.01 是因为一般对比度在0.0到3.0之间的浮点数会有明显效果
				//又因为滑动条上的值是整数,所以用到这个转换
				dstImage.at<Vec3b>(i, j)[c] = //saturate_cast<uchar>将计算的结果转为整数
					saturate_cast<uchar>((g_nContrastValue * 0.01) * (srcImage.at<Vec3b>(i, j)[c]) + g_nBrightValue);
			}
		}
	}
	cout << "------------------" << endl;
	cout << g_nBrightValue << endl;
	cout << g_nContrastValue << endl;
	cout << "------------------" << endl;
	// 显示图像
	imshow("【效果图窗口】", dstImage);
}

