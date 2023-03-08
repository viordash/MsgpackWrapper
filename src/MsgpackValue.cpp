
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "MsgpackWrapper.h"

template <> bool MsgpackValue<bool>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<bool> *)other)->value; }
template <> bool MsgpackValue<int8_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<int8_t> *)other)->value; }
template <> bool MsgpackValue<int16_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<int16_t> *)other)->value; }
template <> bool MsgpackValue<int32_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<int32_t> *)other)->value; }
template <> bool MsgpackValue<int64_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<int64_t> *)other)->value; }
template <> bool MsgpackValue<uint8_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<uint8_t> *)other)->value; }
template <> bool MsgpackValue<uint16_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<uint16_t> *)other)->value; }
template <> bool MsgpackValue<uint32_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<uint32_t> *)other)->value; }
template <> bool MsgpackValue<uint64_t>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<uint64_t> *)other)->value; }
template <> bool MsgpackValue<float>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<float> *)other)->value; }
template <> bool MsgpackValue<double>::Equals(MsgpackValueBase *other) { return Id == other->Id && value == ((MsgpackValue<double> *)other)->value; }
template <> bool MsgpackValue<char *>::Equals(MsgpackValueBase *other) { //
	return Id == other->Id
		&& (value == ((MsgpackValue<char *> *)other)->value //
			|| (value != NULL && ((MsgpackValue<char *> *)other)->value != NULL && strcmp(value, ((MsgpackValue<char *> *)other)->value) == 0));
}
template <> bool MsgpackValue<TMsgpackRawData>::Equals(MsgpackValueBase *other) {
	return Id == other->Id && ((TMsgpackRawData)value).Data == ((TMsgpackRawData)(((MsgpackValue<TMsgpackRawData> *)other)->value)).Data //
		&& ((TMsgpackRawData)value).Size == ((TMsgpackRawData)(((MsgpackValue<TMsgpackRawData> *)other)->value)).Size;
}
// template <> bool MsgpackValue<MsgpackObject *>::Equals(MsgpackValueBase *other) {
// 	return Id == other->Id && (MsgpackObject *)value->Equals((MsgpackObject *)((MsgpackValue<MsgpackObject *> *)other)->value);
// }
// template <> bool MsgpackValue<MsgpackArrayBase *>::Equals(MsgpackValueBase *other) {
// 	return Id == other->Id && (MsgpackObject *)value->Equals((MsgpackArrayBase *)(((MsgpackValue<MsgpackArrayBase *> *)other)->value));
// }
/*
Write(msgpack_packer *packer)

*/
template <> bool MsgpackValue<bool>::Write(msgpack_packer *packer) { return (value ? msgpack_pack_true(packer) : msgpack_pack_false(packer)) == 0; }
template <> bool MsgpackValue<int8_t>::Write(msgpack_packer *packer) { return msgpack_pack_int8(packer, value) == 0; }
template <> bool MsgpackValue<int16_t>::Write(msgpack_packer *packer) { return msgpack_pack_int16(packer, value) == 0; }
template <> bool MsgpackValue<int32_t>::Write(msgpack_packer *packer) { return msgpack_pack_int32(packer, value) == 0; }
template <> bool MsgpackValue<int64_t>::Write(msgpack_packer *packer) { return msgpack_pack_int64(packer, value) == 0; }
template <> bool MsgpackValue<uint8_t>::Write(msgpack_packer *packer) { return msgpack_pack_uint8(packer, value) == 0; }
template <> bool MsgpackValue<uint16_t>::Write(msgpack_packer *packer) { return msgpack_pack_uint16(packer, value) == 0; }
template <> bool MsgpackValue<uint32_t>::Write(msgpack_packer *packer) { return msgpack_pack_uint32(packer, value) == 0; }
template <> bool MsgpackValue<uint64_t>::Write(msgpack_packer *packer) { return msgpack_pack_uint64(packer, value) == 0; }
template <> bool MsgpackValue<float>::Write(msgpack_packer *packer) { return msgpack_pack_float(packer, value) == 0; }
template <> bool MsgpackValue<double>::Write(msgpack_packer *packer) { return msgpack_pack_double(packer, value) == 0; }
template <> bool MsgpackValue<char *>::Write(msgpack_packer *packer) {
	if (value == NULL) {
		return msgpack_pack_nil(packer) == 0;
	} else {
		auto sLen = strlen(value);
		return msgpack_pack_str(packer, sLen) == 0 //
			&& msgpack_pack_str_body(packer, value, sLen) == 0;
	}
}
template <> bool MsgpackValue<TMsgpackRawData>::Write(msgpack_packer *packer) {
	if (value.Data == NULL) {
		return msgpack_pack_nil(packer) == 0;
	} else {
		return msgpack_pack_v4raw(packer, value.Size) == 0 //
			&& msgpack_pack_v4raw_body(packer, value.Data, value.Size) == 0;
	}
}
// template <> bool MsgpackValue<MsgpackObject *>::Write(msgpack_packer *packer) {
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	rapidjson::Document jObject(&allocator);
// 	value->WriteToDoc(&jObject);
// 	doc->AddMember(Name, jObject, allocator);
// }
// template <> void MsgpackValue<MsgpackArrayBase *>::Write(msgpack_packer *packer) {
// 	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
// 	rapidjson::Document jArray(&allocator);
// 	value->WriteToDoc(&jArray);
// 	doc->AddMember(Name, jArray, allocator);
// }
/*


*/
template <> void MsgpackValue<bool>::DeleteValue() {}
template <> void MsgpackValue<int8_t>::DeleteValue() {}
template <> void MsgpackValue<int16_t>::DeleteValue() {}
template <> void MsgpackValue<int32_t>::DeleteValue() {}
template <> void MsgpackValue<int64_t>::DeleteValue() {}
template <> void MsgpackValue<uint8_t>::DeleteValue() {}
template <> void MsgpackValue<uint16_t>::DeleteValue() {}
template <> void MsgpackValue<uint32_t>::DeleteValue() {}
template <> void MsgpackValue<uint64_t>::DeleteValue() {}
template <> void MsgpackValue<float>::DeleteValue() {}
template <> void MsgpackValue<double>::DeleteValue() {}
template <> void MsgpackValue<char *>::DeleteValue() { delete[] this->value; }
template <> void MsgpackValue<TMsgpackRawData>::DeleteValue() {}
// template <> void MsgpackValue<MsgpackObject *>::DeleteValue() {}
// template <> void MsgpackValue<MsgpackArrayBase *>::DeleteValue() {}
/*


*/
template <> void MsgpackValue<bool>::InitValue(const bool value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<int8_t>::InitValue(const int8_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<int16_t>::InitValue(const int16_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<int32_t>::InitValue(const int32_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<int64_t>::InitValue(const int64_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<uint8_t>::InitValue(const uint8_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<uint16_t>::InitValue(const uint16_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<uint32_t>::InitValue(const uint32_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<uint64_t>::InitValue(const uint64_t value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<float>::InitValue(const float value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<double>::InitValue(const double value, size_t valueLen) { this->value = value; }
template <> void MsgpackValue<char *>::InitValue(const char *value, size_t valueLen) {
	if (value == NULL) {
		this->value = NULL;
	} else {
		size_t len = valueLen != size_t() //
					   ? valueLen		  //
					   : strlen(value);
		this->value = new char[len + 1];
		memcpy(this->value, value, len);
		this->value[len] = 0;
	}
}
template <> void MsgpackValue<TMsgpackRawData>::InitValue(const TMsgpackRawData value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<MsgpackObject *>::InitValue(MsgpackObject *value, size_t valueLen) { this->value = value; }
// template <> void MsgpackValue<MsgpackArrayBase *>::InitValue(MsgpackArrayBase *value, size_t valueLen) { this->value = value; }
/*

*/
template <> void MsgpackValue<bool>::Set(const bool newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<int8_t>::Set(const int8_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<int16_t>::Set(const int16_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<int32_t>::Set(const int32_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<int64_t>::Set(const int64_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<uint8_t>::Set(const uint8_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<uint16_t>::Set(const uint16_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<uint32_t>::Set(const uint32_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<uint64_t>::Set(const uint64_t newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<float>::Set(const float newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<double>::Set(const double newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<char *>::Set(const char *newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
template <> void MsgpackValue<TMsgpackRawData>::Set(const TMsgpackRawData newValue, size_t newValueLen) {
	DeleteValue();
	InitValue(newValue, newValueLen);
}
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
/*

*/
template <> bool MsgpackValue<bool>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_BOOLEAN) { return false; }
	Set(object.via.boolean);
	return true;
}
template <> bool MsgpackValue<int8_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_NEGATIVE_INTEGER || object.via.i64 < INT8_MIN || object.via.i64 > INT8_MAX) { return false; }
	Set((int8_t)object.via.i64);
	return true;
}
template <> bool MsgpackValue<int16_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_NEGATIVE_INTEGER || object.via.i64 < INT16_MIN || object.via.i64 > INT16_MAX) { return false; }
	Set((int16_t)object.via.i64);
	return true;
}
template <> bool MsgpackValue<int32_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_NEGATIVE_INTEGER || object.via.i64 < INT32_MIN || object.via.i64 > INT32_MAX) { return false; }
	Set((int32_t)object.via.i64);
	return true;
}
template <> bool MsgpackValue<int64_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_NEGATIVE_INTEGER) { return false; }
	Set(object.via.i64);
	return true;
}
template <> bool MsgpackValue<uint8_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_POSITIVE_INTEGER || object.via.u64 > UINT8_MAX) { return false; }
	Set((uint8_t)object.via.u64);
	return true;
}
template <> bool MsgpackValue<uint16_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_POSITIVE_INTEGER || object.via.u64 > UINT16_MAX) { return false; }
	Set((uint16_t)object.via.u64);
	return true;
}
template <> bool MsgpackValue<uint32_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_POSITIVE_INTEGER || object.via.u64 > UINT32_MAX) { return false; }
	Set((uint32_t)object.via.u64);
	return true;
}
template <> bool MsgpackValue<uint64_t>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_POSITIVE_INTEGER) { return false; }
	Set(object.via.u64);
	return true;
}
template <> bool MsgpackValue<float>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_FLOAT32) { return false; }
	Set((float)object.via.f64);
	return true;
}
template <> bool MsgpackValue<double>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type != MSGPACK_OBJECT_FLOAT64) { return false; }
	Set((double)object.via.f64);
	return true;
}
template <> bool MsgpackValue<char *>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type == MSGPACK_OBJECT_NIL) {
		Set(NULL);
		return true;
	}
	if (object.type != MSGPACK_OBJECT_STR) { return false; }

	Set(object.via.str.ptr, object.via.str.size);
	return true;
}
template <> bool MsgpackValue<TMsgpackRawData>::TryParse(msgpack_object *deserialized) {
	if (this->Id >= deserialized->via.array.size) { return false; }
	msgpack_object object = deserialized->via.array.ptr[this->Id];
	if (object.type == MSGPACK_OBJECT_NIL) {
		Set({});
		return true;
	}
	if (object.type != MSGPACK_OBJECT_BIN) { return false; }

	TMsgpackRawData rawData = {(uint8_t *)object.via.bin.ptr, object.via.bin.size};
	Set(rawData);
	return true;
}
// template <> bool MsgpackValue<MsgpackObject *>::TryParse(msgpack_object *deserialized) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	return jsonVal != NULL && jsonVal->IsObject() && (/*jsonVal->ObjectEmpty() ||*/ value->TryParse((TMsgpackDocument *)jsonVal));
// }
// template <> bool MsgpackValue<MsgpackArrayBase *>::TryParse(msgpack_object *deserialized) {
// 	auto jsonVal = MsgpackValueBase::GetMember(doc, this->Name);
// 	return jsonVal != NULL && jsonVal->IsArray() && value->TryDocParse((TMsgpackDocument *)jsonVal);
// }
/*

*/
template <> void MsgpackValue<bool>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<bool> *)other)->Set(this->value); }
template <> void MsgpackValue<int8_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int8_t> *)other)->Set(this->value); }
template <> void MsgpackValue<int16_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int16_t> *)other)->Set(this->value); }
template <> void MsgpackValue<int32_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int32_t> *)other)->Set(this->value); }
template <> void MsgpackValue<int64_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<int64_t> *)other)->Set(this->value); }
template <> void MsgpackValue<uint8_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint8_t> *)other)->Set(this->value); }
template <> void MsgpackValue<uint16_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint16_t> *)other)->Set(this->value); }
template <> void MsgpackValue<uint32_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint32_t> *)other)->Set(this->value); }
template <> void MsgpackValue<uint64_t>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<uint64_t> *)other)->Set(this->value); }
template <> void MsgpackValue<float>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<float> *)other)->Set(this->value); }
template <> void MsgpackValue<double>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<double> *)other)->Set(this->value); }
template <> void MsgpackValue<char *>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<char *> *)other)->Set(this->value); }
template <> void MsgpackValue<TMsgpackRawData>::CloneTo(MsgpackValueBase *other) { ((MsgpackValue<TMsgpackRawData> *)other)->Set((TMsgpackRawData)this->value); }
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
