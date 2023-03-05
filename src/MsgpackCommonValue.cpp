
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include "MsgpackWrapper.h"

// template <> bool MsgpackCommonValue<bool>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<bool> *)other)->value; }
// template <> bool MsgpackCommonValue<int8_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<int8_t> *)other)->value; }
// template <> bool MsgpackCommonValue<int16_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<int16_t> *)other)->value; }
// template <> bool MsgpackCommonValue<int32_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<int32_t> *)other)->value; }
// template <> bool MsgpackCommonValue<int64_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<int64_t> *)other)->value; }
// template <> bool MsgpackCommonValue<uint8_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<uint8_t> *)other)->value; }
// template <> bool MsgpackCommonValue<uint16_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<uint16_t> *)other)->value; }
// template <> bool MsgpackCommonValue<uint32_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<uint32_t> *)other)->value; }
// template <> bool MsgpackCommonValue<uint64_t>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<uint64_t> *)other)->value; }
// template <> bool MsgpackCommonValue<float>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<float> *)other)->value; }
// template <> bool MsgpackCommonValue<double>::Equals(MsgpackValueBase *other) { return MsgpackValueBase::NamesCompare(Name, other->Name) && value == ((MsgpackCommonValue<double> *)other)->value; }
// template <> bool MsgpackCommonValue<char *>::Equals(MsgpackValueBase *other) { //
// 	return MsgpackValueBase::NamesCompare(Name, other->Name)
// 		&& (value == ((MsgpackCommonValue<char *> *)other)->value
// 			|| (value != NULL && ((MsgpackCommonValue<char *> *)other)->value != NULL && strcmp(value, ((MsgpackCommonValue<char *> *)other)->value) == 0));
// }
// template <> bool MsgpackCommonValue<TJsonRawData>::Equals(MsgpackValueBase *other) {
// 	return MsgpackValueBase::NamesCompare(Name, other->Name)														//
// 		&& ((TJsonRawData)value).Data == ((TJsonRawData)(((MsgpackCommonValue<TJsonRawData> *)other)->value)).Data //
// 		&& ((TJsonRawData)value).Size == ((TJsonRawData)(((MsgpackCommonValue<TJsonRawData> *)other)->value)).Size;
// }
// template <> bool MsgpackCommonValue<MsgpackObject *>::Equals(MsgpackValueBase *other) {
// 	return MsgpackValueBase::NamesCompare(Name, other->Name) && (MsgpackObject *)value->Equals((MsgpackObject *)((MsgpackCommonValue<MsgpackObject *> *)other)->value);
// }
// template <> bool MsgpackCommonValue<MsgpackArrayBase *>::Equals(MsgpackValueBase *other) {
// 	return MsgpackValueBase::NamesCompare(Name, other->Name) && (MsgpackObject *)value->Equals((MsgpackArrayBase *)(((MsgpackCommonValue<MsgpackArrayBase *> *)other)->value));
// }
// /*


// */
// template <> void MsgpackCommonValue<bool>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetBool(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<int8_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetInt(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<int16_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetInt(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<int32_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetInt(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<int64_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetInt64(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<uint8_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetUint(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<uint16_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetUint(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<uint32_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetUint(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<uint64_t>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetUint64(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<float>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetFloat(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<double>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetDouble(value);
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<char *>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	if (isNull || value == NULL) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetString(rapidjson::StringRef(value));
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Value json_val;
// 	TJsonRawData rawData = value;
// 	if (isNull || rawData.Data == NULL) {
// 		json_val.SetNull();
// 	} else {
// 		json_val.SetString(rapidjson::StringRef((char *)rawData.Data, (rapidjson::SizeType)rawData.Size));
// 	}
// 	doc->AddMember(Name, json_val, doc->GetAllocator());
// }
// template <> void MsgpackCommonValue<MsgpackObject *>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	rapidjson::Document jObject(&allocator);
// 	if (isNull || value == NULL) {
// 		jObject.SetNull();
// 	} else {
// 		value->WriteToDoc(&jObject);
// 	}
// 	doc->AddMember(Name, jObject, allocator);
// }
// template <> void MsgpackCommonValue<MsgpackArrayBase *>::WriteToDoc(TJsonDocument *doc) {
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	rapidjson::Document jArray(&allocator);
// 	if (isNull || value == NULL) {
// 		jArray.SetNull();
// 	} else {
// 		value->WriteToDoc(&jArray);
// 	}
// 	doc->AddMember(Name, jArray, allocator);
// }
// /*


