
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

size_t maxCount = 10;

TEST_GROUP(MsgpackArrayTestsGroup){void setup(){maxCount = 10;
}
void teardown() {}
}
;

class UserDto : public MsgpackObject {
  public:
	MsgpackValue<char *> Name;
	MsgpackValue<uint32_t> Role;

	UserDto(const char *name = {}, const uint32_t role = {})
		: Name(this, 0, name), //
		  Role(this, 1, role){};

	bool Validate() override { return Role.Get() < 1000; }
};

class UsersList : public MsgpackObjectsArray {
  public:
	bool Validate(MsgpackObject *item) override { return Size() < maxCount && item != NULL && item->Validate(); }
	MsgpackObject *CreateItem() { return new UserDto(); }
};

class StringsList : public MsgpackArray<char *> {
  public:
	bool Validate(const char *item) override { return Size() < maxCount && (item == NULL || strcmp(item, "notValid") != 0); }
};

class BoolList : public MsgpackArray<TBoolArray> {
  public:
	bool Validate(const TBoolArray item) override { return Size() < maxCount; }
};

class Int64List : public MsgpackArray<int64_t> {
  public:
	bool Validate(const int64_t item) override { return Size() < maxCount && item < 5188146770730811392LL + 1LL; }
};
class Uint64List : public MsgpackArray<uint64_t> {
  public:
	bool Validate(const uint64_t item) override { return Size() < maxCount && item < 10188146770730811392ULL + 1ULL; }
};

class Int32List : public MsgpackArray<int32_t> {
  public:
	bool Validate(const int32_t item) override { return Size() < maxCount; }
};
class Uint32List : public MsgpackArray<uint32_t> {
  public:
	bool Validate(const uint32_t item) override { return Size() < maxCount; }
};

class Int16List : public MsgpackArray<int16_t> {
  public:
	bool Validate(const int16_t item) override { return Size() < maxCount; }
};
class Uint16List : public MsgpackArray<uint16_t> {
  public:
	bool Validate(const uint16_t item) override { return Size() < maxCount; }
};

class Int8List : public MsgpackArray<int8_t> {
  public:
	bool Validate(const int8_t item) override { return Size() < maxCount; }
};
class Uint8List : public MsgpackArray<uint8_t> {
  public:
	bool Validate(const uint8_t item) override { return Size() < maxCount; }
};

class DoubleList : public MsgpackArray<double> {
  public:
	bool Validate(const double item) override { return Size() < maxCount; }
};
class FloatList : public MsgpackArray<float> {
  public:
	bool Validate(const float item) override { return Size() < maxCount; }
};

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Parse_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_int(&pk, 100);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User2", 5);
	msgpack_pack_int(&pk, 0);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User3", 5);
	msgpack_pack_int(&pk, 255);

	UsersList list;
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);

	CHECK_EQUAL(list.Size(), 3);

	STRCMP_EQUAL(list.Item<UserDto *>(0)->Name.Get(), "User1");
	CHECK_EQUAL(list.Item<UserDto *>(0)->Role.Get(), 100);

	STRCMP_EQUAL(list.Item<UserDto *>(1)->Name.Get(), "User2");
	CHECK_EQUAL(list.Item<UserDto *>(1)->Role.Get(), 0);

	STRCMP_EQUAL(list.Item<UserDto *>(2)->Name.Get(), "User3");
	CHECK_EQUAL(list.Item<UserDto *>(2)->Role.Get(), 255);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_WriteTo_Parse_Test) {
	char buffer[2048];
	UsersList list0;
	list0.Add(new UserDto("user 1", 0));
	list0.Add(new UserDto("user 2", 10));
	list0.Add(new UserDto("user 3", 100));

	CHECK_EQUAL(list0.Write(buffer, sizeof(buffer)), 28);

	UsersList list1;
	CHECK_TRUE(list1.TryParse(buffer, 28));

	CHECK_EQUAL(list1.Size(), 3);

	STRCMP_EQUAL(list1.Item<UserDto *>(0)->Name.Get(), "user 1");
	CHECK_EQUAL(list1.Item<UserDto *>(0)->Role.Get(), 0);

	STRCMP_EQUAL(list1.Item<UserDto *>(1)->Name.Get(), "user 2");
	CHECK_EQUAL(list1.Item<UserDto *>(1)->Role.Get(), 10);

	STRCMP_EQUAL(list1.Item<UserDto *>(2)->Name.Get(), "user 3");
	CHECK_EQUAL(list1.Item<UserDto *>(2)->Role.Get(), 100);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Parse_Error_Test) {
	msgpack_sbuffer sbuf = {};
	msgpack_packer pk;
	UsersList list;

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_FALSE(list.TryParse(NULL, 1));

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Parse_Error_Breaked_Data_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_int(&pk, 100);

	UsersList list;
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size - 1));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Parse_With_Begin_End_Stages_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 2);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_int(&pk, 100);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User2", 5);
	msgpack_pack_int(&pk, 0);

	UsersList list;
	auto unpacked = list.BeginTryParse(sbuf.data, sbuf.size);

	CHECK(unpacked != NULL);
	msgpack_sbuffer_destroy(&sbuf);

	CHECK_EQUAL(list.Size(), 2);

	STRCMP_EQUAL(list.Item<UserDto *>(0)->Name.Get(), "User1");
	CHECK_EQUAL(list.Item<UserDto *>(0)->Role.Get(), 100);
	list.EndTryParse(unpacked);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_WriteTo_Test) {
	char buffer[2048];
	UsersList list;
	list.Add(new UserDto("user 1", 0));
	list.Add(new UserDto("user 2", 10));
	list.Add(new UserDto("user 3", 100));
	UserDto user("user 4", 1000);
	list.Add(&user);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 28);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 28, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 3);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_WriteTo_With_Limited_Buffer_Test) {
	char buffer[30];
	UsersList list;
	list.Add(new UserDto("user 1", 0));
	list.Add(new UserDto("user 2", 10));
	list.Add(new UserDto("user 3", 100));
	list.Add(new UserDto("user 4", 999));

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 0);
}

