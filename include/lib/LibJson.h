#pragma once

#include <msgpack.h>
#include <vector>
#include <algorithm>

typedef int TJsonDocument; // typedef rapidjson::Document TJsonDocument;
// typedef rapidjson::Value::Array TJsonArray;
typedef char TJsonValue; // typedef rapidjson::Value TJsonValue;

typedef char TJsonValueName; // typedef rapidjson::GenericStringRef<char> TJsonValueName;

class JsonValueBase;
template <class T> class JsonValue;

class JsonFieldsContainer {
  public:
	std::vector<JsonValueBase *> Fields;
	void Add(JsonValueBase *field) { Fields.push_back(field); }
	JsonValueBase *GetField(const char *name);
};

class JsonValueBase {
  public:
	TJsonValueName Name;
	JsonValueBase(JsonValueBase &&) = delete;
	JsonValueBase(const JsonValueBase &) = delete;

	JsonValueBase(JsonFieldsContainer *container, const char *name, size_t nameLen) /*: Name(name, nameLen)*/ { container->Add(this); }
	virtual ~JsonValueBase(){};

	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonValueBase *other) = 0;
	virtual void CloneTo(JsonValueBase *other) = 0;

	friend bool operator!=(const JsonValueBase &v1, const JsonValueBase &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
	friend bool operator==(const JsonValueBase &v1, const JsonValueBase &v2) { return !(v1 != v2); }

  protected:
	static TJsonValue *GetMember(TJsonDocument *doc, const char *name);
	static bool NamesCompare(const char *name1, const char *name2);
};
