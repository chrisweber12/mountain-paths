#include<vector>
#include<iostream>
#include "functions.h"

using namespace std;

int colorPath(const vector<vector<int>>& heightMap, vector<vector<int>>& r, vector<vector<int>>& g, vector<vector<int>>& b, int color_r, int color_g,
	int color_b, int start_row) {
	int dist = 0;
	int row = start_row;
	int col = 0;
	int width = heightMap.at(0).size();
	int height = heightMap.size();

	while (col<width-1) {
		r.at(row).at(col) = color_r;
		g.at(row).at(col) = color_g;
		b.at(row).at(col) = color_b;
		if (row==0) {  // no up choice
			if (
				abs( heightMap.at(row).at(col) - heightMap.at(row).at(col+1) )
				> abs( heightMap.at(row).at(col) - heightMap.at(row+1).at(col+1) )
			) {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row+1).at(col+1));
				row++;
				col++;
			}
			else {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row).at(col+1));
				col++;
			}
		}
		else if (row==height-1) {  // no down choice
			if (
				abs( heightMap.at(row).at(col) - heightMap.at(row).at(col+1) )
				> abs( heightMap.at(row).at(col) - heightMap.at(row-1).at(col+1) )
			) {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row-1).at(col+1));
				row--;
				col++;
			}
			else {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row).at(col+1));
				col++;
			}
		}
		else { // in middle
			if (
				( abs( heightMap.at(row).at(col) - heightMap.at(row-1).at(col+1) )
				< abs( heightMap.at(row).at(col) - heightMap.at(row).at(col+1) ) )
				&&
				( abs( heightMap.at(row).at(col) - heightMap.at(row-1).at(col+1) )
				< abs( heightMap.at(row).at(col) - heightMap.at(row+1).at(col+1) ) )
			) {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row-1).at(col+1));
				row--;
				col++;
			}
			else if (
				abs( heightMap.at(row).at(col) - heightMap.at(row+1).at(col+1) )
				< abs( heightMap.at(row).at(col) - heightMap.at(row).at(col+1) )
			) {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row+1).at(col+1));
				row++;
				col++;
			}
			else {
				dist = dist + abs(heightMap.at(row).at(col) - heightMap.at(row).at(col+1));
				col++;
			}
		}
	}
	r.at(row).at(col) = color_r;
	g.at(row).at(col) = color_g;
	b.at(row).at(col) = color_b;
	
	return dist;
}
