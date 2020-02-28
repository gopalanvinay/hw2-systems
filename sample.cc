#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    // Create an unordered_map of three strings (that map to strings)
    std::unordered_map<std::string, int*> u;
    // Add two new entries to the unordered_map
    int x = 5;
    u["BLACK"] = &x;


    // Output values by key
    std::cout << "The HEX of color BLACK is:[" << u["ERIC"] << "] " << &x << "\n";

    std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "] " << &x << "\n";
    x = 10;

    std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "] " << &x << "\n";
    std::cout << (u["SJSJSJ"] != &x) << "\n";
    std::cout << sizeof(*u["BLACK"]);
    u.erase("BLACK");
    std::cout << "The HEX of color BLACK is:[" << u["PURPLE"] << "] " << &x << "\n";
    return 0;
}
