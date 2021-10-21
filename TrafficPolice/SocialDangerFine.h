#pragma once
#include "Fine.h"

class SocialDangerFine : public Fine
{
public:
	SocialDangerFine();

	std::string& GetString();

	int GetPoints();
};

