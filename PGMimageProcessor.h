#include "ConnectedComponent.cpp"

#ifndef PGM_IP_H
#define PGM_IP_H

namespace FNNGRE002{
    class PGMimageProcessor{
        private:
            int width;
            int height;
            std::string max;
            unsigned char ** image;
            bool ** check;

            vector<shared_ptr<ConnectedComponent>> cc;
        
        public:
            PGMimageProcessor();
            ~PGMimageProcessor();

            void loadImage(std::string fileName);
            int extractComponents(int threshold, int minValidSize);
            void addComponents(int row, int col, queue<pair<int, int> > &set);
            int checkBounds(int row, int col);
            int filterComponentsBySize(int minSize, int maxSize);
            bool writeComponents(const std::string & outFileName);
            int getComponentCount(void) const;
            int getLargestSize(void) const;
            int getSmallestSize(void) const;
            void printComponentData(const ConnectedComponent & theComponent) const;
    
    };
}

#endif