#pragma GCC optimize "O3,omit-frame-pointer,inline"
#include <iostream>
#include <fstream> 
#include <vector>
#include <bitset>
using namespace std;

// reverse an integer because it's MSB first
int reverse(int num) {
    unsigned char c1 = (num >> 0) & 255, c2 = (num >> 8) & 255, c3 = (num >> 16) & 255, c4 = (num >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + ((int)c4 << 0);
}

// read from database, return images or labels based on the type of file
pair<vector<vector<vector<unsigned char> > >, vector<unsigned char> > read(string file_path) {
	bool succeed = 0;
	int magic_num, num_items, num_imgs, num_rows, num_cols;
    unsigned char temp;
    vector<vector<vector<unsigned char> > > images;
    vector<unsigned char> labels;
    
    ifstream file(file_path, ios::binary);
	cout << "reading file: \"" << file_path << "\"" << endl;
    file.read((char*)&magic_num, sizeof(magic_num));
    magic_num = reverse(magic_num);
    cout << "magic number: " << magic_num << endl;
    
	if (magic_num == 2051) {  // if it's a image file
	    file.read((char*)&num_imgs, sizeof(num_imgs));
	    num_imgs = reverse(num_imgs);
	    cout << "number of images: " << num_imgs << endl;
    	file.read((char*)&num_rows, sizeof(num_rows));
    	num_rows = reverse(num_rows);
    	cout << "number of rows: " << num_rows << endl;
    	file.read((char*)&num_cols, sizeof(num_cols));
    	num_cols = reverse(num_cols);
    	cout << "number of columns: " << num_cols << endl;
	    
		images.resize(num_imgs);
		for (int i = 0; i < num_imgs; i++) {
			images[i].resize(num_rows);
	        for (int j = 0; j < num_rows; j++) {
				images[i][j].resize(num_cols);
	        	for (int k = 0; k < num_cols; k++)
	        		file.read((char*)&images[i][j][k], sizeof(temp));
			}
		}
		succeed = 1;
	} else if (magic_num == 2049) {  // if it's a label file
	    file.read((char*)&num_items, sizeof(num_items));
	    num_items = reverse(num_items);
	    cout << "number of items: " << num_items << endl;
	    
		labels.resize(num_items);
		for (int i = 0; i < num_items; i++)
			file.read((char*)&labels[i], sizeof(temp));
		succeed = 1;
	}
	if (succeed)
		cout << "reading file: \"" << file_path << "\" completed" << endl << endl;
	else
		cout << "reading file: \"" << file_path << "\" failed" << endl << endl;
	return pair<vector<vector<vector<unsigned char> > >, vector<unsigned char> >(images, labels);
}

int main() {
	vector<vector<vector<unsigned char> > > train_imgs = read("train-images.idx3-ubyte").first;
	vector<unsigned char> train_lbls = read("train-labels.idx1-ubyte").second;
	vector<vector<vector<unsigned char> > > test_imgs = read("t10k-images.idx3-ubyte").first;
	vector<unsigned char> test_lbls = read("t10k-labels.idx1-ubyte").second;
	
	ofstream train("train.csv"), test("test.csv");
	cout << "writing to files..." << endl;
	for (int i = 0; i < (int)train_imgs.size(); i++) {
		for (int j = 0; j < 28; j++) {
			for (int k = 0; k < 28; k++)
				train << (unsigned)train_imgs[i][j][k] << ',';
		}
		train << (unsigned)train_lbls[i] << endl;
	}
	for (int i = 0; i < (int)test_imgs.size(); i++) {
		for (int j = 0; j < 28; j++) {
			for (int k = 0; k < 28; k++)
				test << (unsigned)test_imgs[i][j][k] << ',';
		}
		test << (unsigned)test_lbls[i] << endl;
	}
	cout << "writing to files completed" << endl;
	
	return 0;
}

