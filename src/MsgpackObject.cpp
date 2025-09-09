
#include "MsgpackWrapper.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

MsgpackValueBase *MsgpackFieldsContainer::GetField(const unsigned int id) {
    for (auto item = Fields.begin(); item != Fields.end(); item++) {
        auto field = *item;
        if (field->Id == id) { return field; }
    }
    return NULL;
}

bool MsgpackObject::TryParse(msgpack_object *deserialized) {
    if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return false; }
    if (deserialized->via.array.size != Fields.size()) { return false; }

    for (auto item = Fields.begin(); item != Fields.end(); item++) {
        auto field = *item;
        if (!field->TryParse(deserialized)) { return false; }
    }
    if (!this->Validate()) { return false; }
    return true;
}

msgpack_unpacked *MsgpackObject::BeginTryParse(const char *buffer, size_t length) {
    if (buffer == NULL) { return NULL; }

    msgpack_unpacked *unpacked = new msgpack_unpacked();
    msgpack_unpacked_init(unpacked);
    msgpack_unpack_return ret = msgpack_unpack_next(unpacked, buffer, length, NULL);

    if (ret != MSGPACK_UNPACK_SUCCESS) {
        EndTryParse(unpacked);
        return NULL;
    }
    if (!TryParse(&unpacked->data)) {
        EndTryParse(unpacked);
        return NULL;
    }
    return unpacked;
}

void MsgpackObject::EndTryParse(msgpack_unpacked *unpacked) {
    msgpack_unpacked_destroy(unpacked);
    delete unpacked;
}

bool MsgpackObject::TryParse(const char *buffer, size_t length) {
    auto unpacker = BeginTryParse(buffer, length);
    if (unpacker == NULL) { return false; }
    EndTryParse(unpacker);
    return true;
}

bool MsgpackObject::Write(msgpack_packer *packer) {
    msgpack_pack_array(packer, Fields.size());
    for (const auto &field : Fields) {
        if (!field->Write(packer)) { return false; };
    }
    return true;
}

size_t MsgpackObject::Write(char *outBuffer, size_t outBufferSize) {
    msgpack_sbuffer sbuf;
    msgpack_packer packer;
    msgpack_sbuffer_init(&sbuf);
    msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

    if (!Write(&packer)) {
        msgpack_sbuffer_destroy(&sbuf);
        return 0;
    };

    if (sbuf.size > outBufferSize) {
        msgpack_sbuffer_destroy(&sbuf);
        return 0;
    }
    memcpy(outBuffer, sbuf.data, sbuf.size);

    msgpack_sbuffer_destroy(&sbuf);
    return sbuf.size;
}

size_t MsgpackObject::DirectWriteTo(void *parent, TOnReady onReady) {
    msgpack_sbuffer sbuf;
    msgpack_packer packer;
    msgpack_sbuffer_init(&sbuf);
    msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

    if (!Write(&packer)) {
        msgpack_sbuffer_destroy(&sbuf);
        return 0;
    };

    onReady(parent, sbuf.data, sbuf.size);
    msgpack_sbuffer_destroy(&sbuf);
    return sbuf.size;
}

bool operator!=(const MsgpackObject &v1, const MsgpackObject &v2) { return !((MsgpackObject *)&v1)->Equals((MsgpackObject *)&v2); }
bool operator==(const MsgpackObject &v1, const MsgpackObject &v2) { return !(v1 != v2); }

bool MsgpackObject::Equals(MsgpackObject *other) {
    if (other == NULL) { return false; }
    if (Fields.size() != other->Fields.size()) { return false; }

    auto item = Fields.begin();
    auto otherItem = other->Fields.begin();
    while (item != Fields.end() && otherItem != other->Fields.end()) {
        auto field = *item;
        auto otherField = *otherItem;
        if (!field->Equals(otherField)) { return false; }
        item++;
        otherItem++;
    }
    return true;
}

void MsgpackObject::CloneTo(MsgpackObject *other) {
    auto item = Fields.begin();
    auto otherItem = other->Fields.begin();
    while (item != Fields.end() && otherItem != other->Fields.end()) {
        auto field = *item;
        auto otherField = *otherItem;
        field->CloneTo(otherField);
        item++;
        otherItem++;
    }
}