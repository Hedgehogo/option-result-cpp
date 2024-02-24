//included into Error.hpp

namespace orl {
	template<typename... Ts_>
	template<typename... A>
	Error<Ts_...>::Error(A&& ... args) : errors_(std::forward<A>(args)...) {
	}
	
	template<typename... Ts_>
	template<std::size_t Index, typename... A>
	auto Error<Ts_...>::make(A&& ... args) -> Error<Ts_...> {
		return Error<Ts_...>(std::in_place_index<Index>, std::forward<A>(args)...);
	}
	
	template<typename... Ts_>
	auto Error<Ts_...>::get_note() const -> std::string {
		return std::to_string(errors_.index()) + std::string(": ");
	}
	
	template<typename... Ts_>
	auto Error<Ts_...>::get_description() const -> std::string {
		auto func{[](auto const& error) -> std::string {
			return error.get_description();
		}};
		return std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	auto Error<Ts_...>::except() const -> void {
		auto func{[](auto const& error) {
			orl::except(error);
		}};
		std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	template<typename R>
	auto Error<Ts_...>::common() -> R& {
		auto func{[](auto& exception) mutable -> R& {
			return exception;
		}};
		return std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	template<typename R>
	auto Error<Ts_...>::common() const -> R const& {
		auto func{[](auto const& exception) -> R const& {
			return exception;
		}};
		return std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	template<typename... Ts>
	auto Error<Ts_...>::move_cast() -> Error<Ts...> {
		auto func{[](auto& exception) {
			return Error<Ts...>{std::move(exception)};
		}};
		return std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	template<typename... Ts>
	auto Error<Ts_...>::move_upcast() -> Error<Ts_..., Ts...> {
		return move_cast<Ts_..., Ts...>();
	}
	
	template<typename... Ts_>
	auto Error<Ts_...>::variant() const -> std::variant<Ts_...> const& {
		return errors_;
	}
	
	template<typename T>
	auto except(const T& exception) -> void {
		if constexpr(is_error<T>) {
			exception.except();
		} else {
			throw exception;
		}
	}
}
