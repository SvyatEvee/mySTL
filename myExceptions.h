#ifndef ERRORS_H
#define ERRORS_H
#include <iostream>
#include <string>

namespace mystd {

	class myException : public std::exception {
	private:
		std::string msg_;
	public:
		myException(const char* msg) : msg_(msg)
		{}
		myException(const myException& other) : msg_(other.msg_)
		{}
		const char* what() const noexcept override
		{ return msg_.c_str(); }
	};

} // namespace mystd
#endif // ERRORS_H
