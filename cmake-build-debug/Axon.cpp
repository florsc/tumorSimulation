//
// Created by florian on 9/9/21.
//

#include "Axon.h"
Axon::Axon() {}

void Axon::growthStep(double i) {
    tipPositions.push_back({i,i,i});
}

void Axon::run() {
    for(int i=0;i<100;i++)
    {
        growthStep(i);
    }

}