static void *TestParent = NULL;
static char *DirectWriteTestBuffer = NULL;
static size_t DirectWriteTestBufferLenght = 0;
static void OnReady(void *parent, const char *json, size_t size) {
	TestParent = parent;
	DirectWriteTestBuffer = new char[size];
	DirectWriteTestBufferLenght = size;
	memcpy(DirectWriteTestBuffer, json, size);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Direct_Write_From_Msgpack_Memory_Test) {
	UsersList list;
	list.Add(new UserDto("user 1", 0));
	list.Add(new UserDto("user 2", 10));
	list.Add(new UserDto("user 3", 100));
	list.Add(new UserDto("user 4", 999));

	list.DirectWriteTo((void *)987654321, OnReady);
	CHECK_EQUAL(TestParent, (void *)987654321);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, DirectWriteTestBuffer, DirectWriteTestBufferLenght, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 4);
	delete[] DirectWriteTestBuffer;
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Equals_Test) {
	UsersList list1;
	list1.Add(new UserDto("user 1", 0));
	list1.Add(new UserDto("user 2", 10));
	list1.Add(new UserDto("user 3", 100));
	list1.Add(new UserDto("user 4", 999));

	UsersList list2;
	list2.Add(new UserDto("user 1", 0));
	list2.Add(new UserDto("user 2", 10));
	list2.Add(new UserDto("user 3", 100));
	list2.Add(new UserDto("user 4", 999));

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Item<UserDto *>(2)->Name.Set("User3");
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Clone_Test) {
	auto list1 = new UsersList();
	list1->Add(new UserDto("user 1", 0));
	list1->Add(new UserDto("user 2", 10));
	list1->Add(new UserDto("user 3", 100));
	list1->Add(new UserDto("user 4", 999));

	UsersList list2;
	list2.Add(new UserDto(" 1", 0));
	list2.Add(new UserDto(" 2", 10));

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 4);

	STRCMP_EQUAL(list2.Item<UserDto *>(2)->Name.Get(), "user 3");
	CHECK_EQUAL(list2.Item<UserDto *>(2)->Role.Get(), 100);
	STRCMP_EQUAL(list2.Item<UserDto *>(3)->Name.Get(), "user 4");
	CHECK_EQUAL(list2.Item<UserDto *>(3)->Role.Get(), 999);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Find_Test) {
	UsersList list1;
	list1.Add(new UserDto("user 1", 0));
	list1.Add(new UserDto("user 2", 10));
	list1.Add(new UserDto("user 3", 100));
	list1.Add(new UserDto("user 4", 999));
	UserDto user1("user 3", 100);
	auto iter = list1.Find(&user1);
	CHECK(iter != list1.End());
	STRCMP_EQUAL(((UserDto *)*iter)->Name.Get(), "user 3");
	UserDto user2("user 3", 0);
	CHECK_TRUE(list1.Find(&user2) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Remove_Test) {
	UsersList list1;
	list1.Add(new UserDto("user 1", 0));
	list1.Add(new UserDto("user 2", 10));
	list1.Add(new UserDto("user 3", 100));
	list1.Add(new UserDto("user 4", 999));

	auto item1 = new UserDto("user 3", 100);
	CHECK_TRUE(list1.Remove(item1));
	delete item1;

	auto item2 = new UserDto("user 2", 10);
	CHECK_TRUE(list1.Remove(item2));
	delete item2;

	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Add_Test) {
	UsersList list1;
	auto item1 = new UserDto("user 1", 0);
	CHECK_TRUE(list1.Add(item1));
	auto item2 = new UserDto("user 2", 10);
	CHECK_TRUE(list1.Add(item2));

	CHECK_EQUAL(list1.Size(), 2);
	STRCMP_EQUAL(list1.Item<UserDto *>(0)->Name.Get(), "user 1");
	CHECK_EQUAL(list1.Item<UserDto *>(0)->Role.Get(), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Incorrect_Add_Test) {
	UsersList list1;
	auto item1 = new UserDto("user 1", 0);
	CHECK_TRUE(list1.Add(item1));
	auto item2 = new UserDto("user 2", 1010);
	CHECK_FALSE(list1.Add(item2));
	delete item2;

	CHECK_EQUAL(list1.Size(), 1);
	STRCMP_EQUAL(list1.Item<UserDto *>(0)->Name.Get(), "user 1");
	CHECK_EQUAL(list1.Item<UserDto *>(0)->Role.Get(), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Update_Test) {
	UsersList list1;
	auto item1 = new UserDto("user 1", 0);
	list1.Add(item1);
	auto item2 = new UserDto("user 2", 10);
	list1.Add(item2);

	auto item3 = new UserDto("user 3", 100);
	CHECK_TRUE(list1.Update(0, item3));
	CHECK_EQUAL(list1.Size(), 2);

	STRCMP_EQUAL(list1.Item<UserDto *>(0)->Name.Get(), "user 3");
	CHECK_EQUAL(list1.Item<UserDto *>(0)->Role.Get(), 100);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Incorrect_Update_Test) {
	UsersList list1;
	list1.Add(new UserDto("user 1", 0));
	list1.Add(new UserDto("user 2", 10));

	auto item3 = new UserDto("user 2", 10);
	CHECK_FALSE(list1.Update(100, item3));
	delete item3;

	auto item4 = new UserDto("user 3", 1000);
	CHECK_FALSE(list1.Update(0, item4));
	delete item4;

	CHECK_FALSE(list1.Update(0, NULL));
	CHECK_EQUAL(list1.Size(), 2);

	STRCMP_EQUAL(list1.Item<UserDto *>(0)->Name.Get(), "user 1");
	CHECK_EQUAL(list1.Item<UserDto *>(0)->Role.Get(), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_Clear_Test) {
	UsersList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_int(&pk, 100);

	CHECK_TRUE(list.Add(new UserDto("user 1", 0)));
	CHECK_TRUE(list.Add(new UserDto("user 2", 10)));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 1);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_MoveTo_Test) {
	auto list1 = new UsersList();
	list1->Add(new UserDto("user 1", 0));
	list1->Add(new UserDto("user 2", 10));
	list1->Add(new UserDto("user 3", 100));
	list1->Add(new UserDto("user 4", 999));

	UsersList list2;
	list2.Add(new UserDto(" 1", 0));
	list2.Add(new UserDto(" 2", 10));

	auto item0 = list1->Item<UserDto *>(0);
	auto item1 = list1->Item<UserDto *>(1);
	auto iter = list1->MoveTo(&list2, item0);
	STRCMP_EQUAL(((UserDto *)*iter)->Name.Get(), "user 2");

	iter = list1->MoveTo(&list2, item1);
	STRCMP_EQUAL(((UserDto *)*iter)->Name.Get(), "user 3");
	CHECK_EQUAL(list1->Size(), 2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 4);

	STRCMP_EQUAL(list2.Item<UserDto *>(0)->Name.Get(), " 1");
	CHECK_EQUAL(list2.Item<UserDto *>(0)->Role.Get(), 0);
	STRCMP_EQUAL(list2.Item<UserDto *>(1)->Name.Get(), " 2");
	CHECK_EQUAL(list2.Item<UserDto *>(1)->Role.Get(), 10);
	STRCMP_EQUAL(list2.Item<UserDto *>(2)->Name.Get(), "user 1");
	CHECK_EQUAL(list2.Item<UserDto *>(2)->Role.Get(), 0);
	STRCMP_EQUAL(list2.Item<UserDto *>(3)->Name.Get(), "user 2");
	CHECK_EQUAL(list2.Item<UserDto *>(3)->Role.Get(), 10);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_MoveTo_For_Non_Native_Test) {
	auto list1 = new UsersList();
	list1->Add(new UserDto("user 1", 0));
	list1->Add(new UserDto("user 2", 10));

	UsersList list2;
	list2.Add(new UserDto(" 1", 0));

	auto iter = list1->MoveTo(&list2, NULL);
	CHECK(iter == list1->End());

	UserDto other("user 1", 0);
	iter = list1->MoveTo(&list2, &other);
	CHECK(iter == list1->End());

	iter = list1->MoveTo(&list2, *list2.Begin());
	CHECK(iter == list1->End());
	delete list1;
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_MoveTo_With_Validation_Test) {
	maxCount = 3;
	auto list1 = new UsersList();
	list1->Add(new UserDto("user 1", 0));
	list1->Add(new UserDto("user 2", 10));
	list1->Add(new UserDto("user 3", 100));

	UsersList list2;
	list2.Add(new UserDto(" 1", 0));
	list2.Add(new UserDto(" 2", 10));

	auto item0 = list1->Item<UserDto *>(0);
	auto item1 = list1->Item<UserDto *>(1);
	auto iter = list1->MoveTo(&list2, item0);
	STRCMP_EQUAL(((UserDto *)*iter)->Name.Get(), "user 2");

	iter = list1->MoveTo(&list2, item1);
	STRCMP_EQUAL(((UserDto *)*iter)->Name.Get(), "user 3");
	CHECK_EQUAL(list1->Size(), 2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_MoveAllTo_Test) {
	auto list1 = new UsersList();
	list1->Add(new UserDto("user 1", 0));
	list1->Add(new UserDto("user 2", 10));
	list1->Add(new UserDto("user 3", 100));
	list1->Add(new UserDto("user 4", 999));

	UsersList list2;
	list2.Add(new UserDto(" 1", 0));
	list2.Add(new UserDto(" 2", 10));

	list1->MoveAllTo(&list2);
	CHECK_EQUAL(list1->Size(), 0);
	delete list1;
	CHECK_EQUAL(list2.Size(), 6);

	STRCMP_EQUAL(list2.Item<UserDto *>(0)->Name.Get(), " 1");
	CHECK_EQUAL(list2.Item<UserDto *>(0)->Role.Get(), 0);
	STRCMP_EQUAL(list2.Item<UserDto *>(1)->Name.Get(), " 2");
	CHECK_EQUAL(list2.Item<UserDto *>(1)->Role.Get(), 10);
	STRCMP_EQUAL(list2.Item<UserDto *>(2)->Name.Get(), "user 1");
	CHECK_EQUAL(list2.Item<UserDto *>(2)->Role.Get(), 0);
	STRCMP_EQUAL(list2.Item<UserDto *>(3)->Name.Get(), "user 2");
	CHECK_EQUAL(list2.Item<UserDto *>(3)->Role.Get(), 10);
	STRCMP_EQUAL(list2.Item<UserDto *>(4)->Name.Get(), "user 3");
	CHECK_EQUAL(list2.Item<UserDto *>(4)->Role.Get(), 100);
	STRCMP_EQUAL(list2.Item<UserDto *>(5)->Name.Get(), "user 4");
	CHECK_EQUAL(list2.Item<UserDto *>(5)->Role.Get(), 999);
}

TEST(MsgpackArrayTestsGroup, MsgpackObjectsArray_MoveAllTo_With_Validation_Test) {
	maxCount = 3;
	auto list1 = new UsersList();
	list1->Add(new UserDto("user 1", 0));
	list1->Add(new UserDto("user 2", 10));

	UsersList list2;
	list2.Add(new UserDto(" 1", 0));
	list2.Add(new UserDto(" 2", 10));

	list1->MoveAllTo(&list2);
	CHECK_EQUAL(list1->Size(), 1);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Parse_Test) {
	StringsList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User2", 5);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User3", 5);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	STRCMP_EQUAL(list.Item(0), "User1");
	STRCMP_EQUAL(list.Item(2), "User3");

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Parse_Not_String_Test) {
	StringsList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_true(&pk);
	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Parse_With_Null_Values_Test) {
	StringsList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_nil(&pk);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User3", 5);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	STRCMP_EQUAL(list.Item(0), "User1");
	CHECK_EQUAL(list.Item(1), NULL);
	STRCMP_EQUAL(list.Item(2), "User3");

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_WriteTo_Test) {
	char buffer[2048];
	StringsList list;
	CHECK_TRUE(list.Add("user 1"));
	CHECK_TRUE(list.Add("user 2"));
	CHECK_TRUE(list.Add("user 3"));
	CHECK_TRUE(list.Add("user 4"));
	CHECK_FALSE(list.Add("notValid"));

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 29);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 29, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 4);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_STR);
	STRNCMP_EQUAL("user 1", object.via.str.ptr, object.via.str.size);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_STR);
	STRNCMP_EQUAL("user 4", object.via.str.ptr, object.via.str.size);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_WriteTo_With_Null_Values_Test) {
	char buffer[2048];
	StringsList list;
	CHECK_TRUE(list.Add("user 1"));
	CHECK_TRUE(list.Add(NULL));
	CHECK_TRUE(list.Add("user 3"));

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 16);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 16, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 3);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_STR);
	STRNCMP_EQUAL("user 1", object.via.str.ptr, object.via.str.size);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NIL);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Equals_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");
	list1.Add("user 3");
	list1.Add("user 4");
	list1.Add(NULL);

	StringsList list2;
	list2.Add("user 1");
	list2.Add("user 2");
	list2.Add("user 3");
	list2.Add("user 4");
	list2.Add(NULL);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, "User3");
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	list2.Update(2, "User3");
	CHECK_TRUE(list1 == list2);
	CHECK_TRUE(list2.Remove("user 2"));
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	CHECK_TRUE(list1.Remove("user 2"));
	list1.Update(0, NULL);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	list2.Update(0, NULL);
	list1.Update(1, NULL);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	list2.Update(1, NULL);
	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Clone_Test) {
	auto list1 = new StringsList();
	list1->Add("user 1");
	list1->Add("user 2");
	list1->Add("user 3");
	list1->Add("user 4");
	list1->Add(NULL);

	StringsList list2;
	list2.Add("1");
	list2.Add("2");

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 5);
	STRCMP_EQUAL(list2.Item(2), "user 3");
	STRCMP_EQUAL(list2.Item(3), "user 4");
	STRCMP_EQUAL(list2.Item(4), NULL);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Find_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");
	list1.Add("user 3");
	list1.Add("user 4");
	list1.Add(NULL);

	CHECK_TRUE(list1.Find("user 2") != list1.End());
	STRCMP_EQUAL(*(list1.Find("user 2")), "user 2");
	CHECK_TRUE(list1.Find("error") == list1.End());
	CHECK_EQUAL(*(list1.Find(NULL)), NULL);
}

