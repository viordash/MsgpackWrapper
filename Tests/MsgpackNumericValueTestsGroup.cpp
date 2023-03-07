
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MsgpackWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

// TEST_GROUP(MsgpackNumericValueGroup){void setup(){} void teardown(){}};

// TEST(MsgpackNumericValueGroup, MsgpackField_Equals_By_Name_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<unsigned int> testable1(&container, "test", 100);
// 	MsgpackValue<unsigned int> testable01(&container, "test", 100);
// 	MsgpackValue<unsigned int> testable02(&container, "other", 100);

// 	CHECK_TRUE(testable1 == testable01);
// 	testable01.Set(testable01.Get() + 1);
// 	CHECK_FALSE(testable1 == testable01);
// 	testable1.Set(testable1.Get() + 1);
// 	CHECK_TRUE(testable1 == testable01);
// 	CHECK_FALSE(testable1 == testable02);
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_SetValue_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<unsigned int> testable1(&container, "test");
// 	MsgpackValue<uint32_t> testable2(&container, "test");
// 	MsgpackValue<uint16_t> testable3(&container, "test");
// 	MsgpackValue<uint8_t> testable4(&container, "test");
// 	testable1.Set(0xFFFFFFFF);
// 	testable2.Set(0xFFFFFFFF);
// 	testable3.Set(0xFFFFFFFF);
// 	testable4.Set(0xFFFFFFFF);

// 	CHECK_EQUAL(testable1.Get(), 4294967295);
// 	CHECK_EQUAL(testable2.Get(), 4294967295);
// 	CHECK_EQUAL(testable3.Get(), 65535);
// 	CHECK_EQUAL(testable4.Get(), 255);
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<unsigned int> testable1(&container, "test");
// 	MsgpackValue<uint32_t> testable2(&container, "test");
// 	MsgpackValue<uint16_t> testable3(&container, "test");
// 	MsgpackValue<uint8_t> testable4(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":153000}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), 153000);
// 	CHECK_EQUAL(testable2.Get(), 153000);
// 	CHECK_EQUAL(testable3.Get(), 21928);
// 	CHECK_EQUAL(testable4.Get(), 168);

// 	doc.Parse("{\"testOther\":42}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// 	CHECK_FALSE(testable2.TryParse(&doc));
// 	CHECK_FALSE(testable3.TryParse(&doc));
// 	CHECK_FALSE(testable4.TryParse(&doc));

// 	doc.Parse("{\"test\":null}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// 	CHECK_FALSE(testable2.TryParse(&doc));
// 	CHECK_FALSE(testable3.TryParse(&doc));
// 	CHECK_FALSE(testable4.TryParse(&doc));
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<unsigned int> testable1(&container, "test", 19);
// 	MsgpackValue<uint32_t> testable2(&container, "test", 20);
// 	MsgpackValue<uint16_t> testable3(&container, "test", 21);
// 	MsgpackValue<uint8_t> testable4(&container, "test", 22);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable3.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable4.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_Equals_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<unsigned int> testable1(&container, "test", 100);
// 	MsgpackValue<unsigned int> testable01(&container, "test", 100);
// 	MsgpackValue<unsigned int> testable001(&container, "testOtherField", 100);

// 	MsgpackValue<uint32_t> testable2(&container, "test", 101);
// 	MsgpackValue<uint32_t> testable02(&container, "test", 101);
// 	MsgpackValue<uint32_t> testable002(&container, "testOtherField", 101);

// 	MsgpackValue<uint16_t> testable3(&container, "test", 102);
// 	MsgpackValue<uint16_t> testable03(&container, "test", 102);
// 	MsgpackValue<uint16_t> testable003(&container, "testOtherField", 102);

// 	MsgpackValue<uint8_t> testable4(&container, "test", 103);
// 	MsgpackValue<uint8_t> testable04(&container, "test", 103);
// 	MsgpackValue<uint8_t> testable004(&container, "testOtherField", 103);

