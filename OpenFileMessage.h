#pragma once

#include "BaseMessage.h"

class OpenFileMessage : public BaseMessage
{
private:
	string file;
public:
	OpenFileMessage(const string file, const bool isRequest, const string channelName, const string messageType, const string UUID);
	virtual string serialize() const;
	~OpenFileMessage();
};

