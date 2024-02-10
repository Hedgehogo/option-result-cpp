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
		Option(T_ data) noexcept;
		
		Option() noexcept;
		
		bool is_some() const noexcept;
		
		T_ const& some() const& noexcept;
		
		T_& some()& noexcept;
		
		T_ some()&& noexcept;
		
		T_ move_some() noexcept;
		
		T_ some_or(T_ const& value) const& noexcept;
		
		T_& some_or(T_& value)& noexcept;
		
		T_ some_or(T_&& value)&& noexcept;
		
		T_ move_some_or(T_&& value) noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		some_or_else(F fn) const& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>
		some_or_else(F fn)& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		some_or_else(F fn)&& noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		move_some_or_else(F fn) noexcept;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		T_ some_or_ptr(A&& ... args) const noexcept;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_ const&> > map(F fn) const&;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_&> > map(F fn)&;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_> > map(F fn)&&;
		
		template<typename E>
		Result<T_ const&, E> ok_or(E error) const& noexcept;
		
		template<typename E>
		Result<T_&, E> ok_or(E error)& noexcept;
		
		template<typename E>
		Result<T_, E> ok_or(E error)&& noexcept;
		
		template<typename T>
		Result<T, T_ const&> error_or(T ok) const& noexcept;
		
		template<typename T>
		Result<T, T_&> error_or(T ok)& noexcept;
		
		template<typename T>
		Result<T, T_> error_or(T ok)&& noexcept;
		
		template<typename E = std::runtime_error>
		T_ const& except(E const& exception = std::runtime_error("Some was requested, but the orl::Option was None")) const&;
		
		template<typename E = std::runtime_error>
		T_& except(E const& exception = std::runtime_error("Some was requested, but the orl::Option was None"))&;
		
		template<typename E = std::runtime_error>
		T_ except(E const& exception = std::runtime_error("Some was requested, but the orl::Option was None"))&&;
		
		template<typename E = std::runtime_error>
		T_ move_except(const E& exception = std::runtime_error("Some was requested, but the orl::Option was None"));
		
		std::optional<ref<T_ const&> > optional() const& noexcept;
		
		std::optional<ref<T_&> > optional()& noexcept;
		
		std::optional<T_> optional()&& noexcept;
		
		operator bool() const noexcept;
		
		template<typename T>
		bool operator==(Option<T> const& other) const noexcept;
	
	private:
		detail::OptionImpl<T_> data_;
	};
	
	namespace detail {
		template<typename T_>
		class OptionImpl {
		private:
			std::optional<ref<T_> > data_;
		
		public:
			OptionImpl(T_ data) noexcept;
			
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
			OptionImpl(T_* data) noexcept;
			
			OptionImpl() noexcept;
			
			bool is_some() const noexcept;
			
			T_* const& some() const noexcept;
			
			T_*& some() noexcept;
		};
	}
}
