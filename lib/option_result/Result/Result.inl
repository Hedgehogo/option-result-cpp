#include "../Option/Option.hpp"

namespace orl {
	template<typename T_, typename E_>
	Result<T_, E_>::Result(const Data& data) : data_(std::move(data)) {
	}
	
	template<typename T_, typename E_>
	Result<T_, E_> Result<T_, E_>::Ok(const T_& value) noexcept {
		return Result<T_, E_>(Data{std::in_place_index<0>, value});
	}
	
	template<typename T_, typename E_>
	Result<T_, E_> Result<T_, E_>::Error(const E_& value) noexcept {
		return Result<T_, E_>(Data{std::in_place_index<1>, value});
	}
	
	template<typename T_, typename E_>
	bool Result<T_, E_>::is_ok() const noexcept {
		return data_.index() == 0;
	}
	
	template<typename T_, typename E_>
	const T_& Result<T_, E_>::ok() const noexcept {
		return std::get<0>(data_);
	}
	
	template<typename T_, typename E_>
	const T_& Result<T_, E_>::ok_or(const T_& value) const noexcept {
		if(is_ok()) {
			return ok();
		} else {
			return value;
		}
	}
	
	template<typename T_, typename E_>
	Option<const T_&> Result<T_, E_>::ok_or_none() const noexcept {
		if(is_ok()) {
			return Option<const T_&>{ok()};
		} else {
			return Option<const T_&>{};
		}
	}
	
	template<typename T_, typename E_>
	const E_& Result<T_, E_>::error() const noexcept {
		return std::get<1>(data_);
	}
	
	template<typename T_, typename E_>
	const E_& Result<T_, E_>::error_or(const E_& value) const noexcept {
		if(is_ok()) {
			return value;
		} else {
			return error();
		}
	}
	
	template<typename T_, typename E_>
	Option<const E_&> Result<T_, E_>::error_or_none() const noexcept {
		if(is_ok()) {
			return Option<const E_&>{};
		} else {
			return Option<const E_&>{error()};
		}
	}
	
	template<typename T_, typename E_>
	template<typename R>
	R Result<T_, E_>::convert_ok_or(const R& value, std::function<R(const T_&)> func) const noexcept {
		if(is_ok()) {
			return func(ok());
		} else {
			return value;
		}
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	R* Result<T_, E_>::convert_ok_or_ptr(std::function<R*(const T_&)> func, A&& ... args) const noexcept {
		if(is_ok()) {
			return func(ok());
		} else {
			return new R{std::forward<A>(args)...};
		}
	}
	
	template<typename T_, typename E_>
	template<typename R>
	R Result<T_, E_>::convert_error_or(const R& value, std::function<R(const E_&)> func) const noexcept {
		if(is_ok()) {
			return value;
		} else {
			return func(error());
		}
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	R* Result<T_, E_>::convert_error_or_ptr(std::function<R*(const E_&)> func, A&& ... args) const noexcept {
		if(is_ok()) {
			return new R{std::forward<A>(args)...};
		} else {
			return func(error());
		}
	}
	
	template<typename T_, typename E_>
	const T_& Result<T_, E_>::except() const {
		if(is_ok()) {
			return ok();
		} else {
			throw error();
		}
	}
	
	template<typename T_, typename E_>
	Result<T_, E_>::operator bool() const noexcept {
		return is_ok();
	}
	
	template<typename T_, typename E_>
	template<typename T, typename E>
	bool Result<T_, E_>::operator==(const Result<T, E>& other) const noexcept {
		if(is_ok() == other.is_ok()) {
			if(is_ok()) {
				return ok() == other.ok();
			} else {
				return error() == other.error();
			}
		}
		return false;
	}
}
