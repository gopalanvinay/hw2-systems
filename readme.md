# Homework 2 Hash it out

### This project was completed by Eric Boettner and Vinay Gopalan. This project deals with designing a generic look-aside cache.

## Part 1: Basic Cache Operations
We chose to implement our cache by using an unordered_map as a private member in our Impl class because the unordered_map in the STL has most of the functionality required for the project and uses optimal implementations of hashing, rehashing, dynamic resizing and collision-handling.

## Part 2: Testing
All tests are available in test_cache_lib.cc. Run  `make test`  to compile all necessary files following which run `./test` to run all tests.

## Part 3: Performance
In order to allow users to pass in a custom hash function, we used the hasher function passed in the cache constructor to construct an unordered_map with that hasher inside the Impl constructor.

## Part 4: Collision resolution

## Part 5: Dynamic resizing
Since the STL's unordered_map container handles dynamic resizing using its `max_load_factor` parameter, we simply used the value of the `max_load_factor` passed in the Cache constructor and then set the `max_load_factor` parameter for our unordered_map with that value in the Impl constructor.

## Part 6: Eviction Policy
We implemented a First-In First-Out (FIFO) eviction policy using STL's `<queue>` container because it gave us access to functions `push()`, `front()` and `pop()` which handled all the implementation we needed. Touching a key results in pushing the key into the queue, and evicting a key results in 'popping' the top of the queue and returning the popped value.