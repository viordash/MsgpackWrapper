#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "MsgpackWrapper.h"

// int main(const int argc, const char *argv[]) {
// 	fprintf(stdout, "json to class object\n");

// 	return EXIT_SUCCESS;
// }

#include <msgpack.h>
#include <stdio.h>

void print(char const *buf, size_t len) {
	size_t i = 0;
	for (; i < len; ++i) printf("%02x ", 0xff & buf[i]);
	printf("\n");
}

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : MsgpackObject {
  public:
	MsgpackValue<char *> Name;
	MsgpackValue<uint32_t> Role;

	UserDto(const char *name = {}, const TUserRole role = {})
		: Name(this, 0, name), //
		  Role(this, 1, role){};

	size_t WriteTo(char *outBuffer, size_t outBufferSize) {
		TMsgpackBuffer sbuf;
		msgpack_packer packer;
		MsgpackBufferInit(&sbuf);
		msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

		for (const auto &field : Fields) {
			if (!field->Write(&packer)) {
				MsgpackBufferDestroy(&sbuf);
				return 0;
			};
		}

		size_t size;
		if (sbuf.size > outBufferSize) {
			size = outBufferSize;
		} else {
			size = sbuf.size;
		}
		memcpy(outBuffer, sbuf.data, size);

		MsgpackBufferDestroy(&sbuf);
		return size;
	}
};

int main(void) {
	UserDto userDto;

	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	/* msgpack::sbuffer is a simple buffer implementation. */
	msgpack_sbuffer_init(&sbuf);

	/* serialize values into the buffer using msgpack_sbuffer_write callback function. */
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_int(&pk, 1);
	msgpack_pack_true(&pk);
	msgpack_pack_str(&pk, 7);
	msgpack_pack_str_body(&pk, "example", 7);

	print(sbuf.data, sbuf.size);

	msgpack_zone mempool;
	msgpack_object deserialized;
	/* deserialize the buffer into msgpack_object instance. */
	/* deserialized object is valid during the msgpack_zone instance alive. */
	msgpack_zone_init(&mempool, 2048);

	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	/* print the deserialized object. */
	msgpack_object_print(stdout, deserialized);
	puts("");

	msgpack_zone_destroy(&mempool);
	msgpack_sbuffer_destroy(&sbuf);

	return 0;
}
