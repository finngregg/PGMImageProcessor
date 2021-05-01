#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>
#include <queue>

#ifndef CONNECTED_COMP_H
#define CONNECTED_COMP_H

namespace FNNGRE002{
    class ConnectedComponent{
        public:
            int total; // the number of pixels in the component
            int id; // identiﬁer for a component
            std::vector< std::pair<int, int> > set; // to store the pixels in that component

            ConnectedComponent();
            ~ConnectedComponent();

            ConnectedComponent(const ConnectedComponent& rhs) : id(rhs.id), total(rhs.total) { }
            ConnectedComponent(ConnectedComponent && rhs) : id(std::move(rhs.id)), total(std::move(rhs.total)) { }

            ConnectedComponent & operator=(const ConnectedComponent& rhs);
            ConnectedComponent & operator=(ConnectedComponent && rhs);
    };
}

#endif