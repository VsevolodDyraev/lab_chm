#include "chebish.hpp"
#include <math.h>

double Cheb::right_f(double x, double y)
{
	return fabs(pow(sin(pi * x * y), 3));
}

void Cheb::init_right()
{
	double x, y;
	y = y_gran[0] + k;

	for (int i = 1; i < m; i++)
	{
		x = x_gran[0] + h;
		for (int j = 1; j < n; j++)
		{
			F[j][i] = right_f(x, y);
			x += h;
		}
		y += k;
	}


}

double Cheb::init_x(double x,int l_or_r)
{
	switch (l_or_r)
	{
	case 0:
		return fabs(sin(pi * x));
	case 1:
		return fabs(sin(pi * x));
	default:
		return 0.0;
	}

}
double Cheb::init_y(double y,int l_or_r)
{
	switch (l_or_r)
	{
	case 0:
		return -y * y + 1;
	case 1:
		return -y * y + 1;
	default:
		return 0.0;
	}

}

void Cheb::init_v()
{
	double x, y;
	y = y_gran[0];
	for (int i = 0; i < m + 1; i++)
	{
		V[i][0] = init_y(y, 0);
		V[i][n] = init_y(y, 1);
		y += k;
	}
	x = x_gran[0];

	for (int i = 0; i < n; i++)
	{
		V[0][i] = init_x(x, 0);
		V[m][i] = init_x(x, 0);
		x += h;
	}


}

void Cheb::init_params()
{
	min = -4 * tmph * pow(sin(pi / (2.0 * n)), 2) - 4 * tmpk * pow(sin(pi / (2.0 * m)), 2);
	max = -4 * tmph * pow(cos(pi / (2.0 * n)), 2) - 4 * tmpk * pow(cos(pi / (2.0 * m)), 2);


	tau = TVector<double>(K);

	int step = K / 2;
	TVector<int>s(K);

	for (int i = 0; i < K; i++)
		s[i] = i;

	for (int i = 0; i < K; i++)
	{
		tau[i] = 2 / (max + min + (max - min) * cos(pi * (2 * s[i] + 1) / (2.0 * K)));
	}
}

//

double Cheb::work(int ind)
{
	double temp;
	for (int j = 1; j < m; j++)
		for (int i = 1; i < n; i++)
			R[j][i] = A * V[j][i] + tmph * (V[j][i + 1] + V[j][i - 1]) + tmpk * (V[j + 1][i] + V[j - 1][i]) + F[j][i];

	double acc = 0;
	for (int j = 1; j < m; j++)
		for (int i = 1; i < n; i++)
		{
			temp = V[j][i];
			//
			V[j][i] = V[j][i] - tau[ind] * R[j][i];
			//
			temp = fabs(V[j][i] - temp);
			if (temp > acc)
				acc = temp;
		}
	return acc;
}

void Cheb::nevyaz()
{
	for (int j = 1; j < m; j++)
		for (int i = 1; i < n; i++)
			R[j][i] = A * V[j][i] + tmph * (V[j][i - 1] + V[j][i + 1]) + tmpk * (V[j - 1][i] + V[j + 1][i]) + F[j][i];
}
double Cheb::evkl_nevyaz()
{
	double tmp = 0;
	for (int j = 1; j < m; j++)
		for (int i = 1; i < n; i++)
			tmp += pow(R[j][i], 2);

	return sqrt(tmp);
}