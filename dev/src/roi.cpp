#include "../include/Header.h"


//���ø���Ȥ����ROIʵ��ͼ�����
bool  ROI_AddImage()
{

	Mat src = imread("dota_pa.jpg");
	Mat logo = imread("dota_logo.jpg");

	if (!src.data) { cerr<<"��ȡsrcImage1����~�� \n"; return false; }
	if (!logo.data) { cerr<<"��ȡlogoImage����~�� \n"; return false; }

	cout << src.cols <<"*"<< src.rows << endl;//800*450
	cout << logo.cols <<"*"<< logo.rows << endl;//200*200

	//�������Ȥ�ĵط�
	Mat imageROI = src(Rect(200, 250, logo.cols, logo.rows));

	Mat mask = imread("dota_logo.jpg", 0);//�Ҷ�ͼ

	//ʹ��mask�ڶ�������,ʹ��ͼ���Ե����ɫ��ԭͼ����һ��
	logo.copyTo(imageROI, mask);

	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
	imshow("<1>����ROIʵ��ͼ�����ʾ������", src);

	return true;
}


//���Ի��ʵ�ֺ���,ָ����������ͼ����
bool  ROI_LinearBlending()
{

	Mat src = imread("dota_pa.jpg", 1);
	Mat logo = imread("dota_logo.jpg");

	if (!src.data) { cerr << "��ȡsrcImage1����~�� \n"; return false; }
	if (!logo.data) { cerr << "��ȡlogoImage����~�� \n"; return false; }

	Mat imageROI;//ROI
	//����һ
	imageROI = src(Rect(200, 250, logo.cols, logo.rows));//��src�еľ���������в���,�����������ΪimageROI

	//������
	//imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//���Ի��
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);//��imageROI��logo�������Ի��,����imageROI

	imshow("��������ͼ����", src);

	return true;
}

//��һ��ʵ��
bool  LinearBlending()
{
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if (!srcImage2.data) { cerr << "��ȡsrcImage2���� \n"; return false; }
	if (!srcImage3.data) { cerr << "��ȡsrcImage3���� \n"; return false; }

	// ��2������ͼ���ϼ�Ȩ����
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// ��3����ʾԭͼ����
	imshow("<2>���Ի��ʾ�����ڡ�ԭͼ��", srcImage2);
	imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ��", dstImage);

	return true;

}




//-----------------------------��MultiChannelBlending( )������--------------------------------
//	��������ͨ����ϵ�ʵ�ֺ���
//-----------------------------------------------------------------------------------------------
bool  MultiChannelBlending()
{
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;//�����洢ÿ��ͨ����Mat
	Mat  imageBlueChannel;

	//=================����ɫͨ�����֡�=================
	//	��������ͨ�����-��ɫ��������
	//============================================

	// ��1������ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) { printf("Oh��no����ȡlogoImage����~�� \n"); return false; }
	if (!srcImage.data) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }

	//��2����һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);//����ɫ��ͨ��

	//��3����ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageBlueChannel = channels.at(0);
	//��4����ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//��5����������ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	//��6����ʾЧ��ͼ
	namedWindow(" <1>��Ϸԭ��+logo��ɫͨ��");
	imshow(" <1>��Ϸԭ��+logo��ɫͨ��", srcImage);


	//=================����ɫͨ�����֡�=================
	//	��������ͨ�����-��ɫ��������
	//============================================

	//��0��������ر���
	Mat  imageGreenChannel;

	//��1�����¶���ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) { printf("��ȡlogoImage����~�� \n"); return false; }
	if (!srcImage.data) { printf("��ȡsrcImage����~�� \n"); return false; }

	//��2����һ����ͨ��ͼ��ת����������ͨ��ͼ��
	split(srcImage, channels);//����ɫ��ͨ��

	//��3����ԭͼ����ɫͨ�������÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageGreenChannel = channels.at(1);
	//��4����ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageGreenChannel��
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//��5�������������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<2>��Ϸԭ��+logo��ɫͨ��");
	imshow("<2>��Ϸԭ��+logo��ɫͨ��", srcImage);



	//=================����ɫͨ�����֡�=================
	//	��������ͨ�����-��ɫ��������
	//============================================

	//��0��������ر���
	Mat  imageRedChannel;

	//��1�����¶���ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) { printf("Oh��no����ȡlogoImage����~�� \n"); return false; }
	if (!srcImage.data) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }

	//��2����һ����ͨ��ͼ��ת����������ͨ��ͼ��
	split(srcImage, channels);//����ɫ��ͨ��

	//��3����ԭͼ�ĺ�ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageRedChannel = channels.at(2);
	//��4����ԭͼ�ĺ�ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageRedChannel��
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//��5�������������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<3>��Ϸԭ��+logo��ɫͨ�� ");
	imshow("<3>��Ϸԭ��+logo��ɫͨ�� ", srcImage);

	return true;
}

