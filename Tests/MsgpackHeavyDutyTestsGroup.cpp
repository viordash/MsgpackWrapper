
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <vector>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(MsgpackHeavyDutyTestsGroup){void setup(){} void teardown(){}};

static char *strDuplicate(const char *src, size_t len = 0) {
	if (src == NULL) { return NULL; }
	if (len == 0) { len = strlen(src); }
	char *dest = new char[len + 1];
	memcpy(dest, src, len);
	dest[len] = 0;
	return dest;
}

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : public MsgpackObject {
  public:
	MsgpackValue<char *> Name;
	MsgpackValue<uint32_t> Role;

	UserDto(const char *name = {}, const TUserRole role = {})
		: Name(this, 0, name), //
		  Role(this, 1, role){};
};

typedef struct {
	char *name;
	TUserRole role;
} TUserDto;

static void SerializeUserDto(msgpack_packer *packer, const TUserDto *pUserDto) {
	msgpack_pack_array(packer, 2);
	auto sLen = strlen(pUserDto->name);
	msgpack_pack_str(packer, sLen);
	msgpack_pack_str_body(packer, pUserDto->name, sLen);
	msgpack_pack_uint32(packer, pUserDto->role);
}

static TUserDto *DeserializeUserDto(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }
	if (deserialized->via.array.size != 2) { return NULL; }

	msgpack_object name = deserialized->via.array.ptr[0];
	if (name.type != MSGPACK_OBJECT_STR) { return NULL; }

	msgpack_object role = deserialized->via.array.ptr[1];
	if (role.type != MSGPACK_OBJECT_POSITIVE_INTEGER) { return NULL; }

	auto userDto = new TUserDto();
	userDto->name = strDuplicate(name.via.str.ptr, name.via.str.size);
	userDto->role = (TUserRole)role.via.u64;
	return userDto;
}

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

	GoodsDto(const int id = {}, const uint32_t created = {}, const char *group = {}, const char *name = {}, const float price = {}, const double quantity = {}, const bool deleted = {},
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

typedef struct {
	int id;
	uint32_t created;
	char *group;
	char *name;
	float price;
	double quantity;
	bool deleted;
	char *storeName;
} TGoodsDto;

static void SerializeGoodsDto(msgpack_packer *packer, const TGoodsDto *pGoodsDto) {
	msgpack_pack_array(packer, 8);

	msgpack_pack_int(packer, pGoodsDto->id);
	msgpack_pack_uint32(packer, pGoodsDto->created);

	auto sLen = strlen(pGoodsDto->group);
	msgpack_pack_str(packer, sLen);
	msgpack_pack_str_body(packer, pGoodsDto->group, sLen);

	sLen = strlen(pGoodsDto->name);
	msgpack_pack_str(packer, sLen);
	msgpack_pack_str_body(packer, pGoodsDto->name, sLen);

	msgpack_pack_float(packer, pGoodsDto->price);
	msgpack_pack_double(packer, pGoodsDto->quantity);
	if (pGoodsDto->deleted) {
		msgpack_pack_true(packer);
	} else {
		msgpack_pack_false(packer);
	}

	sLen = strlen(pGoodsDto->storeName);
	msgpack_pack_str(packer, sLen);
	msgpack_pack_str_body(packer, pGoodsDto->storeName, sLen);
}

static TGoodsDto *DeserializeGoodsDto(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }
	if (deserialized->via.array.size != 8) { return NULL; }

	msgpack_object id = deserialized->via.array.ptr[0];
	if (id.type != MSGPACK_OBJECT_POSITIVE_INTEGER && id.type != MSGPACK_OBJECT_NEGATIVE_INTEGER) { return NULL; }
	msgpack_object created = deserialized->via.array.ptr[1];
	if (created.type != MSGPACK_OBJECT_POSITIVE_INTEGER) { return NULL; }
	msgpack_object group = deserialized->via.array.ptr[2];
	if (group.type != MSGPACK_OBJECT_STR) { return NULL; }
	msgpack_object name = deserialized->via.array.ptr[3];
	if (name.type != MSGPACK_OBJECT_STR) { return NULL; }
	msgpack_object price = deserialized->via.array.ptr[4];
	if (price.type != MSGPACK_OBJECT_FLOAT32) { return NULL; }
	msgpack_object quantity = deserialized->via.array.ptr[5];
	if (quantity.type != MSGPACK_OBJECT_FLOAT64) { return NULL; }
	msgpack_object deleted = deserialized->via.array.ptr[6];
	if (deleted.type != MSGPACK_OBJECT_BOOLEAN) { return NULL; }
	msgpack_object storeName = deserialized->via.array.ptr[7];
	if (storeName.type != MSGPACK_OBJECT_STR) { return NULL; }

	auto goodsDto = new TGoodsDto();
	goodsDto->id = (int)id.via.i64;
	goodsDto->created = (uint32_t)created.via.u64;
	goodsDto->group = strDuplicate(group.via.str.ptr, group.via.str.size);
	goodsDto->name = strDuplicate(name.via.str.ptr, name.via.str.size);
	goodsDto->price = (float)price.via.f64;
	goodsDto->quantity = quantity.via.f64;
	goodsDto->deleted = deleted.via.boolean;
	goodsDto->storeName = strDuplicate(storeName.via.str.ptr, storeName.via.str.size);
	return goodsDto;
}

