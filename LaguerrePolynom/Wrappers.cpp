#include "pch.h"
#include "LaguerrePolynom.h"

LaguerrePolynoms* createLaguerrePolynoms(
	double inputAlpha, double inputBeta, int inputCount, double inputT, double inputStep, double inputApproximation)
{
	return new LaguerrePolynoms(inputAlpha, inputBeta, inputCount, inputT, inputStep, inputApproximation);
}

void getAlpha(LaguerrePolynoms* inputInstance, double& outputAlpha)
{
	outputAlpha = inputInstance->getAlpha();
}

void setAlpha(LaguerrePolynoms* inputInstance, double inputAlpha)
{
	inputInstance->setAlpha(inputAlpha);
}

void getBeta(LaguerrePolynoms* inputInstance, double& outputBeta)
{
	outputBeta = inputInstance->getBeta();
}

void setBeta(LaguerrePolynoms* inputInstance, double inputBeta)
{
	inputInstance->setBeta(inputBeta);
}

void getPolynomsCount(LaguerrePolynoms* inputInstance, int& outputCount)
{
	outputCount = inputInstance->getPolynomsCount();
}

void setPolynomsCount(LaguerrePolynoms* inputInstance, int inputCount)
{
	inputInstance->setPolynomsCount(inputCount);
}

void getMaxValue(LaguerrePolynoms* inputInstance, double& outputMaxValue)
{
	outputMaxValue = inputInstance->getMaxValue();
}

void getStep(LaguerrePolynoms* inputInstance, double& outputStep)
{
	outputStep = inputInstance->getStep();
}

void setStep(LaguerrePolynoms* inputInstance, double inputStep)
{
	inputInstance->setStep(inputStep);
}

void getT(LaguerrePolynoms* inputInstance, double& outputT)
{
	outputT = inputInstance->getT();
}

void setT(LaguerrePolynoms* inputInstance, double inputT)
{
	inputInstance->setT(inputT);
}

void calculateValues(LaguerrePolynoms* inputInstance)
{
	inputInstance->calculateValues();
}

void getLagFuncValues(LaguerrePolynoms* inputInstance, double* outputLagValues)
{
	inputInstance->getLagFuncValuesPtr(outputLagValues);
	//outputLagValues = inputInstance->getLagFuncValues().begin()._Ptr;
}

void getApproxFuncValues(LaguerrePolynoms* inputInstance, double* outputApproxFuncValues)
{
	outputApproxFuncValues = inputInstance->getApproxFuncValues().begin()._Ptr;
}

void setArbitraryFunction(LaguerrePolynoms* inputInstance, double (*inputArbitraryFunction)(double))
{
	inputInstance->setArbitraryFunction(inputArbitraryFunction);
}

#pragma endregion