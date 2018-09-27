#pragma GCC optimize "O3,omit-frame-pointer,inline"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

vector<vector<double> > read(string filename) {
	ifstream file(filename);  // read from file
	string line, value;  // each line and each value 
	vector<vector<double> > result;
	file >> line;  // skip the header line
	while (file >> line) {
		vector<double> tmpVec;
		for (unsigned i = 0; i < line.size(); ++i)
			if (line[i] == ',')
				line[i] = ' ';
		stringstream tmpSS(line);
		while (tmpSS >> value)
			tmpVec.push_back(atof(value.c_str()));
		tmpVec[0] = 1;
		result.push_back(tmpVec);
	}
	cout << filename << ": " << result.size() << " rows and " << result[0].size() << " columns." << endl;
	return result;
}

int main() {
	// here train[cols] = coeff[0] * train[0] + coeff[1] * train[1] + ... + coeff[cols - 1] * train[cols - 1];
	vector<vector<double> > train = read("save_train.csv"), test = read("save_test.csv");
	unsigned rows = train.size(), cols = train[0].size() - 1;
	vector<double> coeff(cols, 0), tmpCoeff = coeff;
	
	// repeat until convergence
	while (1) {
		for (unsigned j = 0; j < cols; ++j) {
			double tmpSum = 0;
			for (unsigned i = 0; i < rows; ++i) {
				double tmpHypo = 0;
				for (unsigned k = 0; k < cols; ++k)
					tmpHypo += coeff[k] * train[i][k];
				tmpSum += (tmpHypo - train[i][cols]) * train[i][j];
			}
			double alpha = 0.001;
			tmpCoeff[j] = coeff[j] - alpha / cols * tmpSum;
		}
		
		double deviation = 0;
		for (unsigned j = 0; j < cols; ++j)
			deviation += (tmpCoeff[j] - coeff[j]) * (tmpCoeff[j] - coeff[j]);
		cout << deviation << endl;
		if (coeff == tmpCoeff)
			break;
		coeff = tmpCoeff;
		
		ofstream submission("submission.csv");
		submission << "Id,reference" << endl;
		for (unsigned i = 0; i < rows; ++i) {
			double ref = 0;
			for (unsigned j = 0; j < cols; ++j)
				ref += coeff[j] * test[i][j];
			submission << i << ',' << ref << endl;
		}
	}
	
	return 0;
}

