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
	// max and min to determine boundaries for grayscale
	int min = 99999999;
	int max = -min;

	if (!fileIn.is_open()) {
		cout << "Error: File not found";
		exit(1);
	}

	// Get from first two integers in fileIn
	fileIn >> numRows;
	fileIn >> numColumns;

	// dataVect from fileIn and grayVect for grayscale pixels in .ppm file
	vector<vector<int>> dataVect(numRows);
	vector<vector<int>> grayVect(numRows);

	// Populate dataVect
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

	// Write constraints to fileOut
	fileOut << "P3" << endl << numColumns << " " << numRows << endl << 255 << endl;

	// Populate grayVect with dataVect values scaled to 255 max (PPM specs)
	int shade;
	for (int row=0; row<numRows; row++) {
		for (int column=0; column<numColumns; column++) {
			shade = round(((dataVect.at(row).at(column) - min) / static_cast<double>(max-min)) * 255);
			grayVect.at(row).push_back(shade);
		}
	}

	// These 3 vectors will output to the file in grayscale except for pixels changed below
	vector<vector<int>> redVect = grayVect;
	vector<vector<int>> greenVect = grayVect;
	vector<vector<int>> blueVect = grayVect;

	// Color all paths red, save shortest path
	int shortest = 999999999;
	int shortest_index = 0;
	for (int row = 0; row<grayVect.size(); row++) {
		int dist = colorPath(dataVect, redVect, greenVect, blueVect, 252, 25, 63, row);
		if (dist < shortest) {
			shortest = dist;
			shortest_index = row;
		}
	}

	// Color shortes path green
	colorPath(dataVect, redVect, greenVect, blueVect, 31, 253, 13, shortest_index);

	// Write all pixels RGB values to fileOut .ppm file
	for (int row=0; row<numRows; row++) {
		for (int column=0; column<numColumns; column++) {
			fileOut << redVect.at(row).at(column) << " " << greenVect.at(row).at(column) << " " << blueVect.at(row).at(column) << " ";
		}
	}

	cout << "File created: " << outFileName << endl;
}
