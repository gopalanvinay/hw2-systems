#include "cache.hh"
#include <assert.h>


void test_set_and_get(Cache &obj, Cache::size_type& val_size)
{
    obj.set("a","1",25);
    assert(obj.get("a", val_size) == "1");
    obj.set("b","3",25);
    assert(obj.get("b", val_size) == "3");
    obj.set("c","5",25);
    assert(obj.get("c", val_size) == "5");
    obj.set("d","7",25);
    // maxmem exceeded
    assert(obj.get("d", val_size) == nullptr);
    printf("All set and get tests passed!\n");
}

void test_del(Cache &obj, Cache::size_type& val_size)
{

    obj.set("testDel1","1",10);
    assert(obj.get("testDel1",val_size) == "1");
    obj.del("testDel1");
    assert(obj.get("testDel1",val_size) == nullptr);
    obj.set("testDel2","4",40);
    assert(obj.get("testDel2",val_size) == "4");
    obj.del("testDel2");
    assert(obj.get("testDel2",val_size) == nullptr);
    printf("All del tests passed!\n");
}

void test_space_used(Cache &empty_obj)
{
    empty_obj.set("testSpace","3",8);
    assert(empty_obj.space_used() == 8);
    empty_obj.del("testSpace");
    assert(empty_obj.space_used() == 0);
    printf("All space use tests passed!\n");
}

// Main
int main()
{
    Cache::size_type a;
    Cache obj_set(25);
    test_set_and_get(obj_set, a);

    Cache obj_del(10);
    test_del(obj_del, a);

    Cache empty_obj(10);
    test_space_used(empty_obj);

    return 0;
}
