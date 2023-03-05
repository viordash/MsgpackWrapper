#pragma once

#include "lib/LibJson.h"

template <class T> class JsonValue : public JsonValueBase {
  public:
	typedef typename std::conditional<std::is_same<T, char *>::value, const char *, typename std::add_const<T>::type>::type ConstT;

	JsonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, size_t valueLen, ConstT value) : JsonValueBase(container, name, nameLen) { InitValue(value, valueLen); }
	JsonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, ConstT value = T()) : JsonValue(container, nameLen, name, size_t(), value) {}
	template <size_t N> JsonValue(JsonFieldsContainer *container, const char (&name)[N], ConstT value = T()) : JsonValue(container, N - 1, name, value) {}

	virtual ~JsonValue() { DeleteValue(); }

	bool TryParse(TJsonDocument *doc) override final;
	void WriteToDoc(TJsonDocument *doc) override final;

	bool Equals(JsonValueBase *other) override final;
	void CloneTo(JsonValueBase *other) override final;

	ConstT Get() { return value; }

	void Set(ConstT newValue, size_t newValueLen = size_t());

  protected:
	T value;
	void InitValue(ConstT value, size_t valueLen);
	void DeleteValue();
};
