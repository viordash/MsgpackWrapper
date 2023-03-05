
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include "MsgpackWrapper.h"

// template <> bool MsgpackValue<bool>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<bool> *)other)->value; }
// template <> bool MsgpackValue<int8_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<int8_t> *)other)->value; }
// template <> bool MsgpackValue<int16_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<int16_t> *)other)->value; }
// template <> bool MsgpackValue<int32_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<int32_t> *)other)->value; }
// template <> bool MsgpackValue<int64_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<int64_t> *)other)->value; }
// template <> bool MsgpackValue<uint8_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<uint8_t> *)other)->value; }
// template <> bool MsgpackValue<uint16_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<uint16_t> *)other)->value; }
// template <> bool MsgpackValue<uint32_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<uint32_t> *)other)->value; }
// template <> bool MsgpackValue<uint64_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<uint64_t> *)other)->value; }
// template <> bool MsgpackValue<float>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<float> *)other)->value; }
// template <> bool MsgpackValue<double>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackValue<double> *)other)->value; }
// template <> bool MsgpackValue<char *>::Equals(MsgpackValueBase *other) { //
// 	return MsgpackValueBase::NamesCompare(Name, other->Name)
// 		&& (value == ((MsgpackValue<char *> *)other)->value || (value != NULL && ((MsgpackValue<char *> *)other)->value != NULL && strcmp(value, ((MsgpackValue<char *> *)other)->value) == 0));
// }
// template <> bool MsgpackValue<TJsonRawData>::Equals(MsgpackValueBase *other) {
// 	return MsgpackValueBase::NamesCompare(Name, other->Name)												  //
// 		&& ((TJsonRawData)value).Data == ((TJsonRawData)(((MsgpackValue<TJsonRawData> *)other)->value)).Data //
// 		&& ((TJsonRawData)value).Size == ((TJsonRawData)(((MsgpackValue<TJsonRawData> *)other)->value)).Size;
// }
// template <> bool MsgpackValue<MsgpackObject *>::Equals(MsgpackValueBase *other) {
// 	return MsgpackValueBase::NamesCompare(Name, other->Name) && (MsgpackObject *)value->Equals((MsgpackObject *)((MsgpackValue<MsgpackObject *> *)other)->value);
// }
// template <> bool MsgpackValue<MsgpackArrayBase *>::Equals(MsgpackValueBase *other) {
// 	return MsgpackValueBase::NamesCompare(Name, other->Name) && (MsgpackObject *)value->Equals((MsgpackArrayBase *)(((MsgpackValue<MsgpackArrayBase *> *)other)->value));
// }
// /*


// */
// template <> void MsgpackValue<bool>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<int8_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<int16_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<int32_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<int64_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<uint8_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<uint16_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<uint32_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<uint64_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<float>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<double>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
// template <> void MsgpackValue<char *>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (value == NULL) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetString(rapidjson::StringRef(value));
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	TJsonRawData rawData = value;
// 	if (rawData.Data == NULL) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetString(rapidjson::StringRef((char *)rawData.Data, (rapidjson::SizeType)rawData.Size));
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackValue<MsgpackObject *>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	rapidjson::Document jObject(&allocator);
// 	value->WriteToDoc(&jObject);
// 	doc->AddMember(Name, jObject, allocator);
// }
// template <> void MsgpackValue<MsgpackArrayBase *>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	rapidjson::Document jArray(&allocator);
// 	value->WriteToDoc(&jArray);
// 	doc->AddMember(Name, jArray, allocator);
// }
// /*


// */
// template <> void MsgpackValue<bool>::DeleteValue() {}
// template <> void MsgpackValue<int8_t>::DeleteValue() {}
// template <> void MsgpackValue<int16_t>::DeleteValue() {}
// template <> void MsgpackValue<int32_t>::DeleteValue() {}
// template <> void MsgpackValue<int64_t>::DeleteValue() {}
// template <> void MsgpackValue<uint8_t>::DeleteValue() {}
// template <> void MsgpackValue<uint16_t>::DeleteValue() {}
// template <> void MsgpackValue<uint32_t>::DeleteValue() {}
// template <> void MsgpackValue<uint64_t>::DeleteValue() {}
// template <> void MsgpackValue<float>::DeleteValue() {}
// template <> void MsgpackValue<double>::DeleteValue() {}
// template <> void MsgpackValue<char *>::DeleteValue() { delete[] this->value; }
// template <> void MsgpackValue<TJsonRawData>::DeleteValue() {}
// template <> void MsgpackValue<MsgpackObject *>::DeleteValue() {}
// template <> void MsgpackValue<MsgpackArrayBase *>::DeleteValue() {}
// /*


// */
// template <> void MsgpackValue<bool>::InitValue(const bool value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<int8_t>::InitValue(const int8_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<int16_t>::InitValue(const int16_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<int32_t>::InitValue(const int32_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<int64_t>::InitValue(const int64_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<uint8_t>::InitValue(const uint8_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<uint16_t>::InitValue(const uint16_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<uint32_t>::InitValue(const uint32_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<uint64_t>::InitValue(const uint64_t value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<float>::InitValue(const float value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<double>::InitValue(const double value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<char *>::InitValue(const char *value, size_t valueLen) {
// 	if (value == NULL) {
// 		this->value = NULL;
// 	} else {
// 		size_t len = valueLen != size_t() //
// 					   ? valueLen		  //
// 					   : strlen(value);
// 		this->value = new char[len + 1];
// 		memcpy(this->value, value, len);
// 		this->value[len] = 0;
// 	}
// }
// template <> void MsgpackValue<TJsonRawData>::InitValue(const TJsonRawData value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<MsgpackObject *>::InitValue(MsgpackObject *value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<MsgpackArrayBase *>::InitValue(MsgpackArrayBase *value, size_t valueLen) { this->value = value; }
// /*


