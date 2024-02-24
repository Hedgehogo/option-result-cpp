#include "../Result/Result.hpp"

namespace orl {
	template<typename T_>
	Option<T_>::Option(T_ data) noexcept : data_(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	Option<T_>::Option() noexcept : data_() {
	}
	
	template<typename T_>
	auto Option<T_>::is_some() const noexcept -> bool {
		return data_.is_some();
	}
	
	template<typename T_>
	auto Option<T_>::some() const& noexcept -> T_ const& {
		return data_.some();
	}
	
	template<typename T_>
	auto Option<T_>::some()& noexcept -> T_& {
		return data_.some();
	}
	
	template<typename T_>
	auto Option<T_>::some()&& noexcept -> T_ {
		return std::forward<T_>(data_.some());
	}
	
	template<typename T_>
	auto Option<T_>::some_or(T_ const& value) const& noexcept -> T_ {
		if(data_.is_some()) {
			return data_.some();
		}
		return value;
	}
	
	template<typename T_>
	auto Option<T_>::some_or(T_& value)& noexcept -> T_& {
		if(data_.is_some()) {
			return data_.some();
		}
		return value;
	}
	
	template<typename T_>
	auto Option<T_>::some_or(T_&& value)&& noexcept -> T_ {
		if(data_.is_some()) {
			return std::forward<T_>(data_.some());
		}
		return std::forward<T_>(value);
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::some_or_else(F fn) const& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(data_.is_some()) {
			return data_.some();
		}
		return fn();
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::some_or_else(F fn)& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&> {
		if(data_.is_some()) {
			return data_.some();
		}
		return fn();
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::some_or_else(F fn)&& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(data_.is_some()) {
			return std::forward<T_>(data_.some());
		}
		return fn();
	}
	
	template<typename T_>
	template<typename R, typename... A>
	auto Option<T_>::some_or_ptr(A&& ... args) const noexcept -> T_ {
		if(data_.is_some()) {
			return data_.some();
		}
		return new R{std::forward<A...>(args)...};
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::map(F fn) const& -> Option<std::invoke_result_t<F, T_ const&> > {
		if(data_.is_some()) {
			return {fn(data_.some())};
		}
		return {};
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::map(F fn)& -> Option<std::invoke_result_t<F, T_&> > {
		if(data_.is_some()) {
			return {fn(data_.some())};
		}
		return {};
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::map(F fn)&& -> Option<std::invoke_result_t<F, T_> > {
		if(data_.is_some()) {
			return {fn(std::forward<T_>(data_.some()))};
		}
		return {};
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::and_then(F fn) const& -> Option<OptionSomeT<std::invoke_result_t<F, T_ const&> > > {
		if(data_.is_some()) {
			return fn(data_.some());
		}
		return {};
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::and_then(F fn)& -> Option<OptionSomeT<std::invoke_result_t<F, T_&> > > {
		if(data_.is_some()) {
			return fn(data_.some());
		}
		return {};
	}
	
	template<typename T_>
	template<typename F>
	auto Option<T_>::and_then(F fn)&& -> Option<OptionSomeT<std::invoke_result_t<F, T_> > > {
		if(data_.is_some()) {
			return fn(std::forward<T_>(data_.some()));
		}
		return {};
	}
	
	template<typename T_>
	template<typename E>
	auto Option<T_>::ok_or(E error) const& noexcept -> Result<T_ const&, E> {
		if(data_.is_some()) {
			return Result<const T_&, E>::Ok(data_.some());
		}
		return Result<const T_&, E>::Error(std::forward<E>(error));
	}
	
	template<typename T_>
	template<typename E>
	auto Option<T_>::ok_or(E error)& noexcept -> Result<T_&, E> {
		if(data_.is_some()) {
			return Result<T_&, E>::Ok(data_.some());
		}
		return Result<T_&, E>::Error(std::forward<E>(error));
	}
	
	template<typename T_>
	template<typename E>
	auto Option<T_>::ok_or(E error)&& noexcept -> Result<T_, E> {
		if(data_.is_some()) {
			return Result<T_, E>::Ok(std::forward<T_>(data_.some()));
		}
		return Result<T_, E>::Error(std::forward<E>(error));
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::error_or(T ok) const& noexcept -> Result<T, T_ const&> {
		if(data_.is_some()) {
			return Result<T, const T_&>::Error(data_.some());
		}
		return Result<T, const T_&>::Ok(std::forward<T>(ok));
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::error_or(T ok)& noexcept -> Result<T, T_&> {
		if(data_.is_some()) {
			return Result<T, T_&>::Error(data_.some());
		}
		return Result<T, T_&>::Ok(std::forward<T>(ok));
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::error_or(T ok)&& noexcept -> Result<T, T_> {
		if(data_.is_some()) {
			return Result<T, T_>::Error(data_.some());
		}
		return Result<T, T_>::Ok(std::forward<T>(ok));
	}
	
	template<typename T_>
	template<typename E>
	auto Option<T_>::except(E const& exception) const& -> T_ const& {
		if(!data_.is_some()) {
			orl::except(exception);
		}
		return data_.some();
	}
	
	template<typename T_>
	template<typename E>
	auto Option<T_>::except(E const& exception)& -> T_& {
		if(!data_.is_some()) {
			orl::except(exception);
		}
		return data_.some();
	}
	
	template<typename T_>
	template<typename E>
	auto Option<T_>::except(E const& exception)&& -> T_ {
		if(!data_.is_some()) {
			orl::except(exception);
		}
		return std::forward<T_>(data_.some());
	}
	
	template<typename T_>
	auto Option<T_>::optional() const& noexcept -> std::optional<ref<T_ const&> > {
		if(data_.is_some()) {
			return std::optional<ref<T_ const&> >{data_.some()};
		}
		return std::optional<ref<T_ const&> >{};
	}
	
	template<typename T_>
	auto Option<T_>::optional()& noexcept -> std::optional<ref<T_&> > {
		if(data_.is_some()) {
			return std::optional<ref<T_&> >{data_.some()};
		}
		return std::optional<ref<T_&> >{};
	}
	
	template<typename T_>
	auto Option<T_>::optional()&& noexcept -> std::optional<T_> {
		if(data_.is_some()) {
			return std::optional<T_>{data_.some()};
		}
		return std::optional<T_>{};
	}
	
	template<typename T_>
	auto Option<T_>::begin() const -> detail::OptionIter<const T_&> {
		if(data_.is_some()) {
			return detail::OptionIter<T_ const&>{data_.some()};
		}
		return detail::OptionIter<T_ const&>{};
	}
	
	template<typename T_>
	auto Option<T_>::begin() -> detail::OptionIter<T_&> {
		if(data_.is_some()) {
			return detail::OptionIter<T_&>{data_.some()};
		}
		return detail::OptionIter<T_&>{};
	}
	
	template<typename T_>
	auto Option<T_>::end() const -> detail::OptionIter<const T_&> {
		return detail::OptionIter<T_ const&>{};
	}
	
	template<typename T_>
	auto Option<T_>::end() -> detail::OptionIter<T_&> {
		return detail::OptionIter<T_&>{};
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::operator==(Option<T> const& other) const noexcept -> bool {
		if(data_.is_some()) {
			if(other.is_some()) {
				return data_.some() == other.some();
			}
			return false;
		}
		return !other.is_some();
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::operator&&(Option<T> const& other) const& noexcept -> Option<std::tuple<T_ const&, T const&> > {
		if(data_.is_some() && other.is_some()) {
			return {{data_.some(), other.some()}};
		}
		return {};
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::operator&&(Option<T>& other)& noexcept -> Option<std::tuple<T_&, T&> > {
		if(data_.is_some() && other.is_some()) {
			return {{data_.some(), other.some()}};
		}
		return {};
	}
	
	template<typename T_>
	template<typename T>
	auto Option<T_>::operator&&(Option<T>&& other)&& noexcept -> Option<std::tuple<T_, T> > {
		if(data_.is_some() && other.is_some()) {
			return {{std::forward<T_>(data_.some()), std::move(other).some()}};
		}
		return {};
	}
	
	template<typename T_>
	auto Option<T_>::operator&&(bool other) const& noexcept -> Option<const T_&> {
		if(data_.is_some() && other) {
			return {data_.some()};
		}
		return {};
	}
	
	template<typename T_>
	auto Option<T_>::operator&&(bool other)& noexcept -> Option<T_&> {
		if(data_.is_some() && other) {
			return {data_.some()};
		}
		return {};
	}
	
	template<typename T_>
	auto Option<T_>::operator&&(bool other)&& noexcept -> Option<T_> {
		if(data_.is_some() && other) {
			return {std::forward<T_>(data_.some())};
		}
		return {};
	}
	
	template<typename T_>
	auto Option<T_>::operator||(Option<T_> const& other) const& noexcept -> Option<T_ const&> {
		if(data_.is_some()) {
			return {data_.some()};
		}
		if(other.is_some()) {
			return {other.some()};
		}
		return {};
	}
	
	template<typename T_>
	auto Option<T_>::operator||(Option<T_>& other)& noexcept -> Option<T_&> {
		if(data_.is_some()) {
			return {data_.some()};
		}
		if(other.is_some()) {
			return {other.some()};
		}
		return {};
	}
	
	template<typename T_>
	auto Option<T_>::operator||(Option<T_>&& other)&& noexcept -> Option<T_> {
		if(data_.is_some()) {
			return {std::forward<T_>(data_.some())};
		}
		if(other.is_some()) {
			return {std::move(other).some()};
		}
		return {};
	}
	
	namespace detail {
		template<typename T_>
		OptionImpl<T_>::OptionImpl(T_ data) noexcept : data_(std::forward<T_>(data)) {
		}
		
		template<typename T_>
		OptionImpl<T_>::OptionImpl() noexcept : data_() {
		}
		
		template<typename T_>
		auto OptionImpl<T_>::is_some() const noexcept -> bool {
			return data_.has_value();
		}
		
		template<typename T_>
		auto OptionImpl<T_>::some() noexcept -> T_& {
			return *data_;
		}
		
		template<typename T_>
		auto OptionImpl<T_>::some() const noexcept -> T_ const& {
			return *data_;
		}
		
		template<typename T_>
		OptionImpl<T_*>::OptionImpl(T_* data) noexcept : data_(data) {
		}
		
		template<typename T_>
		OptionImpl<T_*>::OptionImpl() noexcept : data_(nullptr) {
		}
		
		template<typename T_>
		auto OptionImpl<T_*>::is_some() const noexcept -> bool {
			return data_ != nullptr;
		}
		
		template<typename T_>
		auto OptionImpl<T_*>::some() noexcept -> T_*& {
			return data_;
		}
		
		template<typename T_>
		auto OptionImpl<T_*>::some() const noexcept -> T_* const& {
			return data_;
		}
		
		template<typename T_>
		OptionIter<T_>::OptionIter(T_ data) : data_(std::forward<T_>(data)) {
		}
		
		template<typename T_>
		auto OptionIter<T_>::operator*() -> T_ {
			return std::forward<T_>(data_.some());
		}
		
		template<typename T_>
		auto OptionIter<T_>::operator++() -> OptionIter<T_>& {
			data_ = Option<T_>{};
			return *this;
		}
		
		template<typename T_>
		auto OptionIter<T_>::operator!=(const OptionIter<T_>& other) -> bool {
			return data_.is_some();
		}
	}
}