#include "OverSpeedFine.h"

OverSpeedFine::OverSpeedFine() {
    this->fine = "Increased speed in the wrong place";
    this->points = 5;
}

std::string& OverSpeedFine::GetString() {
    return this->fine;
}

int OverSpeedFine::GetPoints() {
    return this->points;
}
