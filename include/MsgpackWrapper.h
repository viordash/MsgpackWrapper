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

	MsgpackValue(MsgpackFieldsContainer *container, int id, size_t valueLen, ConstT value) : MsgpackValueBase(container, id) { InitValue(value, valueLen); }
	MsgpackValue(MsgpackFieldsContainer *container, int id, ConstT value = T()) : MsgpackValue(container, id, size_t(), value) {}

	virtual ~MsgpackValue() { DeleteValue(); }

	// bool Parse(TMsgpackBuffer *buffer) override final;

	bool Write(msgpack_packer *packer) override final;
	// void WriteToDoc(TMsgpackDocument *doc) override final;

	// bool Equals(MsgpackValueBase *other) override final;
	// void CloneTo(MsgpackValueBase *other) override final;

	// ConstT Get() { return value; }

	// void Set(ConstT newValue, size_t newValueLen = size_t());

  protected:
	T value;
	void InitValue(ConstT value, size_t valueLen);
	void DeleteValue();
};

class MsgpackObject : public MsgpackFieldsContainer {
  public:
	virtual ~MsgpackObject(){};

	// virtual bool TryParse(TMsgpackDocument *doc);
	// virtual bool TryStringParse(const char *jsonStr, size_t length = 0);
	// TMsgpackDocument *BeginTryStringParse(const char *jsonStr, size_t length = 0);
	// void EndTryStringParse(TMsgpackDocument *doc);

	// void Write(msgpack_packer *packer);
	// size_t WriteToString(char *outBuffer, size_t outBufferSize);
	// typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	// size_t DirectWriteTo(void *parent, TOnReady onReady);

	// virtual bool Validate() { return true; }
	// virtual bool Equals(MsgpackObject *other);
	// virtual void CloneTo(MsgpackObject *other);

	// friend bool operator!=(const MsgpackObject &v1, const MsgpackObject &v2);
	// friend bool operator==(const MsgpackObject &v1, const MsgpackObject &v2);

  protected:
  private:
};