// 	CHECK_TRUE(testable1 == testable01);
// 	CHECK_FALSE(testable1 != testable01);
// 	CHECK_TRUE(testable1.Equals(&testable01));
// 	CHECK_TRUE(testable01.Equals(&testable1));
// 	testable01.Set(testable01.Get() + 1);
// 	CHECK_TRUE(testable1 != testable01);
// 	CHECK_FALSE(testable1 == testable01);
// 	CHECK_FALSE(testable1.Equals(&testable01));
// 	CHECK_FALSE(testable01.Equals(&testable1));
// 	CHECK_FALSE(testable001 == testable1);
// 	CHECK_FALSE(testable1 == testable001);
// 	CHECK_FALSE(testable001.Equals(&testable1));
// 	CHECK_FALSE(testable1.Equals(&testable001));

// 	CHECK_TRUE(testable2 == testable02);
// 	CHECK_FALSE(testable2 != testable02);
// 	CHECK_TRUE(testable2.Equals(&testable02));
// 	CHECK_TRUE(testable02.Equals(&testable2));
// 	testable02.Set(testable02.Get() + 1);
// 	CHECK_TRUE(testable2 != testable02);
// 	CHECK_FALSE(testable2 == testable02);
// 	CHECK_FALSE(testable2.Equals(&testable02));
// 	CHECK_FALSE(testable02.Equals(&testable2));
// 	CHECK_FALSE(testable002 == testable2);
// 	CHECK_FALSE(testable2 == testable002);
// 	CHECK_FALSE(testable002.Equals(&testable2));
// 	CHECK_FALSE(testable2.Equals(&testable002));

// 	CHECK_TRUE(testable3 == testable03);
// 	CHECK_FALSE(testable3 != testable03);
// 	CHECK_TRUE(testable3.Equals(&testable03));
// 	CHECK_TRUE(testable03.Equals(&testable3));
// 	testable03.Set(testable03.Get() + 1);
// 	CHECK_TRUE(testable3 != testable03);
// 	CHECK_FALSE(testable3 == testable03);
// 	CHECK_FALSE(testable3.Equals(&testable03));
// 	CHECK_FALSE(testable03.Equals(&testable3));
// 	CHECK_FALSE(testable003 == testable3);
// 	CHECK_FALSE(testable3 == testable003);
// 	CHECK_FALSE(testable003.Equals(&testable3));
// 	CHECK_FALSE(testable3.Equals(&testable003));

// 	CHECK_TRUE(testable4 == testable04);
// 	CHECK_FALSE(testable4 != testable04);
// 	CHECK_TRUE(testable4.Equals(&testable04));
// 	CHECK_TRUE(testable04.Equals(&testable4));
// 	testable04.Set(testable04.Get() + 1);
// 	CHECK_TRUE(testable4 != testable04);
// 	CHECK_FALSE(testable4 == testable04);
// 	CHECK_FALSE(testable4.Equals(&testable04));
// 	CHECK_FALSE(testable04.Equals(&testable4));
// 	CHECK_FALSE(testable004 == testable4);
// 	CHECK_FALSE(testable4 == testable004);
// 	CHECK_FALSE(testable004.Equals(&testable4));
// 	CHECK_FALSE(testable4.Equals(&testable004));
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_CloneTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<unsigned int> testable1(&container, "test", 100);
// 	MsgpackValue<uint32_t> testable2(&container, "test", 101);
// 	MsgpackValue<uint16_t> testable3(&container, "test", 102);
// 	MsgpackValue<uint8_t> testable4(&container, "test", 103);

// 	MsgpackValue<unsigned int> clone1(&container, "test");
// 	MsgpackValue<uint32_t> clone2(&container, "test");
// 	MsgpackValue<uint16_t> clone3(&container, "test");
// 	MsgpackValue<uint8_t> clone4(&container, "test");

// 	testable1.CloneTo((MsgpackValueBase *)&clone1);
// 	testable2.CloneTo((MsgpackValueBase *)&clone2);
// 	testable3.CloneTo((MsgpackValueBase *)&clone3);
// 	testable4.CloneTo((MsgpackValueBase *)&clone4);

