#include "myvector.h"
#include <vector>
#include <utility>
#include <algorithm>
#include "myList.h"
#include <random>
#include <list>

using namespace mystd;




int main()
{
	using namespace std;

	myList<int> lst{ 1,2,3,4,5,6};
	
	lst.pop_back();
	lst.pop_front();

	lst.push_back(578);
	lst.push_front(578);
	
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