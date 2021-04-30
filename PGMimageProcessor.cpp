#include "PGMimageProcessor.h"
#include "ConnectedComponent.cpp"

using namespace std;

namespace FNNGRE002{

    PGMimageProcessor::PGMimageProcessor(){
        width=0;
        height=0;
    }

    PGMimageProcessor::~PGMimageProcessor() {
        for(int i = 0; i < height; i++){
                delete [] image[i];
        }
        delete [] image;
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
            std::stringstream(dimensions) >> height >> std::ws >> width;
            
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

            check = new bool *[height];
            for(int row = 0; row < height; ++row) {
                check[row] = new bool[width];
                for (int col = 0; col < width; ++col) {
                    check[row][col] = false;
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

        if(fileOut) {

            fileOut << "P5\n" << height << " " << width << "\n" << max << "\n";

            for(int row = 0; row < height; ++row) {
                for (int col = 0; col < width; ++col) {
                    fileOut << image[row][col];
                }
            }

            return true;
        }

        else {
            return false;
        }
    }

    int PGMimageProcessor::extractComponents(int threshold, int minValidSize) {
        for(int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if(image[row][col] >= threshold) {
                    queue<pair<int, int> > set;
                    ConnectedComponent cluster;
                    set.push(std::make_pair(row, col));
                    for (int i = 0; i < set.size(); i++) {
                        pair<int , int> myp =  set.front();
                        if (image[myp.first-1][myp.second] >= threshold && checkBounds(myp.first-1, myp.second) == 1) {
                            set.push(std::make_pair(myp.first-1, myp.second));
                        }
                        if (image[myp.first+1][myp.second] >= threshold && checkBounds(myp.first+1, myp.second) == 1) {
                            set.push(std::make_pair(myp.first+1, myp.second));
                        }
                        if (image[myp.first][myp.second-1] >= threshold && checkBounds(myp.first, myp.second-1) == 1) {
                            set.push(std::make_pair(myp.first, myp.second-1));
                        }
                        if (image[myp.first][myp.second+1] >= threshold && checkBounds(myp.first, myp.second+1) == 1) {
                            set.push(std::make_pair(myp.first, myp.second+1));
                        }
                        cluster.set.push_back(std::make_pair(myp.first, myp.second));
                        image[myp.first][myp.second] = 0;
                        check[myp.first][myp.second] = true;
                        set.pop();
                    }
                    if(cluster.set.size() > minValidSize) {
                        cluster.total = cluster.set.size();
                        cluster.id = cc.size();
                        cc.push_back(std::make_shared<ConnectedComponent>(cluster));
                    }
                }
                else {
                    image[row][col] = 0;
                }
            }
        }
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(check[i][j] == true) {
                    image[i][j] = 255;
                }
            }
        }

        /*for(int i = 0; i < cc.size(); i++) {
            ConnectedComponent c = *cc[i];
            for(int j = 0; j < c.set.size(); j++) {
                image[c.set[j].first][c.set[j].second] = 255;
            }
        }*/
        return cc.size();
    }

    void PGMimageProcessor::addComponents(int row, int col, queue<pair<int, int> > &set) {
        if (checkBounds(row, col) == 1) {
            set.push(std::make_pair(row, col));
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

    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize) {
        for(int i = 0; i < cc.size(); i++) {
            ConnectedComponent c = *cc[i];
            if (c.set.size() < minSize || c.set.size() > maxSize) {
                cc.erase(cc.begin() + i);
            }
        }
        return cc.size();
    }

    int PGMimageProcessor::getComponentCount() const {
        return cc.size();
    }

    int PGMimageProcessor::getLargestSize() const {
        ConnectedComponent c = *cc[0];
        int l = c.set.size();
        for(int i = 0; i < cc.size(); i++) {
            ConnectedComponent c1 = *cc[i];
            int l1 = c1.set.size();
            if(l1 > l) {
                l = l1;
            }
        }
        return l;
    }

    int PGMimageProcessor::getSmallestSize() const {
        ConnectedComponent c = *cc[0];
        int s = c.set.size();
        for(int i = 0; i < cc.size(); i++) {
            ConnectedComponent c1 = *cc[i];
            int s1 = c1.set.size();
            if(s1 < s) {
                s = s1;
            }
        }
        return s;
    }

    void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const {
        cout << "Component ID: " << theComponent.id << "\nTotal number of pixels: " << theComponent.total;
    }
}