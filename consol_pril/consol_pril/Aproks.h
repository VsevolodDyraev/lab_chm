#pragma once
#include <vector>
#include<iostream>
#include<iomanip>

struct mat
{
	std::vector<std::vector<double>> kysok;

	void operator=(mat& matrica)
	{
		if (kysok.empty())
		{
			for (int i = 0; i < matrica.kysok.size(); i++)
			{
				kysok.push_back(matrica.kysok[i]);
			}

		}
		for (int i = 0; i < matrica.kysok.size(); i++)
		{
			kysok[i] = matrica.kysok[i];
		}
	}
	
};

struct mat_gen: public mat
{
	/*std::vector<std::vector<double>> kysok;
	*/
	mat_gen(double h,double k, int n)
	{
		double A = -2.0 * (1.0 / (h * h) + 1.0 / (k + k));
		double t_h = 1.0 / (h * h);

		std::vector < double> tmp;

		tmp.push_back(A);
		tmp.push_back(t_h);


		for (int j = 0; j < n - 3; j++)
		{
			tmp.push_back(0.0);
		}

		/*for (int j = 2; j < n - 1; j++);
		{
			tmp.push_back(0.0);
		}*/

		kysok.push_back(tmp);
		

		for (int i = 1; i < n - 2; i++)
		{
			for (int j = 0; j < n - 1; j++)
			{
				if (j == i - 1 || j==i+1)
				{
					tmp[j] = t_h;
					continue;
				}

				if (j == i)
				{
					tmp[j] = A;
					continue;
				}
				
				tmp[j] = 0.0;

			}
			kysok.push_back(tmp);
		}

		for (int i = 0; i < n - 3; i++)
		{
			tmp[i] = 0.0;
		}
		tmp[n - 3] = t_h;
		tmp[n - 2] = A;
		kysok.push_back(tmp);

	}

	mat_gen(mat& matrica)
	{
		if (kysok.empty())
		{
			for (int i = 0; i < matrica.kysok.size(); i++)
			{
				kysok.push_back(matrica.kysok[i]);
			}
				
		}
		for (int i = 0; i < matrica.kysok.size(); i++)
		{
			kysok[i] = matrica.kysok[i];
		}
	}

	void show()
	{
		for (int i = 0; i < kysok.size(); i++)
		{
			for (int j = 0; j < kysok.size(); j++)
			{
				std::cout << kysok[i][j] << '\t';
			}
			std::cout << '\n';
		}
	}
	~mat_gen()
	{
		kysok.~vector();
	}
};

struct mat_k: public mat
{
	/*std::vector<std::vector<double>> kysok;*/

	mat_k(double k, int n)
	{
		double t_k = 1.0 / (k * k);

		std::vector<double> tmp;

		for (int i = 0; i < n - 1; i++)
		{
			tmp.push_back(0.0);
		}

		for (int i = 0; i < n - 1; i++)
		{
			tmp[i] = t_k;
			kysok.push_back(tmp);
			tmp[i] = 0.0;
		}
	}
	mat_k(mat& matrica)
	{
		if (kysok.empty())
		{
			for (int i = 0; i < matrica.kysok.size(); i++)
			{
				kysok.push_back(matrica.kysok[i]);
			}

		}
		for (int i = 0; i < matrica.kysok.size(); i++)
		{
			kysok[i] = matrica.kysok[i];
		}
	}

	void show()
	{
		for (int i = 0; i < kysok.size(); i++)
		{
			for (int j = 0; j < kysok.size(); j++)
			{
				std::cout << kysok[i][j] << '\t';
			}
			std::cout << '\n';
		}
	}

	~mat_k()
	{
		kysok.~vector();
	}

};

struct mat_zero: public mat
{
	/*std::vector<std::vector<double>> kysok;*/

	mat_zero(mat& matrica)
	{
		if (kysok.empty())
		{
			for (int i = 0; i < matrica.kysok.size(); i++)
			{
				kysok.push_back(matrica.kysok[i]);
			}

		}
		for (int i = 0; i < matrica.kysok.size(); i++)
		{
			kysok[i] = matrica.kysok[i];
		}
	}

