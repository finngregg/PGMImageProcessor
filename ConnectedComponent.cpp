#include "ConnectedComponent.h"

using namespace std;

namespace FNNGRE002{
    ConnectedComponent::ConnectedComponent(){
        id=0;
        total=0;
    }

    ConnectedComponent::~ConnectedComponent() { }

    ConnectedComponent &ConnectedComponent::operator=(ConnectedComponent&& rhs) {
        if(this != &rhs) { 
            id = std::move(rhs.id);
            total = std::move(rhs.total);
        }
        return *this; 
    }

    ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent & rhs) {
        if(this != &rhs) { 
            id = rhs.id;
            total = rhs.total;
        }
        return *this; 
    }
}