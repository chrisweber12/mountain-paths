#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cmath>
#include "functions.h"

using namespace std;

int main()
{
	int numRows;
	int numColumns;
	string inFileName;
	string outFileName;

	cout << "Input file path: ";
	cin >> inFileName;

	outFileName = inFileName + ".ppm";

	ifstream fileIn{inFileName};
	ofstream fileOut{outFileName};

	int rowNum = 0;
	int columnNum = 0;
	int num;
	int min = 99999999;
	int max = -min;

	if (!fileIn.is_open()) {
		cout << "Error: File not found";
		exit(1);
	}

	fileIn >> numRows;
	fileIn >> numColumns;

	vector<vector<int>> dataVect(numRows);
	vector<vector<int>> grayVect(numRows);

	while (fileIn >> num) {
		if (num > max) max = num;
		if (num < min) min = num;
		columnNum++;
		if (columnNum > numColumns) {
			columnNum = 1;
			rowNum++;
		}
		try {
			dataVect.at(rowNum).push_back(num);
		}
		catch(std::out_of_range) {
			cout << "Error: too much data";
			exit(1);
		}
	}

	fileOut << "P3" << endl << numColumns << " " << numRows << endl << 255 << endl;

	int shade;
	for (int row=0; row<numRows; row++) {
		for (int column=0; column<numColumns; column++) {
			shade = round(((dataVect.at(row).at(column) - min) / static_cast<double>(max-min)) * 255);
			grayVect.at(row).push_back(shade);
		}
	}

	vector<vector<int>> redVect = grayVect;
	vector<vector<int>> greenVect = grayVect;
	vector<vector<int>> blueVect = grayVect;

	int shortest = 999999999;
	int shortest_index = 0;

	for (int row = 0; row<grayVect.size(); row++) {
		int dist = colorPath(dataVect, redVect, greenVect, blueVect, 252, 25, 63, row);
		if (dist < shortest) {
			shortest = dist;
			shortest_index = row;
		}
	}

	colorPath(dataVect, redVect, greenVect, blueVect, 31, 253, 13, shortest_index);

	for (int row=0; row<numRows; row++) {
		for (int column=0; column<numColumns; column++) {
			fileOut << redVect.at(row).at(column) << " " << greenVect.at(row).at(column) << " " << blueVect.at(row).at(column) << " ";
		}
	}

	cout << "File created: " << outFileName << endl;
}
