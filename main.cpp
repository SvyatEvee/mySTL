

#include "myvector.h"
#include "myList.h"
#include <iostream>
#include <algorithm>
using namespace mystd;




int main()
{
	
	using namespace std;

	/*myList<int> lst{ 1,2,3,4,5 };
	myList<int> lst2(lst.size());*/

	myVector<int> lst{ 1,2,3,4,5 };
	myVector<int> lst2(lst.size());

	for (auto i : lst)
		cout << i << " ";
	cout << endl;
	
	transform(lst.begin(), lst.end(), lst2.begin(), [](int a) { return a * 2; });

	for (auto i : lst2)
		cout << i << " ";
	cout << endl;
	

}

/*static_assert(std::is_same_v<
		typename iterator_traits<myVector<int>::iterator>::iterator_category,
		random_access_iterator_tag
	>);*/

//myVector<int> vec(10);
//std::random_device rd;
//std::mt19937 gen(rd());
//std::uniform_int_distribution<int> dist(1, 100);
//std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });
//for (auto it : vec) {
//	std::cout << it << " ";
//}
//std::cout << std::endl;
//std::sort(vec.begin(), vec.end());
//
//for (auto it : vec) {
//	std::cout << it << " ";
//}
