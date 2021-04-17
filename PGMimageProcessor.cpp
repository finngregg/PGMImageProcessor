#include "PGMimageProcessor.h"

using namespace std;

namespace FNNGRE002{

    PGMimageProcessor::PGMimageProcessor(){
        width=0;
        height=0;
    }

    PGMimageProcessor::~PGMimageProcessor(){
        for(int i = 0; i < image.size(); i++){
            for(int j = 0; j < height; j ++){
                delete [] image[i][j];
            }
            delete [] image[i];
        }
    }

    void PGMimageProcessor::loadImage(std::string fileName){
        ifstream file(fileName, ios::binary);
        string line;
        string comment;
        string dimensions;
        string max;
        stringstream ss;

        getline(file, line);

        getline(file, comment);
        while(line.at(0)=='#'){
            getline(file, comment);
        }
        dimensions = comment;
        
        getline(file, max);

        ss << file.rdbuf();
       
        for(int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                ss >> image[row][col];
            }
        }

        file.close();

        std::stringstream(dimensions) >> width >> std::ws;
        std::stringstream(dimensions) >> height >> std::ws;

    }

}