#pragma once

#include <msgpack.h>
#include <vector>
#include <algorithm>

typedef int TJsonDocument; // typedef rapidjson::Document TJsonDocument;
// typedef rapidjson::Value::Array TMsgpackArray;
typedef char TMsgpackValue; // typedef rapidjson::Value TMsgpackValue;

typedef char TMsgpackValueName; // typedef rapidjson::GenericStringRef<char> TMsgpackValueName;

class MsgpackValueBase;
template <class T> class MsgpackValue;

class JsonFieldsContainer {
  public:
	std::vector<MsgpackValueBase *> Fields;
	void Add(MsgpackValueBase *field) { Fields.push_back(field); }
	MsgpackValueBase *GetField(const char *name);
};

class MsgpackValueBase {
  public:
	TMsgpackValueName Name;
	MsgpackValueBase(MsgpackValueBase &&) = delete;
	MsgpackValueBase(const MsgpackValueBase &) = delete;

	MsgpackValueBase(JsonFieldsContainer *container, const char *name, size_t nameLen) /*: Name(name, nameLen)*/ { container->Add(this); }
	virtual ~MsgpackValueBase(){};

	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(MsgpackValueBase *other) = 0;
	virtual void CloneTo(MsgpackValueBase *other) = 0;

	friend bool operator!=(const MsgpackValueBase &v1, const MsgpackValueBase &v2) { return !((MsgpackValueBase *)&v1)->Equals((MsgpackValueBase *)&v2); }
	friend bool operator==(const MsgpackValueBase &v1, const MsgpackValueBase &v2) { return !(v1 != v2); }

  protected:
	static TMsgpackValue *GetMember(TJsonDocument *doc, const char *name);
	static bool NamesCompare(const char *name1, const char *name2);
};
