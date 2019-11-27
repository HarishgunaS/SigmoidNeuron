#include "Neuron.h"
#include "Data.h"
#include <math.h>
#include <iostream>
#include <vector>
//double inputs[7][3] = { {0, 0, 1}, {1, 1, 1}, {1, 0, 1}, {0, 1, 1}, {1,0,0},{0,1,0},{1,1,0} };
//double outputs[7] = { 0,1,0,1,0,1,1 };
double errorThreshold = pow(10, 0);
double learningRate;
int main()
{
	double totalErrorSum = 1;
	
	int count = 0;
	double previousError = 1;
	Data d = Data("ExampleData.csv");
	learningRate = d.returnRate();
	std::vector<std::vector<double>> inputs = d.returnInputs();
    std::vector<double> outputs = d.returnOutputs();
	int numExamples = outputs.size();
	Neuron n = Neuron(2, 1, learningRate);
	while (totalErrorSum >= errorThreshold)
	{
		count++;
		previousError = totalErrorSum;
		for (int i = 0; i < numExamples; i++)
		{
			n.train(inputs[i], outputs[i]);
			totalErrorSum = 0;
			for (int j = 0; j < numExamples; j++)
			{
				totalErrorSum += abs(outputs[j] - n.predictedOutput(inputs[j]));
			}
		}
		if ( count%1000 == 0)
		{
			std::cout << count << " generation - Average Error: "<<totalErrorSum/numExamples << std::endl;

		}
		if (totalErrorSum/numExamples == previousError/numExamples)
		{
			learningRate *= (1 + learningRate*10000);
		}

	}
	std::cout << "Average Error: " << totalErrorSum/numExamples << std::endl;
	std::cout << "Network has converged:" << std::endl;
	std::cout << "Weights" << std::endl;
	n.printWeights();
	std::cout << "Predictions vs. Actual" << std::endl;
	for (int i = 0; i < outputs.size(); i++)
	{
		std::cout << (n.predictedOutput(inputs[i])) << " vs. " << outputs[i] << std::endl;
	}
	std::cout << "Number of Generations: " << count << std::endl;
	std::cout << "Test Data" << std::endl;
	Data t = Data("TestData.csv");
	inputs = t.returnInputs();
	outputs = t.returnOutputs();

	for (int i = 0; i < outputs.size(); i++)
	{
		std::cout << (n.predictedOutput(inputs[i])) << " vs. " << outputs[i] << std::endl;
		totalErrorSum += abs(outputs[i] - n.predictedOutput(inputs[i]));
	}
	std::cout << "Average Error: " << totalErrorSum/numExamples << std::endl;
	return 0;
}
