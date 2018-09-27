#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

int main() {
	ifstream train_data("train_data.txt");
	ifstream test_data("test_data.txt");
	
	ofstream train("train.txt");
	ofstream cv("cv.txt");
	ofstream test("test.txt");
	
	string temp, index_str;
	
	srand(time(NULL));
	
	while (getline(train_data, temp)) {
		if (rand() % 10)
			train << temp << endl;
		else
			cv << temp << endl;
	}
	
	vector<string> vec(282796);
	
	while (getline(test_data, temp)) {
		stringstream ss(temp);
		
		ss >> index_str;
		unsigned index = atoi(index_str.c_str());
		vec[index] = temp;
		if (index % 10000 == 0)
			cout << index << endl;
	}
	
	for (unsigned i = 0; i < vec.size(); ++i)
		test << vec[i] << endl;
	
	return 0;
}

