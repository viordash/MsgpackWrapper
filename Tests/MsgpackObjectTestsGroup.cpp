
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

// class GoodsList : public MsgpackObjectsArray {
//   public:
// 	bool Validate(MsgpackObject *item) override { return item->Validate(); }
// 	MsgpackObject *CreateItem() override { return new GoodsDto(); }
// };

// class OrderDto : public MsgpackObject {
//   public:
// 	MsgpackValue<char *> Supplier;
// 	MsgpackValue<uint32_t> DateTime;
// 	MsgpackValue<MsgpackArrayBase *> Goods;
// 	MsgpackValue<MsgpackObject *> User;
// 	GoodsList goodsList;
// 	UserDto userDto;

// 	OrderDto(const char *supplier = {}, const uint32_t dateTime = {}, const char *userName = {}, const TUserRole userRole = {})
// 		: Supplier(this, "supplier", supplier), //
// 		  DateTime(this, "dateTime", dateTime), //
// 		  Goods(this, "goods", &goodsList),		//
// 		  userDto(userName, userRole),			//
// 		  User(this, "user", &userDto){};

// 	~OrderDto() {}
// };

// class OrdersList : public MsgpackObjectsArray {
//   public:
// 	bool Validate(MsgpackObject *item) override { return item->Validate(); }
// 	MsgpackObject *CreateItem() override { return new OrderDto(); }
// };

// class CustomerDto : public MsgpackObject {
//   public:
// 	MsgpackValue<uint64_t> Id;
// 	MsgpackValue<char *> Name;
// 	MsgpackValue<TMsgpackRawData> Blob;
// 	MsgpackValue<MsgpackArrayBase *> Orders;
// 	OrdersList ordersList;

// 	CustomerDto(const uint64_t id = {}, const char *name = {}, const TMsgpackRawData blob = {})
// 		: Id(this, "id", id),		//
// 		  Name(this, "name", name), //
// 		  Blob(this, "blob", blob), //
// 		  Orders(this, "orders", &ordersList){};
// };

// class ValuesWoInstance : public MsgpackObject {
//   public:
// 	ValuesWoInstance(const uint64_t id = {}, const char *name = {}, const TMsgpackRawData blob = {}) {
// 		new MsgpackValue<uint64_t>(this, "id", id);
// 		new MsgpackValue<char *>(this, "name", name);
// 		new MsgpackValue<TMsgpackRawData>(this, "blob", blob);
// 	};