	mat_zero(int n)
	{
		std::vector<double> tmp;
		
		for (int i = 0; i < n - 1; i++)
		{
			tmp.push_back(0.0);
		}
		for (int i = 0; i < n - 1; i++)
		{
			kysok.push_back(tmp);
		}

	}

	void show()
	{
		for (int i = 0; i < kysok.size(); i++)
		{
			for (int j = 0; j < kysok.size(); j++)
			{
				std::cout << kysok[i][j] << '\t';
			}
			std::cout << '\n';
		}
	}
	~mat_zero()
	{
		kysok.~vector();
	}
};

struct mat_itog
{
	std::vector<double> vec;
};


struct main_mat
{
	double** yzl;

	main_mat(int n, int m)
	{
		yzl = new double* [(n - 1) * (m - 1)];
	}

};




class Matrix_A
{
private:
	int n, m;

	mat** A;
	mat* memor;
	main_mat A_main;
	double* main_memor;


	int max_x;
	int max_y;

public:
	Matrix_A(double h, double k, int _n, int _m): A_main(_n, _m), max_x((n - 1)* (m - 1)), max_y((n - 1)* (m - 1))
	{
		n = _n;
		m = _m;

		

		mat_gen t_g(h, k, n);
		mat_k t_k(k, n);
		mat_zero t_z(n);

		mat* tmp = new mat[m-1];

		memor = new mat[(m - 1) * (m - 1)];
		A = new mat * [m - 1];


		for (int i = 0; i < m - 1; i++)
		{
			A[i] = memor + static_cast<int>(i*(m-1));
		}


		tmp[0] = t_g;
		tmp[1] = t_k;
		for (int i = 0; i < m - 3; i++)
		{
			tmp[i+2] = t_z;
		}

		for (int j = 0; j < m - 1; j++)
		{
			A[0][j] = tmp[j];
		}


		for (int i = 1; i < m - 2; i++)
		{
			for (int j = 0; j < m - 1; j++)
			{
				if (j == i - 1 || j == i + 1)
				{
					tmp[j] = t_k;
					continue;
				}
				if (j == i)
				{
					tmp[j] = t_g;
					continue;
				}
				tmp[j] = t_z;
			}

			
			for (int j = 0; j < m - 1; j++)
			{
				A[i][j] = tmp[j];
			}
			/*A[i] = tmp;*/

		}

		for (int i = 0; i < m - 3; i++)
		{
			tmp[i] = t_z;
		}
		tmp[m-3] = t_k;
		tmp[m-2] = t_g;

		for (int j = 0; j < m - 1; j++)
		{
			A[m-2][j] = tmp[j];
		}

	}
	
	void show()
	{
		//std::cout << A[0][0].kysok[0][0];
		main_memor = new double[(n - 1) * (m - 1) * (n - 1) * (m - 1)];
		
		for (int i = 0; i < (n - 1) * (m - 1); i++)
		{
			A_main.yzl[i] = main_memor + i * ((n - 1) * (m - 1));
		}


		int l = 0;
		int p = 0;
		for (int i = 0; i < m - 1; i++)
		{
			for (int j = 0; j < n - 1; j++)
			{
				for (int y = 0; y < m - 1; y++)
				{
					for (int x = 0; x < n - 1; x++)
					{
						std::cout << A[i][y].kysok[j][x]<<std::setw(10);
						A_main.yzl[l][p] = A[i][y].kysok[j][x];
						if (p == (n - 1) * (m - 1))
						{
							p = 0;
							l++;
						}
					}
				}
				std::cout << '\n';
			}
		}
		std::cout << "\n";
		std::cout << "\n";
		std::cout << "\n";

		for (int i = 0; i < max_y; i++)
		{
			for (int j = 0; j < max_y; j++)
			{
				std::cout << A_main.yzl[i][j] << std::setw(10);
			}
			std::cout << "\n";
		}

	}

	~Matrix_A()
	{
		delete[]memor;
	}


};

