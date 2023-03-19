
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(MsgpackObjectTestsGroup){void setup(){} void teardown(){}};

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : public MsgpackObject {
  public:
	MsgpackValue<char *> Name;
	MsgpackValue<uint32_t> Role;

	UserDto(const char *name = {}, const TUserRole role = {})
		: Name(this, 0, name), //
		  Role(this, 1, role){};

	bool Validate() override { return Role.Get() < 1000; }
};

class GoodsDto : public MsgpackObject {
  public:
	MsgpackValue<int> Id;
	MsgpackValue<uint32_t> Created;
	MsgpackValue<char *> Group;
	MsgpackValue<char *> Name;
	MsgpackValue<float> Price;
	MsgpackValue<double> Quantity;
	MsgpackValue<bool> Deleted;
	MsgpackValue<char *> StoreName;

	GoodsDto(const int id = {}, uint32_t created = {}, const char *group = {}, const char *name = {}, const float price = {}, const double quantity = {}, const bool deleted = {},
			 const char *storeName = {})
		: Id(this, 0, id),			   //
		  Created(this, 1, created),   //
		  Group(this, 2, group),	   //
		  Name(this, 3, name),		   //
		  Price(this, 4, price),	   //
		  Quantity(this, 5, quantity), //
		  Deleted(this, 6, deleted),   //
		  StoreName(this, 7, storeName){};
};

class GoodsList : public MsgpackObjectsArray {
  public:
	bool Validate(MsgpackObject *item) override { return item->Validate(); }
	MsgpackObject *CreateItem() override { return new GoodsDto(); }
};

class OrderDto : public MsgpackObject {
  public:
	MsgpackValue<char *> Supplier;
	MsgpackValue<uint32_t> DateTime;
	MsgpackValue<MsgpackArrayBase *> Goods;
	MsgpackValue<MsgpackObject *> User;
	GoodsList goodsList;
	UserDto userDto;

	OrderDto(const char *supplier = {}, const uint32_t dateTime = {}, const char *userName = {}, const TUserRole userRole = {})
		: Supplier(this, 0, supplier), //
		  DateTime(this, 1, dateTime), //
		  Goods(this, 2, &goodsList),  //
		  userDto(userName, userRole), //
		  User(this, 3, &userDto){};

	~OrderDto() {}
};

class OrdersList : public MsgpackObjectsArray {
  public:
	bool Validate(MsgpackObject *item) override { return item->Validate(); }
	MsgpackObject *CreateItem() override { return new OrderDto(); }
};

class CustomerDto : public MsgpackObject {
  public:
	MsgpackValue<uint64_t> Id;
	MsgpackValue<char *> Name;
	MsgpackValue<TMsgpackRawData> Blob;
	MsgpackValue<MsgpackArrayBase *> Orders;
	OrdersList ordersList;

	CustomerDto(const uint64_t id = {}, const char *name = {}, const TMsgpackRawData blob = {})
		: Id(this, 0, id),	   //
		  Name(this, 1, name), //
		  Blob(this, 2, blob), //
		  Orders(this, 3, &ordersList){};
};

class ValuesWoInstance : public MsgpackObject {
  public:
	ValuesWoInstance(const uint64_t id = {}, const char *name = {}, const TMsgpackRawData blob = {}) {
		new MsgpackValue<uint64_t>(this, 0, id);
		new MsgpackValue<char *>(this, 1, name);
		new MsgpackValue<TMsgpackRawData>(this, 2, blob);
	};