static char *CreateTestString(const char *str) {
	auto item = new char[strlen(str) + 1];
	strcpy(item, str);
	return item;
}
TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Remove_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");
	list1.Add("user 3");
	list1.Add("user 4");
	list1.Add(NULL);

	CHECK_TRUE(list1.Remove("user 3"));
	CHECK_TRUE(list1.Remove("user 2"));
	CHECK_TRUE(list1.Remove(NULL));
	CHECK_EQUAL(list1.Size(), 2);
	CHECK_FALSE(list1.Remove("user Not exists"));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Add_Test) {
	StringsList list1;
	CHECK_TRUE(list1.Add("user 1"));

	auto item2 = CreateTestString("user 2");
	CHECK_TRUE(list1.Add(item2));
	delete[] item2;
	CHECK_TRUE(list1.Add(NULL));

	CHECK_EQUAL(list1.Size(), 3);
	STRCMP_EQUAL(list1.Item(0), "user 1");
	STRCMP_EQUAL(list1.Item(1), "user 2");
	CHECK_EQUAL(list1.Item(2), NULL);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Incorrect_Add_Test) {
	StringsList list1;
	auto item1 = CreateTestString("user 1");
	CHECK_TRUE(list1.Add(item1));
	delete[] item1;

	auto item2 = CreateTestString("notValid");
	CHECK_FALSE(list1.Add(item2));
	delete[] item2;

	CHECK_EQUAL(list1.Size(), 1);
	STRCMP_EQUAL(list1.Item(0), "user 1");
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Update_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");

	auto item3 = CreateTestString("user 3");
	CHECK_TRUE(list1.Update(0, item3));
	delete[] item3;

	CHECK_TRUE(list1.Update(1, NULL));
	CHECK_EQUAL(list1.Size(), 2);

	STRCMP_EQUAL(list1.Item(0), "user 3");
	STRCMP_EQUAL(list1.Item(1), NULL);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Incorrect_Update_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");

	auto item3 = CreateTestString("user 2");
	CHECK_FALSE(list1.Update(100, item3));
	delete[] item3;

	auto item4 = CreateTestString("notValid");
	CHECK_FALSE(list1.Update(0, item4));
	delete[] item4;

	CHECK_EQUAL(list1.Size(), 2);

	STRCMP_EQUAL(list1.Item(0), "user 1");
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_Clear_Test) {
	StringsList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User2", 5);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User3", 5);

	CHECK_TRUE(list.Add("user 1"));
	CHECK_TRUE(list.Add("user 2"));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackStringArray_TryParse_Are_Appended_Test) {
	StringsList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);

	CHECK_TRUE(list.Add("user 1"));
	CHECK_TRUE(list.Add("user 2"));
	CHECK_EQUAL(list.Size(), 2);
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);
	STRCMP_EQUAL(list.Item(2), "User1");

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Parse_Test) {
	BoolList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_true(&pk);
	msgpack_pack_false(&pk);
	msgpack_pack_true(&pk);
	msgpack_pack_false(&pk);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);

	CHECK_EQUAL(list.Item(0), (TBoolArray) true);
	CHECK_EQUAL(list.Item(3), false);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Parse_Not_Boolean_Test) {
	BoolList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_int(&pk, 0);
	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_WriteTo_Test) {
	char buffer[2048];
	BoolList list;
	list.Add(true);
	list.Add(false);
	list.Add(false);
	list.Add(true);
	list.Add(false);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 6);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 6, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 5);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_BOOLEAN);
	CHECK_TRUE(object.via.boolean);

	object = unpacked.data.via.array.ptr[4];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_BOOLEAN);
	CHECK_FALSE(object.via.boolean);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Equals_Test) {
	BoolList list1;
	list1.Add(true);
	list1.Add(false);
	list1.Add(false);
	list1.Add(true);

	BoolList list2;
	list2.Add(true);
	list2.Add(false);
	list2.Add(false);
	list2.Add(true);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, true);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Clone_Test) {
	auto list1 = new BoolList();
	list1->Add(true);
	list1->Add(false);
	list1->Add(false);
	list1->Add(true);

	BoolList list2;
	list2.Add(false);
	list2.Add(false);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 4);
	CHECK_EQUAL(list2.Item(2), false);
	CHECK_EQUAL(list2.Item(3), (TBoolArray) true);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Find_Test) {
	BoolList list1;
	list1.Add(true);

	CHECK(list1.Find(true) != list1.End());
	CHECK_EQUAL(*(list1.Find(true)), (TBoolArray) true);
	CHECK_TRUE(list1.Find(false) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Remove_Test) {
	BoolList list1;
	list1.Add(true);
	list1.Add(true);
	list1.Add(false);
	list1.Add(false);

	CHECK_TRUE(list1.Remove(true));
	CHECK_TRUE(list1.Remove(false));
	CHECK_EQUAL(list1.Size(), 2);
	CHECK_TRUE(list1.Remove(true));
	CHECK_EQUAL(list1.Size(), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Add_Test) {
	BoolList list1;
	CHECK_TRUE(list1.Add(true));
	CHECK_TRUE(list1.Add(false));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), (TBoolArray) true);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Update_Test) {
	BoolList list1;
	list1.Add(true);
	list1.Add(true);

	CHECK_TRUE(list1.Update(0, false));
	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), false);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Incorrect_Update_Test) {
	BoolList list1;
	list1.Add(true);
	list1.Add(true);

	CHECK_FALSE(list1.Update(100, false));
	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), (TBoolArray) true);
}

