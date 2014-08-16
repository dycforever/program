#ifndef UTIL_ATOMIC_H
#define UTIL_ATOMIC_H

template <typename T>
class AtomicIntegerT
{
public:
    AtomicIntegerT() 
        : mValue(0)
    {}

public:
    T Get() const {
        //return __sync_val_compare_and_swap(&mValue, 0, 0);
        return mValue;
    }

    T GetAndAdd(T x) {
        return __sync_fetch_and_add(&mValue, x);
    }
    
    T AddAndGet(T x) {
        return GetAndAdd(x) + x;
    }

    T IncrementAndGet() {
        return AddAndGet(1);
    }

    void Add(T x) {
        AddAndGet(x);
    }

    void Increment() {
        IncrementAndGet();
    }

    void Decrement() {
        GetAndAdd(-1);
    }

    T GetAndSet(T x) {
        return __sync_lock_test_and_set(&mValue, x);
    }
private:
    volatile T mValue;

};

typedef AtomicIntegerT<int16_t> AtomicInteger16;
typedef AtomicIntegerT<int32_t> AtomicInteger32;
typedef AtomicIntegerT<int64_t> AtomicInteger64;

#endif //UTIL_ATOMIC_H
