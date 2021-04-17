#include "ConnectedComponent.h"

#ifndef PGM_IP_H
#define PGM_IP_H

namespace FNNGRE002{
    class PGMimageProcessor{
        private:
            int width;
            int height;
            std::vector<unsigned char **> image;
        
        public:
            PGMimageProcessor();
            ~PGMimageProcessor();

            void loadImage(std::string fileName);

    };
}

#endif