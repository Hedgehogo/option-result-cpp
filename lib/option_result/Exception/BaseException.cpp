#include "BaseException.hpp"
#include <cstring>
#include <ostream>

namespace orl {
	std::string BaseException::get_note() const {
		return std::string();
	}
	
	std::string BaseException::get_full_description() const {
		return get_note() + get_description();
	}
	
	const char* BaseException::what() const noexcept {
		std::string str{get_full_description()};
		char* result{new char[str.size() + 1]{}};
		std::strcpy(result, str.c_str());
		return result;
	}
	
	std::ostream& operator<<(std::ostream& stream, BaseException const& exception) {
		stream << exception.get_description();
		return stream;
	}
}