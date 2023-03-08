
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(MsgpackStringValueGroup){void setup(){} void teardown(){}};

TEST(MsgpackStringValueGroup, MsgpackStringValue_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable(&container, 0, "testString");

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_zone mempool;
	msgpack_object deserialized;

	msgpack_zone_init(&mempool, 2048);
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	CHECK_TRUE(testable.TryParse(&deserialized));
	STRCMP_EQUAL(testable.Get(), "User1");

	msgpack_zone_destroy(&mempool);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_TryParse_When_Id_Exceed_Fields_Count_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable(&container, 99, "testString");

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_zone mempool;
	msgpack_object deserialized;

	msgpack_zone_init(&mempool, 2048);
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	CHECK_FALSE(testable.TryParse(&deserialized));

	msgpack_zone_destroy(&mempool);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_TryParse_Null_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable(&container, 0, "testString");

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_zone mempool;
	msgpack_object deserialized;

	msgpack_zone_init(&mempool, 2048);
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_nil(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	CHECK_TRUE(testable.TryParse(&deserialized));
	CHECK_EQUAL(testable.Get(), NULL);

	msgpack_zone_destroy(&mempool);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_Write_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable(&container, 0, "1234567");

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_zone mempool;
	msgpack_object deserialized;
	msgpack_zone_init(&mempool, 2048);
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 1);
	CHECK_TRUE(testable.Write(&packer));
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	msgpack_object object = deserialized.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_STR);
	STRNCMP_EQUAL(object.via.str.ptr, "1234567", object.via.str.size);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_Write_Null_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable(&container, 0, NULL);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_zone mempool;
	msgpack_object deserialized;
	msgpack_zone_init(&mempool, 2048);
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 1);
	CHECK_TRUE(testable.Write(&packer));
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	msgpack_object object = deserialized.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NIL);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_SetValue_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable(&container, 0);
	STRCMP_EQUAL(testable.Get(), NULL);

	testable.Set("0123456789");
	STRCMP_EQUAL(testable.Get(), "0123456789");
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_Equals_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable1(&container, 0, "testString");
	MsgpackValue<char *> testable01(&container, 0, "testString");
	MsgpackValue<char *> testable001(&container, 1, "testString");

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	CHECK_TRUE(testable1.Equals(&testable01));
	CHECK_TRUE(testable01.Equals(&testable1));
	testable01.Set("otherValue");
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
	CHECK_FALSE(testable1.Equals(&testable01));
	CHECK_FALSE(testable01.Equals(&testable1));
	CHECK_FALSE(testable001 == testable1);
	CHECK_FALSE(testable1 == testable001);
	CHECK_FALSE(testable001.Equals(&testable1));
	CHECK_FALSE(testable1.Equals(&testable001));

	MsgpackValue<char *> testable2(&container, 0);
	MsgpackValue<char *> testable02(&container, 0, NULL);
	CHECK_TRUE(testable2 == testable02);
	testable2.Set("123");
	CHECK_FALSE(testable2 == testable02);

	testable2.Set(NULL);
	CHECK_TRUE(testable2 == testable02);
	testable02.Set("123");
	CHECK_FALSE(testable2 == testable02);
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_CloneTo_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testable1(&container, 0, "0123456789");

	MsgpackValue<char *> clone1(&container, 0);

	testable1.CloneTo((MsgpackValueBase *)&clone1);
	testable1.Set("check the full data buffer is cloned");
	STRCMP_EQUAL(clone1.Get(), "0123456789");
}

TEST(MsgpackStringValueGroup, MsgpackStringValue_Null_And_Empty_Value_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<char *> testDefault(&container, 0);
	MsgpackValue<char *> testNull(&container, 0, NULL);
	MsgpackValue<char *> testEmpty(&container, 0, "");

	CHECK_EQUAL(testDefault.Get(), NULL);
	CHECK_EQUAL(testNull.Get(), NULL);
	STRCMP_EQUAL(testEmpty.Get(), "");

	testDefault.Set("");
	STRCMP_EQUAL(testDefault.Get(), "");

	testEmpty.Set(NULL);
	CHECK_EQUAL(testEmpty.Get(), NULL);
}
