#include "Header.h"

//快速傅里叶变换
void test_dft()
{
	//以灰度模式读取原始图像并显示
	Mat srcImage = imread("2.jpg", 0);
	if (!srcImage.data) { cerr << "read error" << endl; }
	imshow("原始图像", srcImage);

	/*
		DFT performance is not a monotonic function of a vector size. Therefore, when you calculate
		convolution of two arrays or perform the spectral analysis of an array, it usually makes sense to
		pad the input data with zeros to get a bit larger array that can be transformed much faster than the
		original one. Arrays whose size is a power-of-two (2, 4, 8, 16, 32, ...) are the fastest to process.
		Though, the arrays whose size is a product of 2's, 3's, and 5's (for example, 300 = 5\*5\*3\*2\*2)
		are also processed quite efficiently.

		> 简而言之,就是要想进行快速傅里叶变换首先先把矩阵的size变化到power-of-two的size or product of 2's
		> 怎么做呢?填充0
		> 离散傅里叶变换的运行速度和图像的尺寸有很大关系,所以要进行处理
		> 常用的方法是通过填充新的边缘像素的方法来获取最佳图像尺寸
	*/
	//先计算出最佳的处理size
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);

	//再将需要填充的地方进行填充
	Mat padded;//目标图像-待处理的图像
	//填充边缘像素,按照上下左右
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//傅里叶变换的结果是复数,这就是说对于每个原图像,结果会有两个图像值
	//频域值至少存在float格式中
	//为傅立叶变换的结果(实部和虚部)分配存储空间。
	//增加了一个复数存储部分 即zero部分
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	
	//将planes数组组合合并成一个多通道的数组complexI
	Mat complexI;
	merge(planes, 2, complexI);//merge将多个单通道的图像合并成一个多通道的图像

	//进行就地(in-place)离散傅里叶变换.所谓就地,就是输入和输出都是同一副图像.
	dft(complexI, complexI);

	//-------到此,DFT已经变换完了----为了用DFT获得图像的几何结构部分

	//-------处理

	//为了得到图像的幅值
	//因为幅值是需要实部和虚部,所以要进行split
	split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	//得到幅值--但是不利于观察,所以还需要一步log转换
	magnitude(planes[0], planes[1], planes[0]); 

	//planes[0]就是幅值图像
	Mat magnitudeImage = planes[0];

	//log转换
	//M1 = log(1+M)
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//求自然对数

	//【7】剪切和重分布幅度图象限
	//若有奇数行或奇数列，进行频谱裁剪      
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//重新排列傅立叶图像中的象限，使得原点位于图像中心  
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
	//交换象限（左上与右下进行交换）
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//交换象限（右上与左下进行交换）
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//-- 经过对数转换之后,图像值还仍然可能不在0-1之间,所以进行归一化处理
	//非黑即白

	//【8】归一化，用0到1之间的浮点值将矩阵变换为可视的图像格式
	//此句代码的OpenCV2版为：
	//normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX); 
	//此句代码的OpenCV3版为:
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	//【9】显示效果图
	imshow("频谱幅值", magnitudeImage);
	waitKey();


}