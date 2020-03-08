#include "evictor.hh"
#include <queue>


class Fifo : public Evictor {
 private:
   // private data structure
   std::queue<key_type> acsess;                 // empty queue

 public:
    // Inform evictor that a certain key has been set or get:
    virtual void touch_key(const key_type&) {
        acsess.push();// ?

    }

    // Request evictor for the next key to evict, and remove it from evictor.
    // If evictor doesn't know what to evict, return an empty key ("").
    virtual const key_type evict() {
        key_type to_remove acsess.front();
        acsess.pop();
        return to_remove;
    }


    Fifo() : { }
};
