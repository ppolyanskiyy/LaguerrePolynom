#ifdef LAGUERREPOLYNOM_EXPORTS
#define LAGUERREPOLYNOM_API __declspec(dllexport)
#else
#define LAGUERREPOLYNOM_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>

class LAGUERREPOLYNOM_API LaguerrePolynoms
{
public:
	LaguerrePolynoms(double inputAlpha, double inputBeta, int inputCount, double inputT, double inputStep, double inputApproximation);

	double getAlpha() const;
	double getBeta() const;
	double getSigma() const;
	double getStep() const;
	double getT() const;
	int getPolynomsCount() const;
	int getMaxValue() const;

	std::vector<double> getLagFuncValues() const;
	std::vector<double> getApproxFuncValues() const;

	void getLagFuncValuesPtr(double* outArr) const;
	void getApproxFuncValuesPtr() const;

	void setAlpha(double inputAlpha);
	void setBeta(double inputBeta);
	void setStep(double inputStep);
	void setT(double inputT);
	void setPolynomsCount(int inputCount);
	void setArbitraryFunction(double (*inputArbitFunc)(double));

	void calculateValues();

private:
	void findMaxValue();
	double integral(int n);
	double rectangleSum(int n, double k);
	double resultedFuncValue(int n, double x);
	double lagFuncValue(int n, double x);
	void calculateLagFuncValues();
	void calculateApproxFuncValues();

	double alpha;
	double beta;
	double sigma;

	double maxValue;
	double step;
	double approximation;
	double T;

	int polynomsCount;

	double (*arbitraryFunction)(double);

	std::vector<double> laguerreFuncValues;
	std::vector<double> approximatedFuncValues;
};

extern "C"
{
	LAGUERREPOLYNOM_API LaguerrePolynoms* createLaguerrePolynoms(
		double inputAlpha, double inputBeta, int inputCount, double inputT, double inputStep, double inputApproximation);

	LAGUERREPOLYNOM_API void getAlpha(LaguerrePolynoms* inputInstance, double& outputAlpha);

	LAGUERREPOLYNOM_API void setAlpha(LaguerrePolynoms* inputInstance, double inputAlpha);

	LAGUERREPOLYNOM_API void getBeta(LaguerrePolynoms* inputInstance, double& outputBeta);

	LAGUERREPOLYNOM_API void setBeta(LaguerrePolynoms* inputInstance, double inputBeta);

	LAGUERREPOLYNOM_API void getPolynomsCount(LaguerrePolynoms* inputInstance, int& outputCount);

	LAGUERREPOLYNOM_API void setPolynomsCount(LaguerrePolynoms* inputInstance, int inputCount);

	LAGUERREPOLYNOM_API void getMaxValue(LaguerrePolynoms* inputInstance, double& outputMaxValue);

	LAGUERREPOLYNOM_API void getStep(LaguerrePolynoms* inputInstance, double& outputStep);

	LAGUERREPOLYNOM_API void setStep(LaguerrePolynoms* inputInstance, double inputStep);

	LAGUERREPOLYNOM_API void getT(LaguerrePolynoms* inputInstance, double& outputT);

	LAGUERREPOLYNOM_API void setT(LaguerrePolynoms* inputInstance, double inputT);

	LAGUERREPOLYNOM_API void calculateValues(LaguerrePolynoms* inputInstance);

	LAGUERREPOLYNOM_API void getLagFuncValues(LaguerrePolynoms* inputInstance, double* outputLagValues);

	LAGUERREPOLYNOM_API void getApproxFuncValues(LaguerrePolynoms* inputInstance, double* outputApproxValues);

	LAGUERREPOLYNOM_API void setArbitraryFunction(LaguerrePolynoms* inputInstance, double (*inputArbitraryFunction)(double));
}