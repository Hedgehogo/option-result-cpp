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
		using Data = std::variant<ref<T_>, ref<E_>>;
	
	public:
		static Result<T_, E_> Ok(T_ const& value) noexcept;
		
		static Result<T_, E_> Error(E_ const& value) noexcept;
		
		bool is_ok() const noexcept;
		
		T_ const& ok() const noexcept;
		
		T_ const& ok_or(T_ const& value) const noexcept;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		R* ok_or_ptr(A&& ... args) const noexcept;
		
		Option<const T_&> ok_or_none() const noexcept;
		
		E_ const& error() const noexcept;
		
		E_ const& error_or(E_ const& value) const noexcept;
		
		template<typename R = std::remove_pointer_t<E_>, typename... A>
		R* error_or_ptr(A&& ... args) const noexcept;
		
		Option<const E_&> error_or_none() const noexcept;
		
		template<typename R>
		R convert_ok_or(const R& value, std::function<R(T_ const&)> func) const noexcept;
		
		template<typename R, typename... A>
		R* convert_ok_or_ptr(std::function<R*(T_ const&)> func, A&& ... args) const noexcept;
		
		template<typename R>
		R convert_error_or(const R& value, std::function<R(E_ const&)> func) const noexcept;
		
		template<typename R, typename... A>
		R* convert_error_or_ptr(std::function<R*(E_ const&)> func, A&& ... args) const noexcept;
		
		T_ const& except() const;
		
		operator bool() const noexcept;
		
		template<typename T, typename E>
		bool operator ==(Result<T, E> const& other) const noexcept;
	
	private:
		Result(Data const& data);
		
		Data data_;
	};
}
