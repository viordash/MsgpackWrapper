#pragma once

#include <msgpack.h>
#include <set>
#include <vector>
#include <algorithm>

class MsgpackValueBase;
template <class T> class MsgpackValue;

class MsgpackArrayBase {
  public:
	virtual ~MsgpackArrayBase(){};

	virtual bool TryParseObject(msgpack_object *deserialized) = 0;
	bool TryParse(const char *buffer, size_t length);
	msgpack_unpacked *BeginTryParse(const char *buffer, size_t length);
	void EndTryParse(msgpack_unpacked *unpacked);

	virtual bool Write(msgpack_packer *packer) = 0;
	size_t Write(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Equals(MsgpackArrayBase *other) = 0;
	virtual void CloneTo(MsgpackArrayBase *other) = 0;
	virtual void Clear() = 0;

  protected:
};

class MsgpackIdField {
  public:
	unsigned int Id;
	MsgpackIdField(unsigned int id) : Id(id) {}
};

class FieldsCmp {
  public:
	bool operator()(const MsgpackIdField *lfield, const MsgpackIdField *rfield) const { return lfield->Id < rfield->Id; }
};

class MsgpackFieldsContainer {
  public:
	std::set<MsgpackValueBase *, FieldsCmp> Fields;
	void Add(MsgpackValueBase *field) { Fields.insert(field); }
};

class MsgpackValueBase : public MsgpackIdField {
  public:
	MsgpackValueBase(MsgpackValueBase &&) = delete;
	MsgpackValueBase(const MsgpackValueBase &) = delete;

	MsgpackValueBase(MsgpackFieldsContainer *container, unsigned int id) : MsgpackIdField(id) { container->Add(this); }
	virtual ~MsgpackValueBase(){};

	virtual bool TryParse(msgpack_object *deserialized) = 0;
	virtual bool Write(msgpack_packer *packer) = 0;
	virtual bool Equals(MsgpackValueBase *other) = 0;
	virtual void CloneTo(MsgpackValueBase *other) = 0;

	friend bool operator!=(const MsgpackValueBase &v1, const MsgpackValueBase &v2) { return !((MsgpackValueBase *)&v1)->Equals((MsgpackValueBase *)&v2); }
	friend bool operator==(const MsgpackValueBase &v1, const MsgpackValueBase &v2) { return !(v1 != v2); }

  protected:
};
