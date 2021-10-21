#include <string>
#include "Fine.h"

 void Fine::Setfine(std::string& fine) {
    this->fine = fine;
}

 void Fine::SetPoints(int points) {
    this->points = points;
}

 std::string& Fine::GetString() {
    return fine;
}

 int Fine::GetPoints() {
    return points;
}