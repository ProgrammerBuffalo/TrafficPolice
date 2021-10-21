#pragma once
#include <string>

class Fine
{
protected:
    std::string fine;
    int points;
public:

    void Setfine(std::string& fine);

    void SetPoints(int points);

    virtual std::string& GetString();

    virtual int GetPoints();
};