// 	CHECK_EQUAL(clone1.Get(), 100);
// 	CHECK_EQUAL(clone2.Get(), 101);
// 	CHECK_EQUAL(clone3.Get(), 102);
// 	CHECK_EQUAL(clone4.Get(), 103);
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_SetValue_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<int> testable1(&container, "test");
// 	MsgpackValue<int32_t> testable2(&container, "test");
// 	MsgpackValue<int16_t> testable3(&container, "test");
// 	MsgpackValue<int8_t> testable4(&container, "test");
// 	testable1.Set(0xFFFFFFFF);
// 	testable2.Set(0xFFFFFFFF);
// 	testable3.Set(0xFFFFFFFF);
// 	testable4.Set(0xFFFFFFFF);

// 	CHECK_EQUAL(testable1.Get(), -1);
// 	CHECK_EQUAL(testable2.Get(), -1);
// 	CHECK_EQUAL(testable3.Get(), -1);
// 	CHECK_EQUAL(testable4.Get(), -1);
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<int> testable1(&container, "test");
// 	MsgpackValue<int32_t> testable2(&container, "test");
// 	MsgpackValue<int16_t> testable3(&container, "test");
// 	MsgpackValue<int8_t> testable4(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":153000}");
// 	CHECK(testable1.TryParse(&doc));
// 	CHECK(testable2.TryParse(&doc));
// 	CHECK(testable3.TryParse(&doc));
// 	CHECK(testable4.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), 153000);
// 	CHECK_EQUAL(testable2.Get(), 153000);
// 	CHECK_EQUAL(testable3.Get(), 21928);
// 	CHECK_EQUAL(testable4.Get(), -88);

// 	doc.Parse("{\"testOther\":42}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// 	CHECK_FALSE(testable2.TryParse(&doc));
// 	CHECK_FALSE(testable3.TryParse(&doc));
// 	CHECK_FALSE(testable4.TryParse(&doc));

// 	doc.Parse("{\"test\":null}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// 	CHECK_FALSE(testable2.TryParse(&doc));
// 	CHECK_FALSE(testable3.TryParse(&doc));
// 	CHECK_FALSE(testable4.TryParse(&doc));
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<int> testable1(&container, "test", 19);
// 	MsgpackValue<int32_t> testable2(&container, "test", 20);
// 	MsgpackValue<int16_t> testable3(&container, "test", 21);
// 	MsgpackValue<int8_t> testable4(&container, "test", 22);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable3.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable4.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_Equals_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<int> testable1(&container, "test", 100);
// 	MsgpackValue<int> testable01(&container, "test", 100);
// 	MsgpackValue<int> testable001(&container, "testOtherField", 100);

// 	MsgpackValue<int32_t> testable2(&container, "test", 101);
// 	MsgpackValue<int32_t> testable02(&container, "test", 101);
// 	MsgpackValue<int32_t> testable002(&container, "testOtherField", 101);

// 	MsgpackValue<int16_t> testable3(&container, "test", 102);
// 	MsgpackValue<int16_t> testable03(&container, "test", 102);
// 	MsgpackValue<int16_t> testable003(&container, "testOtherField", 102);

// 	MsgpackValue<int8_t> testable4(&container, "test", 103);
// 	MsgpackValue<int8_t> testable04(&container, "test", 103);
// 	MsgpackValue<int8_t> testable004(&container, "testOtherField", 103);

// 	CHECK_TRUE(testable1 == testable01);
// 	CHECK_FALSE(testable1 != testable01);
// 	CHECK_TRUE(testable1.Equals(&testable01));
// 	CHECK_TRUE(testable01.Equals(&testable1));
// 	testable01.Set(testable01.Get() + 1);
// 	CHECK_TRUE(testable1 != testable01);
// 	CHECK_FALSE(testable1 == testable01);
// 	CHECK_FALSE(testable1.Equals(&testable01));
// 	CHECK_FALSE(testable01.Equals(&testable1));
// 	CHECK_FALSE(testable001 == testable1);
// 	CHECK_FALSE(testable1 == testable001);
// 	CHECK_FALSE(testable001.Equals(&testable1));
// 	CHECK_FALSE(testable1.Equals(&testable001));

