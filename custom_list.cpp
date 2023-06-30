#include <string>
#include <algorithm>

// Класс контейнера map
template <class T, class Allocator = std::allocator<T> >
class custom_list {
void push_back(const T& x)
{
    if (size == capacity)
    {
        capacity = capacity * 2 + 1;
        //T* newData = ::operator new(capacity * sizeof(T));
        T* newData = alloc.allocate(capacity);
        std::copy(data, data + capacity * sizeof(T), newData); //naive
        std::swap(newData, data);
        alloc.deallocate(newData, capacity);
    }

    alloc.construct(data + size * sizeof(T), x);
    ++size;
}

private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    T* data = nullptr;

    Allocator alloc;
};