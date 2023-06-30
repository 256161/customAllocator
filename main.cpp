#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "custom_allocator.cpp"
#include "custom_list.cpp"
#include "factorial_fun.cpp"

using std::allocator;
using std::map;

template <typename T> void inputMap(int numberTask, const T &mapInput) {

  std::cout << " Вывод map из пункта задания " << numberTask << " размером "
            << mapInput.size();

  std::map<int, int>::const_iterator it = mapInput.begin();
  while (it != mapInput.end()) {
    std::cout << " Ключ " << it->first << " - значение " << it->second
              << std::endl;
     it++;
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
        - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
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
    inputMap<std::map<int, int, std::less<int>, allocator<int>>>(1, mapWhithStlAl);

    //    создание экземпляра std::map<int, int> с новым аллокатором,
    //    ограниченным 10  элементами
    auto mapWhithCustomAl = std::map<int, int, std::less<int>,
                      custom_allocator<std::pair<const int, int>>>{};
    
    for(size_t i = 0; i < 9; ++i)
    {
        mapWhithCustomAl[i] = factorialNumber(i);
    }
    inputMap<map<int, int, std::less<int>,
                 custom_allocator<std::pair<const int, int>>>>(
        2, mapWhithCustomAl);

    /*auto v = std::vector<int, custom_allocator<int>>{};
    for (int i = 0; i < 6; ++i) {
        std::cout << "vector size = " << v.size() << std::endl;
        v.push_back(i);
		std::cout << std::endl;
    }
*/
    auto cList = custom_list<int, custom_allocator<int()>>{};


    return 0;
}