// 	CHECK_TRUE(testable2 == testable02);
// 	CHECK_FALSE(testable2 != testable02);
// 	CHECK_TRUE(testable2.Equals(&testable02));
// 	CHECK_TRUE(testable02.Equals(&testable2));
// 	testable02.Set(testable02.Get() + 1);
// 	CHECK_TRUE(testable2 != testable02);
// 	CHECK_FALSE(testable2 == testable02);
// 	CHECK_FALSE(testable2.Equals(&testable02));
// 	CHECK_FALSE(testable02.Equals(&testable2));
// 	CHECK_FALSE(testable002 == testable2);
// 	CHECK_FALSE(testable2 == testable002);
// 	CHECK_FALSE(testable002.Equals(&testable2));
// 	CHECK_FALSE(testable2.Equals(&testable002));

// 	CHECK_TRUE(testable3 == testable03);
// 	CHECK_FALSE(testable3 != testable03);
// 	CHECK_TRUE(testable3.Equals(&testable03));
// 	CHECK_TRUE(testable03.Equals(&testable3));
// 	testable03.Set(testable03.Get() + 1);
// 	CHECK_TRUE(testable3 != testable03);
// 	CHECK_FALSE(testable3 == testable03);
// 	CHECK_FALSE(testable3.Equals(&testable03));
// 	CHECK_FALSE(testable03.Equals(&testable3));
// 	CHECK_FALSE(testable003 == testable3);
// 	CHECK_FALSE(testable3 == testable003);
// 	CHECK_FALSE(testable003.Equals(&testable3));
// 	CHECK_FALSE(testable3.Equals(&testable003));

// 	CHECK_TRUE(testable4 == testable04);
// 	CHECK_FALSE(testable4 != testable04);
// 	CHECK_TRUE(testable4.Equals(&testable04));
// 	CHECK_TRUE(testable04.Equals(&testable4));
// 	testable04.Set(testable04.Get() + 1);
// 	CHECK_TRUE(testable4 != testable04);
// 	CHECK_FALSE(testable4 == testable04);
// 	CHECK_FALSE(testable4.Equals(&testable04));
// 	CHECK_FALSE(testable04.Equals(&testable4));
// 	CHECK_FALSE(testable004 == testable4);
// 	CHECK_FALSE(testable4 == testable004);
// 	CHECK_FALSE(testable004.Equals(&testable4));
// 	CHECK_FALSE(testable4.Equals(&testable004));
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_CloneTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<int> testable1(&container, "test", 100);
// 	MsgpackValue<int32_t> testable2(&container, "test", 101);
// 	MsgpackValue<int16_t> testable3(&container, "test", 102);
// 	MsgpackValue<int8_t> testable4(&container, "test", 103);

// 	MsgpackValue<int> clone1(&container, "test");
// 	MsgpackValue<int32_t> clone2(&container, "test");
// 	MsgpackValue<int16_t> clone3(&container, "test");
// 	MsgpackValue<int8_t> clone4(&container, "test");

// 	testable1.CloneTo((MsgpackValueBase *)&clone1);
// 	testable2.CloneTo((MsgpackValueBase *)&clone2);
// 	testable3.CloneTo((MsgpackValueBase *)&clone3);
// 	testable4.CloneTo((MsgpackValueBase *)&clone4);

// 	CHECK_EQUAL(clone1.Get(), 100);
// 	CHECK_EQUAL(clone2.Get(), 101);
// 	CHECK_EQUAL(clone3.Get(), 102);
// 	CHECK_EQUAL(clone4.Get(), 103);
// }

// /*



// */

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_SetValue_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<bool> testable1(&container, "test");
// 	testable1.Set(0xFFFFFFFF);
// 	CHECK_EQUAL(testable1.Get(), true);
// 	testable1.Set(0);
// 	CHECK_EQUAL(testable1.Get(), false);
// 	testable1.Set(1);
// 	CHECK_EQUAL(testable1.Get(), true);
// 	testable1.Set(false);
// 	CHECK_EQUAL(testable1.Get(), false);
// 	testable1.Set(true);
// 	CHECK_EQUAL(testable1.Get(), true);
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<bool> testable1(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":true}");
// 	CHECK(testable1.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), true);

// 	doc.Parse("{\"test\":null}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<bool> testable1(&container, "test", true);