	~ValuesWoInstance() {
		for (const auto &field : Fields) { delete field; }
	}
};

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 8);
	msgpack_pack_int(&pk, 1);
	msgpack_pack_uint32(&pk, 1657052045);
	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);
	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);

	GoodsDto goods;
	CHECK_TRUE(goods.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);

	CHECK_EQUAL(goods.Id.Get(), 1);
	CHECK_EQUAL(goods.Created.Get(), 1657052045);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	STRCMP_EQUAL(goods.Name.Get(), "Tomato");
	CHECK_EQUAL(goods.Price.Get(), 123.25);
	CHECK_EQUAL(goods.Quantity.Get(), 165.052045);
	CHECK_EQUAL(goods.Deleted.Get(), false);
	STRCMP_EQUAL(goods.StoreName.Get(), NULL);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_TryParse_Test) {
	char buffer[2048];
	GoodsDto goods0(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_EQUAL(goods0.Write(buffer, sizeof(buffer)), 43);

	GoodsDto goods1;
	CHECK_TRUE(goods1.TryParse(buffer, 43));

	CHECK_EQUAL(goods1.Id.Get(), 2);
	CHECK_EQUAL(goods1.Created.Get(), 1657052789);
	STRCMP_EQUAL(goods1.Group.Get(), "group");
	STRCMP_EQUAL(goods1.Name.Get(), "name");
	CHECK_EQUAL(goods1.Price.Get(), 58.25);
	CHECK_EQUAL(goods1.Quantity.Get(), 48.2);
	CHECK_EQUAL(goods1.Deleted.Get(), false);
	STRCMP_EQUAL(goods1.StoreName.Get(), "storeName");
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Complex_WriteTo_TryParse_Test) {
	char buffer[2048];
	OrderDto order0("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	order0.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	order0.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));
	order0.goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2));
	order0.goodsList.Add(new GoodsDto(4, 1657055789, "Keyboards", "K4-100", 358.25, 648.2));

	CHECK_EQUAL(order0.Write(buffer, sizeof(buffer)), 182);

	OrderDto order1;
	CHECK_TRUE(order1.TryParse(buffer, 182));

	CHECK_EQUAL(order1.goodsList.Size(), 4);
	CHECK_EQUAL(order1.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1657052789);
	STRCMP_EQUAL(order1.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K2-100");
	STRCMP_EQUAL(order1.goodsList.Item<GoodsDto *>(2)->Name.Get(), "K3-100");
	CHECK_EQUAL(order1.goodsList.Item<GoodsDto *>(3)->Price.Get(), 358.25);
	CHECK_EQUAL(order1.goodsList.Item<GoodsDto *>(3)->Quantity.Get(), 648.2);
	STRCMP_EQUAL(order1.userDto.Name.Get(), "Joe Doe");
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_Error_Less_Data_Test) {
	msgpack_sbuffer sbuf = {};
	msgpack_packer pk;
	GoodsDto goods;
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size));
	CHECK_FALSE(goods.TryParse(NULL, 1));

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 1);
	msgpack_pack_int(&pk, 1);
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_Error_Exceeded_Data_Test) {
	msgpack_sbuffer sbuf = {};
	msgpack_packer pk;
	GoodsDto goods;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 8 + 1);
	msgpack_pack_int(&pk, 1);
	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);
	msgpack_pack_uint32(&pk, 1657052045);
	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);
	msgpack_pack_nil(&pk);
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_Error_Incorrect_Field_Test) {
	msgpack_sbuffer sbuf = {};
	msgpack_packer pk;
	GoodsDto goods;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);
	msgpack_pack_array(&pk, 8);
	msgpack_pack_float(&pk, 1);
	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);
	msgpack_pack_uint32(&pk, 1657052045);
	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size));
	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_With_Reordered_Fields_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 8);
	msgpack_pack_int(&pk, 1);

	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);

	msgpack_pack_uint32(&pk, 1657052045);

	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);

	GoodsDto goods;
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_And_Incorrect_Length_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 8);
	msgpack_pack_int(&pk, 1);
	msgpack_pack_uint32(&pk, 1657052045);
	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);
	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);

	GoodsDto goods;
	CHECK_TRUE(goods.TryParse(sbuf.data, sbuf.size));
	CHECK_TRUE(goods.TryParse(sbuf.data, sbuf.size + 100));
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size - 1));
	CHECK_FALSE(goods.TryParse(sbuf.data, 0));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_With_Null_Values_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 8);

	msgpack_pack_nil(&pk);

	msgpack_pack_uint32(&pk, 1657052045);
	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);
	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);

	GoodsDto goods;
	CHECK_FALSE(goods.TryParse(sbuf.data, sbuf.size));

	msgpack_sbuffer_destroy(&sbuf);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_With_Begin_End_Stages_Test) {
	msgpack_sbuffer sbuf;
	msgpack_packer pk;

	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 8);
	msgpack_pack_int(&pk, 1);
	msgpack_pack_uint32(&pk, 1657052048);
	msgpack_pack_str(&pk, 10);
	msgpack_pack_str_body(&pk, "Vegetables", 10);
	msgpack_pack_str(&pk, 6);
	msgpack_pack_str_body(&pk, "Tomato", 6);
	msgpack_pack_float(&pk, 123.25);
	msgpack_pack_double(&pk, 165.052045);
	msgpack_pack_false(&pk);
	msgpack_pack_nil(&pk);

	GoodsDto goods;
	auto unpacked = goods.BeginTryParse(sbuf.data, sbuf.size);

	CHECK(unpacked != NULL);
	msgpack_sbuffer_destroy(&sbuf);

	CHECK_EQUAL(goods.Created.Get(), 1657052048);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	goods.EndTryParse(unpacked);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_Test) {
	char buffer[2048];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_EQUAL(goods.Write(buffer, sizeof(buffer)), 43);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, buffer, 43, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 8);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_With_Limited_Buffer_Test) {
	char buffer[32];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_EQUAL(goods.Write(buffer, sizeof(buffer)), 0);
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

TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_Async_Test) {
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2);
	CHECK_EQUAL(goods.DirectWriteTo((void *)987654321, OnReady), 34);

	CHECK_EQUAL(TestParent, (void *)987654321);
	CHECK_EQUAL(DirectWriteTestBufferLenght, 34);

	msgpack_unpacked unpacked;
	msgpack_unpacked_init(&unpacked);
	CHECK_EQUAL(msgpack_unpack_next(&unpacked, DirectWriteTestBuffer, DirectWriteTestBufferLenght, NULL), MSGPACK_UNPACK_SUCCESS);
	CHECK_EQUAL(unpacked.data.type, MSGPACK_OBJECT_ARRAY);
	CHECK_EQUAL(unpacked.data.via.array.size, 8);
	delete[] DirectWriteTestBuffer;
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Equals_Test) {
	OrderDto orderDto1("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto1.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto1.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	OrderDto orderDto2("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto2.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto2.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	CHECK_TRUE(orderDto1 == orderDto2);
	CHECK_FALSE(orderDto1 != orderDto2);
	CHECK_TRUE(orderDto1.Equals(&orderDto2));
	orderDto1.DateTime.Set(orderDto1.DateTime.Get() + 1);
	CHECK_TRUE(orderDto1 != orderDto2);
	CHECK_FALSE(orderDto1 == orderDto2);
	CHECK_FALSE(orderDto1.Equals(&orderDto2));
	CHECK_FALSE(orderDto1.Equals(NULL));
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Clone_Test) {
	auto orderDto1 = new OrderDto("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto1->goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto1->goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	OrderDto orderDto2;

	orderDto1->CloneTo(&orderDto2);
	delete orderDto1;

	STRCMP_EQUAL(orderDto2.Supplier.Get(), "Dell");
	CHECK_EQUAL(orderDto2.DateTime.Get(), 1657058000);
	CHECK_EQUAL(orderDto2.goodsList.Size(), 2);
	CHECK_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1657052789);
	STRCMP_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K2-100");
	STRCMP_EQUAL(orderDto2.userDto.Name.Get(), "Joe Doe");
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_With_Blob_Field_Test) {
	const int pictureSize = 1'000'0000;
	uint8_t *picture = new uint8_t[pictureSize];
	for (size_t i = 0; i < pictureSize; i++) { picture[i] = 'A' + (i % 58); }

	auto customerDto1 = new CustomerDto(1234567890123456789LL, "Viordash", {picture, pictureSize});
	CHECK(customerDto1->ordersList.Add(new OrderDto("Dell1", 1657058001, "Joe Doe", TUserRole::uViewer)));
	CHECK(customerDto1->ordersList.Add(new OrderDto("Dell2", 1657058002, "Joe Doe", TUserRole::uViewer)));
	auto orderDto1 = customerDto1->ordersList.Item<OrderDto *>(0);
	CHECK(orderDto1->goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2)));
	CHECK(orderDto1->goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2)));
	CHECK(orderDto1->goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2)));
	auto orderDto2 = customerDto1->ordersList.Item<OrderDto *>(1);
	CHECK(orderDto2->goodsList.Add(new GoodsDto(100, 1007052789, "Mouse", "M1-100", 8.25, 18.2)));
	CHECK(orderDto2->goodsList.Add(new GoodsDto(200, 2007053789, "Mouse", "M2-100", 48.25, 28.2)));

	auto size = customerDto1->DirectWriteTo(0, OnReady);
	CHECK_EQUAL(size, 10000264);

	auto doc = customerDto1->BeginTryParse(DirectWriteTestBuffer, size);
	CHECK(doc != NULL);

	CHECK_EQUAL(customerDto1->Id.Get(), 1234567890123456789LL);
	STRCMP_EQUAL(customerDto1->Name.Get(), "Viordash");
	CHECK_EQUAL(customerDto1->ordersList.Size(), 4);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(2)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(3)->goodsList.Size(), 2);
	CHECK_EQUAL(((TMsgpackRawData)customerDto1->Blob.Get()).Size, pictureSize);
	CHECK_FALSE(((TMsgpackRawData)customerDto1->Blob.Get()).Data == picture);
	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TMsgpackRawData)customerDto1->Blob.Get()).Data[i], 'A' + (i % 58)); }
	customerDto1->EndTryParse(doc);

	delete customerDto1;
	delete[] picture;

	CustomerDto customerDto2;
	doc = customerDto2.BeginTryParse(DirectWriteTestBuffer, size);
	CHECK(doc != NULL);

	CHECK_EQUAL(customerDto2.Id.Get(), 1234567890123456789LL);
	STRCMP_EQUAL(customerDto2.Name.Get(), "Viordash");
	CHECK_EQUAL(customerDto2.ordersList.Size(), 2);
	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
	CHECK_EQUAL(((TMsgpackRawData)customerDto2.Blob.Get()).Size, pictureSize);
	CHECK_FALSE(((TMsgpackRawData)customerDto2.Blob.Get()).Data == picture);
	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TMsgpackRawData)customerDto2.Blob.Get()).Data[i], 'A' + (i % 58)); }
	customerDto2.EndTryParse(doc);

	delete[] DirectWriteTestBuffer;
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Values_Without_Instance_Parse_Write_Test) {
	char buffer[2048];
	ValuesWoInstance valuesWoInstance0(1657052789, "Tomato", {(uint8_t *)"ABCDEFGHIJKLMNOPQR", strlen("ABCDEFGHIJKLMNOPQR")});
	CHECK_EQUAL(valuesWoInstance0.Write(buffer, sizeof(buffer)), 32);

	ValuesWoInstance valuesWoInstance1;

	auto doc = valuesWoInstance1.BeginTryParse(buffer, 123);
	CHECK(doc != NULL);

	auto id = (MsgpackValue<uint64_t> *)valuesWoInstance1.GetField(0);
	CHECK_FALSE(id == NULL);
	CHECK_EQUAL(id->Get(), 1657052789);

	auto name = (MsgpackValue<char *> *)valuesWoInstance1.GetField(1);
	CHECK_FALSE(name == NULL);
	STRCMP_EQUAL(name->Get(), "Tomato");

	auto blob = (MsgpackValue<TMsgpackRawData> *)valuesWoInstance1.GetField(2);
	CHECK_FALSE(blob == NULL);
	STRNCMP_EQUAL((char *)((TMsgpackRawData)(blob->Get())).Data, "ABCDEFGHIJKLMNOPQR", ((TMsgpackRawData)(blob->Get())).Size);

	auto notExistsValue = (MsgpackValue<uint32_t> *)valuesWoInstance1.GetField(100);
	CHECK_TRUE(notExistsValue == NULL);
	valuesWoInstance1.EndTryParse(doc);
}

