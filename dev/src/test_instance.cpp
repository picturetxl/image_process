//测试功能

#include "../include/Header.h"


extern int g_nContrastValue; //对比度值
extern int g_nBrightValue;  //亮度值

//二值化图像
void oust_method_process_image()
{
	string pattern = "C:\\Users\\tailiang\\Pictures\\LPR_test\\*.jpg";
	vector<String> files;
	glob(pattern, files);//opencv 自带的遍历文件夹的方法
	int i = 0;
	for (auto img_file : files)
	{
		Mat src_img = imread(img_file, IMREAD_GRAYSCALE);//input image 必须是灰度图片
		Mat dest_img;


		// 全局二值化 oust方法
		//double thresh_value = threshold(src_img, dest_img, 0, 255, THRESH_OTSU);
		//cout << img_file << ":" << thresh_value << endl;


		// 局部二值化--效果更好
		int maxVal = 255;
		int blockSize = 41;
		double C = 0;
		adaptiveThreshold(src_img, dest_img, maxVal, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, C);


		string name_win = "otsu_" + img_file;
		imshow(name_win, dest_img);
		i++;
		waitKey(30);
	}
	waitKey(0);
}

//绘制灰度直方图
int histogram()
{
	//Mat src_img = imread("C:\\Users\\tailiang\\Pictures\\LPR_test\\img1.jpg", IMREAD_GRAYSCALE);//input image 必须是灰度图片
	//加载图像
	Mat image;
	image = imread("C:\\Users\\tailiang\\Pictures\\LPR_test\\img1.jpg", IMREAD_COLOR);
	//判断是否为空
	if (image.empty())
	{
		cerr << "" << endl;
		return -1;
	}
	//定义灰度图像，转成灰度图
	Mat grayImage;
	cvtColor(image, grayImage, COLOR_BGR2GRAY);
	//double x=compareHist(hist,hist,/*CV_COMP_CORREL、CV_COMP_INTERSECT*/CV_COMP_BHATTACHARYYA);
	//直方图图像
	Mat hist = getHistograph(grayImage);

	namedWindow("hist", WINDOW_NORMAL);

	//imshow("hist", image);
	imshow("hist", hist);
	waitKey(0);

}

//画一个atom编辑器的标志
void draw_atom()
{

	// 创建空白的Mat图像
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	//绘制Atom 编辑器的标志
	//先绘制围绕的椭圆线
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	//绘制圆心
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);//移动窗口到指定位置


	waitKey(0);
}

//画一个多边形图 灯塔?
void draw_pologon()
{
	// 创建空白的Mat图像
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	//先绘制出椭圆
	DrawPolygon(rookImage);

	//绘制矩形
	rectangle(rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8);


	//绘制一些线段
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
}


//改变图像的亮度和对比度
//操作像素
void test_bright_and_contrast()
{
	
	system("color 2F");//改变控制台前景色和背景色

	// 读入用户提供的图像
	Mat srcImage = imread("1.jpg");
	if (!srcImage.data) { cerr << "error when read g_srcImage!" << endl; }

	//构造一个和原图像相同的目标图像
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());

	//设定对比度和亮度的初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//创建窗口
	namedWindow("【效果图窗口】", 1);

	Mat imgs[2] = {srcImage,dstImage };


	//创建轨迹条
	createTrackbar("对比度：", "【效果图窗口】", &g_nContrastValue, 300, ContrastAndBright,imgs);
	createTrackbar("亮   度：", "【效果图窗口】", &g_nBrightValue, 200, ContrastAndBright,imgs);

	//刚开始调用回调函数来显示图像
	ContrastAndBright(g_nContrastValue, &imgs);
	ContrastAndBright(g_nBrightValue, &imgs);

	//输出一些帮助信息
	cout << endl << "\t运行成功，请调整滚动条观察图像效果\n\n"
		<< "\t按下“q”键时，程序退出\n";

	//按下“q”键时，程序退出
	while (char(waitKey(1)) != 'q') {}



}