#pragma once
#include <string>

using namespace std;

class IJsonSerializable
{
public:
	virtual string serialize() const = 0;
	virtual ~IJsonSerializable() = 0 {};
};

