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
		
		T_ const& some() const noexcept;
		
		T_& some() noexcept;
		
		T_ move_some() noexcept;
		
		const T_& some_or(const T_& value) const noexcept;
		
		T_ move_some_or(T_&& value) noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_ const&, F>, T_ const&>
		some_or_else(F fn) const noexcept;
		
		template<typename F>
		std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>
		move_some_or_else(F fn) noexcept;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		T_ some_or_ptr(A&& ... args) const noexcept;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_ const&> > map(F fn) const;
		
		template<typename F>
		Option<std::invoke_result_t<F, T_&> > map(F fn);
		
		template<typename E>
		Result<const T_&, E> ok_or(const E& error) const noexcept;
		
		template<typename T>
		Result<T, const T_&> error_or(const T& ok) const noexcept;
		
		template<typename E = std::runtime_error>
		const T_& except(const E& exception = std::runtime_error("Some was requested, but the orl::Option was None")) const;
		
		template<typename E = std::runtime_error>
		T_& except(const E& exception = std::runtime_error("Some was requested, but the orl::Option was None"));
		
		template<typename E = std::runtime_error>
		T_ move_except(const E& exception = std::runtime_error("Some was requested, but the orl::Option was None"));
		
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
			
			T_*& some() noexcept;
			
			T_* const& some() const noexcept;
		};
	}
}
