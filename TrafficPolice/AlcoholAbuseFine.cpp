#include "AlcoholAbuseFine.h"

AlcoholAbuseFine::AlcoholAbuseFine() {
    this->fine = "Excess alcohol ratio";
    this->points = 8;
}

std::string& AlcoholAbuseFine::GetString() {
    return this->fine;
}

int AlcoholAbuseFine::GetPoints() {
    return this->points;
}
