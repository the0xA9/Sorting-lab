#include <iostream>
#include <vector>
#include <chrono>

#include "sort.hpp"


std::vector<std::pair<void(*)(int*, const size_t, bool(*)(const void*, const void*)), std::string>> sort_types = {
	{ sort::Bubble, "Bubble" },
	{ sort::BubbleMod, "BubbleMod" },
	{ sort::Insertion, "Insertion" },
	{ sort::Selection, "Selection" },
	{ sort::Shell, "Shell alg" },
	// { sort::QuickSort, "QuickSort"},
	{ sort::RadixSort, "RadixSort"},
	{ sort::CountingSort, "CountingSort"},
	{ sort::DownwardMerge, "DMerge"},
	{ sort::GrowingMerge, "GMerge"},
	{ sort::X2Merge, "X2Merge"},
};

template< typename T >
void GenType(T* a, size_t sz, T _from, T _to)
{
	srand(static_cast<unsigned>(time(0)));

	for(auto it = 0; it < sz; it++)
		a[it] = _from + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX/(_to - _from)));
}

int main() 
{
	const size_t sz = 8;
	int a[sz] = { 15, 10, 3, 9, 12, 3, 11, 9 };//int* a = new int[sz];
	int* b = new int[sz];
	
	//GenType(a, sz, 0, 20);

	std::cout << "data on start\t-> sz:" << sz << " { ";
	for(int i=0;i < sz;i++)
		std::cout << a[i] << " ";
	std::cout << '}' << std::endl;

	for(auto it : sort_types) {
		memcpy(b, a, sizeof(int)*sz);
		
		auto start_time = std::chrono::steady_clock::now();

			it.first(b, sz, [](const void* a, const void* b) { return *(int*)a < *(int*)b; });

		auto end_time = std::chrono::steady_clock::now();
		
		std::cout << it.second << " for " << std::chrono::duration <double, std::nano> (end_time - start_time).count() << "ns\t->\t";
		for(int i = 0; i < sz; i++)
			std::cout << b[i] << " ";
		std::cout << std::endl;
	}

	char ch; 
	std::cin >> ch;
	return 0;
}