#include "BaseMessage.h"

using namespace rapidjson;

BaseMessage::BaseMessage(const string messageMapId):messageMapId(messageMapId)
{
}

void BaseMessage::preSerialize(Writer<StringBuffer> &writer) const
{	
	writer.String("address");
	writer.StartObject();
	writer.String("messageMapId");
	writer.String(this->messageMapId.c_str());
	writer.EndObject();
}

string BaseMessage::serialize() const
{	
	StringBuffer jsonBuffer;
	Writer<StringBuffer> writer(jsonBuffer);
	writer.StartObject();
	this->preSerialize(writer);
	writer.EndObject();
	string json = jsonBuffer.GetString();

	return json;
}

BaseMessage::~BaseMessage()
{
}
