#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>

#ifndef CONNECTED_COMP_H
#define CONNECTED_COMP_H

namespace FNNGRE002{
    class ConnectedComponent{
        public:
         int total; // the number of pixels in the component
         int id; // identiﬁer for a component
         std::vector< std::pair<int,int> >; // to store the pixels in that component
            
    };
}

#endif