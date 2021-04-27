#include "PGMimageProcessor.h"
#include "ConnectedComponent.cpp"

using namespace std;

namespace FNNGRE002{

    vector<ConnectedComponent> cc;

    PGMimageProcessor::PGMimageProcessor(){
        width=0;
        height=0;
    }

    PGMimageProcessor::~PGMimageProcessor() {
        for(int i = 0; i < height; i++){
                delete [] image[i];
            delete [] image;
        }
    }

    void PGMimageProcessor::loadImage(std::string fileName){
        ifstream fileIn(fileName, ios::binary);
        string line;
        string comment;
        string dimensions;
        stringstream ss;
        unsigned char pixel;

        if(fileIn) {
            getline(fileIn, line);

            getline(fileIn, comment);
            while(comment.at(0)=='#'){
                getline(fileIn, comment);
            }
            dimensions = comment;
            std::stringstream(dimensions) >> width >> std::ws;
            std::stringstream(dimensions) >> height >> std::ws;
            
            getline(fileIn, max);

            ss << fileIn.rdbuf();

            image = new unsigned char *[height];
            for(int row = 0; row < height; ++row) {
                image[row] = new unsigned char[width];
                for (int col = 0; col < width; ++col) {
                    ss >> pixel;
                    image[row][col] = pixel;
                }
            }

            fileIn.close();
        }
        else {
            cout << "File Not Found\n\n";
        }
    }

    bool PGMimageProcessor::writeComponents(const std::string & outFileName) {
        std::ofstream fileOut(outFileName,std::ios_base::out
                              |std::ios_base::binary
                              |std::ios_base::trunc
                            );

        fileOut << "P5\n" << width << " " << height << "\n" << max << "\n";

        for(int row = 0; row < height; ++row) {
                for (int col = 0; col < width; ++col) {
                    fileOut << image[row][col];
                }
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
                            cluster.set.push_back(std::make_pair(get<0>(myp), get<1>(myp)));
                            image[get<0>(myp)][get<1>(myp)] = 0;
                        }
                        else {
                            image[get<0>(myp)][get<1>(myp)] = 0;
                            set.pop();
                        }
                    }
                    if(cluster.set.size() > minValidSize) {
                        cluster.total = cluster.set.size();
                        cluster.id = cc.size();
                        cc.push_back(cluster);
                    }
                }
                else {
                    image[row][col] = 0;
                    continue;
                }
            }
        }
        for(int i = 0; i < cc.size(); i++) {
            for(int j = 0; j < cc[i].set.size(); j++) {
                image[get<0>(cc[i].set[j])][get<1>(cc[i].set[j])] = 255;
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

    int filterComponentsBySize(int minSize, int maxSize) {
        for(int i = 0; i < cc.size(); i++) {
            if (cc[i].set.size() < minSize || cc[i].set.size() > maxSize) {
                cc.erase(cc.begin() + i);
            }
        }
    }

}