
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(MsgpackDataValueGroup){void setup(){} void teardown(){}};

TEST(MsgpackDataValueGroup, TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<TMsgpackRawData> testable(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7};
	msgpack_pack_array(&pk, 1);
	msgpack_pack_v4raw(&pk, sizeof(data));
	msgpack_pack_v4raw_body(&pk, data, sizeof(data));

	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable.TryParse(&deserialized));
	MEMCMP_EQUAL(((TMsgpackRawData)testable.Get()).Data, data, ((TMsgpackRawData)testable.Get()).Size);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackDataValueGroup, TryParse_When_Id_Exceed_Fields_Count_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<TMsgpackRawData> testable(&container, 99);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7};
	msgpack_pack_array(&pk, 1);
	msgpack_pack_v4raw(&pk, sizeof(data));
	msgpack_pack_v4raw_body(&pk, data, sizeof(data));

	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_FALSE(testable.TryParse(&deserialized));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackDataValueGroup, TryParse_String_Test) {
	MsgpackFieldsContainer container;
	TMsgpackRawData initValue = {};
	MsgpackValue<TMsgpackRawData> testable(&container, 0, initValue);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable.TryParse(&deserialized));
	MEMCMP_EQUAL(((TMsgpackRawData)testable.Get()).Data, "User1", ((TMsgpackRawData)testable.Get()).Size);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackDataValueGroup, TryParse_Null_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<TMsgpackRawData> testable(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_nil(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable.TryParse(&deserialized));
	CHECK_EQUAL(((TMsgpackRawData)testable.Get()).Data, NULL);
	CHECK_EQUAL(((TMsgpackRawData)testable.Get()).Size, 0);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackDataValueGroup, Write_Test) {
	MsgpackFieldsContainer container;
	uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7};
	TMsgpackRawData initValue = {data, sizeof(data)};
	MsgpackValue<TMsgpackRawData> testable(&container, 0, initValue);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_object deserialized;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 1);
	CHECK_TRUE(testable.Write(&packer));
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	msgpack_object object = deserialized.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_STR);
	MEMCMP_EQUAL(((TMsgpackRawData)testable.Get()).Data, data, ((TMsgpackRawData)testable.Get()).Size);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackDataValueGroup, Write_Null_Test) {
	MsgpackFieldsContainer container;
	TMsgpackRawData initValue = {NULL, 0};
	MsgpackValue<TMsgpackRawData> testable(&container, 0, initValue);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_object deserialized;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 1);
	CHECK_TRUE(testable.Write(&packer));
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	msgpack_object object = deserialized.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NIL);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackDataValueGroup, SetValue_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<TMsgpackRawData> testable(&container, 0);
	CHECK_EQUAL(((TMsgpackRawData)testable.Get()).Data, NULL);
	CHECK_EQUAL(((TMsgpackRawData)testable.Get()).Size, 0);

	testable.Set({(uint8_t *)"0123456789", sizeof("0123456789") - 1});
	STRCMP_EQUAL((char *)((TMsgpackRawData)testable.Get()).Data, "0123456789");
	CHECK_EQUAL(((TMsgpackRawData)testable.Get()).Size, sizeof("0123456789") - 1);
}

TEST(MsgpackDataValueGroup, Equals_Test) {
	MsgpackFieldsContainer container;
	const char *str = "testString";
	MsgpackValue<TMsgpackRawData> testable1(&container, 0, {(uint8_t *)str, strlen(str) + 1});
	MsgpackValue<TMsgpackRawData> testable01(&container, 0, {(uint8_t *)str, strlen(str) + 1});

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	testable01.Set({(uint8_t *)"otherValue", sizeof("otherValue")});
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
}

TEST(MsgpackDataValueGroup, CloneTo_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<TMsgpackRawData> testable1(&container, 0, {(uint8_t *)"0123456789", sizeof("0123456789")});

	MsgpackValue<TMsgpackRawData> clone1(&container, 0);

	testable1.CloneTo((MsgpackValueBase *)&clone1);
	testable1.Set({(uint8_t *)"check the full data buffer is cloned", sizeof("check the full data buffer is cloned")});
	STRCMP_EQUAL((char *)((TMsgpackRawData)clone1.Get()).Data, "0123456789");
}
