#pragma once
#include <variant>
#include "../Exception/BaseException.hpp"

namespace orl {
	template<typename T_, typename... Ts_>
	class Error : public BaseException {
	private:
		std::variant<T_, Ts_...> exceptions;
		
	public:
		template<typename... A>
		Error(A&&... args);
		
		std::string getNote() const override;
		
		std::string getDescription() const override;
	};
}

#include "Error.inl"