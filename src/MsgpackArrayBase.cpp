
#include "MsgpackWrapper.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

bool MsgpackArrayBase::TryParse(const char *buffer, size_t length) {
    auto unpacker = BeginTryParse(buffer, length);
    if (unpacker == NULL) { return false; }
    EndTryParse(unpacker);
    return true;
}

msgpack_unpacked *MsgpackArrayBase::BeginTryParse(const char *buffer, size_t length) {
    if (buffer == NULL) { return NULL; }

    msgpack_unpacked *unpacked = new msgpack_unpacked();
    msgpack_unpacked_init(unpacked);
    msgpack_unpack_return ret = msgpack_unpack_next(unpacked, buffer, length, NULL);

    if (ret != MSGPACK_UNPACK_SUCCESS) {
        EndTryParse(unpacked);
        return NULL;
    }
    if (!TryParseObject(&unpacked->data)) {
        EndTryParse(unpacked);
        return NULL;
    }
    return unpacked;
}

void MsgpackArrayBase::EndTryParse(msgpack_unpacked *unpacked) {
    msgpack_unpacked_destroy(unpacked);
    delete unpacked;
}

size_t MsgpackArrayBase::Write(char *outBuffer, size_t outBufferSize) {
    msgpack_sbuffer sbuf;
    msgpack_packer packer;
    msgpack_sbuffer_init(&sbuf);
    msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

    if (!WriteObject(&packer)) {
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

size_t MsgpackArrayBase::DirectWriteTo(void *parent, TOnReady onReady) {
    msgpack_sbuffer sbuf;
    msgpack_packer packer;
    msgpack_sbuffer_init(&sbuf);
    msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

    if (!WriteObject(&packer)) {
        msgpack_sbuffer_destroy(&sbuf);
        return 0;
    };

    onReady(parent, sbuf.data, sbuf.size);
    msgpack_sbuffer_destroy(&sbuf);
    return sbuf.size;
}