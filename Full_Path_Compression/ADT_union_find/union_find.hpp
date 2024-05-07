#ifndef UNION_FIND
#define UNION_FIND
#include <cstdint>

// weighted union class, with compression by halving
class union_find
{
private:
    /* data */
    uint64_t* idObject;
    uint64_t* weight;
    uint64_t arraySize;
    uint64_t find(uint64_t&);
    bool find(uint64_t&, uint64_t&);
public:
    union_find(uint64_t);
    virtual ~union_find();
    void unite(uint64_t, uint64_t);
    uint64_t nodeConnected(uint64_t);
};

#endif