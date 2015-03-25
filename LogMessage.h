#pragma once

#include "BaseMessage.h"

class LogMessage : public BaseMessage
{
private:
	string text;

public:
	LogMessage(const string text, const bool isRequest, const string channelName, const string messageType, const string UUID);
	string serialize() const;
	~LogMessage();
};

