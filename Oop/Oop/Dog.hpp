#pragma once
#include "Animal.hpp"
#include <string>

class Dog : public Animal
{
public:
	Dog();
	std::string GetNoise() override;
};