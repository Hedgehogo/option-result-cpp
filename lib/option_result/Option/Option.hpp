#pragma once

#include <optional>
#include <stdexcept>
#include "../Reference/Reference.hpp"
#include "../Error/Error.hpp"

namespace orl {
	template<typename T_, typename E_>
	class Result;
	
	namespace detail {
		template<typename T_>
		class OptionImpl;
	}
	
	template<typename T_>
	class Option {
	public:
		Option(const T_& data) noexcept;
		
		Option() noexcept;
		
		bool is_some() const noexcept;
		
		T_& some() noexcept;
		
		T_ const& some() const noexcept;
		
		const T_& some_or(const T_& value) const noexcept;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		R* some_or_ptr(A&& ... args) const noexcept;
		
		template<typename R>
		R convert_or(const R& value, std::function<R(const T_&)> func) const noexcept;
		
		template<typename R, typename... A>
		R* convert_or_ptr(std::function<R*(const T_&)> func, A&& ... value_args) const noexcept;
		
		template<typename E>
		Result<const T_&, E> ok_or(const E& error) const noexcept;
		
		template<typename T>
		Result<T, const T_&> error_or(const T& ok) const noexcept;
		
		template<typename E = std::runtime_error>
		const T_& except(const E& exception = std::runtime_error("Some was requested, but the orl::Option was None")) const;
		
		std::optional<T_> optional() const noexcept;
		
		operator bool() const noexcept;
		
		template<typename T>
		bool operator ==(Option<T> const& other) const noexcept;
		
	private:
		detail::OptionImpl<T_> data_;
	};
	
	namespace detail {
		template<typename T_>
		class OptionImpl {
		private:
			std::optional<ref<T_>> data_;
		
		public:
			OptionImpl(T_ const& data) noexcept;
			
			OptionImpl() noexcept;
			
			bool is_some() const noexcept;
			
			T_& some() noexcept;
			
			T_ const& some() const noexcept;
		};
		
		template<typename T_>
		class OptionImpl<T_*> {
		private:
			T_* data_;
		
		public:
			OptionImpl(T_* const& data) noexcept;
			
			OptionImpl() noexcept;
			
			bool is_some() const noexcept;
			
			T_*& some() noexcept;
			
			T_* const& some() const noexcept;
		};
	}
}
