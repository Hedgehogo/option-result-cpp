#include "../Result/Result.hpp"

namespace orl {
	template<typename T_>
	Option<T_>::Option(T_ data) noexcept : data_(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	Option<T_>::Option() noexcept : data_() {
	}
	
	template<typename T_>
	bool Option<T_>::is_some() const noexcept {
		return data_.is_some();
	}
	
	template<typename T_>
	T_ const& Option<T_>::some() const noexcept {
		return data_.some();
	}
	
	template<typename T_>
	T_& Option<T_>::some() noexcept {
		return data_.some();
	}
	
	template<typename T_>
	T_ Option<T_>::move_some() noexcept {
		return std::move(data_.some());
	}
	
	template<typename T_>
	const T_& Option<T_>::some_or(const T_& value) const noexcept {
		if(data_.is_some()) {
			return data_.some();
		} else {
			return value;
		}
	}
	
	template<typename T_>
	T_ Option<T_>::move_some_or(T_&& value) noexcept {
		if(data_.is_some()) {
			return std::move(data_.some());
		} else {
			return std::move(value);
		}
	}
	
	template<typename T_>
	template<typename R, typename... A>
	R* Option<T_>::some_or_ptr(A&& ... args) const noexcept {
		if(data_.is_some()) {
			return data_.some();
		} else {
			return new R{std::forward<A...>(args)...};
		}
	}
	
	template<typename T_>
	template<typename R>
	R Option<T_>::convert_or(const R& value, std::function<R(const T_&)> func) const {
		if(data_.is_some()) {
			return func(data_.some());
		} else {
			return value;
		}
	}
	
	template<typename T_>
	template<typename R, typename... A>
	R* Option<T_>::convert_or_ptr(std::function<R*(const T_&)> func, A&& ... value_args) const {
		if(data_.is_some()) {
			return func(data_.some());
		} else {
			return new T_{std::forward<A...>(value_args)...};
		}
	}
	
	template<typename T_>
	template<typename E>
	Result<const T_&, E> Option<T_>::ok_or(const E& error) const noexcept {
		if(data_.is_some()) {
			return Result<const T_&, E>::Ok(data_.some());
		} else {
			return Result<const T_&, E>::Error(error);
		}
	}
	
	template<typename T_>
	template<typename T>
	Result<T, const T_&> Option<T_>::error_or(const T& ok) const noexcept {
		if(data_.is_some()) {
			return Result<T, const T_&>::Error(data_.some());
		} else {
			return Result<T, const T_&>::Ok(ok);
		}
	}
	
	template<typename T_>
	template<typename E>
	const T_& Option<T_>::except(const E& exception) const {
		if(!data_.is_some()) {
			orl::except(exception);
		}
		return data_.some();
	}
	
	template<typename T_>
	template<typename E>
	T_& Option<T_>::except(const E& exception) {
		if(!data_.is_some()) {
			orl::except(exception);
		}
		return data_.some();
	}
	
	template<typename T_>
	template<typename E>
	T_ Option<T_>::move_except(const E& exception) {
		if(!data_.is_some()) {
			orl::except(exception);
		}
		return std::move(data_.some());
	}
	
	template<typename T_>
	std::optional<T_> Option<T_>::optional() const noexcept {
		if(data_.is_some()) {
			return std::optional<T_>{data_.some()};
		} else {
			return std::optional<T_>{};
		}
	}
	
	template<typename T_>
	Option<T_>::operator bool() const noexcept {
		return data_.is_some();
	}
	
	template<typename T_>
	template<typename T>
	bool Option<T_>::operator==(const Option<T>& other) const noexcept {
		if(data_.is_some()) {
			if(other.is_some()) {
				return data_.some() == other.some();
			}
			return false;
		}
		return !other.is_some();
	}
	
	namespace detail {
		template<typename T_>
		OptionImpl<T_>::OptionImpl(T_ data) noexcept : data_(std::forward<T_>(data)) {
		}
		
		template<typename T_>
		OptionImpl<T_>::OptionImpl() noexcept : data_() {
		}
		
		template<typename T_>
		bool OptionImpl<T_>::is_some() const noexcept {
			return data_.has_value();
		}
		
		template<typename T_>
		T_& OptionImpl<T_>::some() noexcept {
			return *data_;
		}
		
		template<typename T_>
		T_ const& OptionImpl<T_>::some() const noexcept {
			return *data_;
		}
		
		template<typename T_>
		OptionImpl<T_*>::OptionImpl(T_* data) noexcept : data_(data) {
		}
		
		template<typename T_>
		OptionImpl<T_*>::OptionImpl() noexcept : data_(nullptr) {
		}
		
		template<typename T_>
		bool OptionImpl<T_*>::is_some() const noexcept {
			return data_ != nullptr;
		}
		
		template<typename T_>
		T_*& OptionImpl<T_*>::some() noexcept {
			return data_;
		}
		
		template<typename T_>
		T_* const& OptionImpl<T_*>::some() const noexcept {
			return data_;
		}
	}
}