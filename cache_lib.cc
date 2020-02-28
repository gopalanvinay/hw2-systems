#include "cache.hh"

void set(key_type key, val_type val, size_type size) {

}

// Retrieve a pointer to the value associated with key in the cache,
// or nullptr if not found.
// Sets the actual size of the returned value (in bytes) in val_size.
val_type get(key_type key, size_type& val_size) const {

}

// Delete an object from the cache, if it's still there
bool del(key_type key) {

}

// Compute the total amount of memory used up by all cache values (not keys)
size_type space_used() const {

}

// Delete all data from the cache
void reset() {

}
