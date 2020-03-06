
#include "../include/Header.h"



int main()
{
	double start = static_cast<double>(getTickCount());

	LinearBlending();

	double end = static_cast<double>(getTickCount());
	double during_time = (end - start) / getTickFrequency();
	cout << "run time :"<<during_time << endl;
	waitKey(0);
	return 0;
}