#include "cache.hh"
#include <assert.h>


int test_set(Cache &obj, uint32_t &val_size)
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
    printf("All set tests passed!\n");
    return 0;
}


// Main
int main()
{
    uint32_t a;
    Cache x(25);
    test_set(x, a);
    return 0;
}
