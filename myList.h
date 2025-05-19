#ifndef MYLIST_H
#define MYLIST_H
#include <initializer_list>
#include "myIterator.h"
#include <iostream>
namespace mystd {

	template<typename T>
	class myList {
	public:
		using size_type = long long; // Тип, используемый для хранения размера

	private:
		struct Node {
			T     data_;
			Node* next_{ nullptr };
			Node* prev_{ nullptr };
		};

		/*********** Поля класса ************/
        Node      sentinel{ T(), nullptr, nullptr };
		Node*     head_   { &sentinel };
		Node*	  tail_   { &sentinel };
		size_type size_   { 0 };

	public:

		/********* Конструкторы и деструктор класса **********/
		myList() = default;

        myList(size_type size, const T& data = T())
        {
            while (size_ != size)
                push_back(data);
        }

        myList(const myList& other)
        {
            Node* other_node = other.head_;
            while (other_node != &sentinel) {
                push_back(other_node->data_);
                other_node = other_node->next_;
            }
        }

        myList(myList&& move) noexcept : size_(move.size_)
        {
            tail_ = move.tail_;
            head_ = move.head_;
            size_ = move.size_;

            move.tail_ = nullptr;
            move.head_ = nullptr;
            move.sentinel.next_ = nullptr;
            move.sentinel.prev_ = nullptr;

            sentinel.next_ = head_;
            sentinel.prev_ = tail_;
        }

        myList(std::initializer_list<T> init_list)
        {
            for (auto& i : init_list)
                push_back(i);
        }


        // ДОБАВИТЬ КОНСТРУКТОР, КОТОРЫЙ МОГ БЫ РАБОАТЬ С ИТЕРАТОРАМИ



        virtual ~myList()
        {
            while (tail_ != &sentinel) pop_back();

           /* while (tail_ != nullptr) 
                std::cout << pop_back() << " ";
            std::cout << std::endl;*/
            
        }
		
        // Реализация итератора для класса myList
        class iterator : public base_iterator<bidirectional_iterator_tag, T> {
        private:
            Node* ptr_node_{ nullptr };

            explicit iterator(Node* ptr_node) : ptr_node_(ptr_node)
                {}
        public:
            
            using typename base_iterator::iterator_category;
            using typename base_iterator::value_type;
            using typename base_iterator::difference_type;
            using typename base_iterator::pointer;
            using typename base_iterator::reference;
            friend class myList;

            iterator() : ptr_node_(nullptr)
            {}

            // Разыменовывание
            T& operator* () const { return  ptr_node_->data_; }
            T* operator->() const { return &ptr_node_->data_; }

            // Инкремент/Декремент
            iterator& operator++() { ptr_node_ = ptr_node_->next_; return *this; }
            iterator  operator++(int) { iterator tmp = *this; ptr_node_ = ptr_node_->next_; return tmp; }
            iterator& operator--() { ptr_node_ = ptr_node_->prev_; return *this; }
            iterator  operator--(int) { iterator tmp = *this; ptr_node_ = ptr_node_->prev_; return tmp; }

            // Операции сравнения
            bool operator==(const iterator& other) const { return ptr_node_ == other.ptr_node_; }
            bool operator!=(const iterator& other) const { return ptr_node_ != other.ptr_node_; }
               
            
        };

        /********** Методы для работы с итераторами ************/
        iterator begin() { return iterator(head_); }
        iterator end() { return iterator(&sentinel); }

        /********* Переопределенные стандартные методы **********/

        void push_back(const T& data)
        {
            if (tail_ == &sentinel) {
                tail_ = new Node{ data, &sentinel, &sentinel };
                head_ = tail_;
                size_++;
            }
            else if (head_ == tail_) {
                tail_ = new Node{ data, &sentinel, head_ };
                head_->next_ = tail_;
                size_++;
            }
            else {
                Node* new_node = new Node{ data, &sentinel, tail_ };
                               
                tail_->next_ = new_node;
                tail_ = new_node;
                new_node = nullptr;
                size_++;
            }
            sentinel.next_ = head_;
            sentinel.prev_ = tail_;
        }

        void push_front(const T& data)
        {
            if (tail_ == &sentinel) {
                tail_ = new Node{ data, &sentinel, &sentinel };
                head_ = tail_;
                size_++;
            }
            else if (head_ == tail_) {
                head_ = new Node{ data, tail_, &sentinel };
                tail_->prev_ = head_;
                size_++;
            }
            else {
                Node* new_node = new Node{ data, head_, &sentinel };

                head_->prev_ = new_node;
                head_ = new_node;
                new_node = nullptr;
                size_++;
            }
            sentinel.next_ = head_;
            sentinel.prev_ = tail_;
        }

        T pop_back()
        {
            if (tail_ == &sentinel) {
                // КИНУТЬ ИСКЛЮЧЕНИЕ
            }
            else if (tail_ == head_) {

                head_ = &sentinel;
                T return_data = std::move(tail_->data_);
                delete tail_;
                tail_ = &sentinel;
                size_--;
                sentinel.next_ = head_;
                sentinel.prev_ = tail_;

                return return_data;
            }
            else {

                T return_data = std::move(tail_->data_);
                tail_ = tail_->prev_;
                delete tail_->next_;
                tail_->next_ = &sentinel;
                size_--;
                sentinel.next_ = head_;
                sentinel.prev_ = tail_;

                return return_data;
            }
            
        }

        T pop_front()
        {
            if (tail_ == nullptr) {
                // КИНУТЬ ИСКЛЮЧЕНИЕ
            }
            else if (tail_ == head_) {

                head_ = &sentinel;
                T return_data = std::move(tail_->data_);
                delete tail_;
                tail_ = &sentinel;
                size_--;
                sentinel.next_ = head_;
                sentinel.prev_ = tail_;

                return return_data;
            }
            else {

                T return_data = std::move(head_->data_);
                head_ = head_->next_;
                delete head_->prev_;
                head_->prev_ = &sentinel;
                size_--;
                sentinel.next_ = head_;
                sentinel.prev_ = tail_;

                return return_data;
            }
            
        }

        size_type size() { return size_; }

	};



} // namespace mystd


#endif // MYLIST_H
