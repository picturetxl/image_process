
#include "../include/Header.h"


Mat getHistograph(const Mat grayImage)
{
	//������ֱ��ͼ��ͨ����Ŀ����0��ʼ����
	int channels[] = { 0 };
	//����ֱ��ͼ����ÿһά�ϵĴ�С������Ҷ�ͼֱ��ͼ�ĺ�������ͼ��ĻҶ�ֵ����һά��bin�ĸ���
	//���ֱ��ͼͼ�������bin����Ϊx��������bin����Ϊy����channels[]={1,2}��ֱ��ͼӦ��Ϊ��ά�ģ�Z����ÿ��bin��ͳ�Ƶ���Ŀ
	const int histSize[] = { 256 };
	//ÿһάbin�ı仯��Χ
	float range[] = { 0,256 };

	//����bin�ı仯��Χ��������channelsӦ�ø�channelsһ��
	const float* ranges[] = { range };

	//����ֱ��ͼ�����������ֱ��ͼ����
	Mat hist;
	//opencv�м���ֱ��ͼ�ĺ�����hist��СΪ256*1��ÿ�д洢��ͳ�Ƶĸ��ж�Ӧ�ĻҶ�ֵ�ĸ���
	calcHist(&grayImage, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);//cv����cvCalcHist

	//�ҳ�ֱ��ͼͳ�Ƶĸ��������ֵ��������Ϊֱ��ͼ������ĸ�
	double maxValue = 0;
	//�Ҿ����������Сֵ����Ӧ�����ĺ���
	minMaxLoc(hist, 0, &maxValue, 0, 0);
	//���ֵȡ��
	int rows = cvRound(maxValue);
	//����ֱ��ͼͼ��ֱ��ͼ������ĸ���Ϊ����������Ϊ256(�Ҷ�ֵ�ĸ���)
	//��Ϊ��ֱ��ͼ��ͼ�������Ժڰ���ɫΪ���֣���ɫΪֱ��ͼ��ͼ��
	Mat histImage = Mat::zeros(rows, 256, CV_8UC1);

	//ֱ��ͼͼ���ʾ
	for (int i = 0; i < 256; i++)
	{
		//ȡÿ��bin����Ŀ
		int temp = (int)(hist.at<float>(i, 0));
		//���bin��ĿΪ0����˵��ͼ����û�иûҶ�ֵ��������Ϊ��ɫ
		//���ͼ�����иûҶ�ֵ���򽫸��ж�Ӧ������������Ϊ��ɫ
		if (temp)
		{
			//����ͼ�������������Ͻ�Ϊԭ�㣬����Ҫ���б任��ʹֱ��ͼͼ�������½�Ϊ����ԭ��
			histImage.col(i).rowRange(Range(rows - temp, rows)) = 255;
		}
	}
	//����ֱ��ͼͼ���и߿��ܸܺߣ���˽���ͼ�����Ҫ���ж�Ӧ��������ʹֱ��ͼͼ���ֱ��
	Mat resizeImage;
	resize(histImage, resizeImage, Size(256, 256));
	return resizeImage;
}