#include <stdio.h>
#include <iostream>
#include <assert.h> 
#include <math.h>

#define INF_ROOTS 3
#define SMALL_VALUE 0.001
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Solves a square equation ax^2 + bx + c = 0
//!
//! @param [in]  a   a‐coefficient
//! @param [in]  b   b‐coefficient
//! @param [in]  c   c‐coefficient
//! @param [out] x1  Pointer to the 1st root
//! @param [out] x2  Pointer to the 2nd root
//!
//! @return Number of roots
//!
//! @note   In case of infinite number of roots,
//!         returns INF_ROOTS.
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

void checkInput(const double a, const double b, const double c, const double* x1, const double* x2)
{
	assert(std::isfinite(a));
	assert(std::isfinite(b));
	assert(std::isfinite(c));
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);
}

double round_(const double a, int precis)
{
	if (a == 0) return 0;
	precis = precis < 0 || precis > 15 ? 0 : precis;
	double precis_d = pow(10, precis);
	return (floor(a * precis_d) / precis_d);
}

int solveEquation(const double a, const double b, const double c, double* x1, double* x2)
{
	checkInput(a, b, c, x1, x2);
	if (a == 0)
	{
		if (b == 0)
			return (c == 0) ? INF_ROOTS : 0;
		else
		{
			*x1 = round_(-c / b, 2);
			return 1;
		}
	}
	else
	{
		double D = b * b - 4 * a * c, SqrtD;
		SqrtD = sqrt(abs(D));
		D = D < SMALL_VALUE && D > 0 ? 0 : D;
		if (D >= 0)
		{
			*x1 = round_((-b + SqrtD) / (2 * a), 2);
			*x2 = round_((-b - SqrtD) / (2 * a), 2);
			return 2;
		}
		else
		{
			SqrtD = round_(SqrtD, 2);
			printf("Complex roots:\nX1 = (%lg + i * %lg) / %lg\n", -b, SqrtD, 2 * a);
			printf("X2 = (%lg - i * %lg) / %lg\n", -b, SqrtD, 2 * a);
			return -1;
		}
	}
}

int main()
{
	printf("Please Enter a, b, c...\n");
	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	if (scanf("%lg %lg %lg", &a, &b, &c) != 3)
	{
		printf("Wrong parameters!\n");
		system("pause");
		return 1;
	}
	int nroots = solveEquation(a, b, c, &x1, &x2);

	switch (nroots)
	{
		case 0:
			printf("No roots.\n");
			break;
		case 1:
			printf("Root:\nX = %lg.\n", x1);
			break;
		case 2:
			printf("Roots:\nX1 = %lg, X2 = %lg.\n", x1, x2);
			break;
		case INF_ROOTS:
			printf("Infinite number of roots.\n");
			break;
		case -1:
			break;
		default:
			printf("Unknown error!\n", nroots);
			system("pause");
			return 1;
	}
	system("pause");
	return 0;
}