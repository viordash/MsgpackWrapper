
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include "MsgpackWrapper.h"

// template <> std::vector<char *>::iterator MsgpackArray<char *>::Find(const char *item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 		if (*iter != NULL && item != NULL && strcmp(*iter, item) == 0) { return iter; }
// 	}
// 	return Items.end();
// }

// template <> std::vector<TBoolArray>::iterator MsgpackArray<TBoolArray>::Find(const TBoolArray item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<int64_t>::iterator MsgpackArray<int64_t>::Find(const int64_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<uint64_t>::iterator MsgpackArray<uint64_t>::Find(const uint64_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<int32_t>::iterator MsgpackArray<int32_t>::Find(const int32_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<uint32_t>::iterator MsgpackArray<uint32_t>::Find(const uint32_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<int16_t>::iterator MsgpackArray<int16_t>::Find(const int16_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<uint16_t>::iterator MsgpackArray<uint16_t>::Find(const uint16_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<int8_t>::iterator MsgpackArray<int8_t>::Find(const int8_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<uint8_t>::iterator MsgpackArray<uint8_t>::Find(const uint8_t item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<double>::iterator MsgpackArray<double>::Find(const double item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// template <> std::vector<float>::iterator MsgpackArray<float>::Find(const float item) {
// 	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 		if (*iter == item) { return iter; }
// 	}
// 	return Items.end();
// }
// /*


