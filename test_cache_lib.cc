#include "cache.hh"
#include "fifo_evictor.hh"
#include <iostream>
#include <assert.h>

void test_set_and_get(Cache &obj, bool ev = false)
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
    if (!ev) {
        assert(obj.get("d", val_size) == nullptr);     // maxmem exceeded
    } else {
        assert(obj.get("a", val_size) == nullptr);     // evictor policy working
    }
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

void test_harness(float b = 0.75, Evictor* c = nullptr, Cache::hash_func d = std::hash<key_type>()) {
    Cache obj_set(3, b, c, d);
    test_set_and_get(obj_set, (c != nullptr));

    Cache obj_del(25, b, c, d);
    test_del(obj_del);

    Cache obj_empty(5, b, c, d);
    test_space_used(obj_empty);

    Cache obj_reset(4, b, c, d);
    test_reset(obj_reset);
}

// Main
int main()
{
    printf("Cache Functions\n");
    test_harness(0.75);

    printf("Cache Functions with Hash Function\n");
    auto count_hash = [](std::string const& key) {
        return key.length();
    };

    test_harness(0.75, nullptr, count_hash);
    // SAX hashing function
    //https://www.daniweb.com/programming/software-development/threads/231987/string-hash-function
    auto hash_sum = [](std::string const& key) {
        unsigned hashVal = 0;
        for (int x = 0; x < key.length(); ++x) {
            hashVal ^= (hashVal << 5) +
                       (hashVal >> 2) +
                       key[x];
        }
    return hashVal % 10;
    };
    test_harness(0.75, nullptr, hash_sum);


    printf("Cache Functions with Evictor\n");
    Fifo* evictor = new Fifo();
    Cache obj_evict(3, 0.6, evictor);
    test_evict(obj_evict);
    test_harness(0.75, evictor);

    return 0;
}
