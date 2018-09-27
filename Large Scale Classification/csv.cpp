#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream pred("pred.txt");
	ofstream csv("sub.csv");
	
	unsigned i = 0;
	string temp;
	
	csv << "id,label" << endl;
	while (getline(pred, temp))
		csv << i++ << ',' << temp << endl;

	return 0;
}

