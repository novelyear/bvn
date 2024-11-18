#pragma once
#include "Map.h"
class MR : public Map {
public:
    MR();
    void loadMap() override;
    void loadPlatform() override;
};

