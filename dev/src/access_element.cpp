
#include "../include/Header.h"


void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();  //��������ԭͼ���Ҷ�ͼƬ���ݲ��ִ���=>����,���ܼ򵥵ĸ�ֵ
	int rowNumber = outputImage.rows;  //����
	int colNumber = outputImage.cols * outputImage.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���

	for (int i = 0; i < rowNumber; i++)  //��ѭ��
	{
		uchar* data = outputImage.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		//���������൱�����������
		for (int j = 0; j < colNumber; j++)   
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}



void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();  //��������ԭͼ���Ҷ�ͼƬ���ݲ��ִ���=>����,���ܼ򵥵ĸ�ֵ
	//������
	//typedef Vec<uchar, 3> Vec3b;//��������uchar��Ԫ�ص�����
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //ָ����ǵ�һ��,��һ�е�����ͨ����ָ��
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();//ָ��������һ��,���һ�е�����ͨ����ָ��

	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;//B
		(*it)[1] = (*it)[1] / div * div + div / 2;//G
		(*it)[2] = (*it)[2] / div * div + div / 2;//R
	}
}



void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();  //��������ԭͼ���Ҷ�ͼƬ���ݲ��ִ���=>����,���ܼ򵥵ĸ�ֵ
	int rowNumber = outputImage.rows;  //����
	int colNumber = outputImage.cols;  //����

	//�͵���������,Ҳ��ָ������ͨ��������,ֻ�Ǳ�ʾ��ʽ��ͬ
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  //��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  //��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  //����ͨ��
		}      
	}
}
