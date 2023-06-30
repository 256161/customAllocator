#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "custom_allocator.cpp"
#include "custom_list.cpp"
#include "factorial_fun.cpp"

int main(int argc, char const *argv[])
{
    
   auto v = std::vector<int, custom_allocator<int>>{};
	for (int i = 0; i < 6; ++i) {
		std::cout << "vector size = " << v.size() << std::endl;
        v.push_back(i);
		std::cout << std::endl;
    }
    return 0;

    auto cList = custom_list<int, custom_allocator<int()>>{};
}