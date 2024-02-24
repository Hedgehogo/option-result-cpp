#include "BaseException.hpp"
#include <cstring>
#include <ostream>

namespace orl {
	auto BaseException::get_note() const -> std::string {
		return std::string{};
	}
	
	auto BaseException::get_full_description() const -> std::string {
		return get_note() + get_description();
	}
	
	auto BaseException::what() const noexcept -> const char* {
		std::string str{get_full_description()};
		char* result{new char[str.size() + 1]{}};
		std::strcpy(result, str.c_str());
		return result;
	}
	
	auto operator<<(std::ostream& stream, BaseException const& exception) -> std::ostream& {
		stream << exception.get_description();
		return stream;
	}
}