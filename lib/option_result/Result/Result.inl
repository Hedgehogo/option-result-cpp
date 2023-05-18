#include "../Option/Option.hpp"

namespace orl {
	template<typename T_, typename E_>
	Result<T_, E_>::Result(Data&& data) : data_(std::forward<Data>(data)) {
	}
	
	template<typename T_, typename E_>
	Result<T_, E_> Result<T_, E_>::Ok(T_ const& value) noexcept {
		return Result<T_, E_>(Data{std::in_place_index<0>, value});
	}
	
	template<typename T_, typename E_>
	Result<T_, E_> Result<T_, E_>::Error(E_ const& value) noexcept {
		return Result<T_, E_>(Data{std::in_place_index<1>, value});
	}
	
	template<typename T_, typename E_>
	bool Result<T_, E_>::is_ok() const noexcept {
		return data_.index() == 0;
	}
	
	template<typename T_, typename E_>
	T_ const& Result<T_, E_>::ok() const noexcept {
		return std::get<0>(data_);
	}
	
	template<typename T_, typename E_>
	T_ const& Result<T_, E_>::ok_or(T_ const& value) const noexcept {
		if(is_ok()) {
			return ok();
		} else {
			return value;
		}
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	R* Result<T_, E_>::ok_or_ptr(A&& ... args) const noexcept {
		if(is_ok()) {
			return ok();
		} else {
			return new R{std::forward<A>(args)...};
		}
	}
	
	template<typename T_, typename E_>
	Option<T_ const&> Result<T_, E_>::ok_or_none() const noexcept {
		if(is_ok()) {
			return Option<const T_&>{ok()};
		} else {
			return Option<const T_&>{};
		}
	}
	
	template<typename T_, typename E_>
	E_ const& Result<T_, E_>::error() const noexcept {
		return std::get<1>(data_);
	}
	
	template<typename T_, typename E_>
	E_ const& Result<T_, E_>::error_or(E_ const& value) const noexcept {
		if(is_ok()) {
			return value;
		} else {
			return error();
		}
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	R* Result<T_, E_>::error_or_ptr(A&& ... args) const noexcept {
		if(is_ok()) {
			return new R{std::forward<A>(args)...};
		} else {
			return error();
		}
	}
	
	template<typename T_, typename E_>
	Option<E_ const&> Result<T_, E_>::error_or_none() const noexcept {
		if(is_ok()) {
			return Option<const E_&>{};
		} else {
			return Option<const E_&>{error()};
		}
	}
	
	template<typename T_, typename E_>
	template<typename R>
	R Result<T_, E_>::convert_ok_or(const R& value, std::function<R(T_ const&)> func) const noexcept {
		if(is_ok()) {
			return func(ok());
		} else {
			return value;
		}
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	R* Result<T_, E_>::convert_ok_or_ptr(std::function<R*(T_ const&)> func, A&& ... args) const noexcept {
		if(is_ok()) {
			return func(ok());
		} else {
			return new R{std::forward<A>(args)...};
		}
	}
	
	template<typename T_, typename E_>
	template<typename R>
	R Result<T_, E_>::convert_error_or(const R& value, std::function<R(E_ const&)> func) const noexcept {
		if(is_ok()) {
			return value;
		} else {
			return func(error());
		}
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	R* Result<T_, E_>::convert_error_or_ptr(std::function<R*(E_ const&)> func, A&& ... args) const noexcept {
		if(is_ok()) {
			return new R{std::forward<A>(args)...};
		} else {
			return func(error());
		}
	}
	
	template<typename T_, typename E_>
	T_ const& Result<T_, E_>::except() const {
		if(!is_ok()) {
			orl::except(error());
		}
		return ok();
	}
	
	template<typename T_, typename E_>
	Result<T_, E_>::operator bool() const noexcept {
		return is_ok();
	}
	
	template<typename T_, typename E_>
	template<typename T, typename E>
	bool Result<T_, E_>::operator==(Result<T, E> const& other) const noexcept {
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
