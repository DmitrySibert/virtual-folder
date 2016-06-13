#pragma once

#include  "IJsonSerializable.h"
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

using namespace rapidjson;

class BaseMessage:public IJsonSerializable
{
private:
	string messageMapId;
protected:
	//ћожно использовать в потомках дл€ получени€ сериализованной части родительского класа
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	BaseMessage(){}
	BaseMessage(const string messageMapId);
	virtual string serialize() const;
	string getMessageMapId() const { return this->messageMapId; }
	~BaseMessage();
};

