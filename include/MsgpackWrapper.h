#pragma once

#include "lib/LibMsgpack.h"

template <class T> class MsgpackValue : public MsgpackValueBase {
  public:
	typedef typename std::conditional<std::is_same<T, char *>::value, const char *, typename std::add_const<T>::type>::type ConstT;

	MsgpackValue(JsonFieldsContainer *container, size_t nameLen, const char *name, size_t valueLen, ConstT value) : MsgpackValueBase(container, name, nameLen) { InitValue(value, valueLen); }
	MsgpackValue(JsonFieldsContainer *container, size_t nameLen, const char *name, ConstT value = T()) : MsgpackValue(container, nameLen, name, size_t(), value) {}
	template <size_t N> MsgpackValue(JsonFieldsContainer *container, const char (&name)[N], ConstT value = T()) : MsgpackValue(container, N - 1, name, value) {}

	virtual ~MsgpackValue() { DeleteValue(); }

	bool TryParse(TJsonDocument *doc) override final;
	void WriteToDoc(TJsonDocument *doc) override final;

	bool Equals(MsgpackValueBase *other) override final;
	void CloneTo(MsgpackValueBase *other) override final;

	ConstT Get() { return value; }

	void Set(ConstT newValue, size_t newValueLen = size_t());

  protected:
	T value;
	void InitValue(ConstT value, size_t valueLen);
	void DeleteValue();
};
