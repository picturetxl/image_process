#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <ctime>

using namespace std;
using namespace cv;


#define WINDOW_NAME1 "【绘制图1】"        //为窗口标题定义的宏 
#define WINDOW_NAME2 "【绘制图2】"        //为窗口标题定义的宏 
#define WINDOW_WIDTH 600//定义窗口大小的宏



//提示信息
void ShowHelpText();


//基本绘图
void DrawEllipse(Mat img, double angle);//绘制椭圆
void DrawFilledCircle(Mat img, Point center);//绘制圆
void DrawPolygon(Mat img);//绘制多边形
void DrawLine(Mat img, Point start, Point end);//绘制线段

void draw_atom();//画一个atom编辑器的标志
void draw_pologon();////画一个多边形图 灯塔?


void createAlphaMat(Mat& mat);//创建带alpha通道的Mat
int create_alpha_img();//创建一个带有alpha通道的图像

//绘制灰度直方图
Mat getHistograph(const Mat grayImage);
int histogram();




//ROI
bool  ROI_AddImage();
bool  ROI_LinearBlending();
bool  LinearBlending();
bool  MultiChannelBlending();


//回调函数,用来改变图像的亮度和对比度
void ContrastAndBright(int, void*);
void test_bright_and_contrast();

//dft:离散傅里叶变换
void test_dft();

//写xml文件
void test_xml_write();