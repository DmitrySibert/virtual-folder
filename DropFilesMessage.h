#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>
#include <list>

using namespace rapidjson;

class DropFilesMessage : public BaseMessage
{
private:
	std::list<char*> files;
	std::list<bool> isFolderFlags;
	string folder;

protected:
	//����� ������������ � �������� ��� ��������� ��������������� ����� ������������� �����
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	DropFilesMessage(std::list<char*> files, std::list<bool> isFolderFlags, string folder, const string messageMapId);
	~DropFilesMessage();
};

