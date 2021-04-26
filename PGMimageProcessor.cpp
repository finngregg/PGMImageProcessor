#include "PGMimageProcessor.h"
#include "ConnectedComponent.cpp"

using namespace std;

namespace FNNGRE002{

    vector<ConnectedComponent> clusters;

    PGMimageProcessor::PGMimageProcessor(){
        width=0;
        height=0;
    }

    PGMimageProcessor::~PGMimageProcessor() {
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
        unsigned char pixel;

        if(file) {
            getline(file, line);

            getline(file, comment);
            while(comment.at(0)=='#'){
                getline(file, comment);
            }
            dimensions = comment;
            std::stringstream(dimensions) >> width >> std::ws;
            std::stringstream(dimensions) >> height >> std::ws;
            
            getline(file, max);

            ss << file.rdbuf();

            image = new unsigned char *[height];
            for(int row = 0; row < height; ++row) {
                image[row] = new unsigned char[width];
                for (int col = 0; col < width; ++col) {
                    ss >> pixel;
                    image[row][col] = pixel;
                }
            }

            file.close();
        }
        else {
            cout << "File Not Found\n\n";
        }
    }

    int PGMimageProcessor::extractComponents(char threshold, int minValidSize) {
        for(int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if(image[row][col] >= threshold) {
                    queue<pair<int, int> > set;
                    ConnectedComponent cluster;
                    addComponents(row, col, set);
                    cluster.set.push_back(std::make_pair(row, col));
                    image[row][col] = 0;
                    for (int i = 0; i < set.size(); i++) {
                        pair<int , int> myp =  set.front();
                        if (image[get<0>(myp)][get<1>(myp)] >= threshold) {
                            addComponents(get<0>(myp), get<1>(myp), set);
                            image[get<0>(myp)][get<1>(myp)] = 0;
                        }
                        else {
                            image[get<0>(myp)][get<1>(myp)] = 255;
                            set.pop();
                        }
                    }
                    
                }
                else {
                    image[row][col] = 255;
                    continue;
                }
            }
        }
        
    }

    int PGMimageProcessor::addComponents(int row, int col, queue<pair<int, int> > set) {
        if (checkBounds(row-1, col) == 1) {
            set.push({row-1, col});
        }
        if (checkBounds(row+1, col) == 1) {
            set.push({row+1, col});
        }
        if (checkBounds(row, col-1) == 1) {
            set.push({row, col-1});
        }
        if (checkBounds(row, col+1) == 1) {
            set.push({row, col+1});
        }
    }

    int PGMimageProcessor::checkBounds(int row, int col) {
        if (row >= 0 && row < height && col >= 0 && col < width) {
            return 1;
        }
        else {
            return 0;
        }
    }

}