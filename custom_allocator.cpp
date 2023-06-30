#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>


// Клас Аллокатора
template <class T>
struct custom_allocator {
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    custom_allocator () noexcept {}
    template <class U> custom_allocator  (const custom_allocator <U>&) noexcept {}

    T* allocate (std::size_t n)
    {
        return static_cast<T*>(::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n)
    {
        ::operator delete(p);
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args) {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

    template< class U >
    struct rebind
    {
        typedef custom_allocator<U> other;
    };
};