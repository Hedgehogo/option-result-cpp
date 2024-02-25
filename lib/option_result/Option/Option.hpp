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
		
		template<typename T_>
		class OptionIter;
	}
	
	template<typename T_>
	class Option;
	
	template<typename Type_>
	struct OptionSome {
	};
	
	template<typename T_>
	struct OptionSome<Option<T_> > {
		using type = T_;
	};
	
	template<typename Type>
	using OptionSomeT = typename OptionSome<Type>::type;
	
	template<typename T_>
	class Option {
	public:
		Option(T_ data) noexcept;
		
		Option() noexcept;
		
		auto is_some() const noexcept -> bool;
		
		auto some() const& noexcept -> T_ const&;
		
		auto some()& noexcept -> T_&;
		
		auto some()&& noexcept -> T_;
		
		auto some_or(T_ const& value) const& noexcept -> T_;
		
		auto some_or(T_& value)& noexcept -> T_&;
		
		auto some_or(T_&& value)&& noexcept -> T_;
		
		template<typename F>
		auto some_or_else(F fn) const& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>;
		
		template<typename F>
		auto some_or_else(F fn)& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&>;
		
		template<typename F>
		auto some_or_else(F fn)&& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_>;
		
		template<typename R = std::remove_pointer_t<T_>, typename... A>
		auto some_or_ptr(A&& ... args) const noexcept -> T_;
		
		template<typename F>
		auto map(F fn) const& -> Option<std::invoke_result_t<F, T_ const&> >;
		
		template<typename F>
		auto map(F fn)& -> Option<std::invoke_result_t<F, T_&> >;
		
		template<typename F>
		auto map(F fn)&& -> Option<std::invoke_result_t<F, T_> >;
		
		template<typename F>
		auto and_then(F fn) const& -> Option<OptionSomeT<std::invoke_result_t<F, T_ const&> > >;
		
		template<typename F>
		auto and_then(F fn)& -> Option<OptionSomeT<std::invoke_result_t<F, T_&> > >;
		
		template<typename F>
		auto and_then(F fn)&& -> Option<OptionSomeT<std::invoke_result_t<F, T_> > >;
		
		template<typename E>
		auto ok_or(E error) const& noexcept -> Result<T_ const&, E>;
		
		template<typename E>
		auto ok_or(E error)& noexcept -> Result<T_&, E>;
		
		template<typename E>
		auto ok_or(E error)&& noexcept -> Result<T_, E>;
		
		template<typename T>
		auto error_or(T ok) const& noexcept -> Result<T, T_ const&>;
		
		template<typename T>
		auto error_or(T ok)& noexcept -> Result<T, T_&>;
		
		template<typename T>
		auto error_or(T ok)&& noexcept -> Result<T, T_>;
		
		template<typename E = std::runtime_error>
		auto except(E const& exception = std::runtime_error("Some was requested, but the orl::Option was None")) const& -> T_ const&;
		
		template<typename E = std::runtime_error>
		auto except(E const& exception = std::runtime_error("Some was requested, but the orl::Option was None"))& -> T_&;
		
		template<typename E = std::runtime_error>
		auto except(E const& exception = std::runtime_error("Some was requested, but the orl::Option was None"))&& -> T_;
		
		auto ref() const& -> Option<T_ const&>;
		
		auto ref()& -> Option<T_&>;
		
		auto optional() const& noexcept -> std::optional<Ref<T_ const&> >;
		
		auto optional()& noexcept -> std::optional<Ref<T_&> >;
		
		auto optional()&& noexcept -> std::optional<T_>;
		
		auto begin() const -> detail::OptionIter<T_ const&>;
		
		auto begin() -> detail::OptionIter<T_&>;
		
		auto end() const -> detail::OptionIter<T_ const&>;
		
		auto end() -> detail::OptionIter<T_&>;
		
		template<typename T>
		auto operator==(Option<T> const& other) const noexcept -> bool;
		
		template<typename T>
		auto operator&&(Option<T> const& other) const& noexcept -> Option<std::tuple<T_ const&, T const&> >;
		
		template<typename T>
		auto operator&&(Option<T>& other)& noexcept -> Option<std::tuple<T_&, T&> >;
		
		template<typename T>
		auto operator&&(Option<T>&& other)&& noexcept -> Option<std::tuple<T_, T> >;
		
		auto operator&&(bool other) const& noexcept -> Option<T_ const&>;
		
		auto operator&&(bool other)& noexcept -> Option<T_&>;
		
		auto operator&&(bool other)&& noexcept -> Option<T_>;
		
		auto operator||(Option<T_> const& other) const& noexcept -> Option<T_ const&>;
		
		auto operator||(Option<T_>& other)& noexcept -> Option<T_&>;
		
		auto operator||(Option<T_>&& other)&& noexcept -> Option<T_>;
		
	private:
		detail::OptionImpl<T_> data_;
	};
	
	template<typename T>
	auto operator&&(bool first, Option<T> const& second) noexcept -> Option<T const&>;
	
	template<typename T>
	auto operator&&(bool first, Option<T>& second) noexcept -> Option<T&>;
	
	template<typename T>
	auto operator&&(bool first, Option<T>&& second) noexcept -> Option<T>;
	
	template<typename T>
	auto rv_or_clone(T object) -> T;
	
	template<typename T>
	auto clone(T const& object) -> T;
	
	namespace detail {
		template<typename T_>
		class OptionImpl {
		public:
			OptionImpl(T_ data) noexcept;
			
			OptionImpl() noexcept;
			
			auto is_some() const noexcept -> bool;
			
			auto some() noexcept -> T_&;
			
			auto some() const noexcept -> T_ const&;
		
		private:
			std::optional<Ref<T_> > data_;
		};
		
		template<typename T_>
		class OptionImpl<T_*> {
		public:
			OptionImpl(T_* data) noexcept;
			
			OptionImpl() noexcept;
			
			auto is_some() const noexcept -> bool;
			
			auto some() const noexcept -> T_* const&;
			
			auto some() noexcept -> T_*&;
		
		private:
			T_* data_;
		};
		
		template<typename T_>
		class OptionIter {
		public:
			OptionIter(T_ data);
			
			OptionIter() = default;
			
			auto operator*() -> T_;
			
			auto operator++() -> OptionIter&;
			
			auto operator!=(OptionIter<T_> const& other) -> bool;
		
		private:
			Option<T_> data_;
		};
	}
}
