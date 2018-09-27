#pragma GCC optimize "O3,omit-frame-pointer,inline"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#define MAX_INDEX 132

using namespace std;

void process(string input, string output) {
	// create file stream
	ifstream file_in(input);
	ofstream file_out(output);

	// process each sample
	string row, temp;
	while (getline(file_in, row)) {
		vector<double> sample(MAX_INDEX + 1);  // max index is 132, and sample[0] equals the type
		stringstream ss(row);
		ss >> temp;
		sample[0] = atof(temp.c_str());
		while (ss >> temp) {
			auto colon = find(temp.begin(), temp.end(), ':');
			int index = atoi(string(temp.begin(), colon).c_str());
			double value = atof(string(colon + 1, temp.end()).c_str());
			if (index <= MAX_INDEX) 
				sample[index] = value;
		}
		for (unsigned j = 0; j < MAX_INDEX; ++j)
			file_out << sample[j] << ',';
		file_out << sample[MAX_INDEX] << endl;
	}
}

int main() {	
	// Process samples
	process("train_data.txt", "train_out.csv");
	process("test_data.txt", "test_out.csv");

	return 0;
}

