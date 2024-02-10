#include "../Option/Option.hpp"

namespace orl {
	template<typename T_, typename E_>
	Result<T_, E_>::Result(Data&& data) : data_(std::forward<Data>(data)) {
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::Ok(T_ value) noexcept -> Result<T_, E_> {
		return Result<T_, E_>(Data{std::in_place_index<0>, std::forward<T_>(value)});
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::Error(E_ value) noexcept -> Result<T_, E_> {
		return Result<T_, E_>(Data{std::in_place_index<1>, std::forward<E_>(value)});
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::is_ok() const noexcept -> bool {
		return data_.index() == 0;
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok() const& noexcept -> T_ const& {
		return std::get<0>(data_);
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok()& noexcept -> T_& {
		return std::get<0>(data_);
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok()&& noexcept -> T_ {
		return std::forward<T_>(std::get<0>(data_));
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::move_ok() noexcept -> T_ {
		return std::forward<T_>(std::get<0>(data_));
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok_or(T_ const& value) const& noexcept -> T_ {
		if(is_ok()) {
			return ok();
		}
		return value;
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok_or(T_& value)& noexcept -> T_& {
		if(is_ok()) {
			return ok();
		}
		return value;
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok_or(T_&& value)&& noexcept -> T_ {
		if(is_ok()) {
			return std::forward<T_>(ok());
		}
		return std::forward<T_>(value);
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::move_ok_or(T_&& value) noexcept -> T_ {
		if(is_ok()) {
			return std::forward<T_>(ok());
		}
		return std::forward<T_>(value);
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::ok_or_else(F fn) const& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(is_ok()) {
			return ok();
		}
		return fn();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::ok_or_else(F fn)& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&> {
		if(is_ok()) {
			return ok();
		}
		return fn();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::ok_or_else(F fn)&& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(is_ok()) {
			return std::forward<T_>(ok());
		}
		return fn();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::move_ok_or_else(F fn) noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(is_ok()) {
			return std::forward<T_>(ok());
		}
		return fn();
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	auto Result<T_, E_>::ok_or_ptr(A&& ... args) const noexcept -> T_ {
		if(is_ok()) {
			return ok();
		}
		return new R{std::forward<A>(args)...};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok_or_none() const& noexcept -> Option<T_ const&> {
		if(is_ok()) {
			return Option<const T_&>{ok()};
		}
		return Option<const T_&>{};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok_or_none()& noexcept -> Option<T_&> {
		if(is_ok()) {
			return Option<T_&>{ok()};
		}
		return Option<T_&>{};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::ok_or_none()&& noexcept -> Option<T_> {
		if(is_ok()) {
			return Option<T_>{std::forward<T_>(ok())};
		}
		return Option<T_>{};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::map_ok(F fn) const& -> Option<std::invoke_result_t<F, T_ const&> > {
		if(is_ok()) {
			return {fn(ok())};
		}
		return {};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::map_ok(F fn)& -> Option<std::invoke_result_t<F, T_&> > {
		if(is_ok()) {
			return {fn(ok())};
		}
		return {};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::map_ok(F fn)&& -> Option<std::invoke_result_t<F, T_> > {
		if(is_ok()) {
			return {fn(std::forward<T_>(ok()))};
		}
		return {};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error() const& noexcept -> E_ const& {
		return std::get<1>(data_);
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error()& noexcept -> E_& {
		return std::get<1>(data_);
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error()&& noexcept -> E_ {
		return std::forward<E_>(std::get<1>(data_));
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::move_error() noexcept -> E_ {
		return std::forward<E_>(std::get<1>(data_));
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error_or(E_ const& value) const& noexcept -> E_ {
		if(is_ok()) {
			return value;
		}
		return error();
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error_or(E_& value)& noexcept -> E_& {
		if(is_ok()) {
			return value;
		}
		return error();
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error_or(E_&& value)&& noexcept -> E_ {
		if(is_ok()) {
			return value;
		}
		return error();
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::move_error_or(E_&& value) noexcept -> E_ {
		if(is_ok()) {
			return std::forward<E_>(value);
		}
		return std::forward<E_>(error());
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::error_or_else(F fn) const& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(is_ok()) {
			return fn();
		}
		return error();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::error_or_else(F fn)& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_&, F>, T_&> {
		if(is_ok()) {
			return fn();
		}
		return error();
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::error_or_else(F fn)&& noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(is_ok()) {
			return fn();
		}
		return std::forward<E_>(error());
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::move_error_or_else(F fn) noexcept -> std::enable_if_t<std::is_invocable_r_v<T_, F>, T_> {
		if(is_ok()) {
			return fn();
		}
		return std::forward<E_>(error());
	}
	
	template<typename T_, typename E_>
	template<typename R, typename... A>
	auto Result<T_, E_>::error_or_ptr(A&& ... args) const noexcept -> E_ {
		if(is_ok()) {
			return new R{std::forward<A>(args)...};
		}
		return error();
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error_or_none() const& noexcept -> Option<E_ const&> {
		if(is_ok()) {
			return Option<const E_&>{};
		}
		return Option<const E_&>{error()};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error_or_none()& noexcept -> Option<E_&> {
		if(is_ok()) {
			return Option<E_&>{};
		}
		return Option<E_&>{error()};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::error_or_none()&& noexcept -> Option<E_> {
		if(is_ok()) {
			return Option<E_>{};
		}
		return Option<E_>{std::forward<E_>(error())};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::map_error(F fn) const& -> Option<std::invoke_result_t<F, E_ const&> > {
		if(is_ok()) {
			return {};
		}
		return {fn(error())};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::map_error(F fn)& -> Option<std::invoke_result_t<F, E_&> > {
		if(is_ok()) {
			return {};
		}
		return {fn(error())};
	}
	
	template<typename T_, typename E_>
	template<typename F>
	auto Result<T_, E_>::map_error(F fn)&& -> Option<std::invoke_result_t<F, E_> > {
		if(is_ok()) {
			return {};
		}
		return {fn(std::forward<E_>(error()))};
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::except() const& -> T_ const& {
		if(!is_ok()) {
			orl::except(error());
		}
		return ok();
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::except()& -> T_& {
		if(!is_ok()) {
			orl::except(error());
		}
		return ok();
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::except()&& -> T_ {
		if(!is_ok()) {
			orl::except(error());
		}
		return std::forward<T_>(ok());
	}
	
	template<typename T_, typename E_>
	auto Result<T_, E_>::move_except() -> T_ {
		if(!is_ok()) {
			orl::except(error());
		}
		return std::forward<T_>(ok());
	}
	
	template<typename T_, typename E_>
	Result<T_, E_>::operator bool() const noexcept {
		return is_ok();
	}
	
	template<typename T_, typename E_>
	template<typename T, typename E>
	auto Result<T_, E_>::operator==(Result<T, E> const& other) const noexcept -> bool {
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
