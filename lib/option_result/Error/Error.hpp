#pragma once
#include <variant>
#include "../Exception/BaseException.hpp"

namespace orl {
	template<typename T_, typename... Ts_>
	class Error : public BaseException {
	private:
		std::variant<T_, Ts_...> exceptions_;
		
	public:
		template<typename... A>
		Error(A&&... args);
		
		std::string get_note() const override;
		
		std::string get_description() const override;
		
		template<typename R>
		R& common();
		
		template<typename R>
		const R& common() const;
	};
}

#include "Error.inl"