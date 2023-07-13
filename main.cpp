#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "custom_allocator.cpp"
#include "custom_list.cpp"
#include "factorial_fun.cpp"

using std::allocator;
using std::map;

template <typename T> void inputMap(const T &mapInput) {

    for (const auto &pair : mapInput)
    {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

int main(int argc, char const *argv[])
{

    // Задание
    /* 1 - создание экземпляра std::map<int, int>
        - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        2 - создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10
        элементами
        - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        - вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
        3 - создание экземпляра своего контейнера для хранения значений типа int
        - заполнение 10 элементами от 0 до 9
        4 - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
        ограниченным 10 элементами
        - заполнение 10 элементами от 0 до 9
        - вывод на экран всех значений, хранящихся в контейнере 
    */

    // создание экземпляра std::map<int, int> - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа

    auto mapWhithStlAl  = std::map<int, int, std::less<int>, std::allocator<int>>{};
    for(size_t i = 0; i < 9; ++i)
    {
        mapWhithStlAl[i] = factorialNumber(i);
    }
    inputMap<std::map<int, int, std::less<int>, allocator<int>>>(mapWhithStlAl);

    //    создание экземпляра std::map<int, int> с новым аллокатором,
    //    ограниченным 10  элементами
    auto mapWhithCustomAl = std::map<int, int, std::less<int>,
                      CustomAllocator<std::pair<const int, int>>>{};
    
    for(size_t i = 0; i < 9; ++i)
    {
        mapWhithCustomAl[i] = factorialNumber(i);
    }
    inputMap<map<int, int, std::less<int>,
                 CustomAllocator<std::pair<const int, int>>>>(mapWhithCustomAl);

    // создание экземпляра своего контейнера для хранения значений типа int
    //    - заполнение 10 элементами от 0 до 9
    auto list = MyList<int, CustomAllocator<int>>{};

    for (int i = 0; i < 9; ++i){
        list.push_back(i);
    }

    MyList<int, CustomAllocator<int>>::Iterator it(&list);
    while (!it.IsEnd())
    {
        std::cout << it->data;
        ++it;
    }

    return 0;
}