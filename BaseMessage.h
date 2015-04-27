#pragma once

#include  "IJsonSerializable.h"
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

using namespace rapidjson;

class BaseMessage:public IJsonSerializable
{
private:
	bool isRequest;
	string channelName;
	string messageType;
	string UUID;
protected:
	//ћожно использовать в потомках дл€ получени€ сериализованной части родительского класа
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	BaseMessage(){}
	BaseMessage(const bool isRequest, const string channelName, const string messageType, const string UUID);
	virtual string serialize() const;
	bool getIsRequest() const { return this->isRequest; }
	string getChannelName() const { return this->channelName; }
	string getMessageType() const { return this->messageType; }
	string getUuid() const { return this->UUID; }
	~BaseMessage();
};

