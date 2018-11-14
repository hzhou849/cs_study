#pragma once
#include "Animal.hpp"
#include <string>

class Cat : public Animal
{
public:
	Cat();
	std::string GetNoise() override;
};