// 	rapidjson::Document doc;
// 	doc.SetObject();
// 	testable1.WriteToDoc(&doc);
// 	rapidjson::StringBuffer buffer;
// 	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 	doc.Accept(writer);
// 	STRCMP_EQUAL(buffer.GetString(), "{\"test\":true}");
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_Equals_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<bool> testable1(&container, "test", true);
// 	MsgpackValue<bool> testable01(&container, "test", true);
// 	MsgpackValue<bool> testable001(&container, "testOtherField", true);

// 	CHECK_TRUE(testable1 == testable01);
// 	CHECK_FALSE(testable1 != testable01);
// 	CHECK_TRUE(testable1.Equals(&testable01));
// 	CHECK_TRUE(testable01.Equals(&testable1));
// 	testable01.Set(!testable01.Get());
// 	CHECK_TRUE(testable1 != testable01);
// 	CHECK_FALSE(testable1 == testable01);
// 	CHECK_FALSE(testable1.Equals(&testable01));
// 	CHECK_FALSE(testable01.Equals(&testable1));
// 	CHECK_FALSE(testable001 == testable1);
// 	CHECK_FALSE(testable1 == testable001);
// 	CHECK_FALSE(testable001.Equals(&testable1));
// 	CHECK_FALSE(testable1.Equals(&testable001));
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_CloneTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<bool> testable1(&container, "test", true);
// 	MsgpackValue<bool> clone1(&container, "test");

// 	testable1.CloneTo((MsgpackValueBase *)&clone1);

// 	CHECK_EQUAL(clone1.Get(), true);
// }
// /*


// */
// TEST(MsgpackNumericValueGroup, MsgpackFloatField_SetValue_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<float> testable1(&container, "test");
// 	MsgpackValue<double> testable2(&container, "test");
// 	testable1.Set(429496729.5);
// 	testable2.Set(42949672.95);

// 	CHECK_EQUAL(testable1.Get(), 429496729.5F);
// 	CHECK_EQUAL(testable2.Get(), 42949672.95);
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<float> testable1(&container, "test");
// 	MsgpackValue<double> testable2(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":150.25}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), 150.25F);
// 	CHECK_EQUAL(testable2.Get(), 150.25);

// 	doc.Parse("{\"testOther\":42.1}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// 	CHECK_FALSE(testable2.TryParse(&doc));

// 	doc.Parse("{\"test\":null}");
// 	CHECK_FALSE(testable1.TryParse(&doc));
// 	CHECK_FALSE(testable2.TryParse(&doc));
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<float> testable1(&container, "test", 19.25);
// 	MsgpackValue<double> testable2(&container, "test", 20.5);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19.25}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20.5}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_Equals_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<float> testable1(&container, "test", 100.5);
// 	MsgpackValue<float> testable01(&container, "test", 100.5);
// 	MsgpackValue<float> testable001(&container, "testOtherField", 100.5);

// 	MsgpackValue<double> testable2(&container, "test", 101.75);
// 	MsgpackValue<double> testable02(&container, "test", 101.75);
// 	MsgpackValue<double> testable002(&container, "testOtherField", 101.75);

// 	CHECK_TRUE(testable1 == testable01);
// 	CHECK_FALSE(testable1 != testable01);
// 	CHECK_TRUE(testable1.Equals(&testable01));
// 	CHECK_TRUE(testable01.Equals(&testable1));
// 	testable01.Set(testable01.Get() + 1);
// 	CHECK_TRUE(testable1 != testable01);
// 	CHECK_FALSE(testable1 == testable01);
// 	CHECK_FALSE(testable1.Equals(&testable01));
// 	CHECK_FALSE(testable01.Equals(&testable1));
// 	CHECK_FALSE(testable001 == testable1);
// 	CHECK_FALSE(testable1 == testable001);
// 	CHECK_FALSE(testable001.Equals(&testable1));
// 	CHECK_FALSE(testable1.Equals(&testable001));

