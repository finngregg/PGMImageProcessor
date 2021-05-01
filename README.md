# README for CSC3022F Assignment 3

## PGMimageProcessor.h
This class contains all the method calls held in PGMimageProcessor.cpp. 

## PGMimageProcessor.cpp
This class contains all methods necessary for reading and manipulating a pgm image as well as writing to a new pgm image file. This class is responsible for creating a vector of ConnectedComponent objects storing the connected pixels of the input image.

Variables and methods include:

* Private Variables
  * int width, int height, string max, unsigned char ** image, bool ** check, vector<shared_ptr<ConnectedComponent>> cc

* PGMimageProcessor() - Default Constructor
* ~PGMimageProcessor() - Destructor
* PGMimageProcessor(const PGMimageProcessor & rhs) - Copy Constructor
* PGMimageProcessor(PGMimageProcessor && rhs) - Move Constructor
* PGMimageProcessor & operator=(const PGMimageProcessor & rhs) - Copy Assignment Operator
* PGMimageProcessor & operator=(PGMimageProcessor & rhs) - Move Assignment Operator
* void loadImage(std::string fileName) - loads pgm image into unsigned char ** array 
* int extractComponents(int threshold, int minValidSize) - iterates through array, finding pixels higher than the threshold and adds them to ConnectedComponent objects
* void addComponents(int row, int col, queue<pair<int, int> > &set) - adds pixel to temporary queue
* int checkBounds(int row, int col) - checks to ensure surrounding pixels are not out of bounds
* int filterComponentsBySize(int minSize, int maxSize) - filters ConnectedComponents by their sizes
* bool writeComponents(const std::string & outFileName) - writes the modified pgm to a new pgm file 'outFileName'
* int getComponentCount(void) const - returns total number of ConnectedComponents in the vector
* int getLargestSize(void) const - return number of pixels in largest component
* int getSmallestSize(void) const - return number of pixels in smallest component
* void printComponentData(const ConnectedComponent & theComponent) const - print the data for a component to std::cout (data being the ConnectedComponents ID and total)
* void printAllData() - prints the data for every ConnectedComponent to std::cout

## ConnectedComponent.h
This class contains all the method calls held in ConnectedComponent.cpp. 

## ConnectedComponent.cpp

Variables and methods include:

* Private Variables
  int total, int id, std::vector< std::pair<int, int> > set

* ConnectedComponent() - Default Constructor
* ~ConnectedComponent() - Destructor
* ConnectedComponent(const ConnectedComponent& rhs) - Copy Constructor
* ConnectedComponent(ConnectedComponent && rhs) - Move Constructor
* ConnectedComponent & operator=(const ConnectedComponent& rhs) - Copy Assignment Operator
* ConnectedComponent & operator=(ConnectedComponent && rhs) - Move Assignment Operator

## findcomp.cpp

Contains the main method which helps process the file name and command line flags entered by the user. 

## Makefile
The Makefile compiles and links all necessary files into the findcomp executable. 

The main commands include:

* make - compiles files
* make run - runs executable according to specific instruction
* make test - runs unit tests to check code is performing as expecteds
* make clean - removes executables

