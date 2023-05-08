#include "BaseException.hpp"
#include <cstring>

namespace orl {
	std::string BaseException::getNote() const {
		return std::string();
	}
	
	std::string BaseException::getFullDescription() const {
		return getNote() + getDescription();
	}
	
	const char* BaseException::what() const noexcept {
		std::string str{getFullDescription()};
		char* result{new char[str.size() + 1]{}};
		strcpy(result, str.c_str());
		return result;
	}
	
	std::ostream& operator<<(std::ostream& stream, BaseException const& exception) {
		stream << exception.getFullDescription();
		return stream;
	}
}