// */
// template <> void MsgpackCommonValue<bool>::DeleteValue() {}
// template <> void MsgpackCommonValue<int8_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<int16_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<int32_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<int64_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<uint8_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<uint16_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<uint32_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<uint64_t>::DeleteValue() {}
// template <> void MsgpackCommonValue<float>::DeleteValue() {}
// template <> void MsgpackCommonValue<double>::DeleteValue() {}
// template <> void MsgpackCommonValue<char *>::DeleteValue() { delete[] this->value; }
// template <> void MsgpackCommonValue<TJsonRawData>::DeleteValue() {}
// template <> void MsgpackCommonValue<MsgpackObject *>::DeleteValue() {}
// template <> void MsgpackCommonValue<MsgpackArrayBase *>::DeleteValue() {}
// /*


// */
// template <> void MsgpackCommonValue<bool>::InitValue(const bool value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<int8_t>::InitValue(const int8_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<int16_t>::InitValue(const int16_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<int32_t>::InitValue(const int32_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<int64_t>::InitValue(const int64_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<uint8_t>::InitValue(const uint8_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<uint16_t>::InitValue(const uint16_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<uint32_t>::InitValue(const uint32_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<uint64_t>::InitValue(const uint64_t value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<float>::InitValue(const float value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<double>::InitValue(const double value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = false;
// }
// template <> void MsgpackCommonValue<char *>::InitValue(const char *value, size_t valueLen) {
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
// 	this->isNull = this->value == NULL;
// }
// template <> void MsgpackCommonValue<TJsonRawData>::InitValue(const TJsonRawData value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = this->value.Data == NULL;
// }
// template <> void MsgpackCommonValue<MsgpackObject *>::InitValue(MsgpackObject *value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = this->value == NULL;
// }
// template <> void MsgpackCommonValue<MsgpackArrayBase *>::InitValue(MsgpackArrayBase *value, size_t valueLen) {
// 	this->value = value;
// 	this->isNull = this->value == NULL;
// }
// /*


//  */
// template <> void MsgpackCommonValue<bool>::Set(const bool newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<int8_t>::Set(const int8_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<int16_t>::Set(const int16_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<int32_t>::Set(const int32_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<int64_t>::Set(const int64_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<uint8_t>::Set(const uint8_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<uint16_t>::Set(const uint16_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<uint32_t>::Set(const uint32_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<uint64_t>::Set(const uint64_t newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<float>::Set(const float newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<double>::Set(const double newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<char *>::Set(const char *newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<TJsonRawData>::Set(const TJsonRawData newValue, size_t newValueLen) {
// 	DeleteValue();
// 	InitValue(newValue, newValueLen);
// 	presented = true;
// }
// template <> void MsgpackCommonValue<MsgpackObject *>::Set(MsgpackObject *newValue, size_t newValueLen) {
// 	if (this->value == NULL) {
// 		this->value = newValue;
// 	} else if (newValue != NULL) {
// 		newValue->CloneTo(this->value);
// 	}
// 	this->isNull = this->value == NULL;
// 	presented = true;
// }
// template <> void MsgpackCommonValue<MsgpackArrayBase *>::Set(MsgpackArrayBase *newValue, size_t newValueLen) {
// 	if (this->value == NULL) {
// 		this->value = newValue;
// 	} else if (newValue != NULL) {
// 		newValue->CloneTo(this->value);
// 	}
// 	this->isNull = this->value == NULL;
// 	presented = true;
// }
// /*



