# Homework 2 Hash it out

#### This project was completed by Eric Boettner and Vinay Gopalan. This project deals with designing a generic look-aside cache.

## Part 1: Basic Cache Operations
We chose to implement our cache by using an unordered_map as a private member in our Impl class because the unordered_map in the STL has most of the functionality required for the project and uses optimal implementations of hashing, rehashing, dynamic resizing and collision-handling.

## Part 2: Testing
All tests are available in test_cache_lib.cc. Run  `make`  to compile all necessary files following which run `./test` to run all tests.

## Part 3: Performance
In order to allow users to pass in a custom hash function, we used the hasher function passed in the cache constructor to construct an unordered_map with that hasher inside the Impl constructor. We added two basic hash objects. One that just hashes the key based on its length and one that uses XOR and byte shifts to more optimally hash keys and confirmed our implementation with verbose tests. While our code completely supports the ability to pass custom hash functions, the default hash function in the STL is fully sufficient.

## Part 4: Collision resolution

## Part 5: Dynamic resizing
Since the STL's unordered_map container handles dynamic resizing using its `max_load_factor` parameter, we simply used the value of the `max_load_factor` passed in the Cache constructor and then set the `max_load_factor` parameter for our unordered_map with that value in the Impl constructor. Upon testing with different values for the max_load_factor, we saw that the bucket_count of the unordered_map changes dynamically with the max_laod_factor, i.e., the number of buckets is dynamically resized (no data was lost during any of our testing of this standard feature). In researching max_load_factor we learned that it has constant runtime and triggers a rehash on overload.

## Part 6: Eviction Policy
We implemented a First-In First-Out (FIFO) eviction policy using STL's `<queue>` container because it gave us access to functions `push()`, `front()` and `pop()` which handled all the implementation we needed. These operations are carried out through a Doubly Linked-List which meets the required time and space complexities. Touching a key results in pushing the key into the queue, and evicting a key results in 'popping' the top of the queue and returning the popped value.