// */
// template <> void MsgpackArray<char *>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) {
// 		if (item != NULL) {
// 			doc->PushBack(rapidjson::Value(rapidjson::StringRef(item)).Move(), allocator);
// 		} else {
// 			rapidjson::Value json_val;
// 			doc->PushBack(json_val.SetNull(), allocator);
// 		}
// 	}
// }
// template <> void MsgpackArray<TBoolArray>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((bool)item).Move(), allocator); }
// }
// template <> void MsgpackArray<int64_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<uint64_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<int32_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<uint32_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<int16_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<uint16_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<int8_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<uint8_t>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<double>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// template <> void MsgpackArray<float>::WriteToDoc(TJsonDocument *doc) {
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), doc->GetAllocator());
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	for (const auto &item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
// }
// /*


// */
// template <> void MsgpackArray<char *>::AddInternal(const char *item) {
// 	if (item == NULL) {
// 		Items.push_back((char *)item);
// 	} else {
// 		auto len = strlen(item);
// 		auto newItem = new char[len + 1];
// 		memcpy(newItem, item, len);
// 		newItem[len] = 0;
// 		Items.push_back(newItem);
// 	}
// }
// template <> void MsgpackArray<TBoolArray>::AddInternal(const TBoolArray item) { Items.push_back(item); }
// template <> void MsgpackArray<int64_t>::AddInternal(const int64_t item) { Items.push_back(item); }
// template <> void MsgpackArray<uint64_t>::AddInternal(const uint64_t item) { Items.push_back(item); }
// template <> void MsgpackArray<int32_t>::AddInternal(const int32_t item) { Items.push_back(item); }
// template <> void MsgpackArray<uint32_t>::AddInternal(const uint32_t item) { Items.push_back(item); }
// template <> void MsgpackArray<int16_t>::AddInternal(const int16_t item) { Items.push_back(item); }
// template <> void MsgpackArray<uint16_t>::AddInternal(const uint16_t item) { Items.push_back(item); }
// template <> void MsgpackArray<int8_t>::AddInternal(const int8_t item) { Items.push_back(item); }
// template <> void MsgpackArray<uint8_t>::AddInternal(const uint8_t item) { Items.push_back(item); }
// template <> void MsgpackArray<double>::AddInternal(const double item) { Items.push_back(item); }
// template <> void MsgpackArray<float>::AddInternal(const float item) { Items.push_back(item); }
// /*


// */
// template <> bool MsgpackArray<char *>::Add(const char *item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<TBoolArray>::Add(const TBoolArray item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<int64_t>::Add(const int64_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<uint64_t>::Add(const uint64_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<int32_t>::Add(const int32_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<uint32_t>::Add(const uint32_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<int16_t>::Add(const int16_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<uint16_t>::Add(const uint16_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<int8_t>::Add(const int8_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<uint8_t>::Add(const uint8_t item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<double>::Add(const double item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// template <> bool MsgpackArray<float>::Add(const float item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }
// /*


// */
// template <> void MsgpackArray<char *>::DeleteItem(const char *item) { delete[] item; }
// template <> void MsgpackArray<TBoolArray>::DeleteItem(const TBoolArray item) {}
// template <> void MsgpackArray<int64_t>::DeleteItem(const int64_t item) {}
// template <> void MsgpackArray<uint64_t>::DeleteItem(const uint64_t item) {}
// template <> void MsgpackArray<int32_t>::DeleteItem(const int32_t item) {}
// template <> void MsgpackArray<uint32_t>::DeleteItem(const uint32_t item) {}
// template <> void MsgpackArray<int16_t>::DeleteItem(const int16_t item) {}
// template <> void MsgpackArray<uint16_t>::DeleteItem(const uint16_t item) {}
// template <> void MsgpackArray<int8_t>::DeleteItem(const int8_t item) {}
// template <> void MsgpackArray<uint8_t>::DeleteItem(const uint8_t item) {}
// template <> void MsgpackArray<double>::DeleteItem(const double item) {}
// template <> void MsgpackArray<float>::DeleteItem(const float item) {}
// /*


// */
// template <> void MsgpackArray<char *>::Remove(const char *item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<TBoolArray>::Remove(const TBoolArray item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<int64_t>::Remove(const int64_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<uint64_t>::Remove(const uint64_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<int32_t>::Remove(const int32_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<uint32_t>::Remove(const uint32_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<int16_t>::Remove(const int16_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<uint16_t>::Remove(const uint16_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<int8_t>::Remove(const int8_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<uint8_t>::Remove(const uint8_t item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<double>::Remove(const double item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// template <> void MsgpackArray<float>::Remove(const float item) {
// 	auto iter = Find(item);
// 	if (iter == Items.end()) { return; }
// 	DeleteItem(*iter);
// 	Items.erase(iter);
// }
// /*


// */
// template <> bool MsgpackArray<char *>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<char *> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		char *s1 = Items[i];
// 		char *s2 = ((MsgpackArray<char *> *)other)->Items[i];

// 		if (s1 == s2) { continue; }
// 		if (s1 == NULL || s2 == NULL) { return false; }
// 		if (strcmp(s1, s2) != 0) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<TBoolArray>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<TBoolArray> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<TBoolArray> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<int64_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<int64_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<int64_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<uint64_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<uint64_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<uint64_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<int32_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<int32_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<int32_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<uint32_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<uint32_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<uint32_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<int16_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<int16_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<int16_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<uint16_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<uint16_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<uint16_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<int8_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<int8_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<int8_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<uint8_t>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<uint8_t> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<uint8_t> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<double>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<double> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<double> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<float>::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackArray<float> *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (Items[i] != ((MsgpackArray<float> *)other)->Items[i]) { return false; }
// 	}
// 	return true;
// }
// /*


// */
// template <> void MsgpackArray<char *>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<char *> *)other);
// 	for (const auto &item : otherArray->Items) { delete[] item; }
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<TBoolArray>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<TBoolArray> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<int64_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<int64_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<uint64_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<uint64_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<int32_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<int32_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<uint32_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<uint32_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<int16_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<int16_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<uint16_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<uint16_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<int8_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<int8_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<uint8_t>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<uint8_t> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<double>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<double> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// template <> void MsgpackArray<float>::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackArray<float> *)other);
// 	otherArray->Items.clear();
// 	for (const auto &item : Items) { otherArray->AddInternal(item); }
// }
// /*


// */
// template <> bool MsgpackArray<char *>::Update(size_t index, const char *item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	if (item == NULL) {
// 		Items[index] = (char *)item;
// 	} else {
// 		auto len = strlen(item);
// 		auto newItem = new char[len + 1];
// 		memcpy(newItem, item, len);
// 		newItem[len] = 0;
// 		Items[index] = newItem;
// 	}
// 	return true;
// }
// template <> bool MsgpackArray<TBoolArray>::Update(size_t index, const TBoolArray item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<int64_t>::Update(size_t index, const int64_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<uint64_t>::Update(size_t index, const uint64_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<int32_t>::Update(size_t index, const int32_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<uint32_t>::Update(size_t index, const uint32_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<int16_t>::Update(size_t index, const int16_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<uint16_t>::Update(size_t index, const uint16_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<int8_t>::Update(size_t index, const int8_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<uint8_t>::Update(size_t index, const uint8_t item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<double>::Update(size_t index, const double item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// template <> bool MsgpackArray<float>::Update(size_t index, const float item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }
// /*


// */
// template <> bool MsgpackArray<char *>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (jItem.IsString()) {
// 			if (!Add(jItem.GetString())) {
// 				Items.shrink_to_fit();
// 				return false;
// 			}
// 		} else if (jItem.IsNull()) {
// 			if (!Add(NULL)) {
// 				Items.shrink_to_fit();
// 				return false;
// 			}
// 		} else {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<TBoolArray>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsBool() || !Add((TBoolArray)jItem.GetBool())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<int64_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsInt64() || !Add(jItem.GetInt64())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<uint64_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsUint64() || !Add(jItem.GetUint64())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<int32_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsInt() || !Add(jItem.GetInt())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<uint32_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsUint() || !Add(jItem.GetUint())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<int16_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsInt() || !Add(jItem.GetInt())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<uint16_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsUint() || !Add(jItem.GetUint())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<int8_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsInt() || !Add(jItem.GetInt())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<uint8_t>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsUint() || !Add(jItem.GetUint())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<double>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsDouble() || !Add(jItem.GetDouble())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// template <> bool MsgpackArray<float>::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());
// 	for (const auto &jItem : jArray) {
// 		if (!jItem.IsFloat() || !Add(jItem.GetFloat())) {
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }
// /*


// */
// template <> void MsgpackArray<char *>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<TBoolArray>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<int64_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<uint64_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<int32_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<uint32_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<int16_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<uint16_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<int8_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<uint8_t>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<double>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }
// template <> void MsgpackArray<float>::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }