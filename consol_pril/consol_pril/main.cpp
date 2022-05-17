#include <iostream>
#include"chebish.hpp"

int main()
{
	TVector<double> x(2);
	TVector<double> y(2);
	x[0] = -1; x[1] = 1;
	y[0] = -1; y[1] = 1;

	double eps = 0.00005;
	int Mstep = 10000;

	Cheb ch(30, 30, x, y);
	ch.go_met(eps,Mstep);

	system("python graph.py");


	return 0;
}