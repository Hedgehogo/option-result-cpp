#pragma once

#include <variant>
#include <type_traits>
#include "../Reference/Reference.hpp"

namespace orl {
	template<typename T>
	class Option;
	
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
		
		T_ move_ok() noexcept;
		
		T_ ok_or(T_ const& value) const& noexcept;
		
		T_& ok_or(T_& value)& noexcept;
		
		T_ ok_or(T_&& value)&& noexcept;
		
		T_ move_ok_or(T_&& value) noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		ok_or_else(F fn) const& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>
		ok_or_else(F fn)& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		ok_or_else(F fn)&& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		move_ok_or_else(F fn) noexcept;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		T_ ok_or_ptr(A&& ... args) const noexcept;
		
		Option<T_ const&> ok_or_none() const& noexcept;
		
		Option<T_&> ok_or_none()& noexcept;
		
		Option<T_> ok_or_none()&& noexcept;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_ const&> > map_ok(F fn) const&;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_&> > map_ok(F fn)&;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_> > map_ok(F fn)&&;
		
		E_ const& error() const& noexcept;
		
		E_& error()& noexcept;
		
		E_ error()&& noexcept;
		
		E_ move_error() noexcept;
		
		E_ error_or(E_ const& value) const& noexcept;
		
		E_& error_or(E_& value)& noexcept;
		
		E_ error_or(E_&& value)&& noexcept;
		
		E_ move_error_or(E_&& value) noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		error_or_else(F fn) const& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>
		error_or_else(F fn)& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		error_or_else(F fn)&& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		move_error_or_else(F fn) noexcept;
		
		template<typename R = std::remove_pointer_t<E_>, typename... A>
		E_ error_or_ptr(A&& ... args) const noexcept;
		
		Option<E_ const&> error_or_none() const& noexcept;
		
		Option<E_&> error_or_none()& noexcept;
		
		Option<E_> error_or_none()&& noexcept;
		
		template<typename F>
		Option<std::invoke_result_t<F, E_ const&> > map_error(F fn) const&;
		
		template<typename F>
		Option<std::invoke_result_t<F, E_&> > map_error(F fn)&;
		
		template<typename F>
		Option<std::invoke_result_t<F, E_> > map_error(F fn)&&;
		
		T_ const& except() const&;
		
		T_& except()&;
		
		T_ except()&&;
		
		T_ move_except();
		
		operator bool() const noexcept;
		
		template<typename T, typename E>
		bool operator==(Result<T, E> const& other) const noexcept;
	
	private:
		Result(Data&& data);
		
		Data data_;
	};
}
