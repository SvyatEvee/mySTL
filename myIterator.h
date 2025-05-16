#ifndef ITERATOR_BASE_H
#define ITERATOR_BASE_H
#include <iostream>


namespace mystd {

	// Теги
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	// Базовый класс
	template <typename Category, typename T, typename Distance = ptrdiff_t,
		      typename Pointer = T*, typename Reference = T&>
	struct base_iterator {
		using iterator_category = Category;
		using value_type		= T;
		using difference_type	= Distance;
		using pointer       	= Pointer;
		using reference       	= Reference;
	};

	// Характеристики итераторов, также дополнительные специализации для указателей
	template<class base_iterator>
	struct iterator_traits {
		using iterator_category = typename base_iterator::iterator_category;
		using value_type        = typename base_iterator::value_type;
		using difference_type   = typename base_iterator::difference_type;
		using pointer			= typename base_iterator::pointer;
		using reference         = typename base_iterator::reference;
	};

	template<typename T>
	struct iterator_traits<T*> {
		using iterator_category = random_access_iterator_tag;
		using value_type		= T;
		using difference_type   = ptrdiff_t;
		using pointer			= T*;
		using reference			= T&;
	};

	template<typename T>
	struct iterator_traits<const T*> {
		using iterator_category = random_access_iterator_tag;
		using value_type		= T;
		using difference_type	= ptrdiff_t;
		using pointer			= const T*;
		using reference			= const T&;
	};


} // namespace mystd

#endif // ITERATOR_BASE_H
