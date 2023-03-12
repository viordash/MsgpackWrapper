
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "MsgpackWrapper.h"

template <> std::vector<char *>::iterator MsgpackArray<char *>::Find(const char *item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
		if (*iter != NULL && item != NULL && strcmp(*iter, item) == 0) { return iter; }
	}
	return Items.end();
}

template <> std::vector<TBoolArray>::iterator MsgpackArray<TBoolArray>::Find(const TBoolArray item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int64_t>::iterator MsgpackArray<int64_t>::Find(const int64_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint64_t>::iterator MsgpackArray<uint64_t>::Find(const uint64_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int32_t>::iterator MsgpackArray<int32_t>::Find(const int32_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint32_t>::iterator MsgpackArray<uint32_t>::Find(const uint32_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int16_t>::iterator MsgpackArray<int16_t>::Find(const int16_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint16_t>::iterator MsgpackArray<uint16_t>::Find(const uint16_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int8_t>::iterator MsgpackArray<int8_t>::Find(const int8_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint8_t>::iterator MsgpackArray<uint8_t>::Find(const uint8_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<double>::iterator MsgpackArray<double>::Find(const double item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<float>::iterator MsgpackArray<float>::Find(const float item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
/*


*/
template <> bool MsgpackArray<char *>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (item == NULL) {
			if (msgpack_pack_nil(packer) != 0) { return false; }
		} else {
			auto sLen = strlen(item);
			if (msgpack_pack_str(packer, sLen) != 0 //
				|| msgpack_pack_str_body(packer, item, sLen) != 0) {
				return false;
			}
		}
	}
	return true;
}
template <> bool MsgpackArray<TBoolArray>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (((bool)item ? msgpack_pack_true(packer) : msgpack_pack_false(packer)) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int64_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_int64(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint64_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_uint64(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int32_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_int32(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint32_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_uint32(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int16_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_int16(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint16_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_uint16(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int8_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_int8(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint8_t>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_uint8(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<double>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_double(packer, item) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<float>::Write(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (msgpack_pack_float(packer, item) != 0) { return false; }
	}
	return true;
}
/*


*/
template <> void MsgpackArray<char *>::AddInternal(const char *item, size_t newValueLen) {
	if (item == NULL) {
		Items.push_back((char *)item);
	} else {
		size_t len = newValueLen != size_t() //
					   ? newValueLen		 //
					   : strlen(item);
		auto newItem = new char[len + 1];
		memcpy(newItem, item, len);
		newItem[len] = 0;
		Items.push_back(newItem);
	}
}
template <> void MsgpackArray<TBoolArray>::AddInternal(const TBoolArray item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<int64_t>::AddInternal(const int64_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<uint64_t>::AddInternal(const uint64_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<int32_t>::AddInternal(const int32_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<uint32_t>::AddInternal(const uint32_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<int16_t>::AddInternal(const int16_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<uint16_t>::AddInternal(const uint16_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<int8_t>::AddInternal(const int8_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<uint8_t>::AddInternal(const uint8_t item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<double>::AddInternal(const double item, size_t newValueLen) { Items.push_back(item); }
template <> void MsgpackArray<float>::AddInternal(const float item, size_t newValueLen) { Items.push_back(item); }
/*


*/
template <> bool MsgpackArray<char *>::Add(const char *item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<TBoolArray>::Add(const TBoolArray item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<int64_t>::Add(const int64_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<uint64_t>::Add(const uint64_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<int32_t>::Add(const int32_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<uint32_t>::Add(const uint32_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<int16_t>::Add(const int16_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<uint16_t>::Add(const uint16_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<int8_t>::Add(const int8_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<uint8_t>::Add(const uint8_t item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<double>::Add(const double item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
template <> bool MsgpackArray<float>::Add(const float item, size_t newValueLen) {
	if (!Validate(item)) { return false; }
	AddInternal(item, newValueLen);
	return true;
}
/*


*/
template <> void MsgpackArray<char *>::DeleteItem(const char *item) { delete[] item; }
template <> void MsgpackArray<TBoolArray>::DeleteItem(const TBoolArray item) {}
template <> void MsgpackArray<int64_t>::DeleteItem(const int64_t item) {}
template <> void MsgpackArray<uint64_t>::DeleteItem(const uint64_t item) {}
template <> void MsgpackArray<int32_t>::DeleteItem(const int32_t item) {}
template <> void MsgpackArray<uint32_t>::DeleteItem(const uint32_t item) {}
template <> void MsgpackArray<int16_t>::DeleteItem(const int16_t item) {}
template <> void MsgpackArray<uint16_t>::DeleteItem(const uint16_t item) {}
template <> void MsgpackArray<int8_t>::DeleteItem(const int8_t item) {}
template <> void MsgpackArray<uint8_t>::DeleteItem(const uint8_t item) {}
template <> void MsgpackArray<double>::DeleteItem(const double item) {}
template <> void MsgpackArray<float>::DeleteItem(const float item) {}
/*


*/
template <> void MsgpackArray<char *>::Remove(const char *item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<TBoolArray>::Remove(const TBoolArray item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<int64_t>::Remove(const int64_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<uint64_t>::Remove(const uint64_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<int32_t>::Remove(const int32_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<uint32_t>::Remove(const uint32_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<int16_t>::Remove(const int16_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<uint16_t>::Remove(const uint16_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<int8_t>::Remove(const int8_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<uint8_t>::Remove(const uint8_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<double>::Remove(const double item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void MsgpackArray<float>::Remove(const float item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
/*


*/
template <> bool MsgpackArray<char *>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<char *> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		char *s1 = Items[i];
		char *s2 = ((MsgpackArray<char *> *)other)->Items[i];

		if (s1 == s2) { continue; }
		if (s1 == NULL || s2 == NULL) { return false; }
		if (strcmp(s1, s2) != 0) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<TBoolArray>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<TBoolArray> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<TBoolArray> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int64_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<int64_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<int64_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint64_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<uint64_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<uint64_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int32_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<int32_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<int32_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint32_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<uint32_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<uint32_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int16_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<int16_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<int16_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint16_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<uint16_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<uint16_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<int8_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<int8_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<int8_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<uint8_t>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<uint8_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<uint8_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<double>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<double> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<double> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool MsgpackArray<float>::Equals(MsgpackArrayBase *other) {
	if (Items.size() != ((MsgpackArray<float> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((MsgpackArray<float> *)other)->Items[i]) { return false; }
	}
	return true;
}
/*


*/
template <> void MsgpackArray<char *>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<char *> *)other);
	for (const auto &item : otherArray->Items) { delete[] item; }
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<TBoolArray>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<TBoolArray> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<int64_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<int64_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<uint64_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<uint64_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<int32_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<int32_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<uint32_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<uint32_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<int16_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<int16_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<uint16_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<uint16_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<int8_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<int8_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<uint8_t>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<uint8_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<double>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<double> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
template <> void MsgpackArray<float>::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackArray<float> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal(item); }
}
/*


*/
template <> bool MsgpackArray<char *>::Update(size_t index, const char *item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	if (item == NULL) {
		Items[index] = (char *)item;
	} else {
		auto len = strlen(item);
		auto newItem = new char[len + 1];
		memcpy(newItem, item, len);
		newItem[len] = 0;
		Items[index] = newItem;
	}
	return true;
}
template <> bool MsgpackArray<TBoolArray>::Update(size_t index, const TBoolArray item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<int64_t>::Update(size_t index, const int64_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<uint64_t>::Update(size_t index, const uint64_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<int32_t>::Update(size_t index, const int32_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<uint32_t>::Update(size_t index, const uint32_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<int16_t>::Update(size_t index, const int16_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<uint16_t>::Update(size_t index, const uint16_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<int8_t>::Update(size_t index, const int8_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<uint8_t>::Update(size_t index, const uint8_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<double>::Update(size_t index, const double item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool MsgpackArray<float>::Update(size_t index, const float item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
/*


*/
template <> bool MsgpackArray<char *>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NIL) {
			if (!Add(NULL)) {
				Items.shrink_to_fit();
				return false;
			}
		} else if (object.type == MSGPACK_OBJECT_STR) {
			if (!Add(object.via.str.ptr, object.via.str.size)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<TBoolArray>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_BOOLEAN) {
			if (!Add((TBoolArray)object.via.boolean)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<int64_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add(object.via.i64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<uint64_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add(object.via.u64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<int32_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add((int32_t)object.via.i64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<uint32_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add((uint32_t)object.via.u64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<int16_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add((int16_t)object.via.i64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<uint16_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add((uint16_t)object.via.u64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<int8_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add((int8_t)object.via.i64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<uint8_t>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_NEGATIVE_INTEGER || object.type == MSGPACK_OBJECT_POSITIVE_INTEGER) {
			if (!Add((uint8_t)object.via.u64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<double>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_FLOAT64) {
			if (!Add((double)object.via.f64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool MsgpackArray<float>::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	for (size_t i = 0; i < deserialized->via.array.size; i++) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type == MSGPACK_OBJECT_FLOAT32) {
			if (!Add((float)object.via.f64)) {
				Items.shrink_to_fit();
				return false;
			}
		}
	}
	Items.shrink_to_fit();
	return true;
}
/*


*/
template <> void MsgpackArray<char *>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<TBoolArray>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<int64_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<uint64_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<int32_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<uint32_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<int16_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<uint16_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<int8_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<uint8_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<double>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void MsgpackArray<float>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}