#pragma once

#include <variant>
#include "../Reference/Reference.hpp"

namespace orl {
	template<typename T>
	class Option;
	
	template<typename T_, typename E_>
	class Result {
	protected:
		using Data = std::variant<ref<T_>, ref<E_>>;
	
	public:
		static Result<T_, E_> Ok(const T_& value) noexcept;
		
		static Result<T_, E_> Error(const E_& value) noexcept;
		
		bool is_ok() const noexcept;
		
		const T_& ok() const noexcept;
		
		const T_& ok_or(const T_& value) const noexcept;
		
		Option<const T_&> ok_or_none() const noexcept;
		
		const E_& error() const noexcept;
		
		const E_& error_or(const E_& value) const noexcept;
		
		Option<const E_&> error_or_none() const noexcept;
		
		template<typename R>
		R convert_ok_or(const R& value, std::function<R(const T_&)> func) const noexcept;
		
		template<typename R, typename... A>
		R* convert_ok_or_ptr(std::function<R*(const T_&)> func, A&& ... args) const noexcept;
		
		template<typename R>
		R convert_error_or(const R& value, std::function<R(const E_&)> func) const noexcept;
		
		template<typename R, typename... A>
		R* convert_error_or_ptr(std::function<R*(const E_&)> func, A&& ... args) const noexcept;
		
		const T_& except() const;
		
		operator bool() const noexcept;
		
		template<typename T, typename E>
		bool operator ==(Result<T, E> const& other) const noexcept;
	
	private:
		Result(const Data& data);
		
		Data data_;
	};
}
