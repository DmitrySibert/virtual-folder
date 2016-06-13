#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

class CreateFolderMessage :
	public BaseMessage
{
private: 
	char* file;
	string folder;
protected:
	//����� ������������ � �������� ��� ��������� ��������������� ����� ������������� �����
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	CreateFolderMessage(char* files, string folder, const string messageMapId);
	~CreateFolderMessage();
};

