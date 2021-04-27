#include "ConnectedComponent.cpp"

#ifndef PGM_IP_H
#define PGM_IP_H

namespace FNNGRE002{
    class PGMimageProcessor{
        private:
            int width;
            int height;
            unsigned char ** image;
        
        public:
            PGMimageProcessor();
            ~PGMimageProcessor();

            void PGMimageProcessor::loadImage(std::string fileName);
            int extractComponents(char threshold, int minValidSize);
            int addComponents(int row, int col, queue<pair<int, int> > set);
            int checkBounds(int row, int col);
            int filterComponentsBySize(int minSize, int maxSize);
    };
}

#endif