class GoodsList : public MsgpackObjectsArray {
  public:
	bool Validate(MsgpackObject *item) override { return item->Validate(); }
	MsgpackObject *CreateItem() override { return new GoodsDto(); }
};

static void SerializeGoodsList(msgpack_packer *packer, std::vector<TGoodsDto *> *goods) {
	msgpack_pack_array(packer, goods->size());
	for (const auto &item : *goods) { //
		SerializeGoodsDto(packer, item);
	}
}

static std::vector<TGoodsDto *> *DeserializeGoodsList(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }

	auto goodsList = new std::vector<TGoodsDto *>();
	goodsList->reserve(deserialized->via.array.size);
	size_t i = 0;
	while (i < deserialized->via.array.size) {
		msgpack_object object = deserialized->via.array.ptr[i];
		TGoodsDto *goods = NULL;
		if (object.type == MSGPACK_OBJECT_ARRAY) { goods = DeserializeGoodsDto(&object); }

		if (goods == NULL) {
			for (const auto &item : *goodsList) { delete item; }
			delete goodsList;
			return NULL;
		}
		goodsList->push_back(goods);
		i++;
	}
	goodsList->shrink_to_fit();
	return goodsList;
}

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
};

typedef struct {
	char *supplier;
	uint32_t dateTime;
	std::vector<TGoodsDto *> *goods;
	TUserDto *user;
} TOrderDto;

static void SerializeOrderDto(msgpack_packer *packer, const TOrderDto *pOrderDto) {
	msgpack_pack_array(packer, 4);
	auto sLen = strlen(pOrderDto->supplier);
	msgpack_pack_str(packer, sLen);
	msgpack_pack_str_body(packer, pOrderDto->supplier, sLen);
	msgpack_pack_uint32(packer, pOrderDto->dateTime);

	SerializeGoodsList(packer, pOrderDto->goods);
	SerializeUserDto(packer, pOrderDto->user);
}

static TOrderDto *DeserializeOrderDto(msgpack_object *deserialized) {

	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }
	if (deserialized->via.array.size != 4) { return NULL; }

	msgpack_object supplier = deserialized->via.array.ptr[0];
	if (supplier.type != MSGPACK_OBJECT_STR) { return NULL; }

	msgpack_object dateTime = deserialized->via.array.ptr[1];
	if (dateTime.type != MSGPACK_OBJECT_POSITIVE_INTEGER) { return NULL; }

	msgpack_object goods = deserialized->via.array.ptr[2];
	if (goods.type != MSGPACK_OBJECT_ARRAY) { return NULL; }

	msgpack_object user = deserialized->via.array.ptr[3];
	if (user.type != MSGPACK_OBJECT_ARRAY) { return NULL; }

	auto orderDto = new TOrderDto();
	orderDto->supplier = strDuplicate(supplier.via.str.ptr, supplier.via.str.size);
	orderDto->dateTime = (uint32_t)dateTime.via.u64;
	orderDto->goods = DeserializeGoodsList(&goods);
	orderDto->user = DeserializeUserDto(&user);
	return orderDto;
}

class OrdersList : public MsgpackObjectsArray {
  public:
	bool Validate(MsgpackObject *item) override { return item->Validate(); }
	MsgpackObject *CreateItem() override { return new OrderDto(); }
};

static void SerializeOrdersList(msgpack_packer *packer, std::vector<TOrderDto *> *orders) {
	msgpack_pack_array(packer, orders->size());
	for (const auto &item : *orders) { //
		SerializeOrderDto(packer, item);
	}
}