TEST(MsgpackArrayTestsGroup, MsgpackBoolArray_Clear_Test) {
	BoolList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_true(&pk);
	msgpack_pack_false(&pk);
	msgpack_pack_false(&pk);

	CHECK_TRUE(list.Add(true));
	CHECK_TRUE(list.Add(false));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Parse_Test) {
	Int64List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_int64(&pk, 0);
	msgpack_pack_int64(&pk, 1);
	msgpack_pack_int64(&pk, -5188146770730811392LL);
	msgpack_pack_int64(&pk, 5188146770730811392LL);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), 1);
	CHECK_EQUAL(list.Item(2), -5188146770730811392LL);
	CHECK_EQUAL(list.Item(3), 5188146770730811392LL);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Parse_Not_Int64_Test) {
	Int64List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_true(&pk);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_WriteTo_Test) {
	char buffer[2048];
	Int64List list;
	list.Add(-5188146770730811392LL);
	list.Add(5188146770730811392LL);
	list.Add(0);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 20);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 20, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 3);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -5188146770730811392LL);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 5188146770730811392LL);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Equals_Test) {
	Int64List list1;
	list1.Add(-5188146770730811392LL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	Int64List list2;
	list2.Add(-5188146770730811392LL);
	list2.Add(5188146770730811392LL);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, -1);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Clone_Test) {
	auto list1 = new Int64List();
	list1->Add(-5188146770730811392LL);
	list1->Add(5188146770730811392LL);
	list1->Add(0);

	Int64List list2;
	list2.Add(1);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), -5188146770730811392LL);
	CHECK_EQUAL(list2.Item(1), 5188146770730811392LL);
	CHECK_EQUAL(list2.Item(2), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Find_Test) {
	Int64List list1;
	list1.Add(-5188146770730811392LL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	CHECK(list1.Find(5188146770730811392LL) != list1.End());
	CHECK_EQUAL(*(list1.Find(5188146770730811392LL)), 5188146770730811392LL);
	CHECK_TRUE(list1.Find(-1) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Remove_Test) {
	Int64List list1;
	list1.Add(-5188146770730811392LL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Add_Test) {
	Int64List list1;
	CHECK_TRUE(list1.Add(5188146770730811392LL));
	CHECK_TRUE(list1.Add(-5188146770730811392LL));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 5188146770730811392LL);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Incorrect_Add_Test) {
	Int64List list1;
	CHECK_TRUE(list1.Add(5188146770730811392LL));
	CHECK_FALSE(list1.Add(5188146770730811392LL + 1LL));

	CHECK_EQUAL(list1.Size(), 1);
	CHECK_EQUAL(list1.Item(0), 5188146770730811392LL);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Update_Test) {
	Int64List list1;
	list1.Add(5188146770730811392LL);
	list1.Add(-5188146770730811392LL);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Incorrect_Update_Test) {
	Int64List list1;
	list1.Add(5188146770730811392LL);
	list1.Add(-5188146770730811392LL);

	CHECK_FALSE(list1.Update(100, 10));
	CHECK_FALSE(list1.Update(0, 5188146770730811392LL + 1LL));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 5188146770730811392LL);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt64Array_Clear_Test) {
	Int64List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_int64(&pk, 0);
	msgpack_pack_int64(&pk, 1);
	msgpack_pack_int64(&pk, 2);

	CHECK_TRUE(list.Add(5188146770730811392LL));
	CHECK_TRUE(list.Add(-5188146770730811392LL));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Parse_Test) {
	Uint64List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_uint64(&pk, 1);
	msgpack_pack_uint64(&pk, 0);
	msgpack_pack_uint64(&pk, 10188146770730811392ULL);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);
	CHECK_EQUAL(list.Item(0), 1);
	CHECK_EQUAL(list.Item(1), 0);
	CHECK_TRUE(list.Item(2) == 10188146770730811392ULL);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Parse_Not_Uint64_Test) {
	Uint64List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_str(&pk, 5);
	msgpack_pack_str_body(&pk, "User1", 5);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_WriteTo_Test) {
	char buffer[2048];
	Uint64List list;
	list.Add(0);
	list.Add(10188146770730811392ULL);
	list.Add(1);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 12);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 12, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 3);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 10188146770730811392ULL);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Equals_Test) {
	Uint64List list1;
	list1.Add(0);
	list1.Add(10188146770730811392ULL);
	list1.Add(1);

	Uint64List list2;
	list2.Add(0);
	list2.Add(10188146770730811392ULL);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 5222);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Clone_Test) {
	auto list1 = new Uint64List();
	list1->Add(0);
	list1->Add(10188146770730811392ULL);
	list1->Add(1);

	Uint64List list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), 0);
	CHECK_TRUE(list2.Item(1) == 10188146770730811392ULL);
	CHECK_EQUAL(list2.Item(2), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Find_Test) {
	Uint64List list1;
	list1.Add(10188146770730811392ULL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	CHECK(list1.Find(5188146770730811392LL) != list1.End());
	CHECK_EQUAL(*(list1.Find(5188146770730811392LL)), 5188146770730811392LL);
	CHECK_TRUE(list1.Find(1) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Remove_Test) {
	Uint64List list1;
	list1.Add(10188146770730811392ULL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Add_Test) {
	Uint64List list1;
	CHECK_TRUE(list1.Add(5188146770730811392LL));
	CHECK_TRUE(list1.Add(10188146770730811392ULL));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 5188146770730811392LL);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Incorrect_Add_Test) {
	Uint64List list1;
	CHECK_TRUE(list1.Add(5188146770730811392LL));
	CHECK_FALSE(list1.Add(10188146770730811392ULL + 1LL));

	CHECK_EQUAL(list1.Size(), 1);
	CHECK_EQUAL(list1.Item(0), 5188146770730811392LL);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Update_Test) {
	Uint64List list1;
	list1.Add(5188146770730811392LL);
	list1.Add(10188146770730811392ULL);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Incorrect_Update_Test) {
	Uint64List list1;
	list1.Add(5188146770730811392LL);
	list1.Add(10188146770730811392ULL);

	CHECK_FALSE(list1.Update(100, 10));
	CHECK_FALSE(list1.Update(0, 10188146770730811392ULL + 1LL));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 5188146770730811392LL);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint64Array_Clear_Test) {
	Uint64List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_uint64(&pk, 0);
	msgpack_pack_uint64(&pk, 1);
	msgpack_pack_uint64(&pk, 2);

	CHECK_TRUE(list.Add(5188146770730811392LL));
	CHECK_TRUE(list.Add(10188146770730811392ULL));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Parse_Test) {
	Int32List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_int32(&pk, 0);
	msgpack_pack_int32(&pk, -2147483647);
	msgpack_pack_int32(&pk, 2147483647);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), -2147483647);
	CHECK_EQUAL(list.Item(2), 2147483647);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Parse_Not_Int32_Test) {
	Int32List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_float(&pk, 0);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_WriteTo_Test) {
	char buffer[2048];
	Int32List list;
	list.Add(-2147483647);
	list.Add(2147483647);
	list.Add(0);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 12);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 12, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 3);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -2147483647);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 2147483647);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Equals_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);
	list1.Add(0);

	Int32List list2;
	list2.Add(-2147483647);
	list2.Add(2147483647);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 100);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Clone_Test) {
	auto list1 = new Int32List();
	list1->Add(-2147483647);
	list1->Add(2147483647);
	list1->Add(0);

	Int32List list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), -2147483647);
	CHECK_EQUAL(list2.Item(1), 2147483647);
	CHECK_EQUAL(list2.Item(2), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Find_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);
	list1.Add(0);

	CHECK(list1.Find(-2147483647) != list1.End());
	CHECK_EQUAL(*(list1.Find(-2147483647)), -2147483647);
	CHECK_TRUE(list1.Find(1) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Remove_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);
	list1.Add(0);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Add_Test) {
	Int32List list1;
	CHECK_TRUE(list1.Add(-2147483647));
	CHECK_TRUE(list1.Add(2147483647));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), -2147483647);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Update_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Incorrect_Update_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), -2147483647);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt32Array_Clear_Test) {
	Int32List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_int32(&pk, 0);
	msgpack_pack_int32(&pk, 1);
	msgpack_pack_int32(&pk, 2);

	CHECK_TRUE(list.Add(2147483647));
	CHECK_TRUE(list.Add(-2147483647));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Parse_Test) {
	Uint32List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 2);
	msgpack_pack_uint32(&pk, 0);
	msgpack_pack_uint32(&pk, 4294967295);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 2);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), 4294967295);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Parse_Not_Uint32_Test) {
	Uint32List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_double(&pk, 1);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_WriteTo_Test) {
	char buffer[2048];
	Uint32List list;
	list.Add(0);
	list.Add(4294967295);
	list.Add(1);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 8);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 8, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 3);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 4294967295);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Equals_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);
	list1.Add(0);

	Uint32List list2;
	list2.Add(147483647);
	list2.Add(2147483647);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Clone_Test) {
	auto list1 = new Uint32List();
	list1->Add(147483647);
	list1->Add(2147483647);
	list1->Add(0);

	Uint32List list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), 147483647);
	CHECK_EQUAL(list2.Item(1), 2147483647);
	CHECK_EQUAL(list2.Item(2), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Find_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);
	list1.Add(5);

	CHECK(list1.Find(5) != list1.End());
	CHECK_EQUAL(*(list1.Find(5)), 5);
	CHECK_TRUE(list1.Find(1) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Remove_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);
	list1.Add(5);

	CHECK_TRUE(list1.Remove(5));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Add_Test) {
	Uint32List list1;
	CHECK_TRUE(list1.Add(147483647));
	CHECK_TRUE(list1.Add(2147483647));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 147483647);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Update_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Incorrect_Update_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 147483647);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint32Array_Clear_Test) {
	Uint32List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_uint32(&pk, 0);
	msgpack_pack_uint32(&pk, 4294967295);
	msgpack_pack_uint32(&pk, 1);
	msgpack_pack_uint32(&pk, 2);

	CHECK_TRUE(list.Add(2147483647));
	CHECK_TRUE(list.Add(147483647));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Parse_Test) {
	Int16List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 5);
	msgpack_pack_int16(&pk, 0);
	msgpack_pack_int16(&pk, -32768);
	msgpack_pack_int16(&pk, 32767);
	msgpack_pack_int16(&pk, 1);
	msgpack_pack_int16(&pk, -1);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 5);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), -32768);
	CHECK_EQUAL(list.Item(2), 32767);
	CHECK_EQUAL(list.Item(3), 1);
	CHECK_EQUAL(list.Item(4), -1);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Parse_Not_Int16_Test) {
	Int16List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_float(&pk, 0);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_WriteTo_Test) {
	char buffer[2048];
	Int16List list;
	list.Add(-32768);
	list.Add(32767);
	list.Add(0);
	list.Add(-2147483647);
	list.Add(2147483647);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 10);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 10, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 5);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -32768);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 32767);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 1);

	object = unpacked.data.via.array.ptr[4];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Equals_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);
	list1.Add(0);

	Int16List list2;
	list2.Add(-32768);
	list2.Add(32767);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Clone_Test) {
	auto list1 = new Int16List();
	list1->Add(-32768);
	list1->Add(32767);
	list1->Add(0);

	Int16List list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), -32768);
	CHECK_EQUAL(list2.Item(1), 32767);
	CHECK_EQUAL(list2.Item(2), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Find_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);
	list1.Add(0);

	CHECK(list1.Find(32767) != list1.End());
	CHECK_EQUAL(*(list1.Find(32767)), 32767);
	CHECK_TRUE(list1.Find(1) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Remove_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);
	list1.Add(0);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Add_Test) {
	Int16List list1;
	CHECK_TRUE(list1.Add(-32768));
	CHECK_TRUE(list1.Add(32767));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), -32768);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Update_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Incorrect_Update_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), -32768);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt16Array_Clear_Test) {
	Int16List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_int16(&pk, 0);
	msgpack_pack_int16(&pk, -32768);
	msgpack_pack_int16(&pk, 32767);
	msgpack_pack_int16(&pk, -2147483647);

	CHECK_TRUE(list.Add(-32768));
	CHECK_TRUE(list.Add(32767));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Parse_Test) {
	Uint16List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_uint16(&pk, 0);
	msgpack_pack_uint16(&pk, 65535);
	msgpack_pack_uint16(&pk, 2147483647);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), 65535);
	CHECK_EQUAL(list.Item(2), 65535);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Parse_Not_Uint16_Test) {
	Uint16List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_double(&pk, 1);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_WriteTo_Test) {
	char buffer[2048];
	Uint16List list;
	list.Add(0);
	list.Add(65535);
	list.Add(1);
	list.Add(2147483647);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 9);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 9, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 4);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 65535);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 1);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 65535);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Equals_Test) {
	Uint16List list1;
	list1.Add(0);
	list1.Add(65535);
	list1.Add(1);

	Uint16List list2;
	list2.Add(0);
	list2.Add(65535);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Clone_Test) {
	auto list1 = new Uint16List();
	list1->Add(65535);
	list1->Add(32767);
	list1->Add(0);

	Uint16List list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), 65535);
	CHECK_EQUAL(list2.Item(1), 32767);
	CHECK_EQUAL(list2.Item(2), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Find_Test) {
	Uint16List list1;
	list1.Add(0);
	list1.Add(65535);
	list1.Add(1);

	CHECK(list1.Find(65535) != list1.End());
	CHECK_EQUAL(*(list1.Find(65535)), 65535);
	CHECK_TRUE(list1.Find(10) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Remove_Test) {
	Uint16List list1;
	list1.Add(0);
	list1.Add(65535);
	list1.Add(1);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Add_Test) {
	Uint16List list1;
	CHECK_TRUE(list1.Add(0));
	CHECK_TRUE(list1.Add(65535));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Update_Test) {
	Uint16List list1;
	list1.Add(0);
	list1.Add(65535);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Incorrect_Update_Test) {
	Uint16List list1;
	list1.Add(0);
	list1.Add(65535);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint16Array_Clear_Test) {
	Uint16List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 3);
	msgpack_pack_uint16(&pk, 0);
	msgpack_pack_uint16(&pk, 65535);
	msgpack_pack_uint16(&pk, 2147483647);

	CHECK_TRUE(list.Add(0));
	CHECK_TRUE(list.Add(65535));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 3);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Parse_Test) {
	Int8List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 5);
	msgpack_pack_int8(&pk, 0);
	msgpack_pack_int8(&pk, -128);
	msgpack_pack_int8(&pk, 127);
	msgpack_pack_int8(&pk, -2147483647);
	msgpack_pack_int8(&pk, 2147483647);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 5);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), -128);
	CHECK_EQUAL(list.Item(2), 127);
	CHECK_EQUAL(list.Item(3), 1);
	CHECK_EQUAL(list.Item(4), -1);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Parse_Not_Int8_Test) {
	Int8List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_float(&pk, 0);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_WriteTo_Test) {
	char buffer[2048];
	Int8List list;
	list.Add(-128);
	list.Add(127);
	list.Add(-32768);
	list.Add(32767);
	list.Add(0);
	list.Add(-2147483647);
	list.Add(2147483647);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 9);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 9, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 7);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -128);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 127);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -1);

	object = unpacked.data.via.array.ptr[4];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[5];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 1);

	object = unpacked.data.via.array.ptr[6];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_NEGATIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, -1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Equals_Test) {
	Int8List list1;
	list1.Add(0);
	list1.Add(-128);
	list1.Add(1);

	Int8List list2;
	list2.Add(0);
	list2.Add(-128);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Clone_Test) {
	auto list1 = new Int8List();
	list1->Add(0);
	list1->Add(-128);
	list1->Add(1);

	Int8List list2;
	list2.Add(123);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), 0);
	CHECK_EQUAL(list2.Item(1), -128);
	CHECK_EQUAL(list2.Item(2), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Find_Test) {
	Int8List list1;
	list1.Add(0);
	list1.Add(-128);
	list1.Add(1);

	CHECK(list1.Find(1) != list1.End());
	CHECK_EQUAL(*(list1.Find(1)), 1);
	CHECK_TRUE(list1.Find(2) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Remove_Test) {
	Int8List list1;
	list1.Add(0);
	list1.Add(-128);
	list1.Add(1);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Add_Test) {
	Int8List list1;
	CHECK_TRUE(list1.Add(-128));
	CHECK_TRUE(list1.Add(0));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), -128);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Update_Test) {
	Int8List list1;
	list1.Add(-128);
	list1.Add(0);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Incorrect_Update_Test) {
	Int8List list1;
	list1.Add(-128);
	list1.Add(0);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), -128);
}