// */
// template <> bool MsgpackCommonValue<bool>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsBool()) {
// 		Set(jsonVal->GetBool());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<int8_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsInt()) {
// 		Set(jsonVal->GetInt());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<int16_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsInt()) {
// 		Set(jsonVal->GetInt());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<int32_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsInt()) {
// 		Set(jsonVal->GetInt());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<int64_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsInt64()) {
// 		Set(jsonVal->GetInt64());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<uint8_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsUint()) {
// 		Set(jsonVal->GetUint());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<uint16_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsUint()) {
// 		Set(jsonVal->GetUint());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<uint32_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsUint()) {
// 		Set(jsonVal->GetUint());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<uint64_t>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsUint()) {
// 		Set(jsonVal->GetUint());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<float>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsFloat()) {
// 		Set(jsonVal->GetFloat());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<double>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsDouble()) {
// 		Set(jsonVal->GetDouble());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<char *>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsString()) {
// 		Set(jsonVal->GetString(), jsonVal->GetStringLength());
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		Set(NULL);
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<TJsonRawData>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsString()) {
// 		TJsonRawData rawData = {(uint8_t *)jsonVal->GetString(), jsonVal->GetStringLength()};
// 		Set(rawData);
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		Set({});
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<MsgpackObject *>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsObject()) {
// 		value->TryParse((TJsonDocument *)jsonVal);
// 		isNull = false;
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }
// template <> bool MsgpackCommonValue<MsgpackArrayBase *>::TryParse(TJsonDocument *doc) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	if (jsonVal == NULL) {
// 		presented = false;
// 		return true;
// 	}
// 	presented = true;
// 	if (jsonVal->IsArray()) {
// 		value->TryDocParse((TJsonDocument *)jsonVal);
// 		isNull = false;
// 		return true;
// 	}
// 	if (jsonVal->IsNull()) {
// 		isNull = true;
// 		return true;
// 	}
// 	return false;
// }

// /*


// */
// template <> void MsgpackCommonValue<bool>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<bool> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<int8_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<int8_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<int16_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<int16_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<int32_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<int32_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<int64_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<int64_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<uint8_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<uint8_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<uint16_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<uint16_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<uint32_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<uint32_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<uint64_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<uint64_t> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<float>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<float> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<double>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<double> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<char *>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<char *> *)other)->Set(this->value); }
// template <> void MsgpackCommonValue<TJsonRawData>::CloneTo(MsgpackValueBase *other) { ((MsgpackCommonValue<TJsonRawData> *)other)->Set((TJsonRawData)this->value); }
// template <> void MsgpackCommonValue<MsgpackObject *>::CloneTo(MsgpackValueBase *other) {
// 	auto thisObject = ((MsgpackObject *)value);
// 	auto otherObject = ((MsgpackObject *)((MsgpackCommonValue<MsgpackObject *> *)other)->value);
// 	thisObject->CloneTo(otherObject);
// }
// template <> void MsgpackCommonValue<MsgpackArrayBase *>::CloneTo(MsgpackValueBase *other) {
// 	auto thisArray = ((MsgpackArrayBase *)value);
// 	auto otherArray = ((MsgpackArrayBase *)((MsgpackCommonValue<MsgpackArrayBase *> *)other)->value);
// 	thisArray->CloneTo(otherArray);
// }
// /*


// */
// template <> bool MsgpackCommonValue<bool>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<int8_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<int16_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<int32_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<int64_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<uint8_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<uint16_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<uint32_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<uint64_t>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<float>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<double>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<char *>::IsNull() { return isNull || (char *)value == NULL; }
// template <> bool MsgpackCommonValue<TJsonRawData>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<MsgpackObject *>::IsNull() { return isNull; }
// template <> bool MsgpackCommonValue<MsgpackArrayBase *>::IsNull() { return isNull; }
// /*



// */
// template <> void MsgpackCommonValue<bool>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<int8_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<int16_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<int32_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<int64_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<uint8_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<uint16_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<uint32_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<uint64_t>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<float>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<double>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<char *>::ResetToNull() { Set(NULL); }
// template <> void MsgpackCommonValue<TJsonRawData>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<MsgpackObject *>::ResetToNull() { isNull = true; }
// template <> void MsgpackCommonValue<MsgpackArrayBase *>::ResetToNull() { isNull = true; }
