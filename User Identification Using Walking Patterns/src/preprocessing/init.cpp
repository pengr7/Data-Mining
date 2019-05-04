#pragma GCC optimize "O3,omit-frame-pointer,inline"
#include "headers.h"

const int num_users = 22;
const int window_size = 100, window_slide = 50;

int main() {
	for (int user_id = 1; user_id <= num_users; user_id++) {
		cout << "current user id: " << user_id << endl;
		ifstream input("raw/" + to_string(user_id) + ".csv");
		ofstream output("data/" + to_string(user_id) + ".csv");
		string s;
		vector<vector<double>> data;
		while (getline(input, s)) {
			for (auto it = s.begin(); it != s.end(); ++it)
				if (*it == ',')
					* it = ' ';
			stringstream ss(s);
			vector<double> vec;
			double temp;
			ss >> temp;
			while (ss >> temp)
				vec.push_back(temp);
			data.push_back(vec);
		}
		for (unsigned pos = 0; pos + window_size <= data.size(); pos += window_slide) {
			auto window = vector<vector<double>>(data.begin() + pos, data.begin() + pos + window_size);

			double mean_x = 0, mean_y = 0, mean_z = 0;
			for (int i = 0; i < window_size; i++) {
				mean_x += window[i][0] / window_size;
				mean_y += window[i][1] / window_size;
				mean_z += window[i][2] / window_size;
			}

			double sd_x = 0, sd_y = 0, sd_z = 0;
			for (int i = 0; i < window_size; i++) {
				sd_x += pow(window[i][0] - mean_x, 2) / window_size;
				sd_y += pow(window[i][1] - mean_y, 2) / window_size;
				sd_z += pow(window[i][2] - mean_z, 2) / window_size;
			}
			sd_x = sqrt(sd_x);
			sd_y = sqrt(sd_y);
			sd_z = sqrt(sd_z);

			vector<vector<double>> window_t = { {}, {}, {} };
			for (int i = 0; i < window_size; i++) {
				window_t[0].push_back(window[i][0]);
				window_t[1].push_back(window[i][1]);
				window_t[2].push_back(window[i][2]);
			}
			sort(window_t[0].begin(), window_t[0].end());
			sort(window_t[1].begin(), window_t[1].end());
			sort(window_t[2].begin(), window_t[2].end());
			double median_x = (window_t[0][window_size / 2 - 1] + window_t[0][window_size / 2]) / 2;
			double median_y = (window_t[1][window_size / 2 - 1] + window_t[1][window_size / 2]) / 2;
			double median_z = (window_t[2][window_size / 2 - 1] + window_t[2][window_size / 2]) / 2;
			for (int i = 0; i < window_size; i++) {
				window_t[0][i] = abs(window_t[0][i] - median_x);
				window_t[1][i] = abs(window_t[1][i] - median_y);
				window_t[2][i] = abs(window_t[2][i] - median_z);
			}
			sort(window_t[0].begin(), window_t[0].end());
			sort(window_t[1].begin(), window_t[1].end());
			sort(window_t[2].begin(), window_t[2].end());
			double mad_x = (window_t[0][window_size / 2 - 1] + window_t[0][window_size / 2]) / 2;
			double mad_y = (window_t[1][window_size / 2 - 1] + window_t[1][window_size / 2]) / 2;
			double mad_z = (window_t[2][window_size / 2 - 1] + window_t[2][window_size / 2]) / 2;

			output << mean_x << "," << mean_y << "," << mean_z << ",";
			output << sd_x << "," << sd_y << "," << sd_z << ",";
			output << mad_x << "," << mad_y << "," << mad_z << ",";
			output << user_id << endl;
		}
	}
	return 0;
}

