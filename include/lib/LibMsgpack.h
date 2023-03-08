#pragma once

#include <msgpack.h>
#include <vector>
#include <algorithm>

typedef msgpack_sbuffer TMsgpackBuffer;
#define MsgpackBufferInit msgpack_sbuffer_init
#define MsgpackBufferDestroy msgpack_sbuffer_destroy
// typedef char TMsgpackValue; // typedef rapidjson::Value TMsgpackValue;

typedef char TMsgpackValueName; // typedef rapidjson::GenericStringRef<char> TMsgpackValueName;

class MsgpackValueBase;
template <class T> class MsgpackValue;

class MsgpackFieldsContainer {
  public:
	std::vector<MsgpackValueBase *> Fields;
	void Add(MsgpackValueBase *field) { Fields.push_back(field); }
	MsgpackValueBase *GetField(const char *name);
};

class MsgpackValueBase {
  public:
	unsigned int Id;
	MsgpackValueBase(MsgpackValueBase &&) = delete;
	MsgpackValueBase(const MsgpackValueBase &) = delete;

	MsgpackValueBase(MsgpackFieldsContainer *container, unsigned int id) : Id(id) { container->Add(this); }
	virtual ~MsgpackValueBase(){};

	virtual bool Parse(msgpack_object *deserialized) = 0;
	virtual bool Write(msgpack_packer *packer) = 0;
	virtual bool Equals(MsgpackValueBase *other) = 0;
	virtual void CloneTo(MsgpackValueBase *other) = 0;

	friend bool operator!=(const MsgpackValueBase &v1, const MsgpackValueBase &v2) { return !((MsgpackValueBase *)&v1)->Equals((MsgpackValueBase *)&v2); }
	friend bool operator==(const MsgpackValueBase &v1, const MsgpackValueBase &v2) { return !(v1 != v2); }

  protected:
};
