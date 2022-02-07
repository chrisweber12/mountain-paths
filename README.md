# Mountain Paths

Program that can take in data representing mountain heights and visualize the best path

### Usage

Running the command `make` within the project directory will compile the executable *mountain-paths.exe*. Running `make run` will run the program, and running `make clean` will remove *mountain-paths.exe* and any output *.ppm* files. When prompted for a file path, 5 example files are provided within *example-data*, so `example-data/#.dat` can be entered, with # being an integer 1-5. Alternatively, another filepath can be used, provided it fits the constraints shown [below](#input). The output will be a .ppm (Portable Pixel Map) file in the same location as the input file, which will be a greyscale representation of the data with red paths shown from left to right across the image, one starting at the leftmost pixel in each row. The [best overall path](#algorithm) will be colored green.

### Specifics

#### Input

The input file should consist of only integers, with the first two representing the number of rows and columns in the area, and the rest of the integers representing the altitude at specific points in the terrain, in row-major order. Newlines between rows are allowed, but not required.

#### Algorithm

In determining the best path to the other side of the map, the program implements a greedy algorithm in which each step moves directly right or diagonally right, depending on which step has the smallest change in altitude (with drops in altitude being treated the same as increases). The best path, highlighted green, will be the path which has the lowest sum of step costs.

#### Output File

The output will be a .ppm file of Plain PPM or P3 format. More information can be found [here](http://netpbm.sourceforge.net/doc/ppm.html).
