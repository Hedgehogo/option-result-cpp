#pragma once

#include <variant>
#include "../Exception/BaseException.hpp"

namespace orl {
	template<typename... Ts_>
	class Error : public BaseException {
	private:
		std::variant<Ts_...> errors_;
	
	public:
		template<typename... A>
		Error(A&& ... args);
		
		template<std::size_t Index, typename... A>
		static Error<Ts_...> make(A&&... args);
		
		std::string get_note() const override;
		
		std::string get_description() const override;
		
		void except() const;
		
		template<typename R>
		R& common();
		
		template<typename R>
		R const& common() const;
		
		template<typename... Ts>
		Error<Ts...> move_cast();
		
		template<typename... Ts>
		Error<Ts_..., Ts...> move_upcast();
		
		const std::variant<Ts_...>& variant() const;
	};
	
	namespace detail {
		template<typename T_>
		struct IsError : std::integral_constant<bool, false> {};
		
		template<typename... Ts_>
		struct IsError<Error<Ts_...> > : std::integral_constant<bool, true> {};
	}
	
	template<typename T_>
	constexpr bool is_error = detail::IsError<T_>::value;
	
	template<typename T>
	void except(T const& exception);
}

#include "Error.inl"