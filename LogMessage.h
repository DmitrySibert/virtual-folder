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
	//����� ������������ � �������� ��� ��������� ��������������� ����� ������������� �����
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	LogMessage(const string text, const bool isRequest, const string channelName, const string messageType, const string UUID);
	~LogMessage();
};