class SetValueObjectDto : public MsgpackObject {
  public:
	MsgpackValue<int> Id;
	MsgpackValue<MsgpackArrayBase *> Goods;
	MsgpackValue<MsgpackObject *> User;
	GoodsList goodsList;
	UserDto userDto;

	SetValueObjectDto(int id = {}, char *userName = {}, TUserRole userRole = {})
		: Id(this, 0, id),			   //
		  Goods(this, 1, &goodsList),  //
		  userDto(userName, userRole), //
		  User(this, 2, &userDto){};
};

TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_ArrayValue_Test) {
	SetValueObjectDto testDto(1657058000, "Joe Doe", TUserRole::uViewer);
	testDto.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	testDto.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));
	testDto.goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2));
	testDto.goodsList.Add(new GoodsDto(4, 1657055789, "Keyboards", "K4-100", 358.25, 648.2));
	CHECK_EQUAL(testDto.goodsList.Size(), 4);

	GoodsList newGoodsList;
	newGoodsList.Add(new GoodsDto(100, 1111, "Keyboards-111", "K111-100", 1158.25, 1148.2));
	newGoodsList.Add(new GoodsDto(200, 2222, "Keyboards-222", "K222-100", 22158.25, 22448.2));

	testDto.Goods.Set(&newGoodsList);

	CHECK_EQUAL(testDto.goodsList.Size(), 2);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Id.Get(), 100);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1111);
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Group.Get(), "Keyboards-111");
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Name.Get(), "K111-100");
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Price.Get(), 1158.25);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Quantity.Get(), 1148.2);

	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Id.Get(), 200);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Created.Get(), 2222);
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Group.Get(), "Keyboards-222");
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K222-100");
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Price.Get(), 22158.25);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Quantity.Get(), 22448.2);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_ObjectValue_Test) {
	SetValueObjectDto testDto(1657058000, "Joe Doe", TUserRole::uViewer);

	UserDto userDto("User 1", TUserRole::uAdmin);

	testDto.User.Set(&userDto);
	STRCMP_EQUAL(testDto.userDto.Name.Get(), "User 1");
	CHECK_EQUAL(testDto.userDto.Role.Get(), TUserRole::uAdmin);
}