// 	CHECK_TRUE(testable2 == testable02);
// 	CHECK_FALSE(testable2 != testable02);
// 	CHECK_TRUE(testable2.Equals(&testable02));
// 	CHECK_TRUE(testable02.Equals(&testable2));
// 	testable02.Set(testable02.Get() + 1);
// 	CHECK_TRUE(testable2 != testable02);
// 	CHECK_FALSE(testable2 == testable02);
// 	CHECK_FALSE(testable2.Equals(&testable02));
// 	CHECK_FALSE(testable02.Equals(&testable2));
// 	CHECK_FALSE(testable002 == testable2);
// 	CHECK_FALSE(testable2 == testable002);
// 	CHECK_FALSE(testable002.Equals(&testable2));
// 	CHECK_FALSE(testable2.Equals(&testable002));
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_CloneTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackValue<float> testable1(&container, "test", 100.5);
// 	MsgpackValue<double> testable2(&container, "test", 101.15);

// 	MsgpackValue<float> clone1(&container, "test");
// 	MsgpackValue<double> clone2(&container, "test");

// 	testable1.CloneTo((MsgpackValueBase *)&clone1);
// 	testable2.CloneTo((MsgpackValueBase *)&clone2);

// 	CHECK_EQUAL(clone1.Get(), 100.5);
// 	CHECK_EQUAL(clone2.Get(), 101.15);
// }
// /*


// */
// TEST(MsgpackNumericValueGroup, MsgpackUIntField_Common_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<unsigned int> testable1(&container, "test", 100);
// 	MsgpackCommonValue<uint32_t> testable2(&container, "test", 101);
// 	MsgpackCommonValue<uint16_t> testable3(&container, "test", 102);
// 	MsgpackCommonValue<uint8_t> testable4(&container, "test", 103);
// 	MsgpackCommonValue<uint64_t> testable5(&container, "test", 104);

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable3.Presented());
// 	CHECK_FALSE(testable4.Presented());
// 	CHECK_FALSE(testable5.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());

// 	rapidjson::Document doc;
// 	doc.Parse("{\"testOther\":42}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable3.Presented());
// 	CHECK_FALSE(testable4.Presented());
// 	CHECK_FALSE(testable5.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());

// 	doc.Parse("{\"test\":42}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), 42);
// 	CHECK_EQUAL(testable2.Get(), 42);
// 	CHECK_EQUAL(testable3.Get(), 42);
// 	CHECK_EQUAL(testable4.Get(), 42);
// 	CHECK_EQUAL(testable5.Get(), 42);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable3.Presented());
// 	CHECK_TRUE(testable4.Presented());
// 	CHECK_TRUE(testable5.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());

// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable3.Presented());
// 	CHECK_TRUE(testable4.Presented());
// 	CHECK_TRUE(testable5.Presented());
// 	CHECK_TRUE(testable1.IsNull());
// 	CHECK_TRUE(testable2.IsNull());
// 	CHECK_TRUE(testable3.IsNull());
// 	CHECK_TRUE(testable4.IsNull());
// 	CHECK_TRUE(testable5.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_Common_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<unsigned int> testable1(&container, "test", 19);
// 	MsgpackCommonValue<uint32_t> testable2(&container, "test", 20);
// 	MsgpackCommonValue<uint16_t> testable3(&container, "test", 21);
// 	MsgpackCommonValue<uint8_t> testable4(&container, "test", 22);
// 	MsgpackCommonValue<uint64_t> testable5(&container, "test", 22);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.ResetToNull();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.ResetToNull();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable3.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable3.ResetToNull();
// 		testable3.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable4.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable4.ResetToNull();
// 		testable4.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable5.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable5.ResetToNull();
// 		testable5.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_Common_Change_Presented_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<unsigned int> testable1(&container, "test");
// 	MsgpackCommonValue<uint32_t> testable2(&container, "test");
// 	MsgpackCommonValue<uint16_t> testable3(&container, "test");
// 	MsgpackCommonValue<uint8_t> testable4(&container, "test");
// 	MsgpackCommonValue<uint64_t> testable5(&container, "test");

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable3.Presented());
// 	CHECK_FALSE(testable4.Presented());
// 	CHECK_FALSE(testable5.Presented());

// 	testable1.Set(1);
// 	testable2.Set(1);
// 	testable3.Set(1);
// 	testable4.Set(1);
// 	testable5.Set(1);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable3.Presented());
// 	CHECK_TRUE(testable4.Presented());
// 	CHECK_TRUE(testable5.Presented());
// }

