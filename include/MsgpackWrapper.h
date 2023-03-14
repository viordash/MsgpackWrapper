#pragma once

#include "lib/LibMsgpack.h"

typedef char TBoolArray;
typedef struct {
	uint8_t *Data;
	size_t Size;
} TMsgpackRawData;

template <class T> class MsgpackValue : public MsgpackValueBase {
  public:
	typedef typename std::conditional<std::is_same<T, char *>::value, const char *, typename std::add_const<T>::type>::type ConstT;

	MsgpackValue(MsgpackFieldsContainer *container, unsigned int id, size_t valueLen, ConstT value) : MsgpackValueBase(container, id) { InitValue(value, valueLen); }
	MsgpackValue(MsgpackFieldsContainer *container, unsigned int id, ConstT value = T()) : MsgpackValue(container, id, size_t(), value) {}

	virtual ~MsgpackValue() { DeleteValue(); }

	bool TryParse(msgpack_object *deserialized) override final;
	bool Write(msgpack_packer *packer) override final;

	bool Equals(MsgpackValueBase *other) override final;
	void CloneTo(MsgpackValueBase *other) override final;

	ConstT Get() { return value; }

	void Set(ConstT newValue, size_t newValueLen = size_t());

  protected:
	T value;
	void InitValue(ConstT value, size_t valueLen);
	void DeleteValue();
};

class MsgpackObject : public MsgpackFieldsContainer {
  public:
	virtual ~MsgpackObject(){};

	virtual bool TryParse(msgpack_object *deserialized);
	virtual bool TryParse(const char *buffer, size_t length);
	msgpack_unpacked *BeginTryParse(const char *buffer, size_t length);
	void EndTryParse(msgpack_unpacked *unpacked);

	bool Write(msgpack_packer *packer);
	size_t Write(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Validate() { return true; }
	virtual bool Equals(MsgpackObject *other);
	virtual void CloneTo(MsgpackObject *other);

	friend bool operator!=(const MsgpackObject &v1, const MsgpackObject &v2);
	friend bool operator==(const MsgpackObject &v1, const MsgpackObject &v2);

  protected:
  private:
};

template <class TItem> class MsgpackArray : public MsgpackArrayBase {
  public:
	typedef typename std::conditional<std::is_same<TItem, char *>::value, const char *, typename std::add_const<TItem>::type>::type ConstTItem;
	virtual ~MsgpackArray() { Clear(); }

	TItem Item(size_t index) { return (TItem)Items[index]; }
	size_t Size() { return Items.size(); }
	typename std::vector<TItem>::iterator const Begin() { return Items.begin(); }
	typename std::vector<TItem>::iterator const End() { return Items.end(); }
	void Reserve(size_t capacity) { Items.reserve(capacity); }
	bool Empty() { return Items.empty(); }

	bool TryParseObject(msgpack_object *deserialized) override final;
	bool WriteObject(msgpack_packer *packer) override final;

	virtual bool Add(ConstTItem item, size_t newValueLen = size_t());
	virtual bool Update(size_t index, ConstTItem item);
	virtual void Remove(ConstTItem item);
	typename std::vector<TItem>::iterator Find(ConstTItem item);

	bool Equals(MsgpackArrayBase *other) override;
	void CloneTo(MsgpackArrayBase *other) override;
	void Clear() override;

	friend bool operator!=(const MsgpackArray<TItem> &v1, const MsgpackArray<TItem> &v2) { return !((MsgpackArray<TItem> *)&v1)->Equals((MsgpackArray<TItem> *)&v2); }
	friend bool operator==(const MsgpackArray<TItem> &v1, const MsgpackArray<TItem> &v2) { return !(v1 != v2); }

  protected:
	std::vector<TItem> Items;
	virtual bool Validate(ConstTItem item) = 0;
	void AddInternal(ConstTItem item, size_t newValueLen = size_t());
	void DeleteItem(ConstTItem item);
};

class MsgpackObjectsArray : public MsgpackArrayBase {
  public:
	virtual ~MsgpackObjectsArray();

	template <class TItem> TItem Item(size_t index) { return (TItem)Items[index]; }
	size_t Size() { return Items.size(); }
	typename std::vector<MsgpackObject *>::iterator const Begin() { return Items.begin(); }
	typename std::vector<MsgpackObject *>::iterator const End() { return Items.end(); }
	void Reserve(size_t capacity) { Items.reserve(capacity); }
	bool Empty() { return Items.empty(); }

	bool TryParseObject(msgpack_object *deserialized) override final;
	bool WriteObject(msgpack_packer *packer) override final;

	virtual bool Add(MsgpackObject *item);
	virtual bool Update(size_t index, MsgpackObject *item);
	virtual void Remove(MsgpackObject *item);

	typename std::vector<MsgpackObject *>::iterator Find(MsgpackObject *item);

	bool Equals(MsgpackArrayBase *other) override;
	void CloneTo(MsgpackArrayBase *other) override;
	typename std::vector<MsgpackObject *>::iterator MoveTo(MsgpackArrayBase *other, MsgpackObject *item);
	void MoveAllTo(MsgpackArrayBase *other);

	void Clear() override;
	virtual bool Validate(MsgpackObject *item) = 0;
	virtual MsgpackObject *CreateItem() = 0;

	friend bool operator!=(const MsgpackObjectsArray &v1, const MsgpackObjectsArray &v2);
	friend bool operator==(const MsgpackObjectsArray &v1, const MsgpackObjectsArray &v2);

  protected:
	std::vector<MsgpackObject *> Items;
	void AddInternal(MsgpackObject *item);
	void DeleteItem(MsgpackObject *item);
};