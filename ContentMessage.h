#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

using namespace rapidjson;

class ContentMessage : public BaseMessage
{
	string path;
protected:
	//����� ������������ � �������� ��� ��������� ��������������� ����� ������������� �����
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	ContentMessage(const string path, const string messageMapId);
	~ContentMessage();
};

