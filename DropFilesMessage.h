#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>
#include <list>

using namespace rapidjson;

class DropFilesMessage : BaseMessage
{
private:
	std::list<char*> files;

protected:
	//ћожно использовать в потомках дл€ получени€ сериализованной части родительского класа
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:

	DropFilesMessage(std::list<char*> files, const bool isRequest, const string channelName, const string messageType, const string UUID);
	~DropFilesMessage();
};