static std::vector<TOrderDto *> *DeserializeOrdersList(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }

	auto ordersList = new std::vector<TOrderDto *>();
	ordersList->reserve(deserialized->via.array.size);
	size_t i = 0;
	while (i < deserialized->via.array.size) {
		msgpack_object object = deserialized->via.array.ptr[i];
		TOrderDto *order = NULL;
		if (object.type == MSGPACK_OBJECT_ARRAY) { order = DeserializeOrderDto(&object); }

		if (order == NULL) {
			for (const auto &item : *ordersList) { delete item; }
			delete ordersList;
			return NULL;
		}
		ordersList->push_back(order);
		i++;
	}
	ordersList->shrink_to_fit();
	return ordersList;
}

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

typedef struct {
	uint64_t id;
	char *name;
	TMsgpackRawData blob;
	std::vector<TOrderDto *> *orders;
} TCustomerDto;

static void SerializeCustomerDto(msgpack_packer *packer, const TCustomerDto *customerDto) {
	msgpack_pack_array(packer, 4);
	msgpack_pack_int64(packer, customerDto->id);

	auto sLen = strlen(customerDto->name);
	msgpack_pack_str(packer, sLen);
	msgpack_pack_str_body(packer, customerDto->name, sLen);

	msgpack_pack_v4raw(packer, customerDto->blob.Size);
	msgpack_pack_v4raw_body(packer, customerDto->blob.Data, customerDto->blob.Size);

	SerializeOrdersList(packer, customerDto->orders);
}

static TCustomerDto *DeserializeCustomerDto(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }
	if (deserialized->via.array.size != 4) { return NULL; }

	msgpack_object id = deserialized->via.array.ptr[0];
	if (id.type != MSGPACK_OBJECT_POSITIVE_INTEGER) { return NULL; }

	msgpack_object name = deserialized->via.array.ptr[1];
	if (name.type != MSGPACK_OBJECT_STR) { return NULL; }

	msgpack_object blob = deserialized->via.array.ptr[2];
	if (blob.type != MSGPACK_OBJECT_STR) { return NULL; }

	msgpack_object orders = deserialized->via.array.ptr[3];
	if (orders.type != MSGPACK_OBJECT_ARRAY) { return NULL; }

	auto customerDto = new TCustomerDto();
	customerDto->id = (uint64_t)id.via.u64;
	customerDto->name = strDuplicate(name.via.str.ptr, name.via.str.size);
	customerDto->blob = {(uint8_t *)blob.via.str.ptr, blob.via.str.size};
	customerDto->orders = DeserializeOrdersList(&orders);
	return customerDto;
}

class CustomerList : public MsgpackObjectsArray {
  public:
	bool Validate(MsgpackObject *item) override { return item->Validate(); }
	MsgpackObject *CreateItem() override { return new CustomerDto(); }
};

static void SerializeCustomerList(msgpack_packer *packer, std::vector<TCustomerDto *> *customers) {
	msgpack_pack_array(packer, customers->size());
	for (const auto &item : *customers) { //
		SerializeCustomerDto(packer, item);
	}
}

static std::vector<TCustomerDto *> *DeserializeCustomerList(msgpack_object *deserialized) {
	if (deserialized->type != MSGPACK_OBJECT_ARRAY) { return NULL; }

	auto customerList = new std::vector<TCustomerDto *>();
	customerList->reserve(deserialized->via.array.size);
	size_t i = 0;
	while (i < deserialized->via.array.size) {
		msgpack_object object = deserialized->via.array.ptr[i];
		TCustomerDto *customer = NULL;
		if (object.type == MSGPACK_OBJECT_ARRAY) { customer = DeserializeCustomerDto(&object); }

		if (customer == NULL) {
			for (const auto &item : *customerList) { delete item; }
			delete customerList;
			return NULL;
		}
		customerList->push_back(customer);
		i++;
	}
	customerList->shrink_to_fit();
	return customerList;
}

static void *TestParent = NULL;
static char *DirectWriteTestBuffer = NULL;
static void OnReady(void *parent, const char *json, size_t size) {
	TestParent = parent;
	DirectWriteTestBuffer = new char[size + 1];
	memcpy(DirectWriteTestBuffer, json, size);
	DirectWriteTestBuffer[size] = 0;
}

const int perfTestItemsCount = 1'000;
int picture[] = {0x66, 0x00, 0x67, 0x67, 0x67, 0x00, 0x68, 0x68, 0x68, 0x00, 0x69, 0x69, 0x69, 0x00, 0x6A, 0x6A};

