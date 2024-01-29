#include "../Option/Option.hpp"

namespace orl {
	template<typename T_, typename E_>
	Result<T_, E_>::Result(Data&& data) : data_(std::forward<Data>(data)) {
	}
	
	template<typename T_, typename E_>
	Result<T_, E_> Result<T_, E_>::Ok(T_ value) noexcept {
		return Result<T_, E_>(Data{std::in_place_index<0>, std::forward<T_>(value)});
	}
	
	template<typename T_, typename E_>
	Result<T_, E_> Result<T_, E_>::Error(E_ value) noexcept {
		return Result<T_, E_>(Data{std::in_place_index<1>, std::forward<E_>(value)});
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
	T_& Result<T_, E_>::ok() noexcept {
		return std::get<0>(data_);
	}
	
	template<typename T_, typename E_>
	T_ Result<T_, E_>::move_ok() noexcept {
		return std::move(std::get<0>(data_));
	}
	
	template<typename T_, typename E_>
	T_ const& Result<T_, E_>::ok_or(T_ const& value) const noexcept {
		if(is_ok()) {
			return ok();
		}
		return value;
	}
	
	template<typename T_, typename E_>
	T_ Result<T_, E_>::move_ok_or(T_&& value) noexcept {
		if(is_ok()) {
			return std::move(ok());
		}
		return std::move(value);
	}
	
	template<typename T_, typename E_>
	template<typename F>
	std::enable_if_t<std::is_invocable_r_v<T_ const&, F>, T_ const&> Result<T_, E_>::ok_or_else(F fn) const noexcept {
		if(is_ok()) {
			return ok();
		}
		return fn();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> Result<T_, E_>::move_ok_or_else(F fn) noexcept {
		if(is_ok()) {
			return std::move(ok());
		}
		return fn();
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	T_ Result<T_, E_>::ok_or_ptr(A&& ... args) const noexcept {
		if(is_ok()) {
			return ok();
		}
		return new R{std::forward<A>(args)...};
	}
	
	template<typename T_, typename E_>
	Option<T_ const&> Result<T_, E_>::ok_or_none() const noexcept {
		if(is_ok()) {
			return Option<const T_&>{ok()};
		}
		return Option<const T_&>{};
	}
	
	template<typename T_, typename E_>
	E_ const& Result<T_, E_>::error() const noexcept {
		return std::get<1>(data_);
	}
	
	template<typename T_, typename E_>
	E_& Result<T_, E_>::error() noexcept {
		return std::get<1>(data_);
	}
	
	template<typename T_, typename E_>
	E_ Result<T_, E_>::move_error() noexcept {
		return std::move(std::get<1>(data_));
	}
	
	template<typename T_, typename E_>
	E_ const& Result<T_, E_>::error_or(E_ const& value) const noexcept {
		if(is_ok()) {
			return value;
		}
		return error();
	}
	
	template<typename T_, typename E_>
	E_ Result<T_, E_>::move_error_or(E_&& value) noexcept {
		if(is_ok()) {
			return std::move(value);
		}
		return std::move(error());
	}
	
	template<typename T_, typename E_>
	template<typename F>
	std::enable_if_t<std::is_invocable_r_v<T_ const&, F>, T_ const&> Result<T_, E_>::error_or_else(F fn) const noexcept {
		if(is_ok()) {
			return fn();
		}
		return error();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> Result<T_, E_>::move_error_or_else(F fn) noexcept {
		if(is_ok()) {
			return fn();
		}
		return std::move(error());
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	E_ Result<T_, E_>::error_or_ptr(A&& ... args) const noexcept {
		if(is_ok()) {
			return new R{std::forward<A>(args)...};
		}
		return error();
	}
	
	template<typename T_, typename E_>
	Option<E_ const&> Result<T_, E_>::error_or_none() const noexcept {
		if(is_ok()) {
			return Option<const E_&>{};
		}
		return Option<const E_&>{error()};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	Option<std::invoke_result_t<F, T_ const&> > Result<T_, E_>::map_ok(F fn) const {
		if(is_ok()) {
			return {fn(ok())};
		}
		return {};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	Option<std::invoke_result_t<F, T_&> > Result<T_, E_>::map_ok(F fn) {
		if(is_ok()) {
			return {fn(ok())};
		}
		return {};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	Option<std::invoke_result_t<F, E_ const&> > Result<T_, E_>::map_error(F fn) const {
		if(is_ok()) {
			return {};
		}
		return {fn(error())};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	Option<std::invoke_result_t<F, E_&> > Result<T_, E_>::map_error(F fn) {
		if(is_ok()) {
			return {};
		}
		return {fn(error())};
	}
	
	template<typename T_, typename E_>
	T_ const& Result<T_, E_>::except() const {
		if(!is_ok()) {
			orl::except(error());
		}
		return ok();
	}
	
	template<typename T_, typename E_>
	T_& Result<T_, E_>::except() {
		if(!is_ok()) {
			orl::except(error());
		}
		return ok();
	}
	
	template<typename T_, typename E_>
	T_ Result<T_, E_>::move_except() {
		if(!is_ok()) {
			orl::except(error());
		}
		return std::move(ok());
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
