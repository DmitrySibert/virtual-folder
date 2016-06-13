#pragma once

#include "BaseMessage.h"
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>
#include <list>
class DeleteFilesMessage :
	public BaseMessage
{
private:
	std::list<char*> files;
	string folder;

protected:
	//����� ������������ � �������� ��� ��������� ��������������� ����� ������������� �����
	virtual void preSerialize(Writer<StringBuffer> &writer) const;

public:
	DeleteFilesMessage(std::list<char*> files, string folder, const string messageMapId);
	~DeleteFilesMessage();
};