TEST(MsgpackArrayTestsGroup, MsgpackInt8Array_Clear_Test) {
	Int8List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 5);
	msgpack_pack_int8(&pk, 0);
	msgpack_pack_int8(&pk, -128);
	msgpack_pack_int8(&pk, 127);
	msgpack_pack_int8(&pk, -2147483647);
	msgpack_pack_int8(&pk, 2147483647);

	CHECK_TRUE(list.Add(-128));
	CHECK_TRUE(list.Add(0));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 5);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Parse_Test) {
	Uint8List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_uint8(&pk, 0);
	msgpack_pack_uint8(&pk, 254);
	msgpack_pack_uint8(&pk, 65535);
	msgpack_pack_uint8(&pk, 2147483647);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);
	CHECK_EQUAL(list.Item(0), 0);
	CHECK_EQUAL(list.Item(1), 254);
	CHECK_EQUAL(list.Item(2), 255);
	CHECK_EQUAL(list.Item(3), 255);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Parse_Not_Uint8_Test) {
	Uint8List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_double(&pk, 1);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_WriteTo_Test) {
	char buffer[2048];
	Uint8List list;
	list.Add(0);
	list.Add(254);
	list.Add(65535);
	list.Add(1);
	list.Add(2147483647);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 9);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 9, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 5);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 0);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 254);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 255);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 1);

	object = unpacked.data.via.array.ptr[4];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_POSITIVE_INTEGER);
	CHECK_EQUAL(object.via.i64, 255);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Equals_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);
	list1.Add(1);

	Uint8List list2;
	list2.Add(0);
	list2.Add(254);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Clone_Test) {
	auto list1 = new Uint8List();
	list1->Add(0);
	list1->Add(254);
	list1->Add(1);

	Uint8List list2;
	list2.Add(123);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), 0);
	CHECK_EQUAL(list2.Item(1), 254);
	CHECK_EQUAL(list2.Item(2), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Find_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);
	list1.Add(1);

	CHECK(list1.Find(1) != list1.End());
	CHECK_EQUAL(*(list1.Find(1)), 1);
	CHECK_TRUE(list1.Find(2) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Remove_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);
	list1.Add(1);

	CHECK_TRUE(list1.Remove(0));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Add_Test) {
	Uint8List list1;
	CHECK_TRUE(list1.Add(0));
	CHECK_TRUE(list1.Add(254));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Update_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Incorrect_Update_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackUint8Array_Clear_Test) {
	Uint8List list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_uint8(&pk, 0);
	msgpack_pack_uint8(&pk, 254);
	msgpack_pack_uint8(&pk, 65535);
	msgpack_pack_uint8(&pk, 2147483647);

	CHECK_TRUE(list.Add(0));
	CHECK_TRUE(list.Add(254));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Parse_Test) {
	DoubleList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_double(&pk, 0.00001);
	msgpack_pack_double(&pk, 254.123);
	msgpack_pack_double(&pk, -65535.523);
	msgpack_pack_double(&pk, 2147483647.1);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);
	CHECK_EQUAL(list.Item(0), 0.00001);
	CHECK_EQUAL(list.Item(1), 254.123);
	CHECK_EQUAL(list.Item(2), -65535.523);
	CHECK_EQUAL(list.Item(3), 2147483647.1);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Parse_Not_Double_Test) {
	DoubleList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_int(&pk, 1);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_WriteTo_Test) {
	char buffer[2048];
	DoubleList list;
	list.Add(-0.05);
	list.Add(1.254);
	list.Add(65535.15);
	list.Add(0.1);
	list.Add(2147.483647);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 46);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 46, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 5);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT64);
	CHECK_EQUAL(object.via.f64, -0.05);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT64);
	CHECK_EQUAL(object.via.f64, 1.254);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT64);
	CHECK_EQUAL(object.via.f64, 65535.15);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT64);
	CHECK_EQUAL(object.via.f64, 0.1);

	object = unpacked.data.via.array.ptr[4];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT64);
	CHECK_EQUAL(object.via.f64, 2147.483647);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Equals_Test) {
	DoubleList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	DoubleList list2;
	list2.Add(-0.05);
	list2.Add(1.254);
	list2.Add(65535.15);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Clone_Test) {
	auto list1 = new DoubleList();
	list1->Add(-0.05);
	list1->Add(1.254);
	list1->Add(65535.15);

	DoubleList list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), -0.05);
	CHECK_EQUAL(list2.Item(1), 1.254);
	CHECK_EQUAL(list2.Item(2), 65535.15);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Find_Test) {
	DoubleList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	CHECK(list1.Find(-0.05) != list1.End());
	CHECK_EQUAL(*(list1.Find(-0.05)), -0.05);
	CHECK_TRUE(list1.Find(2) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Remove_Test) {
	DoubleList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	CHECK_TRUE(list1.Remove(1.254));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Add_Test) {
	DoubleList list1;
	CHECK_TRUE(list1.Add(0));
	CHECK_TRUE(list1.Add(1.254));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Update_Test) {
	DoubleList list1;
	list1.Add(0);
	list1.Add(1.254);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Incorrect_Update_Test) {
	DoubleList list1;
	list1.Add(0);
	list1.Add(1.254);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackDoubleArray_Clear_Test) {
	DoubleList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_double(&pk, 0.00001);
	msgpack_pack_double(&pk, 254.123);
	msgpack_pack_double(&pk, -65535.523);
	msgpack_pack_double(&pk, 2147483647.1);

	CHECK_TRUE(list.Add(0));
	CHECK_TRUE(list.Add(1.254));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Parse_Test) {
	FloatList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_float(&pk, 0.1);
	msgpack_pack_float(&pk, 254.1);
	msgpack_pack_float(&pk, -65535.5);
	msgpack_pack_float(&pk, 214748.1);

	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);
	CHECK_EQUAL(list.Item(0), 0.1f);
	CHECK_EQUAL(list.Item(1), 254.1f);
	CHECK_EQUAL(list.Item(2), -65535.5f);
	CHECK_EQUAL(list.Item(3), 214748.1f);

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Parse_Not_Float_Test) {
	FloatList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 1);
	msgpack_pack_int(&pk, 1);

	CHECK_FALSE(list.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_WriteTo_Test) {
	char buffer[2048];
	FloatList list;
	list.Add(-1.5f);
	list.Add(1.25f);
	list.Add(1000.25f);
	list.Add(-100.75f);
	list.Add(214789.5625f);

	CHECK_EQUAL(list.Write(buffer, sizeof(buffer)), 26);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 46, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 5);

	msgpack_object object = unpacked.data.via.array.ptr[0];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT32);
	CHECK_EQUAL(object.via.f64, -1.5f);

	object = unpacked.data.via.array.ptr[1];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT32);
	CHECK_EQUAL(object.via.f64, 1.25f);

	object = unpacked.data.via.array.ptr[2];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT32);
	CHECK_EQUAL(object.via.f64, 1000.25f);

	object = unpacked.data.via.array.ptr[3];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT32);
	CHECK_EQUAL(object.via.f64, -100.75f);

	object = unpacked.data.via.array.ptr[4];
	CHECK_EQUAL(object.type, MSGPACK_OBJECT_FLOAT32);
	CHECK_EQUAL(object.via.f64, 214789.5625f);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Equals_Test) {
	FloatList list1;
	list1.Add(-0.05f);
	list1.Add(1.254f);
	list1.Add(65535.15f);

	FloatList list2;
	list2.Add(-0.05f);
	list2.Add(1.254f);
	list2.Add(65535.15f);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Update(2, 42);
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	CHECK_FALSE(list1.Equals(NULL));
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Clone_Test) {
	auto list1 = new FloatList();
	list1->Add(-0.05f);
	list1->Add(1.254f);
	list1->Add(65535.15f);

	FloatList list2;
	list2.Add(1234);

	list1->CloneTo(&list2);
	delete list1;
	CHECK_EQUAL(list2.Size(), 3);
	CHECK_EQUAL(list2.Item(0), -0.05f);
	CHECK_EQUAL(list2.Item(1), 1.254f);
	CHECK_EQUAL(list2.Item(2), 65535.15f);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Find_Test) {
	FloatList list1;
	list1.Add(-0.05f);
	list1.Add(1.254f);
	list1.Add(65535.15f);

	CHECK(list1.Find(-0.05f) != list1.End());
	CHECK_EQUAL(*(list1.Find(-0.05f)), -0.05f);
	CHECK_TRUE(list1.Find(2) == list1.End());
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Remove_Test) {
	FloatList list1;
	list1.Add(-0.05f);
	list1.Add(1.254f);
	list1.Add(65535.15f);

	CHECK_TRUE(list1.Remove(1.254f));
	CHECK_EQUAL(list1.Size(), 2);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Add_Test) {
	FloatList list1;
	CHECK_TRUE(list1.Add(0));
	CHECK_TRUE(list1.Add(1.254f));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Update_Test) {
	FloatList list1;
	list1.Add(0);
	list1.Add(1.254f);

	CHECK_TRUE(list1.Update(0, 1));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 1);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Incorrect_Update_Test) {
	FloatList list1;
	list1.Add(0);
	list1.Add(1.254f);

	CHECK_FALSE(list1.Update(100, 10));

	CHECK_EQUAL(list1.Size(), 2);
	CHECK_EQUAL(list1.Item(0), 0);
}

TEST(MsgpackArrayTestsGroup, MsgpackFloatArray_Clear_Test) {
	FloatList list;
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_float(&pk, 0.1);
	msgpack_pack_float(&pk, 254.1);
	msgpack_pack_float(&pk, -65535.5);
	msgpack_pack_float(&pk, 214748.1);

	CHECK_TRUE(list.Add(0));
	CHECK_TRUE(list.Add(1.254f));
	CHECK_EQUAL(list.Size(), 2);
	list.Clear();
	CHECK_TRUE(list.TryParse(sbuf.data, sbuf.size));
	CHECK_EQUAL(list.Size(), 4);

	msgpack_sbuffer_destroy(&sbuf);
}