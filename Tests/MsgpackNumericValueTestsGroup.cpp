
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(MsgpackNumericValueGroup){void setup(){} void teardown(){}};

TEST(MsgpackNumericValueGroup, MsgpackUIntField_SetValue_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<unsigned int> testable1(&container, 0);
	MsgpackValue<uint32_t> testable2(&container, 0);
	MsgpackValue<uint16_t> testable3(&container, 0);
	MsgpackValue<uint8_t> testable4(&container, 0);
	testable1.Set(0xFFFFFFFF);
	testable2.Set(0xFFFFFFFF);
	testable3.Set(0xFFFFFFFF);
	testable4.Set(0xFFFFFFFF);

	CHECK_EQUAL(testable1.Get(), 4294967295);
	CHECK_EQUAL(testable2.Get(), 4294967295);
	CHECK_EQUAL(testable3.Get(), 65535);
	CHECK_EQUAL(testable4.Get(), 255);
}

TEST(MsgpackNumericValueGroup, Uint64_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<uint64_t> testable0(&container, 0);
	MsgpackValue<unsigned int> testable1(&container, 0);
	MsgpackValue<uint32_t> testable2(&container, 0);
	MsgpackValue<uint16_t> testable3(&container, 0);
	MsgpackValue<uint8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_uint64(&pk, 12345678901234567890LL);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 12345678901234567890LL);

	CHECK_FALSE(testable1.TryParse(&deserialized));
	CHECK_FALSE(testable2.TryParse(&deserialized));
	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Uint32_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<uint64_t> testable0(&container, 0);
	MsgpackValue<unsigned int> testable1(&container, 0);
	MsgpackValue<uint32_t> testable2(&container, 0);
	MsgpackValue<uint16_t> testable3(&container, 0);
	MsgpackValue<uint8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_uint32(&pk, 1234567890);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 1234567890);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 1234567890);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), 1234567890);

	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Uint16_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<uint64_t> testable0(&container, 0);
	MsgpackValue<unsigned int> testable1(&container, 0);
	MsgpackValue<uint32_t> testable2(&container, 0);
	MsgpackValue<uint16_t> testable3(&container, 0);
	MsgpackValue<uint8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_uint16(&pk, 12345);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 12345);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 12345);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), 12345);

	CHECK_TRUE(testable3.TryParse(&deserialized));
	CHECK_EQUAL(testable3.Get(), 12345);

	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Uint8_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<uint64_t> testable0(&container, 0);
	MsgpackValue<unsigned int> testable1(&container, 0);
	MsgpackValue<uint32_t> testable2(&container, 0);
	MsgpackValue<uint16_t> testable3(&container, 0);
	MsgpackValue<uint8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_uint8(&pk, 123);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 123);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 123);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), 123);

	CHECK_TRUE(testable3.TryParse(&deserialized));
	CHECK_EQUAL(testable3.Get(), 123);

	CHECK_TRUE(testable4.TryParse(&deserialized));
	CHECK_EQUAL(testable4.Get(), 123);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Int64_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int64_t> testable0(&container, 0);
	MsgpackValue<int> testable1(&container, 0);
	MsgpackValue<int32_t> testable2(&container, 0);
	MsgpackValue<int16_t> testable3(&container, 0);
	MsgpackValue<int8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int64(&pk, 1234567890123456789LL);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 1234567890123456789LL);

	CHECK_FALSE(testable1.TryParse(&deserialized));
	CHECK_FALSE(testable2.TryParse(&deserialized));
	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int64(&pk, -1234567890123456789LL);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), -1234567890123456789LL);

	CHECK_FALSE(testable1.TryParse(&deserialized));
	CHECK_FALSE(testable2.TryParse(&deserialized));
	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Int32_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int64_t> testable0(&container, 0);
	MsgpackValue<int> testable1(&container, 0);
	MsgpackValue<int32_t> testable2(&container, 0);
	MsgpackValue<int16_t> testable3(&container, 0);
	MsgpackValue<int8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int32(&pk, 1234567890);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 1234567890);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 1234567890);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), 1234567890);

	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int32(&pk, -1234567890);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), -1234567890);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), -1234567890);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), -1234567890);

	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Int16_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int64_t> testable0(&container, 0);
	MsgpackValue<int> testable1(&container, 0);
	MsgpackValue<int32_t> testable2(&container, 0);
	MsgpackValue<int16_t> testable3(&container, 0);
	MsgpackValue<int8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int16(&pk, 12345);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 12345);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 12345);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), 12345);

	CHECK_TRUE(testable3.TryParse(&deserialized));
	CHECK_EQUAL(testable3.Get(), 12345);

	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int16(&pk, -12345);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), -12345);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), -12345);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), -12345);

	CHECK_TRUE(testable3.TryParse(&deserialized));
	CHECK_EQUAL(testable3.Get(), -12345);

	CHECK_FALSE(testable4.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Int8_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int64_t> testable0(&container, 0);
	MsgpackValue<int> testable1(&container, 0);
	MsgpackValue<int32_t> testable2(&container, 0);
	MsgpackValue<int16_t> testable3(&container, 0);
	MsgpackValue<int8_t> testable4(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int8(&pk, 123);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 123);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 123);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), 123);

	CHECK_TRUE(testable3.TryParse(&deserialized));
	CHECK_EQUAL(testable3.Get(), 123);

	CHECK_TRUE(testable4.TryParse(&deserialized));
	CHECK_EQUAL(testable4.Get(), 123);
	msgpack_sbuffer_destroy(&sbuf);

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int8(&pk, -123);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), -123);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), -123);
	CHECK_TRUE(testable2.TryParse(&deserialized));
	CHECK_EQUAL(testable2.Get(), -123);

	CHECK_TRUE(testable3.TryParse(&deserialized));
	CHECK_EQUAL(testable3.Get(), -123);

	CHECK_TRUE(testable4.TryParse(&deserialized));
	CHECK_EQUAL(testable4.Get(), -123);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, TryParse_NULL_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<uint64_t> testable0(&container, 0);
	MsgpackValue<unsigned int> testable1(&container, 0);
	MsgpackValue<uint32_t> testable2(&container, 0);
	MsgpackValue<uint16_t> testable3(&container, 0);
	MsgpackValue<uint8_t> testable4(&container, 0);

	MsgpackValue<int64_t> testable5(&container, 0);
	MsgpackValue<int> testable6(&container, 0);
	MsgpackValue<int32_t> testable7(&container, 0);
	MsgpackValue<int16_t> testable8(&container, 0);
	MsgpackValue<int8_t> testable9(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_nil(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_FALSE(testable0.TryParse(&deserialized));
	CHECK_FALSE(testable1.TryParse(&deserialized));
	CHECK_FALSE(testable2.TryParse(&deserialized));
	CHECK_FALSE(testable3.TryParse(&deserialized));
	CHECK_FALSE(testable4.TryParse(&deserialized));
	CHECK_FALSE(testable5.TryParse(&deserialized));
	CHECK_FALSE(testable6.TryParse(&deserialized));
	CHECK_FALSE(testable7.TryParse(&deserialized));
	CHECK_FALSE(testable8.TryParse(&deserialized));
	CHECK_FALSE(testable9.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Write_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<uint64_t> testable0(&container, 0, 12345678901234567890LL);
	MsgpackValue<unsigned int> testable1(&container, 0, 1234567890);
	MsgpackValue<uint32_t> testable2(&container, 0, 1234567891);
	MsgpackValue<uint16_t> testable3(&container, 0, 12345);
	MsgpackValue<uint8_t> testable4(&container, 0, 123);

	MsgpackValue<int64_t> testable5(&container, 0, 1234567890123456789LL);
	MsgpackValue<int> testable6(&container, 0, 1234567890);
	MsgpackValue<int32_t> testable7(&container, 0, 1234567891);
	MsgpackValue<int16_t> testable8(&container, 0, 12345);
	MsgpackValue<int8_t> testable9(&container, 0, 123);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_object deserialized;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 10);
	CHECK_TRUE(testable0.Write(&packer));
	CHECK_TRUE(testable1.Write(&packer));
	CHECK_TRUE(testable2.Write(&packer));
	CHECK_TRUE(testable3.Write(&packer));
	CHECK_TRUE(testable4.Write(&packer));
	CHECK_TRUE(testable5.Write(&packer));
	CHECK_TRUE(testable6.Write(&packer));
	CHECK_TRUE(testable7.Write(&packer));
	CHECK_TRUE(testable8.Write(&packer));
	CHECK_TRUE(testable9.Write(&packer));
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_EQUAL(deserialized.via.array.ptr[0].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[0].via.u64, 12345678901234567890LL);

	CHECK_EQUAL(deserialized.via.array.ptr[1].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[1].via.u64, 1234567890);

	CHECK_EQUAL(deserialized.via.array.ptr[2].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[2].via.u64, 1234567891);

	CHECK_EQUAL(deserialized.via.array.ptr[3].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[3].via.u64, 12345);

	CHECK_EQUAL(deserialized.via.array.ptr[4].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[4].via.u64, 123);

	CHECK_EQUAL(deserialized.via.array.ptr[5].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[5].via.i64, 1234567890123456789LL);

	CHECK_EQUAL(deserialized.via.array.ptr[6].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[6].via.i64, 1234567890);

	CHECK_EQUAL(deserialized.via.array.ptr[7].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[7].via.i64, 1234567891);

	CHECK_EQUAL(deserialized.via.array.ptr[8].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[8].via.i64, 12345);

	CHECK_EQUAL(deserialized.via.array.ptr[9].type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[9].via.i64, 123);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Write_Negative_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int64_t> testable5(&container, 0, -1234567890123456789LL);
	MsgpackValue<int> testable6(&container, 0, -1234567890);
	MsgpackValue<int32_t> testable7(&container, 0, -1234567891);
	MsgpackValue<int16_t> testable8(&container, 0, -12345);
	MsgpackValue<int8_t> testable9(&container, 0, -123);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_object deserialized;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 5);
	CHECK_TRUE(testable5.Write(&packer));
	CHECK_TRUE(testable6.Write(&packer));
	CHECK_TRUE(testable7.Write(&packer));
	CHECK_TRUE(testable8.Write(&packer));
	CHECK_TRUE(testable9.Write(&packer));
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_EQUAL(deserialized.via.array.ptr[0].type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[0].via.i64, -1234567890123456789LL);

	CHECK_EQUAL(deserialized.via.array.ptr[1].type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[1].via.i64, -1234567890);

	CHECK_EQUAL(deserialized.via.array.ptr[2].type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[2].via.i64, -1234567891);

	CHECK_EQUAL(deserialized.via.array.ptr[3].type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[3].via.i64, -12345);

	CHECK_EQUAL(deserialized.via.array.ptr[4].type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(deserialized.via.array.ptr[4].via.i64, -123);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, MsgpackUIntField_Equals_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<unsigned int> testable1(&container, 0, 100);
	MsgpackValue<unsigned int> testable01(&container, 0, 100);

	MsgpackValue<uint32_t> testable2(&container, 0, 101);
	MsgpackValue<uint32_t> testable02(&container, 0, 101);

	MsgpackValue<uint16_t> testable3(&container, 0, 102);
	MsgpackValue<uint16_t> testable03(&container, 0, 102);

	MsgpackValue<uint8_t> testable4(&container, 0, 103);
	MsgpackValue<uint8_t> testable04(&container, 0, 103);

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	CHECK_TRUE(testable1.Equals(&testable01));
	CHECK_TRUE(testable01.Equals(&testable1));
	testable01.Set(testable01.Get() + 1);
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
	CHECK_FALSE(testable1.Equals(&testable01));
	CHECK_FALSE(testable01.Equals(&testable1));

	CHECK_TRUE(testable2 == testable02);
	CHECK_FALSE(testable2 != testable02);
	CHECK_TRUE(testable2.Equals(&testable02));
	CHECK_TRUE(testable02.Equals(&testable2));
	testable02.Set(testable02.Get() + 1);
	CHECK_TRUE(testable2 != testable02);
	CHECK_FALSE(testable2 == testable02);
	CHECK_FALSE(testable2.Equals(&testable02));
	CHECK_FALSE(testable02.Equals(&testable2));

	CHECK_TRUE(testable3 == testable03);
	CHECK_FALSE(testable3 != testable03);
	CHECK_TRUE(testable3.Equals(&testable03));
	CHECK_TRUE(testable03.Equals(&testable3));
	testable03.Set(testable03.Get() + 1);
	CHECK_TRUE(testable3 != testable03);
	CHECK_FALSE(testable3 == testable03);
	CHECK_FALSE(testable3.Equals(&testable03));
	CHECK_FALSE(testable03.Equals(&testable3));

	CHECK_TRUE(testable4 == testable04);
	CHECK_FALSE(testable4 != testable04);
	CHECK_TRUE(testable4.Equals(&testable04));
	CHECK_TRUE(testable04.Equals(&testable4));
	testable04.Set(testable04.Get() + 1);
	CHECK_TRUE(testable4 != testable04);
	CHECK_FALSE(testable4 == testable04);
	CHECK_FALSE(testable4.Equals(&testable04));
	CHECK_FALSE(testable04.Equals(&testable4));
}

TEST(MsgpackNumericValueGroup, MsgpackUIntField_CloneTo_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<unsigned int> testable1(&container, 0, 100);
	MsgpackValue<uint32_t> testable2(&container, 0, 101);
	MsgpackValue<uint16_t> testable3(&container, 0, 102);
	MsgpackValue<uint8_t> testable4(&container, 0, 103);

	MsgpackValue<unsigned int> clone1(&container, 0);
	MsgpackValue<uint32_t> clone2(&container, 0);
	MsgpackValue<uint16_t> clone3(&container, 0);
	MsgpackValue<uint8_t> clone4(&container, 0);

	testable1.CloneTo((MsgpackValueBase *)&clone1);
	testable2.CloneTo((MsgpackValueBase *)&clone2);
	testable3.CloneTo((MsgpackValueBase *)&clone3);
	testable4.CloneTo((MsgpackValueBase *)&clone4);

	CHECK_EQUAL(clone1.Get(), 100);
	CHECK_EQUAL(clone2.Get(), 101);
	CHECK_EQUAL(clone3.Get(), 102);
	CHECK_EQUAL(clone4.Get(), 103);
}

TEST(MsgpackNumericValueGroup, MsgpackIntField_SetValue_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int> testable1(&container, 0);
	MsgpackValue<int32_t> testable2(&container, 0);
	MsgpackValue<int16_t> testable3(&container, 0);
	MsgpackValue<int8_t> testable4(&container, 0);
	testable1.Set(0xFFFFFFFF);
	testable2.Set(0xFFFFFFFF);
	testable3.Set(0xFFFFFFFF);
	testable4.Set(0xFFFFFFFF);

	CHECK_EQUAL(testable1.Get(), -1);
	CHECK_EQUAL(testable2.Get(), -1);
	CHECK_EQUAL(testable3.Get(), -1);
	CHECK_EQUAL(testable4.Get(), -1);
}

TEST(MsgpackNumericValueGroup, MsgpackIntField_Equals_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int> testable1(&container, 0, 100);
	MsgpackValue<int> testable01(&container, 0, 100);

	MsgpackValue<int32_t> testable2(&container, 0, 101);
	MsgpackValue<int32_t> testable02(&container, 0, 101);

	MsgpackValue<int16_t> testable3(&container, 0, 102);
	MsgpackValue<int16_t> testable03(&container, 0, 102);

	MsgpackValue<int8_t> testable4(&container, 0, 103);
	MsgpackValue<int8_t> testable04(&container, 0, 103);

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	CHECK_TRUE(testable1.Equals(&testable01));
	CHECK_TRUE(testable01.Equals(&testable1));
	testable01.Set(testable01.Get() + 1);
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
	CHECK_FALSE(testable1.Equals(&testable01));
	CHECK_FALSE(testable01.Equals(&testable1));

	CHECK_TRUE(testable2 == testable02);
	CHECK_FALSE(testable2 != testable02);
	CHECK_TRUE(testable2.Equals(&testable02));
	CHECK_TRUE(testable02.Equals(&testable2));
	testable02.Set(testable02.Get() + 1);
	CHECK_TRUE(testable2 != testable02);
	CHECK_FALSE(testable2 == testable02);
	CHECK_FALSE(testable2.Equals(&testable02));
	CHECK_FALSE(testable02.Equals(&testable2));

	CHECK_TRUE(testable3 == testable03);
	CHECK_FALSE(testable3 != testable03);
	CHECK_TRUE(testable3.Equals(&testable03));
	CHECK_TRUE(testable03.Equals(&testable3));
	testable03.Set(testable03.Get() + 1);
	CHECK_TRUE(testable3 != testable03);
	CHECK_FALSE(testable3 == testable03);
	CHECK_FALSE(testable3.Equals(&testable03));
	CHECK_FALSE(testable03.Equals(&testable3));

	CHECK_TRUE(testable4 == testable04);
	CHECK_FALSE(testable4 != testable04);
	CHECK_TRUE(testable4.Equals(&testable04));
	CHECK_TRUE(testable04.Equals(&testable4));
	testable04.Set(testable04.Get() + 1);
	CHECK_TRUE(testable4 != testable04);
	CHECK_FALSE(testable4 == testable04);
	CHECK_FALSE(testable4.Equals(&testable04));
	CHECK_FALSE(testable04.Equals(&testable4));
}

TEST(MsgpackNumericValueGroup, MsgpackIntField_CloneTo_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<int> testable1(&container, 0, 100);
	MsgpackValue<int32_t> testable2(&container, 0, 101);
	MsgpackValue<int16_t> testable3(&container, 0, 102);
	MsgpackValue<int8_t> testable4(&container, 0, 103);

	MsgpackValue<int> clone1(&container, 0);
	MsgpackValue<int32_t> clone2(&container, 0);
	MsgpackValue<int16_t> clone3(&container, 0);
	MsgpackValue<int8_t> clone4(&container, 0);

	testable1.CloneTo((MsgpackValueBase *)&clone1);
	testable2.CloneTo((MsgpackValueBase *)&clone2);
	testable3.CloneTo((MsgpackValueBase *)&clone3);
	testable4.CloneTo((MsgpackValueBase *)&clone4);

	CHECK_EQUAL(clone1.Get(), 100);
	CHECK_EQUAL(clone2.Get(), 101);
	CHECK_EQUAL(clone3.Get(), 102);
	CHECK_EQUAL(clone4.Get(), 103);
}

/*

*/

TEST(MsgpackNumericValueGroup, MsgpackBoolField_SetValue_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<bool> testable1(&container, 0);
	testable1.Set(0xFFFFFFFF);
	CHECK_EQUAL(testable1.Get(), true);
	testable1.Set(0);
	CHECK_EQUAL(testable1.Get(), false);
	testable1.Set(1);
	CHECK_EQUAL(testable1.Get(), true);
	testable1.Set(false);
	CHECK_EQUAL(testable1.Get(), false);
	testable1.Set(true);
	CHECK_EQUAL(testable1.Get(), true);
}

TEST(MsgpackNumericValueGroup, Bool_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<bool> testable0(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_true(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_TRUE(testable0.Get());
	msgpack_sbuffer_destroy(&sbuf);

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_false(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_FALSE(testable0.Get());
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Bool_TryParse_NULL_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<bool> testable0(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_nil(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_FALSE(testable0.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Bool_Write_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<bool> testable0(&container, 0, true);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_object deserialized;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 2);
	CHECK_TRUE(testable0.Write(&packer));

	testable0.Set(false);
	CHECK_TRUE(testable0.Write(&packer));

	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_EQUAL(deserialized.via.array.ptr[0].type, MSGPACK_OBJECT_BOOLEAN);
	CHECK_TRUE(deserialized.via.array.ptr[0].via.boolean);

	CHECK_EQUAL(deserialized.via.array.ptr[1].type, MSGPACK_OBJECT_BOOLEAN);
	CHECK_FALSE(deserialized.via.array.ptr[1].via.boolean);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, MsgpackBoolField_CloneTo_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<bool> testable1(&container, 0, true);
	MsgpackValue<bool> clone1(&container, 0);

	testable1.CloneTo((MsgpackValueBase *)&clone1);

	CHECK_EQUAL(clone1.Get(), true);
}
/*

*/
TEST(MsgpackNumericValueGroup, MsgpackFloatField_SetValue_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<float> testable1(&container, 0);
	MsgpackValue<double> testable2(&container, 0);
	testable1.Set(429496729.5);
	testable2.Set(42949672.95);

	CHECK_EQUAL(testable1.Get(), 429496729.5F);
	CHECK_EQUAL(testable2.Get(), 42949672.95);
}

TEST(MsgpackNumericValueGroup, Float_TryParse_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<float> testable0(&container, 0);
	MsgpackValue<double> testable1(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_float(&pk, 150.25F);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable0.TryParse(&deserialized));
	CHECK_EQUAL(testable0.Get(), 150.25F);
	msgpack_sbuffer_destroy(&sbuf);

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_double(&pk, 150.25);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_TRUE(testable1.TryParse(&deserialized));
	CHECK_EQUAL(testable1.Get(), 150.25);
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Float_TryParse_NULL_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<float> testable0(&container, 0);
	MsgpackValue<double> testable1(&container, 0);

	msgpack_sbuffer sbuf;
	msgpack_packer pk;
	msgpack_object deserialized;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_nil(&pk);
	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_FALSE(testable0.TryParse(&deserialized));
	CHECK_FALSE(testable1.TryParse(&deserialized));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, Float_Write_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<float> testable0(&container, 0, 19.25);
	MsgpackValue<double> testable1(&container, 0, 20.5);

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_object deserialized;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&packer, 2);
	CHECK_TRUE(testable0.Write(&packer));

	testable0.Set(false);
	CHECK_TRUE(testable1.Write(&packer));

	msgpack_unpack(sbuf.data, sbuf.size, NULL, NULL, &deserialized);

	CHECK_EQUAL(deserialized.via.array.ptr[0].type, MSGPACK_OBJECT_FLOAT32);
	CHECK_EQUAL(deserialized.via.array.ptr[0].via.f64, 19.25);

	CHECK_EQUAL(deserialized.via.array.ptr[1].type, MSGPACK_OBJECT_FLOAT64);
	CHECK_EQUAL(deserialized.via.array.ptr[1].via.f64, 20.5);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackNumericValueGroup, MsgpackFloatField_Equals_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<float> testable1(&container, 0, 100.5);
	MsgpackValue<float> testable01(&container, 0, 100.5);

	MsgpackValue<double> testable2(&container, 0, 101.75);
	MsgpackValue<double> testable02(&container, 0, 101.75);

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	CHECK_TRUE(testable1.Equals(&testable01));
	CHECK_TRUE(testable01.Equals(&testable1));
	testable01.Set(testable01.Get() + 1);
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
	CHECK_FALSE(testable1.Equals(&testable01));
	CHECK_FALSE(testable01.Equals(&testable1));

	CHECK_TRUE(testable2 == testable02);
	CHECK_FALSE(testable2 != testable02);
	CHECK_TRUE(testable2.Equals(&testable02));
	CHECK_TRUE(testable02.Equals(&testable2));
	testable02.Set(testable02.Get() + 1);
	CHECK_TRUE(testable2 != testable02);
	CHECK_FALSE(testable2 == testable02);
	CHECK_FALSE(testable2.Equals(&testable02));
	CHECK_FALSE(testable02.Equals(&testable2));
}

TEST(MsgpackNumericValueGroup, MsgpackFloatField_CloneTo_Test) {
	MsgpackFieldsContainer container;
	MsgpackValue<float> testable1(&container, 0, 100.5);
	MsgpackValue<double> testable2(&container, 0, 101.15);

	MsgpackValue<float> clone1(&container, 0);
	MsgpackValue<double> clone2(&container, 0);

	testable1.CloneTo((MsgpackValueBase *)&clone1);
	testable2.CloneTo((MsgpackValueBase *)&clone2);

	CHECK_EQUAL(clone1.Get(), 100.5);
	CHECK_EQUAL(clone2.Get(), 101.15);
}
