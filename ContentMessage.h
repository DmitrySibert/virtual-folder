#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

using namespace rapidjson;

class ContentMessage : public BaseMessage
{
	string path;
protected:
	//ћожно использовать в потомках дл€ получени€ сериализованной части родительского класа
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	ContentMessage(const string path, const bool isRequest, const string channelName, const string messageType, const string UUID);
	~ContentMessage();
};

