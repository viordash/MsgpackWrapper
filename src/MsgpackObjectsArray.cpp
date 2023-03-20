
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "MsgpackWrapper.h"

MsgpackObjectsArray::~MsgpackObjectsArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}

bool MsgpackObjectsArray::TryParseObject(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
	Items.reserve(deserialized->via.array.size);
	size_t i = 0;
	while (i < deserialized->via.array.size) {
		msgpack_object object = deserialized->via.array.ptr[i];
		if (object.type != MSGPACK_OBJECT_ARRAY) { break; }

		auto newItem = CreateItem();
		if (!newItem->TryParse(&object) || !Add(newItem)) {
			delete newItem;
			break;
		}
		i++;
	}
	Items.shrink_to_fit();
	return i == deserialized->via.array.size;
}

bool MsgpackObjectsArray::Add(MsgpackObject *item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}

void MsgpackObjectsArray::AddInternal(MsgpackObject *item) { Items.push_back(item); }

bool MsgpackObjectsArray::Update(size_t index, MsgpackObject *item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}

bool MsgpackObjectsArray::Remove(MsgpackObject *item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return false; }
	DeleteItem(*iter);
	Items.erase(iter);
	return true;
}
std::vector<MsgpackObject *>::iterator MsgpackObjectsArray::Find(MsgpackObject *item) {
	if (item != NULL) {
		for (auto iter = Items.begin(); iter != Items.end(); iter++) {
			if (*(*iter) == *item) { return iter; }
		}
	}
	return Items.end();
}

void MsgpackObjectsArray::DeleteItem(MsgpackObject *item) { delete item; }

bool MsgpackObjectsArray::WriteObject(msgpack_packer *packer) {
	if (msgpack_pack_array(packer, Items.size()) != 0) { return false; }
	for (const auto &item : Items) {
		if (!item->Write(packer)) { return false; }
	}
	return true;
}

bool operator!=(const MsgpackObjectsArray &v1, const MsgpackObjectsArray &v2) { return !((MsgpackObjectsArray *)&v1)->Equals((MsgpackObjectsArray *)&v2); }
bool operator==(const MsgpackObjectsArray &v1, const MsgpackObjectsArray &v2) { return !(v1 != v2); }

bool MsgpackObjectsArray::Equals(MsgpackArrayBase *other) {
	if (other == NULL) { return false; }
	if (Items.size() != ((MsgpackObjectsArray *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (*(Items[i]) != *(((MsgpackObjectsArray *)other)->Items[i])) { return false; }
	}
	return true;
}

void MsgpackObjectsArray::CloneTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackObjectsArray *)other);
	for (const auto &item : otherArray->Items) { delete item; }
	otherArray->Items.clear();

	for (const auto &item : Items) {
		auto newItem = CreateItem();
		item->CloneTo(newItem);
		otherArray->AddInternal(newItem);
	}
}

typename std::vector<MsgpackObject *>::iterator MsgpackObjectsArray::MoveTo(MsgpackArrayBase *other, MsgpackObject *item) {
	auto otherArray = ((MsgpackObjectsArray *)other);
	auto iter = std::find(Items.begin(), Items.end(), item);
	if (iter != Items.end()) {
		if (otherArray->Validate(*iter)) {
			otherArray->AddInternal(*iter);
			iter = Items.erase(iter);
		} else {
			iter++;
		}
	}
	return iter;
}

void MsgpackObjectsArray::MoveAllTo(MsgpackArrayBase *other) {
	auto otherArray = ((MsgpackObjectsArray *)other);
	auto iter = Items.begin();
	while (iter != Items.end()) {
		if (otherArray->Validate(*iter)) {
			otherArray->AddInternal(*iter);
			iter = Items.erase(iter);
		} else {
			iter++;
		}
	}
}

void MsgpackObjectsArray::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}