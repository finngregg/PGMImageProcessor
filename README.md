# README for CSC3022F Assignment 3

## huffencode.cpp
This class contains all methods for manipulating the data contained in the main method which deals with the recieving of input instructions, input file names and output file names. 

This class is responsible for creating an object of the huffmanTree class and encoding the data stored in the input file using:
* huffmanTree methods such as buildTree() and buildCodeTable()
* bit packing the contents to acheive better compression

## huffmanTree.cpp
This class defines the variables and methods of the huffmanTree class. These variables and methods include:

* Private Variables
  * unordered_map<char, int> mapping, priority_queue<HuffmanNode, vector<HuffmanNode>,compareFrequency> myQueue
* Public Variables
  * shared_ptr<HuffmanNode> root

* HuffmanTree(unordered_map<char, int> map) - Default Constructor
* ~HuffmanTree() - Destructor
* HuffmanTree(const HuffmanTree & tree) - Copy Constructor
* HuffmanTree(HuffmanTree && tree) - Move Constructor
* HuffmanTree & operator=(const HuffmanTree & tree) - Copy Assignment Operator
* HuffmanTree & operator=(HuffmanTree && tree) - Move Assignment Operator
* void buildTree() - used to build the Huffman Tree structure according to the priorty queue
* void insertNode(int i, SLDALE003::HuffmanNode l, SLDALE003::HuffmanNode r) - used to insert a node in the buildTree() method
* void buildCodeTable(unordered_map<char, string> &map, shared_ptr<SLDALE003::HuffmanNode> r, string bitString) - generates the code table populated by bit streams using a form of recursive call
* void writeCodeTableToFile(unordered_map<char, string> map, string outputBuffer, string outputFile, string outputPath) - generates output header and data file from given parameters
* double returnRatio(int size1, int size2) - returns a ratio of compression performance given different lengths/sizes of files

## huffmanTree.h
This class contains all the method calls held in huffmanTree.cpp. This class also defines the compareFrequency struct which returns a boolean value which is determined by comparing the frequency of two nodes.

## huffmanNode.cpp
This class defines the variables and methods of the huffmanNode class. These variables and methods include:
* char letter, int frequency, shared_ptr<HuffmanNode> left, shared_ptr<HuffmanNode> right
* HuffmanNode(char l, int f) - Default Constructor
* ~HuffmanNode() - Destructor
* HuffmanNode(const HuffmanNode & node) - Copy Constructor
* HuffmanNode(HuffmanNode && node) - Move Constructor
* HuffmanNode & operator=(const HuffmanNode & node) - Copy Assignment Operator
* HuffmanNode & operator=(HuffmanNode && node) - Move Assignment Operator

## huffmanNode.h
This class contains all the method calls held in huffmanNode.cpp

## Makefile
The Makefile compiles and links all necessary files into the volimage.run executable. 

The input is of the form: ./huffencode "input file name" "output file base name"
N.B: The output file type changes so this extension must be excluded

Some examples have been commented out in the Makfile. The main commands include:

* make - compiles files
* make run - runs executable according to specific instruction
* make test - runs unit tests to check code is performing as expecteds
* make clean - removes executables

