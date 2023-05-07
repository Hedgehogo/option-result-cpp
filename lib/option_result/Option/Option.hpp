#pragma once

#include <optional>
#include <functional>

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
		Result<T_, E> ok_or(const E& error) const noexcept;
		
		template<typename O>
		Result<T_, O> error_or(const O& ok) const noexcept;
		
		template<typename E>
		const T_& except(const E& exception) const;
		
		std::optional<T_> optional() const noexcept;
		
		operator bool() const noexcept;
		
		bool operator ==(Option<T_> const& other) const noexcept;
	};
	
	namespace detail {
		template<typename T>
		class Option {
		private:
			std::optional<T> data_;
		
		public:
			Option(const T& data) noexcept;
			
			Option() noexcept;
			
			bool is_some() const noexcept;
			
			T& some() noexcept;
			
			const T& some() const noexcept;
		};
		
		template<typename T>
		class Option<T*> {
		private:
			T* data_;
		
		public:
			Option(const T*& data) noexcept;
			
			Option() noexcept;
			
			bool is_some() const noexcept;
			
			T*& some() noexcept;
			
			const T*& some() const noexcept;
			
			template<typename... A>
			const T*& some_or_ptr(A&& ... args) const noexcept;
		};
	}
}
