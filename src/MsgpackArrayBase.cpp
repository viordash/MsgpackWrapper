
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include "MsgpackWrapper.h"

// bool MsgpackArrayBase::TryStringParse(const char *jsonStr, size_t length) {
// 	auto doc = BeginTryStringParse(jsonStr, length);
// 	if (doc == NULL) { return false; }
// 	EndTryStringParse(doc);
// 	return true;
// }

// TMsgpackDocument *MsgpackArrayBase::BeginTryStringParse(const char *jsonStr, size_t length) {
// 	if (jsonStr == NULL) { return NULL; }

// 	rapidjson::Document *doc = new rapidjson::Document();
// 	if (length == 0) {
// 		doc->Parse(jsonStr);
// 	} else {
// 		doc->Parse(jsonStr, length);
// 	}
// 	if (doc->HasParseError() || !this->TryDocParse(doc)) {
// 		delete doc;
// 		return NULL;
// 	}
// 	return doc;
// }

// void MsgpackArrayBase::EndTryStringParse(TMsgpackDocument *doc) { delete doc; }

// size_t MsgpackArrayBase::WriteToString(char *outBuffer, size_t outBufferSize) {
// 	rapidjson::Document doc;
// 	this->WriteToDoc(&doc);
// 	rapidjson::StringBuffer buffer;
// 	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 	doc.Accept(writer);

// 	const char *jsonStr = buffer.GetString();
// 	size_t size = buffer.GetSize();
// 	if (size > outBufferSize - 1) { size = outBufferSize - 1; }
// 	strncpy(outBuffer, jsonStr, size);
// 	outBuffer[size] = 0;
// 	return size;
// }

// size_t MsgpackArrayBase::DirectWriteTo(void *parent, TOnReady onReady) {
// 	rapidjson::Document doc;
// 	this->WriteToDoc(&doc);
// 	rapidjson::StringBuffer buffer;
// 	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 	doc.Accept(writer);

// 	const char *json = buffer.GetString();
// 	size_t size = buffer.GetSize();
// 	onReady(parent, json, size);
// 	return size;
// }