// TEST(MsgpackNumericValueGroup, MsgpackUIntField_Common_Change_IsNull_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<unsigned int> testable1(&container, "test");
// 	MsgpackCommonValue<uint32_t> testable2(&container, "test");
// 	MsgpackCommonValue<uint16_t> testable3(&container, "test");
// 	MsgpackCommonValue<uint8_t> testable4(&container, "test");
// 	MsgpackCommonValue<uint64_t> testable5(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_TRUE(testable1.IsNull());
// 	CHECK_TRUE(testable2.IsNull());
// 	CHECK_TRUE(testable3.IsNull());
// 	CHECK_TRUE(testable4.IsNull());
// 	CHECK_TRUE(testable5.IsNull());

// 	testable1.Set(1);
// 	testable2.Set(1);
// 	testable3.Set(1);
// 	testable4.Set(1);
// 	testable5.Set(1);
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_Common_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<int> testable1(&container, "test", 100);
// 	MsgpackCommonValue<int32_t> testable2(&container, "test", 101);
// 	MsgpackCommonValue<int16_t> testable3(&container, "test", 102);
// 	MsgpackCommonValue<int8_t> testable4(&container, "test", 103);
// 	MsgpackCommonValue<int64_t> testable5(&container, "test", 103);

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable3.Presented());
// 	CHECK_FALSE(testable4.Presented());
// 	CHECK_FALSE(testable5.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());

// 	rapidjson::Document doc;
// 	doc.Parse("{\"testOther\":42}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable3.Presented());
// 	CHECK_FALSE(testable4.Presented());
// 	CHECK_FALSE(testable5.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());

// 	doc.Parse("{\"test\":42}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), 42);
// 	CHECK_EQUAL(testable2.Get(), 42);
// 	CHECK_EQUAL(testable3.Get(), 42);
// 	CHECK_EQUAL(testable4.Get(), 42);
// 	CHECK_EQUAL(testable5.Get(), 42);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable3.Presented());
// 	CHECK_TRUE(testable4.Presented());
// 	CHECK_TRUE(testable5.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());

// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable3.Presented());
// 	CHECK_TRUE(testable4.Presented());
// 	CHECK_TRUE(testable5.Presented());
// 	CHECK_TRUE(testable1.IsNull());
// 	CHECK_TRUE(testable2.IsNull());
// 	CHECK_TRUE(testable3.IsNull());
// 	CHECK_TRUE(testable4.IsNull());
// 	CHECK_TRUE(testable5.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_Common_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<int> testable1(&container, "test", 19);
// 	MsgpackCommonValue<int32_t> testable2(&container, "test", 20);
// 	MsgpackCommonValue<int16_t> testable3(&container, "test", 21);
// 	MsgpackCommonValue<int8_t> testable4(&container, "test", 22);
// 	MsgpackCommonValue<int64_t> testable5(&container, "test", 22);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.ResetToNull();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.ResetToNull();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable3.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable3.ResetToNull();
// 		testable3.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable4.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable4.ResetToNull();
// 		testable4.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable5.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable5.ResetToNull();
// 		testable5.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_Common_Change_Presented_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<int> testable1(&container, "test");
// 	MsgpackCommonValue<int32_t> testable2(&container, "test");
// 	MsgpackCommonValue<int16_t> testable3(&container, "test");
// 	MsgpackCommonValue<int8_t> testable4(&container, "test");
// 	MsgpackCommonValue<int64_t> testable5(&container, "test");

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable3.Presented());
// 	CHECK_FALSE(testable4.Presented());
// 	CHECK_FALSE(testable5.Presented());

// 	testable1.Set(1);
// 	testable2.Set(1);
// 	testable3.Set(1);
// 	testable4.Set(1);
// 	testable5.Set(1);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable3.Presented());
// 	CHECK_TRUE(testable4.Presented());
// 	CHECK_TRUE(testable5.Presented());
// }

