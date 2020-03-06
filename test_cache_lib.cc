#include "cache.hh"
#include <iostream>
#include <assert.h>


void test_set_and_get(Cache &obj, Cache::size_type& val_size)
{
    obj.set("a","1",1);
    assert(obj.get("a", val_size) == "1");
    obj.set("b","3",1);
    assert(obj.get("b", val_size) == "3");
    obj.set("c","5",1);
    assert(obj.get("c", val_size) == "5");
    obj.set("d","7",1);
    // maxmem exceeded
    //assert(obj.get("d", val_size) == nullptr);
    // fix size stuff
    printf("All set and get tests passed!\n");
}

void test_del(Cache &obj, Cache::size_type& val_size)
{

    obj.set("testDel1","1",1);
    assert(obj.get("testDel1",val_size) == "1");
    obj.del("testDel1");
    assert(obj.get("testDel1",val_size) == nullptr);
    obj.set("testDel2","4",1);
    assert(obj.get("testDel2",val_size) == "4");
    obj.del("testDel2");
    assert(obj.get("testDel2",val_size) == nullptr);
    printf("All del tests passed!\n");
}

void test_space_used(Cache &empty_obj)
{
    empty_obj.set("testSpace","3",1);
    assert(empty_obj.space_used() == 8);
    empty_obj.del("testSpace");
    assert(empty_obj.space_used() == 0);
    printf("All space use tests passed!\n");
}

void test_reset(Cache &obj)
{
    obj.set("testReset1","2",1);
    obj.set("testReset2","4",1);
    obj.set("testReset3","8",1);
    assert(obj.space_used() == 1);
    obj.reset();
    // temp
    Cache::size_type temp;
    assert(obj.get("testRest1",temp)== nullptr);
    assert(obj.get("testRest2",temp)== nullptr);
    assert(obj.get("testRest3",temp)== nullptr);
    assert(obj.space_used() == 0);
    printf("All reset tests passed!\n");
}


// Main
int main()
{
    Cache::size_type a;
    Cache obj_set(25);
    test_set_and_get(obj_set, a);

    Cache obj_del(25);
    test_del(obj_del, a);

    Cache obj_empty(25);
    test_space_used(obj_empty);

    //Cache obj_reset(25);
    //test_reset(obj_reset);

    auto my_hash = [](std::string const& foo) {
        return foo.length();
    };
    Cache obj_hash(25, 0.75, nullptr, my_hash);
    test_set_and_get(obj_hash, a);

    return 0;
}
