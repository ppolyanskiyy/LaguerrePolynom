#include "pch.h"
#include "framework.h"
#include "LaguerrePolynom.h"

#pragma region C-tors, setters, getters

LaguerrePolynoms::LaguerrePolynoms(
	double inputAlpha, double inputBeta, int inputCount, double inputT, double inputStep, double inputApproximation) :
	alpha(inputAlpha), beta(inputBeta), sigma(inputAlpha + inputBeta), polynomsCount(inputCount), T(inputT), step(inputStep), approximation(inputApproximation)
{
	findMaxValue();
}

double LaguerrePolynoms::getAlpha() const
{
	return alpha;
}

double LaguerrePolynoms::getBeta() const
{
	return beta;
}

double LaguerrePolynoms::getSigma() const
{
	return sigma;
}

double LaguerrePolynoms::getStep() const
{
	return step;
}

double LaguerrePolynoms::getT() const
{
	return T;
}

int LaguerrePolynoms::getPolynomsCount() const
{
	return polynomsCount;
}

int LaguerrePolynoms::getMaxValue() const
{
	return maxValue;
}

void LaguerrePolynoms::setAlpha(double inputAlpha)
{
	alpha = inputAlpha;
}

void LaguerrePolynoms::setBeta(double inputBeta)
{
	beta = inputBeta;
}

void LaguerrePolynoms::setStep(double inputStep)
{
	step = inputStep;
}

void LaguerrePolynoms::setT(double inputT)
{
	T = inputT;
}

void LaguerrePolynoms::setPolynomsCount(int inputCount)
{
	polynomsCount = inputCount;
}

void LaguerrePolynoms::setArbitraryFunction(double(*inputArbitraryFunction)(double))
{
	arbitraryFunction = inputArbitraryFunction;
}

#pragma endregion

void LaguerrePolynoms::calculateValues()
{
	calculateLagFuncValues();
	calculateApproxFuncValues();
}

void LaguerrePolynoms::calculateLagFuncValues()
{
	for (size_t i = 0; i < polynomsCount; ++i)
	{
		double value = integral(i);
		laguerreFuncValues.push_back(value);
	}
}

void LaguerrePolynoms::calculateApproxFuncValues()
{
	for (double x = 0; x < T; x += step)
	{
		double sum{ 0 };
		for (size_t i = 0; i < polynomsCount; ++i)
		{
			sum += laguerreFuncValues[i] * lagFuncValue(i, x);
		}

		approximatedFuncValues.push_back(sum);
	}
}

std::vector<double> LaguerrePolynoms::getLagFuncValues() const
{
	return laguerreFuncValues;
}

std::vector<double> LaguerrePolynoms::getApproxFuncValues() const
{
	return approximatedFuncValues;
}

void LaguerrePolynoms::getLagFuncValuesPtr(double* outArr) const
{
	std::cout << "GET___\n";
	if (laguerreFuncValues.empty())
	{
		std::vector<double> example = { 1,2,3,4,5,6,7,8,9,10 };
		memcpy(example.begin()._Ptr, outArr, 10 * sizeof(double));
	}
	else
		memcpy(laguerreFuncValues.begin()._Ptr, outArr, polynomsCount * sizeof(double));
}

double LaguerrePolynoms::integral(int n)
{
	double tempResult = maxValue * resultedFuncValue(n, maxValue / 2);
	double result = (maxValue / 2) * rectangleSum(n, 2);

	int multiplier = 4;
	double coefficient = maxValue / double(2 * multiplier);

	while (abs((tempResult - result) / result) > approximation)
	{
		tempResult = result;
		result = coefficient * rectangleSum(n, multiplier);

		multiplier *= 2;
		coefficient = maxValue / multiplier;
	}

	return result;
}

void LaguerrePolynoms::findMaxValue()
{
	while (exp(-alpha * maxValue) >= exp(-10))
		maxValue += step;
}

double LaguerrePolynoms::rectangleSum(int n, double k)
{
	double result{ 0 };
	double step = maxValue / k;

	while (k >= 1)
	{
		result += resultedFuncValue(n, (k - 0.5) * step);
		--k;
	}

	return result;
}

double LaguerrePolynoms::resultedFuncValue(int n, double x)
{
	return arbitraryFunction(x) * lagFuncValue(n, x) * exp(-alpha * x);
}

double LaguerrePolynoms::lagFuncValue(int n, double x)
{
	std::vector<double> results;

	for (size_t i = 0; i < n + 1; i++)
	{
		if (0 == i)
			results.push_back(sqrt(sigma) * exp((-beta / 2) * x));

		else if (1 == i)
			results.push_back(sqrt(sigma) * (1 - sigma * x) * exp((-beta / 2) * x));

		else
			results.push_back(((2 * i) - 1 - x) / i * lagFuncValue(i - 1, x) - (double(i - 1) / i * lagFuncValue(i - 2, x)));
	}

	if (results.empty())
		return 0;

	return results.back();
}