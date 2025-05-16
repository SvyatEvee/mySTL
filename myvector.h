#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <numeric>
#include <initializer_list>
#include "myExceptions.h"
#include "myIterator.h"
#include <algorithm>


namespace mystd {

    template<typename T>
    class myVector {
    public:

        using size_type = long long; // Тип, используемый для хранения размера
    private:
        enum {
            start_length = 8,                                        // Начальная длина массива
            resize_factor = 2,                                        // Множитель для увеличения длины массива
            max_length = std::numeric_limits<size_type>::max() / 2     // Максимальный физический размер массива
        };

        T* data_{ nullptr };
        size_type size_{ 0 };            // Размер массива
        size_type capacity_{ 0 };        // Физический размер массива

        


        /********* Служебные методы **************/
        void _resize_array(size_type new_size)         // Переопределение физического размера массива
        {
            if (new_size <= capacity_)
                return;

            size_type new_capacity = capacity_;

            while (new_capacity < new_size) {
                new_capacity *= resize_factor;
                if (new_capacity >= max_length) {
                    new_capacity = max_length;
                    break;
                }
            }
            capacity_ = new_capacity;

            


            T* temp_data = new T[capacity_];
            for (int i = 0; i < size_; ++i)
                temp_data[i] = data_[i];

            delete[] data_;
            data_ = temp_data;
        }       

    public:
        // Реализация итератора для класса myVector
        class iterator : public base_iterator<mystd::random_access_iterator_tag, T> {
            T* ptr_;

            

            explicit iterator(T* ptr = nullptr) : ptr_(ptr)
                {}
        public:
            friend class myVector;
            using typename base_iterator::difference_type;
            iterator() : ptr_(nullptr)
                {}
            

            // Разыменовывание
            T& operator* () const { return *ptr_; }
            T* operator->() const { return  ptr_; }

            // Increment/Decrement
            iterator& operator++()    { ++ptr_; return *this; }
            iterator  operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }
            iterator& operator--()    { --ptr_; return *this; }
            iterator  operator--(int) { iterator tmp = *this; --ptr_; return tmp; }
            
            // Арифметические операции
            iterator  operator+ (difference_type n) const { return iterator(ptr_ + n); }
            iterator  operator- (difference_type n) const { return iterator(ptr_ - n); }
            iterator& operator+=(difference_type n) { ptr_ += n;  return *this; }
            iterator& operator-=(difference_type n) { ptr_ -= n;  return *this; }
            difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }
            
            // Операции сравнения
            bool operator == (const iterator & other) const { return ptr_ == other.ptr_; }
            bool operator != (const iterator & other) const { return ptr_ != other.ptr_; }
            bool operator >  (const iterator & other) const { return ptr_ >  other.ptr_; }
            bool operator <  (const iterator & other) const { return ptr_ <  other.ptr_; }
            bool operator >= (const iterator & other) const { return ptr_ >= other.ptr_; }
            bool operator <= (const iterator & other) const { return ptr_ <= other.ptr_; }

            // Получение значения по индексу от указателя
            T& operator[](difference_type n) const { return ptr_[n]; }

        };

        /********** Методы для работы с итераторами ************/
        iterator begin() { return iterator(data_); }
        iterator end()   { return iterator(data_ + size_); }

        /********* Конструкторы и деструктор класса **********/
        myVector() : size_(0), capacity_(start_length)
        {
            data_ = new T[capacity_];
        }

        myVector(size_type size) : size_(size), capacity_(size)
        {
            data_ = new T[capacity_];
        }

        myVector(size_type size, const T& value) : size_(size), capacity_(size)
        {
            data_ = new T[capacity_];
            for (int i = 0; i < size_; ++i)
                data_[i] = value;
        }

        myVector(const myVector& other) : size_(other.size_), capacity_(other.capacity_)
        {
            data_ = new T[capacity_];
            for (int i = 0; i < size_; ++i)
                data_[i] = other.data_[i];
        }

        myVector(myVector&& move) noexcept : size_(move.size_), capacity_(move.capacity_)
        {
            data_ = move.data_;
            move.data_ = nullptr;
        }

        myVector(std::initializer_list<T> init_list)
        {
            size_     = init_list.size();
            capacity_ = size_;
            data_     = new T[capacity_];

            std::copy(init_list.begin(), init_list.end(), data_);
        }

        virtual ~myVector()
        {
            delete[] data_;
        }

        /********* Переопределенные операции **********/
        myVector& operator=(const myVector& other)
        {
            // Проверка на присваивание себя же
            if (this == &other)
                return other;

            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            data_ = new T[capacity_];
            for (int i = 0; i < size_; ++i)
                data_[i] = other.data_[i];

            return *this;
        }
        
        myVector& operator=(myVector&& move) noexcept
        {
            // Проверка на приравнивание себя же
            if (this == &move)
                return move;

            delete[] data_;
            size_ = move.size_;
            capacity_ = move.capacity_;
            data_ = move.data_;
            move.data_ = nullptr;

            return *this;
        }

        /*Item operator[](size_type indx)
        {
            return Item(this, indx);
        }*/

        T& operator[](size_type indx)
        {
            if (indx < 0 || size_ <= indx) {
                /*throw myException("Ты еблан? Индекс за диапазон вышел");*/
                _CrtDbgReport(
                    _CRT_ERROR,                     // Тип отчета (ошибка)
                    __FILE__,                       // Имя файла
                    __LINE__,                      // Номер строки
                    nullptr,                        // Модуль (необязательно)
                    "wdadw?");
                throw std::out_of_range("Ты дебил?");
            }
            return data_[indx];
        }


        /********* Переопределенные стандартные методы **********/
        void push_back(T& value)
        {
            if (size_ >= capacity_)
                _resize_array(capacity_ * resize_factor);

            if (size_ < capacity_)
                data_[size_++] = value;
            else
                // Можно кинуть исключение о переполнении
        }
        
        T pop_back()
        {
            if (size_ > 0)
                return std::move(data_[--size_]);
            // Кинуть исключение о попытке достать данные из пустого вектора
        }
        
        size_type size() const
        {
            return size_;
        }
        
        size_type max_size() const
        {
            return max_length;
        }

        T* get_data() 
        {
            return data_;
        }

        
    };


}// namespace mystd





#endif // MYVECTOR_H
