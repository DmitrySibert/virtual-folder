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
	//����� ������������ � �������� ��� ��������� ��������������� ����� ������������� �����
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	OpenFileMessage(const string file, const bool isRequest, const string channelName, const string messageType, const string UUID);
	~OpenFileMessage();
};

