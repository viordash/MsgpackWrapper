#pragma once

#include <msgpack.h>
#include <set>
#include <algorithm>

class MsgpackValueBase;
template <class T> class MsgpackValue;

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
