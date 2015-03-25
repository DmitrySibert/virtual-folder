#pragma once

#include "BaseMessage.h"

class ContentMessage : public BaseMessage
{
	string path;
public:
	ContentMessage(const string path, const bool isRequest, const string channelName, const string messageType, const string UUID);
	string serialize() const;
	~ContentMessage();
};

