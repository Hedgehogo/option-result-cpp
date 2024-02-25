#pragma once

#include <variant>
#include <type_traits>
#include "../Reference/Reference.hpp"

namespace orl {
	template<typename T>
	class Option;
	
	template<typename T_, typename E_>
	class Result;
	
	template<typename Type_, typename E_>
	struct ResultOk {
	};
	
	template<typename T_, typename E_>
	struct ResultOk<Result<T_, E_>, E_> {
		using type = T_;
	};
	
	template<typename T, typename E>
	using ResultOkT = typename ResultOk<T, E>::type;
	
	template<typename Type_, typename T_>
	struct ResultError {
	};
	
	template<typename T_, typename E_>
	struct ResultError<Result<T_, E_>, T_> {
		using type = E_;
	};
	
	template<typename Type, typename T>
	using ResultErrorT = typename ResultError<Type, T>::type;
	
	template<typename T_, typename E_>
	class Result {
	protected:
		using Data = std::variant<Ref<T_>, Ref<E_> >;
	
	public:
		static auto Ok(T_ value) noexcept -> Result<T_, E_>;
		
		static auto Error(E_ value) noexcept -> Result<T_, E_>;
		
		auto is_ok() const noexcept -> bool;
		
		auto ok() const& noexcept -> T_ const&;
		
		auto ok()& noexcept -> T_&;
		
		auto ok()&& noexcept -> T_;
		
		auto ok_or(T_ const& value) const& noexcept -> T_;
		
		auto ok_or(T_& value)& noexcept -> T_&;
		
		auto ok_or(T_&& value)&& noexcept -> T_;
		
		template<typename F>
		auto ok_or_else(F fn) const& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>;
		
		template<typename F>
		auto ok_or_else(F fn)& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>;
		
		template<typename F>
		auto ok_or_else(F fn)&& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		auto ok_or_ptr(A&& ... args) const noexcept -> T_;
		
		auto ok_or_none() const& noexcept -> Option<T_ const&>;
		
		auto ok_or_none()& noexcept -> Option<T_&>;
		
		auto ok_or_none()&& noexcept -> Option<T_>;
		
		template<typename F>
		auto map_ok(F fn) const& -> Result<std::invoke_result_t<F, T_ const&>, E_ const&>;
		
		template<typename F>
		auto map_ok(F fn)& -> Result<std::invoke_result_t<F, T_&>, E_&>;
		
		template<typename F>
		auto map_ok(F fn)&& -> Result<std::invoke_result_t<F, T_>, E_>;
		
		template<typename F>
		auto ok_and_then(F fn) const& -> Result<ResultOkT<std::invoke_result_t<F, T_ const&>, E_ const&>, E_ const&>;
		
		template<typename F>
		auto ok_and_then(F fn)& -> Result<ResultOkT<std::invoke_result_t<F, T_&>, E_&>, E_&>;
		
		template<typename F>
		auto ok_and_then(F fn)&& -> Result<ResultOkT<std::invoke_result_t<F, T_>, E_>, E_>;
		
		auto is_error() const noexcept -> bool;
		
		auto error() const& noexcept -> E_ const&;
		
		auto error()& noexcept -> E_&;
		
		auto error()&& noexcept -> E_;
		
		auto error_or(E_ const& value) const& noexcept -> E_;
		
		auto error_or(E_& value)& noexcept -> E_&;
		
		auto error_or(E_&& value)&& noexcept -> E_;
		
		template<typename F>
		auto error_or_else(F fn) const& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>;
		
		template<typename F>
		auto error_or_else(F fn)& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>;
		
		template<typename F>
		auto error_or_else(F fn)&& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>;
		
		template<typename R = std::remove_pointer_t<E_>, typename... A>
		auto error_or_ptr(A&& ... args) const noexcept -> E_;
		
		auto error_or_none() const& noexcept -> Option<E_ const&>;
		
		auto error_or_none()& noexcept -> Option<E_&>;
		
		auto error_or_none()&& noexcept -> Option<E_>;
		
		template<typename F>
		auto map_error(F fn) const& -> Result<T_ const&, std::invoke_result_t<F, E_ const&> >;
		
		template<typename F>
		auto map_error(F fn)& -> Result<T_&, std::invoke_result_t<F, E_&> >;
		
		template<typename F>
		auto map_error(F fn)&& -> Result<T_, std::invoke_result_t<F, E_> >;
		
		template<typename F>
		auto error_and_then(F fn) const& -> Result<T_ const&, ResultErrorT<std::invoke_result_t<F, E_ const&>, T_ const&> >;
		
		template<typename F>
		auto error_and_then(F fn)& -> Result<T_&, ResultErrorT<std::invoke_result_t<F, E_&>, T_&> >;
		
		template<typename F>
		auto error_and_then(F fn)&& -> Result<T_, ResultErrorT<std::invoke_result_t<F, E_>, T_> >;
		
		auto except() const& -> T_ const&;
		
		auto except()& -> T_&;
		
		auto except()&& -> T_;
		
		template<typename T, typename E>
		auto operator==(Result<T, E> const& other) const noexcept -> bool;
	
	private:
		Result(Data&& data);
		
		Data data_;
	};
}
