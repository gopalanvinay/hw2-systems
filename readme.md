# Homework 2 Hash it out

### This project was completed by Eric Boettner and Vinay Gopalan

## Part 1: Basic Cache Operations
We chose to implement our cache by using an unordered_map as a private member in our Impl class. 

## Part 2: Testing
All tests are available in test_cache_lib.cc. Run  `make test`  to compile all necessary files following which run `./test` to run all tests.

## Part 3: Performance
In order to allow users to pass in a custom hash function, we used the hasher function passed in the cache constructor to construct an unordered_map with that hasher inside the Impl constructor.