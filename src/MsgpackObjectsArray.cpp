
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include "MsgpackWrapper.h"

// MsgpackObjectsArray::~MsgpackObjectsArray() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// }

// bool MsgpackObjectsArray::TryDocParse(TJsonDocument *doc) {
// 	if (!doc->IsArray()) { return false; }
// 	auto jArray = doc->GetArray();
// 	Items.reserve(jArray.Size());

// 	for (const auto &jItem : jArray) {
// 		auto newItem = CreateItem();
// 		if (!newItem->TryParse((TJsonDocument *)&jItem) || !Add(newItem)) {
// 			delete newItem;
// 			Items.shrink_to_fit();
// 			return false;
// 		}
// 	}
// 	Items.shrink_to_fit();
// 	return true;
// }

// bool MsgpackObjectsArray::Add(MsgpackObject *item) {
// 	if (!Validate(item)) { return false; }
// 	AddInternal(item);
// 	return true;
// }

// void MsgpackObjectsArray::AddInternal(MsgpackObject *item) { Items.push_back(item); }

// bool MsgpackObjectsArray::Update(size_t index, MsgpackObject *item) {
// 	if (index >= Size() || !Validate(item)) { return false; }
// 	DeleteItem(Items[index]);
// 	Items[index] = item;
// 	return true;
// }

// void MsgpackObjectsArray::Remove(MsgpackObject *item) {
// 	auto iter = Find(item);
// 	if (iter != Items.end()) {
// 		DeleteItem(*iter);
// 		Items.erase(iter);
// 	}
// }
// std::vector<MsgpackObject *>::iterator MsgpackObjectsArray::Find(MsgpackObject *item) {
// 	if (item != NULL) {
// 		for (auto iter = Items.begin(); iter != Items.end(); iter++) {
// 			if (*(*iter) == *item) { return iter; }
// 		}
// 	}
// 	return Items.end();
// }

// void MsgpackObjectsArray::DeleteItem(MsgpackObject *item) { delete item; }

// void MsgpackObjectsArray::WriteToDoc(TJsonDocument *doc) {
// 	auto &allocator = doc->GetAllocator();
// 	doc->SetArray();
// 	doc->Reserve(Items.size(), allocator);

// 	for (const auto &item : Items) {
// 		rapidjson::Document childDoc(&allocator);
// 		MsgpackObject *jObject = item;
// 		jObject->WriteToDoc(&childDoc);
// 		doc->PushBack(childDoc, allocator);
// 	}
// }

// bool operator!=(const MsgpackObjectsArray &v1, const MsgpackObjectsArray &v2) { return !((MsgpackObjectsArray *)&v1)->Equals((MsgpackObjectsArray *)&v2); }
// bool operator==(const MsgpackObjectsArray &v1, const MsgpackObjectsArray &v2) { return !(v1 != v2); }

// bool MsgpackObjectsArray::Equals(MsgpackArrayBase *other) {
// 	if (Items.size() != ((MsgpackObjectsArray *)other)->Items.size()) { return false; }
// 	for (size_t i = 0; i < Items.size(); i++) {
// 		if (*(Items[i]) != *(((MsgpackObjectsArray *)other)->Items[i])) { return false; }
// 	}
// 	return true;
// }

// void MsgpackObjectsArray::CloneTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackObjectsArray *)other);
// 	for (const auto &item : otherArray->Items) { delete item; }
// 	otherArray->Items.clear();

// 	for (const auto &item : Items) {
// 		auto newItem = CreateItem();
// 		item->CloneTo(newItem);
// 		otherArray->AddInternal(newItem);
// 	}
// }

// typename std::vector<MsgpackObject *>::iterator MsgpackObjectsArray::MoveTo(MsgpackArrayBase *other, MsgpackObject *item) {
// 	auto otherArray = ((MsgpackObjectsArray *)other);
// 	auto iter = std::find(Items.begin(), Items.end(), item);
// 	if (iter != Items.end()) {
// 		if (otherArray->Validate(*iter)) {
// 			otherArray->AddInternal(*iter);
// 			iter = Items.erase(iter);
// 		} else {
// 			iter++;
// 		}
// 	}
// 	return iter;
// }

// void MsgpackObjectsArray::MoveAllTo(MsgpackArrayBase *other) {
// 	auto otherArray = ((MsgpackObjectsArray *)other);
// 	auto iter = Items.begin();
// 	while (iter != Items.end()) {
// 		if (otherArray->Validate(*iter)) {
// 			otherArray->AddInternal(*iter);
// 			iter = Items.erase(iter);
// 		} else {
// 			iter++;
// 		}
// 	}
// }

// void MsgpackObjectsArray::Clear() {
// 	for (const auto &item : Items) { DeleteItem(item); }
// 	Items.clear();
// }