static uint64_t testFillArray(CustomerList *customerList) {
	auto start = std::chrono::high_resolution_clock::now();
	customerList->Reserve(perfTestItemsCount);
	for (int i = 0; i < perfTestItemsCount; i++) {
		picture[0] = i;
		customerList->Add(new CustomerDto(12345678901100LL + i, "Viordash", {(uint8_t *)picture, sizeof(picture)}));
		auto customerDto = customerList->Item<CustomerDto *>(i);
		for (int k = 0; k < (perfTestItemsCount / 100) + 1; k++) {
			customerDto->ordersList.Add(new OrderDto("Dell1", 165700 + i + k, "Joe Doe", TUserRole::uViewer));

			auto orderDto = customerDto->ordersList.Item<OrderDto *>(k);
			for (int m = 0; m < (perfTestItemsCount / 1000) + 1; m++) { //
				orderDto->goodsList.Add(
					new GoodsDto(1, 16570 + i + k + m, "Keyboards", "K1-100", k * 2.5F, k * 0.1, m % 2 == 0, "Chargoggagoggmanchauggagoggchaubunagungamaugg 0123456789012345678901234567890123456789"));
			}
		}
	}
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static uint64_t testArrayWriteTo(CustomerList *customerList, size_t *size) {
	auto start = std::chrono::high_resolution_clock::now();
	*size = customerList->DirectWriteTo(0, OnReady);
	CHECK(*size > 0);
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static uint64_t testArrayTryParse(CustomerList *customerList, const char *jsonStr, size_t size) {
	auto start = std::chrono::high_resolution_clock::now();
	CHECK(customerList->TryParse(jsonStr, size));
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static void DeleteCustomerList(std::vector<TCustomerDto *> *customerList) {
	for (const auto customer : *customerList) {
		delete[] customer->name;
		for (const auto order : *customer->orders) {
			delete[] order->supplier;
			delete[] order->user->name;
			delete order->user;
			for (const auto goods : *order->goods) {
				delete[] goods->group;
				delete[] goods->name;
				delete[] goods->storeName;
				delete goods;
			}
			delete order->goods;
			delete order;
		}
		delete customer->orders;
		delete customer;
	}
	delete customerList;
}

static uint64_t testFillRapidArray(std::vector<TCustomerDto *> *customerList) {
	auto start = std::chrono::high_resolution_clock::now();
	customerList->reserve(perfTestItemsCount);
	for (int i = 0; i < perfTestItemsCount; i++) {
		picture[0] = i;
		auto customer = new TCustomerDto();
		customer->id = 12345678901100LL + i;
		customer->name = strDuplicate("Viordash");
		customer->blob = {(uint8_t *)picture, sizeof(picture)};
		customer->orders = new std::vector<TOrderDto *>();
		customerList->push_back(customer);

		auto customerDto = (*customerList)[i];
		for (int k = 0; k < (perfTestItemsCount / 100) + 1; k++) {
			auto order = new TOrderDto();
			order->supplier = strDuplicate("Dell1");
			order->dateTime = 165700 + i + k;
			order->user = new TUserDto();
			order->user->name = strDuplicate("Joe Doe");
			order->user->role = TUserRole::uViewer;

			order->goods = new std::vector<TGoodsDto *>();
			customerDto->orders->push_back(order);

			auto orderDto = (*customerDto->orders)[k];
			for (int m = 0; m < (perfTestItemsCount / 1000) + 1; m++) { //
				auto goods = new TGoodsDto();
				goods->id = 1;
				goods->created = 16570 + i + k + m;
				goods->group = strDuplicate("Keyboards");
				goods->name = strDuplicate("K1-100");
				goods->price = k * 2.5F;
				goods->quantity = k * 0.1;
				goods->deleted = m % 2 == 0;
				goods->storeName = strDuplicate("Chargoggagoggmanchauggagoggchaubunagungamaugg 0123456789012345678901234567890123456789");
				orderDto->goods->push_back(goods);
			}
		}
	}
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static char *RapidWriteTestBuffer = NULL;
static uint64_t testRapidArrayWriteTo(std::vector<TCustomerDto *> *customerList, size_t *size) {
	auto start = std::chrono::high_resolution_clock::now();

	msgpack_sbuffer sbuf;
	msgpack_packer packer;
	msgpack_sbuffer_init(&sbuf);
	msgpack_packer_init(&packer, &sbuf, msgpack_sbuffer_write);

	SerializeCustomerList(&packer, customerList);

	*size = sbuf.size;
	CHECK(*size > 0);
	RapidWriteTestBuffer = new char[sbuf.size + 1];
	memcpy(RapidWriteTestBuffer, sbuf.data, sbuf.size);
	RapidWriteTestBuffer[sbuf.size] = 0;
	msgpack_sbuffer_destroy(&sbuf);

	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static uint64_t testRapidArrayTryParse(const char *jsonStr, size_t size) {
	auto start = std::chrono::high_resolution_clock::now();

	msgpack_unpacked *unpacked = new msgpack_unpacked();
	msgpack_unpacked_init(unpacked);
	msgpack_unpack_return ret = msgpack_unpack_next(unpacked, jsonStr, size, NULL);
	CHECK(ret == MSGPACK_UNPACK_SUCCESS);

	auto customerList = DeserializeCustomerList(&unpacked->data);
	CHECK(customerList != NULL);
	auto finish = std::chrono::high_resolution_clock::now();
	DeleteCustomerList(customerList);
	msgpack_unpacked_destroy(unpacked);
	delete unpacked;
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

TEST(MsgpackHeavyDutyTestsGroup, MsgpackObject_Perfomance_Test) {
	uint64_t durationAdd = 0;
	uint64_t durationDirectWriteTo = 0;
	uint64_t durationTryParse = 0;

	uint64_t nativeDurationAdd = 0;
	uint64_t nativeDurationDirectWriteTo = 0;
	uint64_t nativeDurationTryParse = 0;

	size_t size = 0;
	size_t nativeSize = 0;

	const int avgCount = 10;
	for (size_t a = 0; a < avgCount; a++) {

		auto customerList = new CustomerList();
		auto nativeCustomerList = new std::vector<TCustomerDto *>();

		durationAdd += testFillArray(customerList);
		nativeDurationAdd += testFillRapidArray(nativeCustomerList);

		DirectWriteTestBuffer = NULL;
		RapidWriteTestBuffer = NULL;
		durationDirectWriteTo += testArrayWriteTo(customerList, &size);
		nativeDurationDirectWriteTo += testRapidArrayWriteTo(nativeCustomerList, &nativeSize);

		DeleteCustomerList(nativeCustomerList);
		delete customerList;

		customerList = new CustomerList();
		durationTryParse += testArrayTryParse(customerList, DirectWriteTestBuffer, size);
		nativeDurationTryParse += testRapidArrayTryParse(RapidWriteTestBuffer, nativeSize);
		delete customerList;

		delete[] RapidWriteTestBuffer;
		delete[] DirectWriteTestBuffer;
	}
	char text[512];
	sprintf(text, "wrapper 'Add' dur(mean %u): %.02f us", avgCount, durationAdd / avgCount / 1000.0);
	UT_PRINT(text);
	sprintf(text, "native   'Add' dur(mean %u): %.02f us", avgCount, nativeDurationAdd / avgCount / 1000.0);
	UT_PRINT(text);

	sprintf(text, "wrapper 'WriteTo' size: %zu, dur(mean %u): %.02f us", size, avgCount, durationDirectWriteTo / avgCount / 1000.0);
	UT_PRINT(text);
	sprintf(text, "native   'WriteTo' size: %zu, dur(mean %u): %.02f us", nativeSize, avgCount, nativeDurationDirectWriteTo / avgCount / 1000.0);
	UT_PRINT(text);

	sprintf(text, "wrapper TryParse dur(mean %u): %.02f us", avgCount, durationTryParse / avgCount / 1000.0);
	UT_PRINT(text);
	sprintf(text, "native   TryParse dur(mean %u): %.02f us", avgCount, nativeDurationTryParse / avgCount / 1000.0);
	UT_PRINT(text);

	sprintf(text, "wrapper to native ratio 'Add':%.03f, 'WriteTo':%.03f, 'TryParse':%.03f", (double)durationAdd / (double)nativeDurationAdd,
			(double)durationDirectWriteTo / (double)nativeDurationDirectWriteTo, (double)durationTryParse / (double)nativeDurationTryParse);
	UT_PRINT(text);

	CHECK_EQUAL(size, nativeSize);
	CHECK_FALSE(durationAdd > nativeDurationAdd * 6);
	CHECK_FALSE(durationDirectWriteTo > nativeDurationDirectWriteTo * 6);
	CHECK_FALSE(durationTryParse > nativeDurationTryParse * 6);
}