#include "cache.hh"
#include "fifo_evictor.hh"
#include <iostream>
#include <assert.h>


void test_set_and_get(Cache &obj)
{
    Cache::size_type val_size;
    obj.set("a","1",1);
    assert(obj.get("a", val_size) == "1");
    obj.set("b","3",1);
    assert(obj.get("b", val_size) == "3");
    obj.set("c","5",1);
    assert(obj.get("c", val_size) == "5");
    obj.set("c","10",2);
    assert(obj.get("c", val_size) == "10"); // change key
    obj.set("d","7",1);
    assert(obj.get("d", val_size) == nullptr);     // maxmem exceeded
    printf("\tAll set and get tests passed!\n");
}

void test_del(Cache &obj)
{
    Cache::size_type val_size;
    obj.set("testDel1","5", 1);
    assert(obj.get("testDel1",val_size) == "5");
    obj.del("testDel1");
    assert(obj.get("testDel1",val_size) == nullptr);
    obj.set("testDel2","7",1);
    assert(obj.get("testDel2",val_size) == "7");
    obj.del("testDel2");
    assert(obj.get("testDel2",val_size) == nullptr);
    printf("\tAll del tests passed!\n");
}

void test_space_used(Cache &empty_obj)
{
    empty_obj.set("testSpace","3",1);
    assert(empty_obj.space_used() == 1);
    empty_obj.set("a","30",2);
    assert(empty_obj.space_used() == 3);
    empty_obj.del("testSpace");
    assert(empty_obj.space_used() == 2);
    printf("\tAll space use tests passed!\n");
}

void test_reset(Cache &obj)
{
    Cache::size_type val_size;
    obj.set("testReset1","2",1);
    obj.set("testReset2","4",1);
    obj.set("testReset3","8",1);
    assert(obj.space_used() == 3);
    obj.reset();
    assert(obj.get("testRest1",val_size)== nullptr);
    assert(obj.get("testRest2",val_size)== nullptr);
    assert(obj.get("testRest3",val_size)== nullptr);
    assert(obj.space_used() == 0);
    printf("\tAll reset tests passed!\n");
}

void test_evict(Cache &obj)
{
    Cache::size_type val_size;
    obj.set("a","1",1);
    assert(obj.get("a", val_size) == "1");
    obj.set("b","3",1);
    assert(obj.get("b", val_size) == "3");
    obj.set("c","5",1);
    assert(obj.get("c", val_size) == "5");
    obj.set("d","7",1);
    // maxmem exceeded
    assert(obj.get("d", val_size) == "7");
    assert(obj.get("a", val_size) == nullptr);
    printf("\tAll evictor tests passed!\n");
}


// Main
int main()
{
    printf("Cache Functions\n");
    Cache obj_set(3);
    test_set_and_get(obj_set);

    Cache obj_del(25);
    test_del(obj_del);

    Cache obj_empty(5);
    test_space_used(obj_empty);

    Cache obj_reset(4);
    test_reset(obj_reset);

    printf("Cache Functions with Hash Function\n");
    auto my_hash = [](std::string const& foo) {
        return foo.length();
    };
    Cache obj_hash(3, 0.75, nullptr, my_hash);
    test_set_and_get(obj_hash);

    Cache obj_hashset(3, 0.75, nullptr, my_hash);
    test_set_and_get(obj_hashset);

    Cache obj_hashdel(25, 0.75, nullptr, my_hash);
    test_del(obj_hashdel);

    Cache obj_hashempty(5, 0.75, nullptr, my_hash);
    test_space_used(obj_hashempty);

    Cache obj_hashreset(4, 0.75, nullptr, my_hash);
    test_reset(obj_hashreset);

    printf("Cache Functions with Evictor\n");
    Fifo* evictor = new Fifo();
    Cache obj_evict(3, 0.6, evictor);
    test_evict(obj_evict);

    Cache obj_evictset(3, 0.75, nullptr, my_hash);
    test_set_and_get(obj_evictset);

    Cache obj_evictdel(25, 0.75, nullptr, my_hash);
    test_del(obj_evictdel);

    Cache obj_evictempty(5, 0.75, nullptr, my_hash);
    test_space_used(obj_evictempty);

    Cache obj_evictreset(4, 0.75, nullptr, my_hash);
    test_reset(obj_evictreset);
    
    return 0;
}
