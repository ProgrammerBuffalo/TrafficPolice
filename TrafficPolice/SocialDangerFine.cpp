#include "SocialDangerFine.h"

SocialDangerFine::SocialDangerFine() {
    this->fine = "Risking other people's lives";
    this->points = 15;
}
std::string& SocialDangerFine::GetString() {
    return this->fine;
}

int SocialDangerFine::GetPoints() {
    return this->points;
}
