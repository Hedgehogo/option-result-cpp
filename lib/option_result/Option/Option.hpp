#pragma once

#include <optional>
#include <stdexcept>
#include "../Reference/Reference.hpp"

namespace orl {
	template<typename T, typename E>
	class Result;
	
	namespace detail {
		template<typename T>
		class Option;
	}
	
	template<typename T_>
	class Option final : public detail::Option<T_> {
	public:
		Option(const T_& data) noexcept;
		
		Option() noexcept;
		
		const T_& some_or(const T_& value) const noexcept;
		
		template<typename R>
		R convert_or(const R& value, std::function<R(const T_&)> func) const noexcept;
		
		template<typename R, typename... A>
		R* convert_or_ptr(std::function<R*(const T_&)> func, A&& ... value_args) const noexcept;
		
		template<typename E>
		Result<const T_&, E> ok_or(const E& error) const noexcept;
		
		template<typename T>
		Result<T, const T_&> error_or(const T& ok) const noexcept;
		
		template<typename E>
		const T_& except(const E& exception = std::runtime_error("Some was requested, but the orl::Option was None")) const;
		
		std::optional<T_> optional() const noexcept;
		
		operator bool() const noexcept;
		
		template<typename T>
		bool operator ==(Option<T> const& other) const noexcept;
	};
	
	namespace detail {
		template<typename T_>
		class Option {
		private:
			std::optional<ref<T_>> data_;
		
		public:
			Option(T_ const& data) noexcept;
			
			Option() noexcept;
			
			bool is_some() const noexcept;
			
			T_& some() noexcept;
			
			T_ const& some() const noexcept;
		};
		
		template<typename T_>
		class Option<T_*> {
		private:
			T_* data_;
		
		public:
			Option(T_* const& data) noexcept;
			
			Option() noexcept;
			
			bool is_some() const noexcept;
			
			T_*& some() noexcept;
			
			T_* const& some() const noexcept;
			
			template<typename R = T_, typename... A>
			R* some_or_ptr(A&& ... args) const noexcept;
		};
	}
}
