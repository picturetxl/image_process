

#include "../include/Header.h"


//��һ��ͼ���ϻ���ͬ�Ƕȵ���Բ(��С��һ��)
void DrawEllipse(Mat img, double angle)
{
	
	/*
		@param img 
		@param center Center of the ellipse.
		@param axes Half of the size of the ellipse main axes.
		@param angle Ellipse rotation angle in degrees.
		@param startAngle Starting angle of the elliptic arc in degrees.
		@param endAngle Ending angle of the elliptic arc in degrees.
		@param color Ellipse color.
		@param thickness Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that
		a filled ellipse sector is to be drawn.
		@param lineType Type of the ellipse boundary. See #LineTypes
		@param shift Number of fractional bits in the coordinates of the center and values of axes.
	
		void ellipse(InputOutputArray img, //���ĸ�ͼ���ϻ�
					 Point center,			//��Բ������
					 Size axes,				//��Բ����ߴ��һ�롣
                     double angle,			//��Բ��ת�Ƕȣ��ȣ���
					 double startAngle,		//��Բ������ʼ�ǣ��ȣ��� startAngle �� endAngle ��ʾԲ����start �� end ����0->360 ����һ����Բ 0-180���ǰ��
					 double endAngle,		//��Բ���Ľ����ǣ��ȣ���
                     const Scalar& color,	//��Բ����ɫ
					 int thickness = 1,		//��Բ�������ĺ�ȣ����Ϊ���������ı�ʾ�����ɫ
                     int lineType = LINE_8, //�ߵ�����
					 int shift = 0			//�����������ֵ�е�С��λ����
					 );

	*/
	int thickness = 2;//�����,���Ϊ2
	int lineType = 8;//���Բ�д ʹ��Ĭ�ϵ�

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType//����ʡ��
	);
}



//-----------------------------------��DrawFilledCircle( )������---------------------------
//		�������Զ���Ļ��ƺ�����ʵ����ʵ��Բ�Ļ���
//-----------------------------------------------------------------------------------------
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center,
		WINDOW_WIDTH / 32,
		Scalar(0, 0, 255),
		thickness,
		lineType);
}



//-----------------------------------��DrawPolygon( )������--------------------------
//		�������Զ���Ļ��ƺ�����ʵ���˰�����εĻ���
//--------------------------------------------------------------------------------------
void DrawPolygon(Mat img)
{
	int lineType = 8;

	//����һЩ��
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	/*
		void fillPoly(Mat& img, 
						const Point** pts,
                        const int* npts, 
						int ncontours,
                        const Scalar& color, 
						int lineType = LINE_8, 
						int shift = 0,
                        Point offset = Point()
						);
	
	*/

	fillPoly(img,
		ppt,
		npt,
		1,
		Scalar(255, 255, 255),
		lineType);
}


//-----------------------------------��DrawLine( )������--------------------------
//		�������Զ���Ļ��ƺ�����ʵ�����ߵĻ���
//---------------------------------------------------------------------------------
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		start,
		end,
		Scalar(0, 0, 0),
		thickness,
		lineType);
}