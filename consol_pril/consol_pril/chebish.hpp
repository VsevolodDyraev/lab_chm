#include"TMatrix.h"
#include<fstream>

class Cheb
{
private:
	TMatrix<double> V, R, F;
	TVector<double> x_gran,y_gran;
	double h, k;
	double tmph, tmpk, A;
	double pi;
	int n, m;
	double min, max;
	int K;
	TVector<double> tau;

	//все для инициализации
	double right_f(double, double);
	void init_right();
	void init_v();
	double init_y(double,int);
	double init_x(double,int);
	void init_params();

	//для подсчетов
	double work(int);
	void nevyaz();
	double evkl_nevyaz();

	//сохранение данных
	void save(string s)
	{
		ofstream file(s);

		file << n << endl << m << endl;

		for (int i = 0; i < x_gran.Size(); i++)
			file << x_gran[i] << endl;
		file << h << endl;

		for (int i = 0; i < y_gran.Size(); i++)
			file << y_gran[i] << endl;
		file << k << endl;

		for (int j = 0; j <= m; j++)
			for (int i = 0; i <= n; i++)
				file << V[j][i] << endl;

		file.close();
	}
	void SaveGrid(string s)
	{
		ofstream file(s);

		file << n << endl << m << endl;

		for (int i = 0; i < x_gran.Size(); i++)
			file << x_gran[i] << endl;
		file << h << endl;

		for (int i = 0; i < y_gran.Size(); i++)
			file << y_gran[i] << endl;
		file << k << endl;

		file.close();
	}

public:

	Cheb(int N, int M, TVector<double> ab,TVector<double> cd)
	{
		n = N;
		m = M;

		pi = 3.14;

		K = 8;

		x_gran = ab; y_gran = cd;

		h = static_cast<double>(x_gran[1] - x_gran[0]) / static_cast<double>(n);
		k = static_cast<double>(y_gran[1] - y_gran[0]) / static_cast<double>(m);

		tmph = 1.0 / (h * h);
		tmpk = 1.0 / (k * k);

		A = -2 * (tmph + tmpk);

		V = TMatrix<double>(m + 1);

		for (int i = 0; i < m + 1; i++)
		{
			V[i] = TVector<double>(n + 1);
		}

		R = V;
		F = V;

		init_right();
		init_v();
	}

	TVector<double> go_met(double eps, int max_step)
	{
		Cheb duo_tmp(2 * n, 2 * m, x_gran, y_gran);
		init_params();
		duo_tmp.init_params();

		TVector<double> acc(2);

		for (int i = 0; i < 2; i++)
			acc[i] = 2;

		TVector<int> IterationsCount(2);

		int TauIndex = 0;
		while ((acc[0] > eps) && (IterationsCount[0] < max_step))
		{
			if (TauIndex < K - 1)
			{
				work(TauIndex);
				TauIndex++;
			}
			else
			{
				acc[0] = work(TauIndex);
				TauIndex = 0;
				IterationsCount[0]++;
			}
		}

		TauIndex = 0;
		while ((acc[1] > eps) && (IterationsCount[1] < max_step))
		{
			if (TauIndex < K - 1)
			{
				duo_tmp.work(TauIndex);
				TauIndex++;
			}
			else
			{
				acc[1] = duo_tmp.work(TauIndex);
				TauIndex = 0;
				IterationsCount[1]++;
			}
		}

		save("osn_setka.txt"); //Заполнили файл численным решением
		duo_tmp.save("dop_setka.txt");  //Заполнили файл с численным решением на вспомогательной сетке
		SaveGrid("diff.txt");

		ofstream diff("diff.txt", ios::app); //Запись в файл будет продолжена с последнего элемента

		double error = 0; //Точность решения
		double tmp; //Вспомогательная переменная
		int ix, jy;
		for (int j = 0; j <= m; j++)
			for (int i = 0; i <= n; i++)
			{
				tmp = fabs(V[j][i] - duo_tmp.V[2 * j][2 * i]);
				diff << tmp << endl;
				if (tmp > error)
				{
					error = tmp;
					ix = i;
					jy = j;
				}
			}

		nevyaz();
		duo_tmp.nevyaz();

		tmp = evkl_nevyaz();

		TVector<double> result(6);
		result[0] = acc[0]; //Точность метода
		result[1] = IterationsCount[0]; //Количество итераций
		result[2] = error; //Погрешность решения
		result[3] = tmp; //Евклидова норма невязки
		result[4] = x_gran[0] + h * ix; //Значение x в самой плохой точке
		result[5] = y_gran[0] + k * jy; //Значение y в самой плохой точке

		return result;
	}

};