class NullValueObjectDto : public MsgpackObject {
  public:
	MsgpackValue<int> Id;
	MsgpackValue<MsgpackArrayBase *> Goods;
	MsgpackValue<MsgpackObject *> User;

	NullValueObjectDto(int id = {})
		: Id(this, 0, id), //
		  Goods(this, 1),  //
		  User(this, 2){};
};

TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_Nulled_ArrayValue_Test) {
	NullValueObjectDto testDto(1657058000);

	GoodsList newGoodsList;
	newGoodsList.Add(new GoodsDto(100, 1111, "Keyboards-111", "K111-100", 1158.25, 1148.2));
	newGoodsList.Add(new GoodsDto(200, 2222, "Keyboards-222", "K222-100", 22158.25, 22448.2));

	testDto.Goods.Set(&newGoodsList);

	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Size(), 2);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Id.Get(), 100);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Created.Get(), 1111);
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Group.Get(), "Keyboards-111");
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Name.Get(), "K111-100");
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Price.Get(), 1158.25);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Quantity.Get(), 1148.2);

	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Id.Get(), 200);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Created.Get(), 2222);
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Group.Get(), "Keyboards-222");
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Name.Get(), "K222-100");
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Price.Get(), 22158.25);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Quantity.Get(), 22448.2);
}

TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_Nulled_ObjectValue_Test) {
	NullValueObjectDto testDto(1657058000);

	UserDto userDto("User 1", TUserRole::uAdmin);

	testDto.User.Set(&userDto);
	STRCMP_EQUAL(((UserDto *)testDto.User.Get())->Name.Get(), "User 1");
	CHECK_EQUAL(((UserDto *)testDto.User.Get())->Role.Get(), TUserRole::uAdmin);
}