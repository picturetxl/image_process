#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <ctime>

using namespace std;
using namespace cv;


#define WINDOW_NAME1 "������ͼ1��"        //Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME2 "������ͼ2��"        //Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_WIDTH 600//���崰�ڴ�С�ĺ�



//��ʾ��Ϣ
void ShowHelpText();


//������ͼ
void DrawEllipse(Mat img, double angle);//������Բ
void DrawFilledCircle(Mat img, Point center);//����Բ
void DrawPolygon(Mat img);//���ƶ����
void DrawLine(Mat img, Point start, Point end);//�����߶�

void draw_atom();//��һ��atom�༭���ı�־
void draw_pologon();////��һ�������ͼ ����?


void createAlphaMat(Mat& mat);//������alphaͨ����Mat
int create_alpha_img();//����һ������alphaͨ����ͼ��

//���ƻҶ�ֱ��ͼ
Mat getHistograph(const Mat grayImage);
int histogram();




//ROI
bool  ROI_AddImage();
bool  ROI_LinearBlending();
bool  LinearBlending();
bool  MultiChannelBlending();


//�ص�����,�����ı�ͼ������ȺͶԱȶ�
void ContrastAndBright(int, void*);
void test_bright_and_contrast();

//dft:��ɢ����Ҷ�任
void test_dft();

//дxml�ļ�
void test_xml_write();