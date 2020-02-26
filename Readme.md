# 利用OpenCV进行图像处理

> 利用opencv这个开源库学习图像处理

+ 车牌识别**LPR**[License Plate Recognition]



##  数字图像的表示

+ 黑白图像:0和1
+ 灰度图像
  + ![image-20200226173713576](Readme.assets/image-20200226173713576.png)
+ 彩色图像
  + ![image-20200226173723353](Readme.assets/image-20200226173723353.png)

##  简单的例子

> 代码参考毛星云的《OpenCV3编程入门》
>
> 简单感受下OpenCV的魅力

+ 头文件

  ```cpp
  #include <opencv2 / opencv.hpp>//包含了众多模块 一劳永逸
  
  using namespace std;
  using namespace cv;
  
  ```

+ 读取图像,显示图像

  ```cpp
  
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
  ```

  ![image-20200226172156372](Readme.assets/image-20200226172156372.png)

+ 腐蚀图像

  ```cpp
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
  
  ```

  ![image-20200226172302726](Readme.assets/image-20200226172302726.png)

+ 均值滤波

  ```cpp
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
  
  ```

  ![image-20200226172342910](Readme.assets/image-20200226172342910.png)

+ 边缘检测

  ```cpp
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
  
  ```

  ![image-20200226172429192](Readme.assets/image-20200226172429192.png)

+ 读取视频

  ```cpp
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
  
  ```

  ![vedio](Readme.assets/vedio.gif)

+ 读取摄像头

  ```cpp
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
  // 自己尝试下 就不放自己了 哈哈啊
  ```

  

+ 通过读取摄像头进行边缘检测

  ```cpp
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
  ```

  

+ 输出OpenCV的版本

```cpp
/*
 *@function:print_opencv_version
 *@desc:打印版本
 *@param:
**/
void print_opencv_version()
{
	printf("version:" CV_VERSION);

}
```

![image-20200226173223402](Readme.assets/image-20200226173223402.png)



## 二值化

> 二值化不是二值图像,只是将**灰度图像**利用**阙值threshold**进行了划分

+ 全局阙值
  + **oust**算法 也叫大津算法/最大间类方差法
+ 局部阙值
+ 动态阙值

```cpp

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
		adaptiveThreshold(src_img, dest_img, maxVal, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize,C);


		string name_win = "otsu_" + img_file;
		imshow(name_win, dest_img);
		i++;
		waitKey(30);
	}
	waitKey(0);
}
```



## OpenCV的函数

#### imread 函数

> 原型

```cpp
CV_EXPORTS_W Mat imread( const String& filename, int flags = IMREAD_COLOR );
```

> 作用:读取图像

![image-20200226105032319](opencv.assets/image-20200226105032319.png)

![image-20200226105044559](opencv.assets/image-20200226105044559.png)

### glob 函数

> 原型

```cpp
CV_EXPORTS void glob(String pattern, std::vector<String>& result, bool recursive = false);
```

> 作用:遍历文件夹

```cpp
string pattern = "C:\\Users\\tailiang\\Pictures\\LPR_test\\*.jpg";
vector<String> files;
glob(pattern, files);//opencv 自带的遍历文件夹的方法
```

+ 第一个参数是搜索的模式
+ 第二个参数是一个vector但是类型是OpenCV的String
+ 第三个参数是是否递归搜索



## 项目

### LPR

> 车牌处理的大致过程-对应于papers的文件夹
>
> 1. 车牌定位
> 2. 二值化
> 3. 车牌字符分割
> 4. 字符识别







### 我国车牌标准 GA36-2018

[link]( https://max.book118.com/html/2019/0430/8026050061002021.shtm )