// 	~ValuesWoInstance() {
// 		for (const auto &field : Fields) { delete field; }
// 	}
// };

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

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Complex_TryParse_Test) {
// 	OrderDto order;

// 	CHECK(order.TryStringParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
// 							   "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
// 							   "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
// 							   "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_EQUAL(order.goodsList.Size(), 3);
// 	CHECK_EQUAL(order.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1657052789);
// 	STRCMP_EQUAL(order.goodsList.Item<GoodsDto *>(2)->Name.Get(), "K4-100");
// 	STRCMP_EQUAL(order.userDto.Name.Get(), "Joe Doe");
// }

TEST(MsgpackObjectTestsGroup, MsgpackObject_Parse_Error_Test) {
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
	CHECK_TRUE(goods.TryParse(sbuf.data, sbuf.size));
	auto unpacked = goods.BeginTryParse(sbuf.data, sbuf.size);

	CHECK(unpacked != NULL);
	msgpack_sbuffer_destroy(&sbuf);

	CHECK_EQUAL(goods.Created.Get(), 1657052048);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	goods.EndTryParse(unpacked);
}

// TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_Test) {
// 	char buffer[2048];
// 	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
// 	CHECK_EQUAL(goods.WriteToString(buffer, sizeof(buffer)), 129);

// 	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
// 						 "\"StoreName\":\"storeName\"}");
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_With_Limited_Buffer_Test) {
// 	char buffer[32];
// 	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
// 	CHECK_EQUAL(goods.WriteToString(buffer, sizeof(buffer)), 31);

// 	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"G");
// }

// static void *TestParent = NULL;
// static char *DirectWriteTestBuffer = NULL;
// static void OnReady(void *parent, const char *json, size_t size) {
// 	TestParent = parent;
// 	DirectWriteTestBuffer = new char[size + 1];
// 	memcpy(DirectWriteTestBuffer, json, size);
// 	DirectWriteTestBuffer[size] = 0;
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_WriteTo_Async_Test) {
// 	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2);
// 	goods.DirectWriteTo((void *)987654321, OnReady);

// 	CHECK_EQUAL(TestParent, (void *)987654321);
// 	STRCMP_EQUAL(DirectWriteTestBuffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
// 										"\"StoreName\":null}");
// 	delete[] DirectWriteTestBuffer;
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Complex_WriteTo_Test) {
// 	OrderDto orderDto("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
// 	orderDto.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
// 	orderDto.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));
// 	orderDto.goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2));
// 	orderDto.goodsList.Add(new GoodsDto(4, 1657055789, "Keyboards", "K4-100", 358.25, 648.2));

// 	rapidjson::Document doc;
// 	doc.SetObject();

// 	orderDto.WriteToDoc(&doc);

// 	rapidjson::StringBuffer buffer;
// 	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 	doc.Accept(writer);

// 	const char *jsonStr = buffer.GetString();
// 	STRCMP_EQUAL(jsonStr, "{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
// 						  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":null},{\"Id\":2,\"Created\":1657053789,\"Group\":\"Keyboards\",\"Name\":\"K2-100\",\"Price\":158."
// 						  "25,\"Quantity\":448.2,\"Deleted\":false,\"StoreName\":null},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
// 						  "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":null},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
// 						  "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":null}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}");
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Equals_Test) {
// 	OrderDto orderDto1("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
// 	orderDto1.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
// 	orderDto1.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

// 	OrderDto orderDto2("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
// 	orderDto2.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
// 	orderDto2.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

// 	CHECK_TRUE(orderDto1 == orderDto2);
// 	CHECK_FALSE(orderDto1 != orderDto2);
// 	CHECK_TRUE(orderDto1.Equals(&orderDto2));
// 	orderDto1.DateTime.Set(orderDto1.DateTime.Get() + 1);
// 	CHECK_TRUE(orderDto1 != orderDto2);
// 	CHECK_FALSE(orderDto1 == orderDto2);
// 	CHECK_FALSE(orderDto1.Equals(&orderDto2));
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Clone_Test) {
// 	auto orderDto1 = new OrderDto("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
// 	orderDto1->goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
// 	orderDto1->goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

// 	OrderDto orderDto2;

// 	orderDto1->CloneTo(&orderDto2);
// 	delete orderDto1;

// 	STRCMP_EQUAL(orderDto2.Supplier.Get(), "Dell");
// 	CHECK_EQUAL(orderDto2.DateTime.Get(), 1657058000);
// 	CHECK_EQUAL(orderDto2.goodsList.Size(), 2);
// 	CHECK_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1657052789);
// 	STRCMP_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K2-100");
// 	STRCMP_EQUAL(orderDto2.userDto.Name.Get(), "Joe Doe");
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_With_Blob_Field_Test) {
// 	const int pictureSize = 1'000'0000;
// 	uint8_t *picture = new uint8_t[pictureSize];
// 	for (size_t i = 0; i < pictureSize; i++) { picture[i] = 'A' + (i % 58); }

// 	auto customerDto1 = new CustomerDto(1234567890123456789LL, "Viordash", {picture, pictureSize});
// 	CHECK(customerDto1->ordersList.Add(new OrderDto("Dell1", 1657058001, "Joe Doe", TUserRole::uViewer)));
// 	CHECK(customerDto1->ordersList.Add(new OrderDto("Dell2", 1657058002, "Joe Doe", TUserRole::uViewer)));
// 	auto orderDto1 = customerDto1->ordersList.Item<OrderDto *>(0);
// 	CHECK(orderDto1->goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2)));
// 	CHECK(orderDto1->goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2)));
// 	CHECK(orderDto1->goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2)));
// 	auto orderDto2 = customerDto1->ordersList.Item<OrderDto *>(1);
// 	CHECK(orderDto2->goodsList.Add(new GoodsDto(100, 1007052789, "Mouse", "M1-100", 8.25, 18.2)));
// 	CHECK(orderDto2->goodsList.Add(new GoodsDto(200, 2007053789, "Mouse", "M2-100", 48.25, 28.2)));

// 	auto size = customerDto1->DirectWriteTo(0, OnReady);
// 	CHECK_EQUAL(size, 10173299);

// 	auto doc = customerDto1->BeginTryStringParse(DirectWriteTestBuffer, size);
// 	CHECK(doc != NULL);

// 	CHECK_EQUAL(customerDto1->Id.Get(), 1234567890123456789LL);
// 	STRCMP_EQUAL(customerDto1->Name.Get(), "Viordash");
// 	CHECK_EQUAL(customerDto1->ordersList.Size(), 4);
// 	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
// 	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
// 	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(2)->goodsList.Size(), 3);
// 	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(3)->goodsList.Size(), 2);
// 	CHECK_EQUAL(((TMsgpackRawData)customerDto1->Blob.Get()).Size, pictureSize);
// 	CHECK_FALSE(((TMsgpackRawData)customerDto1->Blob.Get()).Data == picture);
// 	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TMsgpackRawData)customerDto1->Blob.Get()).Data[i], 'A' + (i % 58)); }
// 	customerDto1->EndTryStringParse(doc);

// 	delete customerDto1;
// 	delete[] picture;

// 	CustomerDto customerDto2;
// 	doc = customerDto2.BeginTryStringParse(DirectWriteTestBuffer, size);
// 	CHECK(doc != NULL);

// 	CHECK_EQUAL(customerDto2.Id.Get(), 1234567890123456789LL);
// 	STRCMP_EQUAL(customerDto2.Name.Get(), "Viordash");
// 	CHECK_EQUAL(customerDto2.ordersList.Size(), 2);
// 	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
// 	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
// 	CHECK_EQUAL(((TMsgpackRawData)customerDto2.Blob.Get()).Size, pictureSize);
// 	CHECK_FALSE(((TMsgpackRawData)customerDto2.Blob.Get()).Data == picture);
// 	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TMsgpackRawData)customerDto2.Blob.Get()).Data[i], 'A' + (i % 58)); }
// 	customerDto2.EndTryStringParse(doc);

// 	delete[] DirectWriteTestBuffer;
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Optional_Values_Presented_Test) {
// 	OrderDto order;

// 	CHECK_FALSE(order.DateTime.Presented());

// 	CHECK(order.TryStringParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_TRUE(order.DateTime.Presented());

// 	CHECK(order.TryStringParse("{\"supplier\":\"Dell\",\"goods\":[],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_FALSE(order.DateTime.Presented());
// }

// class OptionalObjectDto : public MsgpackObject {
//   public:
// 	MsgpackValue<int> Id;
// 	MsgpackValue<MsgpackArrayBase *> Goods;
// 	MsgpackValue<MsgpackObject *> User;
// 	GoodsList goodsList;
// 	UserDto userDto;

// 	OptionalObjectDto(int id = {}, char *userName = {}, TUserRole userRole = {})
// 		: Id(this, "id", id),				//
// 		  Goods(this, "goods", &goodsList), //
// 		  userDto(userName, userRole),		//
// 		  User(this, "user", &userDto){};
// };

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Optional_TryParse_Test) {
// 	OptionalObjectDto optionalObjectDto;

// 	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
// 												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_TRUE(optionalObjectDto.Goods.Presented());
// 	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
// 	CHECK_TRUE(optionalObjectDto.User.Presented());
// 	CHECK_FALSE(optionalObjectDto.User.IsNull());

// 	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":null,\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_TRUE(optionalObjectDto.Goods.Presented());
// 	CHECK_TRUE(optionalObjectDto.Goods.IsNull());
// 	CHECK_TRUE(optionalObjectDto.User.Presented());
// 	CHECK_FALSE(optionalObjectDto.User.IsNull());

// 	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
// 												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":null}"));
// 	CHECK_TRUE(optionalObjectDto.Goods.Presented());
// 	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
// 	CHECK_TRUE(optionalObjectDto.User.Presented());
// 	CHECK_TRUE(optionalObjectDto.User.IsNull());

// 	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goodsOther\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
// 												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_FALSE(optionalObjectDto.Goods.Presented());
// 	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
// 	CHECK_TRUE(optionalObjectDto.User.Presented());
// 	CHECK_FALSE(optionalObjectDto.User.IsNull());

// 	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
// 												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"userOther\":{\"name\":\"Joe Doe\",\"role\":1}}"));
// 	CHECK_TRUE(optionalObjectDto.Goods.Presented());
// 	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
// 	CHECK_FALSE(optionalObjectDto.User.Presented());
// 	CHECK_FALSE(optionalObjectDto.User.IsNull());
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Values_Without_Instance_Parse_Test) {
// 	ValuesWoInstance valuesWoInstance;

// 	auto doc = valuesWoInstance.BeginTryStringParse("{\"id\":123,\"name\":\"Tomato\",\"blob\":\"ABCDEFGHIJKLMNOPQR\"}");
// 	CHECK(doc != NULL);

// 	auto id = (MsgpackValue<uint64_t> *)valuesWoInstance.GetField("id");
// 	CHECK_FALSE(id == NULL);
// 	CHECK_EQUAL(id->Get(), 123);

// 	auto name = (MsgpackValue<char *> *)valuesWoInstance.GetField("name");
// 	CHECK_FALSE(name == NULL);
// 	STRCMP_EQUAL(name->Get(), "Tomato");

// 	auto blob = (MsgpackValue<TMsgpackRawData> *)valuesWoInstance.GetField("blob");
// 	CHECK_FALSE(blob == NULL);
// 	STRCMP_EQUAL((char *)((TMsgpackRawData)(blob->Get())).Data, "ABCDEFGHIJKLMNOPQR");

// 	auto notExistsValue = (MsgpackValue<uint32_t> *)valuesWoInstance.GetField("notExistsValue");
// 	CHECK_TRUE(notExistsValue == NULL);
// 	valuesWoInstance.EndTryStringParse(doc);
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Values_Without_Instance_WriteTo_Test) {
// 	char buffer[2048];
// 	ValuesWoInstance valuesWoInstance(1657052789, "Tomato", {(uint8_t *)"ABCDEFGHIJKLMNOPQR", strlen("ABCDEFGHIJKLMNOPQR")});
// 	valuesWoInstance.WriteToString(buffer, sizeof(buffer));

// 	STRCMP_EQUAL(buffer, "{\"id\":1657052789,\"name\":\"Tomato\",\"blob\":\"ABCDEFGHIJKLMNOPQR\"}");
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Validate_Test) {
// 	auto userDto = new UserDto();
// 	CHECK_TRUE(userDto->Validate());
// 	userDto->Role.Set(1000);
// 	CHECK_FALSE(userDto->Validate());
// 	CHECK_TRUE(userDto->TryStringParse("{\"name\":\"Joe Doe\",\"role\":999}"));
// 	CHECK_FALSE(userDto->TryStringParse("{\"name\":\"Joe Doe\",\"role\":1000}"));
// 	delete userDto;
// }

// class SetValueObjectDto : public MsgpackObject {
//   public:
// 	MsgpackValue<int> Id;
// 	MsgpackValue<MsgpackArrayBase *> Goods;
// 	MsgpackValue<MsgpackObject *> User;
// 	GoodsList goodsList;
// 	UserDto userDto;

// 	SetValueObjectDto(int id = {}, char *userName = {}, TUserRole userRole = {})
// 		: Id(this, "id", id),				//
// 		  Goods(this, "goods", &goodsList), //
// 		  userDto(userName, userRole),		//
// 		  User(this, "user", &userDto){};
// };

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_ArrayValue_Test) {
// 	SetValueObjectDto testDto(1657058000, "Joe Doe", TUserRole::uViewer);
// 	testDto.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
// 	testDto.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));
// 	testDto.goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2));
// 	testDto.goodsList.Add(new GoodsDto(4, 1657055789, "Keyboards", "K4-100", 358.25, 648.2));
// 	CHECK_EQUAL(testDto.goodsList.Size(), 4);

// 	GoodsList newGoodsList;
// 	newGoodsList.Add(new GoodsDto(100, 1111, "Keyboards-111", "K111-100", 1158.25, 1148.2));
// 	newGoodsList.Add(new GoodsDto(200, 2222, "Keyboards-222", "K222-100", 22158.25, 22448.2));

// 	testDto.Goods.Set(&newGoodsList);

// 	CHECK_EQUAL(testDto.goodsList.Size(), 2);
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Id.Get(), 100);
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1111);
// 	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Group.Get(), "Keyboards-111");
// 	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Name.Get(), "K111-100");
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Price.Get(), 1158.25);
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Quantity.Get(), 1148.2);

// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Id.Get(), 200);
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Created.Get(), 2222);
// 	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Group.Get(), "Keyboards-222");
// 	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K222-100");
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Price.Get(), 22158.25);
// 	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Quantity.Get(), 22448.2);
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_ObjectValue_Test) {
// 	SetValueObjectDto testDto(1657058000, "Joe Doe", TUserRole::uViewer);

// 	UserDto userDto("User 1", TUserRole::uAdmin);

// 	testDto.User.Set(&userDto);
// 	STRCMP_EQUAL(testDto.userDto.Name.Get(), "User 1");
// 	CHECK_EQUAL(testDto.userDto.Role.Get(), TUserRole::uAdmin);
// }

// class NullValueObjectDto : public MsgpackObject {
//   public:
// 	MsgpackValue<int> Id;
// 	MsgpackValue<MsgpackArrayBase *> Goods;
// 	MsgpackValue<MsgpackObject *> User;

// 	NullValueObjectDto(int id = {})
// 		: Id(this, "id", id),	//
// 		  Goods(this, "goods"), //
// 		  User(this, "user"){};
// };

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_Nulled_ArrayValue_Test) {
// 	NullValueObjectDto testDto(1657058000);

// 	GoodsList newGoodsList;
// 	newGoodsList.Add(new GoodsDto(100, 1111, "Keyboards-111", "K111-100", 1158.25, 1148.2));
// 	newGoodsList.Add(new GoodsDto(200, 2222, "Keyboards-222", "K222-100", 22158.25, 22448.2));

// 	testDto.Goods.Set(&newGoodsList);

// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Size(), 2);
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Id.Get(), 100);
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Created.Get(), 1111);
// 	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Group.Get(), "Keyboards-111");
// 	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Name.Get(), "K111-100");
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Price.Get(), 1158.25);
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Quantity.Get(), 1148.2);

// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Id.Get(), 200);
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Created.Get(), 2222);
// 	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Group.Get(), "Keyboards-222");
// 	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Name.Get(), "K222-100");
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Price.Get(), 22158.25);
// 	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Quantity.Get(), 22448.2);
// }

// TEST(MsgpackObjectTestsGroup, MsgpackObject_Update_Nulled_ObjectValue_Test) {
// 	NullValueObjectDto testDto(1657058000);

// 	UserDto userDto("User 1", TUserRole::uAdmin);

// 	testDto.User.Set(&userDto);
// 	STRCMP_EQUAL(((UserDto *)testDto.User.Get())->Name.Get(), "User 1");
// 	CHECK_EQUAL(((UserDto *)testDto.User.Get())->Role.Get(), TUserRole::uAdmin);
// }