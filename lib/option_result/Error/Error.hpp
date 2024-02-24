#pragma once

#include <variant>
#include "../Exception/BaseException.hpp"

namespace orl {
	template<typename... Ts_>
	class Error : public BaseException {
	public:
		template<typename... A>
		Error(A&& ... args);
		
		template<std::size_t Index, typename... A>
		static auto make(A&&... args) -> Error<Ts_...>;
		
		auto get_note() const -> std::string override;
		
		auto get_description() const -> std::string override;
		
		auto except() const -> void;
		
		template<typename R>
		auto common() -> R&;
		
		template<typename R>
		auto common() const -> R const&;
		
		template<typename... Ts>
		auto move_cast() -> Error<Ts...>;
		
		template<typename... Ts>
		auto move_upcast() -> Error<Ts_..., Ts...>;
		
		auto variant() const -> std::variant<Ts_...> const&;
		
	private:
		std::variant<Ts_...> errors_;
	};
	
	namespace detail {
		template<typename T_>
		struct IsError : std::integral_constant<bool, false> {};
		
		template<typename... Ts_>
		struct IsError<Error<Ts_...> > : std::integral_constant<bool, true> {};
	}
	
	template<typename T_>
	constexpr auto is_error = detail::IsError<T_>::value;
	
	template<typename T>
	auto except(T const& exception) -> void;
}

#include "Error.inl"