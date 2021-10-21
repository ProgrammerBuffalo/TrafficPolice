#pragma once
#include "Fine.h"

class AlcoholAbuseFine : public Fine {
public:
    AlcoholAbuseFine();

    std::string& GetString();

    int GetPoints();

};
