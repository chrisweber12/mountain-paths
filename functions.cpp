#include<vector>
#include<iostream>
#include "functions.h"

using namespace std;

int colorPath(
	const vector<vector<int>>& heightMap,
	vector<vector<int>>& r,
	vector<vector<int>>& g,
	vector<vector<int>>& b,
	int color_r,
	int color_g,
	int color_b,
	int start_row`
) {

	int dist = 0;
	int row = start_row;
	int col = 0;
	int width = heightMap.at(0).size();
	int height = heightMap.size();

	// Loop until reach right edge of map
	while (col<width-1) {
		// Color pixels
		r.at(row).at(col) = color_r;
		g.at(row).at(col) = color_g;
		b.at(row).at(col) = color_b;
		if (row==0) {  // At top edge, can't go up
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
		else if (row==height-1) {  // At bottom edge, can't go down
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
		else { // Can go up, down, or right
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
	// Color last pixel
	r.at(row).at(col) = color_r;
	g.at(row).at(col) = color_g;
	b.at(row).at(col) = color_b;

	return dist;
}
