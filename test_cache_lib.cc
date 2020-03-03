#include "cache.hh"

// Main
int main()
{
    uint32_t a;
    Cache x(1000);
    x.set("h", "10", 1000);
    printf("%s\n", x.get("h" , a));
    x.reset();
    printf("%s\n", x.get("h" , a));
    return 0;
}
