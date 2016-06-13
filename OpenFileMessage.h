#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

using namespace rapidjson;

class OpenFileMessage : public BaseMessage
{
private:
	string file;

protected:
	//ћожно использовать в потомках дл€ получени€ сериализованной части родительского класа
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	OpenFileMessage(const string file, const string messageMapId);
	~OpenFileMessage();
};