// TEST(MsgpackNumericValueGroup, MsgpackIntField_Common_Change_IsNull_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<int> testable1(&container, "test");
// 	MsgpackCommonValue<int32_t> testable2(&container, "test");
// 	MsgpackCommonValue<int16_t> testable3(&container, "test");
// 	MsgpackCommonValue<int8_t> testable4(&container, "test");
// 	MsgpackCommonValue<int64_t> testable5(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable3.TryParse(&doc));
// 	CHECK_TRUE(testable4.TryParse(&doc));
// 	CHECK_TRUE(testable5.TryParse(&doc));
// 	CHECK_TRUE(testable1.IsNull());
// 	CHECK_TRUE(testable2.IsNull());
// 	CHECK_TRUE(testable3.IsNull());
// 	CHECK_TRUE(testable4.IsNull());
// 	CHECK_TRUE(testable5.IsNull());

// 	testable1.Set(1);
// 	testable2.Set(1);
// 	testable3.Set(1);
// 	testable4.Set(1);
// 	testable5.Set(1);
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// 	CHECK_FALSE(testable3.IsNull());
// 	CHECK_FALSE(testable4.IsNull());
// 	CHECK_FALSE(testable5.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_Common_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<bool> testable1(&container, "test", false);

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable1.IsNull());

// 	rapidjson::Document doc;
// 	doc.Parse("{\"testOther\":true}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), false);
// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable1.IsNull());

// 	doc.Parse("{\"test\":true}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), true);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_FALSE(testable1.IsNull());

// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable1.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_Common_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<bool> testable1(&container, "test", true);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":true}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.ResetToNull();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_Common_Change_Presented_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<bool> testable1(&container, "test");

// 	CHECK_FALSE(testable1.Presented());

// 	testable1.Set(true);
// 	CHECK_TRUE(testable1.Presented());
// }

// TEST(MsgpackNumericValueGroup, MsgpackBoolField_Common_Change_IsNull_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<bool> testable1(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable1.IsNull());

// 	testable1.Set(true);
// 	CHECK_FALSE(testable1.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_Common_TryParse_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<float> testable1(&container, "test", 100);
// 	MsgpackCommonValue<double> testable2(&container, "test", 101);

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());

// 	rapidjson::Document doc;
// 	doc.Parse("{\"testOther\":42.0}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());

// 	doc.Parse("{\"test\":42.0}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_EQUAL(testable1.Get(), 42);
// 	CHECK_EQUAL(testable2.Get(), 42);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());

// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// 	CHECK_TRUE(testable1.IsNull());
// 	CHECK_TRUE(testable2.IsNull());
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_Common_WriteTo_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<float> testable1(&container, "test", 19);
// 	MsgpackCommonValue<double> testable2(&container, "test", 20);

// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19.0}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable1.ResetToNull();
// 		testable1.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20.0}");
// 	}
// 	{
// 		rapidjson::Document doc;
// 		doc.SetObject();
// 		testable2.ResetToNull();
// 		testable2.WriteToDoc(&doc);
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// 		doc.Accept(writer);
// 		STRCMP_EQUAL(buffer.GetString(), "{\"test\":null}");
// 	}
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_Common_Change_Presented_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<float> testable1(&container, "test");
// 	MsgpackCommonValue<double> testable2(&container, "test");

// 	CHECK_FALSE(testable1.Presented());
// 	CHECK_FALSE(testable2.Presented());

// 	testable1.Set(1);
// 	testable2.Set(1);
// 	CHECK_TRUE(testable1.Presented());
// 	CHECK_TRUE(testable2.Presented());
// }

// TEST(MsgpackNumericValueGroup, MsgpackFloatField_Common_Change_IsNull_After_Set_Value_Test) {
// 	MsgpackFieldsContainer container;
// 	MsgpackCommonValue<float> testable1(&container, "test");
// 	MsgpackCommonValue<double> testable2(&container, "test");

// 	rapidjson::Document doc;
// 	doc.Parse("{\"test\":null}");
// 	CHECK_TRUE(testable1.TryParse(&doc));
// 	CHECK_TRUE(testable2.TryParse(&doc));
// 	CHECK_TRUE(testable1.IsNull());
// 	CHECK_TRUE(testable2.IsNull());

// 	testable1.Set(1);
// 	testable2.Set(1);
// 	CHECK_FALSE(testable1.IsNull());
// 	CHECK_FALSE(testable2.IsNull());
// }