// */
// template <> void MsgpackValue<bool>::Set(const bool newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<int8_t>::Set(const int8_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<int16_t>::Set(const int16_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<int32_t>::Set(const int32_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<int64_t>::Set(const int64_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<uint8_t>::Set(const uint8_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<uint16_t>::Set(const uint16_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<uint32_t>::Set(const uint32_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<uint64_t>::Set(const uint64_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<float>::Set(const float newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<double>::Set(const double newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<char *>::Set(const char *newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<TJsonRawData>::Set(const TJsonRawData newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// }
// template <> void MsgpackValue<MsgpackObject *>::Set(MsgpackObject *newValue, size_t newValueLen) {
// 	if (this->value == NULL) {
// 		this->value = newValue;
// 	} else if (newValue != NULL) {
// 		newValue->CloneTo(this->value);
// 	}
// }
// template <> void MsgpackValue<MsgpackArrayBase *>::Set(MsgpackArrayBase *newValue, size_t newValueLen) {
// 	if (this->value == NULL) {
// 		this->value = newValue;
// 	} else if (newValue != NULL) {
// 		newValue->CloneTo(this->value);
// 	}
// }
// /*


// */
// template <> bool MsgpackValue<bool>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsBool()) { return false; }
// 	Set(jsonVal->GetBool());
// 	return true;
// }
// template <> bool MsgpackValue<int8_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
// 	Set(jsonVal->GetInt());
// 	return true;
// }
// template <> bool MsgpackValue<int16_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
// 	Set(jsonVal->GetInt());
// 	return true;
// }
// template <> bool MsgpackValue<int32_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
// 	Set(jsonVal->GetInt());
// 	return true;
// }
// template <> bool MsgpackValue<int64_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsInt64()) { return false; }
// 	Set(jsonVal->GetInt64());
// 	return true;
// }
// template <> bool MsgpackValue<uint8_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
// 	Set(jsonVal->GetUint());
// 	return true;
// }
// template <> bool MsgpackValue<uint16_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
// 	Set(jsonVal->GetUint());
// 	return true;
// }
// template <> bool MsgpackValue<uint32_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
// 	Set(jsonVal->GetUint());
// 	return true;
// }
// template <> bool MsgpackValue<uint64_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsUint64()) { return false; }
// 	Set(jsonVal->GetUint64());
// 	return true;
// }
// template <> bool MsgpackValue<float>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsFloat()) { return false; }
// 	Set((float)jsonVal->GetFloat());
// 	return true;
// }
// template <> bool MsgpackValue<double>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL || !jsonVal->IsDouble()) { return false; }
// 	Set(jsonVal->GetDouble());
// 	return true;
// }
// template <> bool MsgpackValue<char *>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) { return false; }
// 	if (!jsonVal->IsString()) {
// 		if (jsonVal->IsNull()) {
// 			Set(NULL);
// 			return true;
// 		}
// 		return false;
// 	}
// 	Set(jsonVal->GetString(), jsonVal->GetStringLength());
// 	return true;
// }
// template <> bool MsgpackValue<TJsonRawData>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) { return false; }
// 	if (!jsonVal->IsString()) {
// 		if (jsonVal->IsNull()) {
// 			Set({});
// 			return true;
// 		}
// 		return false;
// 	}
// 	TJsonRawData rawData = {(uint8_t *)jsonVal->GetString(), jsonVal->GetStringLength()};
// 	Set(rawData);
// 	return true;
// }
// template <> bool MsgpackValue<MsgpackObject *>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	return jsonVal != NULL && jsonVal->IsObject() && (/*jsonVal->ObjectEmpty() ||*/ value->TryParse((TJsonDocument *)jsonVal));
// }
// template <> bool MsgpackValue<MsgpackArrayBase *>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	return jsonVal != NULL && jsonVal->IsArray() && value->TryDocParse((TJsonDocument *)jsonVal);
// }
// /*


// */
// template <> void MsgpackValue<bool>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<bool> *)other)->Set(this->value); }
// template <> void MsgpackValue<int8_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int8_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<int16_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int16_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<int32_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int32_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<int64_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int64_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<uint8_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint8_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<uint16_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint16_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<uint32_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint32_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<uint64_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint64_t> *)other)->Set(this->value); }
// template <> void MsgpackValue<float>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<float> *)other)->Set(this->value); }
// template <> void MsgpackValue<double>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<double> *)other)->Set(this->value); }
// template <> void MsgpackValue<char *>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<char *> *)other)->Set(this->value); }
// template <> void MsgpackValue<TJsonRawData>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<TJsonRawData> *)other)->Set((TJsonRawData)this->value); }
// template <> void MsgpackValue<MsgpackObject *>::CloneTo(MsgpackValueBase *other) {
// 	auto thisObject = ((MsgpackObject *)value);
// 	auto otherObject = ((MsgpackObject *)((MsgpackValue<MsgpackObject *> *)other)->value);
// 	thisObject->CloneTo(otherObject);
// }
// template <> void MsgpackValue<MsgpackArrayBase *>::CloneTo(MsgpackValueBase *other) {
// 	auto thisArray = ((MsgpackArrayBase *)value);
// 	auto otherArray = ((MsgpackArrayBase *)((MsgpackValue<MsgpackArrayBase *> *)other)->value);
// 	thisArray->CloneTo(otherArray);
// }
