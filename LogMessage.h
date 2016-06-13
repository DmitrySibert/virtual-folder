#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

using namespace rapidjson;

class LogMessage : public BaseMessage
{
private:
	string text;

protected:
	//ћожно использовать в потомках дл€ получени€ сериализованной части родительского класа
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	LogMessage(const string text, const string messageMapId);
	~LogMessage();
};

