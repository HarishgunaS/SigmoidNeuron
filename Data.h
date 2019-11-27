#include <fstream>
#include <string>
#include <iostream>
#include <vector>
class Data
{
private:
    std::vector<std::vector<double>> inputs;
    std::vector<double> outputs;
    double rate;   
public:
    Data(std::string fileName)
    {
        
        
        std::ifstream ip(fileName);
        std::string tempString;
        
        std::getline(ip,tempString,'\n');
        double r = std::stod(tempString);

        std::getline(ip,tempString,',');
        int numExamples = std::stoi(tempString);
        
        std::getline(ip,tempString,'\n');
        int numInputs = std::stoi(tempString);
        
        inputs.resize(numExamples);
        outputs.resize(numExamples);
        
        for(int n = 0; n < numExamples; n++)
        {
            inputs[n].resize(numInputs);
            for(int i = 0; i < numInputs; i++)
            {
                std::getline(ip,tempString,',');
                double temp = std::stod(tempString);
                inputs[n][i] = temp;
            }
            std::getline(ip,tempString,'\n');
            double temp = std::stod(tempString);
            outputs[n] = temp;
        }
        ip.close();
        rate = r;
    }
    std::vector<std::vector<double>> returnInputs()
    {
        return inputs;
    }
    std::vector<double> returnOutputs()
    {
        return outputs;
    }
    double returnRate()
    {
        return rate;
    }
};
