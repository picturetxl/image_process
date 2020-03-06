//���Թ���

#include "../include/Header.h"



//��ֵ��ͼ��
void oust_method_process_image()
{
	string pattern = "C:\\Users\\tailiang\\Pictures\\LPR_test\\*.jpg";
	vector<String> files;
	glob(pattern, files);//opencv �Դ��ı����ļ��еķ���
	int i = 0;
	for (auto img_file : files)
	{
		Mat src_img = imread(img_file, IMREAD_GRAYSCALE);//input image �����ǻҶ�ͼƬ
		Mat dest_img;


		// ȫ�ֶ�ֵ�� oust����
		//double thresh_value = threshold(src_img, dest_img, 0, 255, THRESH_OTSU);
		//cout << img_file << ":" << thresh_value << endl;


		// �ֲ���ֵ��--Ч������
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

//���ƻҶ�ֱ��ͼ
int histogram()
{
	//Mat src_img = imread("C:\\Users\\tailiang\\Pictures\\LPR_test\\img1.jpg", IMREAD_GRAYSCALE);//input image �����ǻҶ�ͼƬ
	//����ͼ��
	Mat image;
	image = imread("C:\\Users\\tailiang\\Pictures\\LPR_test\\img1.jpg", IMREAD_COLOR);
	//�ж��Ƿ�Ϊ��
	if (image.empty())
	{
		cerr << "" << endl;
		return -1;
	}
	//����Ҷ�ͼ��ת�ɻҶ�ͼ
	Mat grayImage;
	cvtColor(image, grayImage, COLOR_BGR2GRAY);
	//double x=compareHist(hist,hist,/*CV_COMP_CORREL��CV_COMP_INTERSECT*/CV_COMP_BHATTACHARYYA);
	//ֱ��ͼͼ��
	Mat hist = getHistograph(grayImage);

	namedWindow("hist", WINDOW_NORMAL);

	//imshow("hist", image);
	imshow("hist", hist);
	waitKey(0);

}

//��һ��atom�༭���ı�־
void draw_atom()
{

	// �����հ׵�Matͼ��
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	//����Atom �༭���ı�־
	//�Ȼ���Χ�Ƶ���Բ��
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	//����Բ��
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);//�ƶ����ڵ�ָ��λ��


	waitKey(0);
}

//��һ�������ͼ ����?
void draw_pologon()
{
	// �����հ׵�Matͼ��
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	//�Ȼ��Ƴ���Բ
	DrawPolygon(rookImage);

	//���ƾ���
	rectangle(rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8);


	//����һЩ�߶�
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
}
