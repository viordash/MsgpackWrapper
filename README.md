# MsgpackWrapper
Wrap Msgpack to be used as objects of predefined class, in continuation of the project [RapidJSONWrapper](https://github.com/viordash/RapidJSONWrapper) 


Objects are represented as DTOs with [msgpack](https://github.com/msgpack/msgpack-c/tree/c_master) serialization/deserialization support:
 
    
    class UserDto : public MsgpackObject {
      public:
    	MsgpackValue<char *> Name;
    	MsgpackValue<uint32_t> Role;
    
    	UserDto(char *name = {}, TUserRole role = {})
    		: Name(this, 0, name), 
    		  Role(this, 1, role){};
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
    
    	GoodsDto(int id = {}, uint32_t created = {}, char *group = {}, char *name = {}, float price = {}, double quantity = {}, bool deleted = {}, char *storeName = {})
    		: Id(this, 0, id),					
    		  Created(this, 1, created),	
    		  Group(this, 2, group),			
    		  Name(this, 3, name),				
    		  Price(this, 4, price),			
    		  Quantity(this, 5, quantity), 
    		  Deleted(this, 6, deleted),	
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
    
    	OrderDto(char *supplier = {}, uint32_t dateTime = {}, char *userName = {}, TUserRole userRole = {})
    		: Supplier(this, 0, supplier), 
    		  DateTime(this, 1, dateTime), 
    		  Goods(this, 2, &goodsList),		
    		  userDto(userName, userRole),			
    		  User(this, 3, &userDto){};
    };

sample code (from tests): 
	
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

