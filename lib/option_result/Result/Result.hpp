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
		using Data = std::variant<ref<T_>, ref<E_> >;
	
	public:
		static Result<T_, E_> Ok(T_ value) noexcept;
		
		static Result<T_, E_> Error(E_ value) noexcept;
		
		bool is_ok() const noexcept;
		
		T_ const& ok() const& noexcept;
		
		T_& ok()& noexcept;
		
		T_ ok()&& noexcept;
		
		T_ ok_or(T_ const& value) const& noexcept;
		
		T_& ok_or(T_& value)& noexcept;
		
		T_ ok_or(T_&& value)&& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		ok_or_else(F fn) const& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>
		ok_or_else(F fn)& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		ok_or_else(F fn)&& noexcept;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		T_ ok_or_ptr(A&& ... args) const noexcept;
		
		Option<T_ const&> ok_or_none() const& noexcept;
		
		Option<T_&> ok_or_none()& noexcept;
		
		Option<T_> ok_or_none()&& noexcept;
		
		template<typename F>
		Result<std::invoke_result_t<F, T_ const&>, E_ const&> map_ok(F fn) const&;
		
		template<typename F>
		Result<std::invoke_result_t<F, T_&>, E_&> map_ok(F fn)&;
		
		template<typename F>
		Result<std::invoke_result_t<F, T_>, E_> map_ok(F fn)&&;
		
		template<typename F>
		Result<ResultOkT<std::invoke_result_t<F, T_ const&>, E_ const&>, E_ const&> ok_and_then(F fn) const&;
		
		template<typename F>
		Result<ResultOkT<std::invoke_result_t<F, T_&>, E_&>, E_&> ok_and_then(F fn)&;
		
		template<typename F>
		Result<ResultOkT<std::invoke_result_t<F, T_>, E_>, E_> ok_and_then(F fn)&&;
		
		bool is_error() const noexcept;
		
		E_ const& error() const& noexcept;
		
		E_& error()& noexcept;
		
		E_ error()&& noexcept;
		
		E_ error_or(E_ const& value) const& noexcept;
		
		E_& error_or(E_& value)& noexcept;
		
		E_ error_or(E_&& value)&& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		error_or_else(F fn) const& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>
		error_or_else(F fn)& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		error_or_else(F fn)&& noexcept;
		
		template<typename R = std::remove_pointer_t<E_>, typename... A>
		E_ error_or_ptr(A&& ... args) const noexcept;
		
		Option<E_ const&> error_or_none() const& noexcept;
		
		Option<E_&> error_or_none()& noexcept;
		
		Option<E_> error_or_none()&& noexcept;
		
		template<typename F>
		Result<T_ const&, std::invoke_result_t<F, E_ const&> > map_error(F fn) const&;
		
		template<typename F>
		Result<T_&, std::invoke_result_t<F, E_&> > map_error(F fn)&;
		
		template<typename F>
		Result<T_, std::invoke_result_t<F, E_> > map_error(F fn)&&;
		
		template<typename F>
		Result<T_ const&, ResultErrorT<std::invoke_result_t<F, E_ const&>, T_ const&> > error_and_then(F fn) const&;
		
		template<typename F>
		Result<T_&, ResultErrorT<std::invoke_result_t<F, E_&>, T_&> > error_and_then(F fn)&;
		
		template<typename F>
		Result<T_, ResultErrorT<std::invoke_result_t<F, E_>, T_> > error_and_then(F fn)&&;
		
		T_ const& except() const&;
		
		T_& except()&;
		
		T_ except()&&;
		
		template<typename T, typename E>
		bool operator==(Result<T, E> const& other) const noexcept;
	
	private:
		Result(Data&& data);
		
		Data data_;
	};
}
