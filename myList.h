#ifndef MYLIST_H
#define MYLIST_H
#include <initializer_list>
#include <iostream>
namespace mystd {

	template<typename T>
	class myList {
	public:
		using size_type = long long; // “ËÔ, ËÒÔÓÎ¸ÁÛÂÏ˚È ‰Îˇ ı‡ÌÂÌËˇ ‡ÁÏÂ‡

	private:
		struct Node {
			T     data_{ nullptr };
			Node* next_{ nullptr };
			Node* prev_{ nullptr };
		};

		/*********** œÓÎˇ ÍÎ‡ÒÒ‡ ************/
		Node*     head_{ nullptr };
		Node*	  tail_{ nullptr };
		size_type size_{ 0 };

	public:

		/*********  ÓÌÒÚÛÍÚÓ˚ Ë ‰ÂÒÚÛÍÚÓ ÍÎ‡ÒÒ‡ **********/
		myList() = default;

        myList(size_type size, const T& data = T())
        {
            while (size_ != size)
                push_back(data);
        }

        myList(const myList& other)
        {
            Node* other_node = other.head_;
            while (other_node != nullptr) {
                push_back(other_node->data_);
                other_node = other_node->next_;
            }
        }

        myList(myList&& move) noexcept : size_(move.size_)
        {
            tail_ = move.tail_;
            head_ = move.head_;
            size_ = move.size_;

            tail_ = nullptr;
            head_ = nullptr;
        }

        myList(std::initializer_list<T> init_list)
        {
            for (auto& i : init_list)
                push_back(i);
        }


        // ƒŒ¡¿¬»“‹  ŒÕ—“–” “Œ–,  Œ“Œ–€… ÃŒ√ ¡€ –¿¡Œ¿“‹ — »“≈–¿“Œ–¿Ã»!!!!!!



        virtual ~myList()
        {
            /*while (tail_ != nullptr) pop_back();*/

            while (tail_ != nullptr) 
                std::cout << pop_back() << " ";
            std::cout << std::endl;
            
        }
			
        /********* œÂÂÓÔÂ‰ÂÎÂÌÌ˚Â ÒÚ‡Ì‰‡ÚÌ˚Â ÏÂÚÓ‰˚ **********/

        void push_back(const T& data)
        {
            if (tail_ == nullptr) {
                tail_ = new Node{ data, nullptr, nullptr };
                head_ = tail_;
                size_++;
            }
            else if (head_ == tail_) {
                tail_ = new Node{ data, nullptr, head_ };
                head_->next_ = tail_;
                size_++;
            }
            else {
                Node* new_node = new Node{ data, nullptr, tail_ };
                               
                tail_->next_ = new_node;
                tail_ = new_node;
                new_node = nullptr;
                size_++;
            }
        }

        void push_front(const T& data)
        {
            if (tail_ == nullptr) {
                tail_ = new Node{ data, nullptr, nullptr };
                head_ = tail_;
                size_++;
            }
            else if (head_ == tail_) {
                head_ = new Node{ data, tail_, nullptr };
                tail_->prev_ = head_;
                size_++;
            }
            else {
                Node* new_node = new Node{ data, head_, nullptr };

                head_->prev_ = new_node;
                head_ = new_node;
                new_node = nullptr;
                size_++;
            }
        }

        T pop_back()
        {
            if (tail_ == nullptr) {
                //  »Õ”“‹ »— Àﬁ◊≈Õ»≈
            }
            else if (tail_ == head_) {

                head_ = nullptr;
                T return_data = std::move(tail_->data_);
                delete tail_;
                tail_ = nullptr;
                size_--;

                return return_data;
            }
            else {

                T return_data = std::move(tail_->data_);
                tail_ = tail_->prev_;
                delete tail_->next_;
                tail_->next_ = nullptr;
                size_--;

                return return_data;
            }
        }

        T pop_front()
        {
            if (tail_ == nullptr) {
                //  »Õ”“‹ »— Àﬁ◊≈Õ»≈
            }
            else if (tail_ == head_) {

                head_ = nullptr;
                T return_data = std::move(tail_->data_);
                delete tail_;
                tail_ = nullptr;
                size_--;

                return return_data;
            }
            else {

                T return_data = std::move(head_->data_);
                head_ = head_->next_;
                delete head_->prev_;
                head_->prev_ = nullptr;
                size_--;

                return return_data;
            }
        }
	};



} // namespace mystd


#endif // MYLIST_H
