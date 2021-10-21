#pragma once
#include "Fine.h"

class OverSpeedFine : public Fine {
public:
    OverSpeedFine();

    std::string& GetString();

    int GetPoints();
};
