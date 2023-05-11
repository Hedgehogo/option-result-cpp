//included into Error.hpp

namespace orl {
	template<typename... Ts_>
	template<typename... A>
	Error<Ts_...>::Error(A&&... args) : errors_(std::forward<A>(args)...) {
	}
	
	template<typename... Ts_>
	template<std::size_t Index, typename... A>
	Error<Ts_...> Error<Ts_...>::make(A&&... args) {
		return Error<Ts_...>(std::in_place_index<Index>, std::forward<A>(args)...);
	}
	
	template<typename... Ts_>
	std::string Error<Ts_...>::get_note() const {
		return std::to_string(errors_.index()) + std::string(": ");
	}
	
	template<typename... Ts_>
	std::string Error<Ts_...>::get_description() const {
		auto func{[](auto const& error) -> std::string { return error.get_description(); }};
		return std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	void Error<Ts_...>::except() const {
		auto func{[](auto const& error) { orl::except(error); }};
		std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	template<typename R>
	R& Error<Ts_...>::common() {
		auto func{[](auto& exception) mutable -> R& { return exception; }};
		return std::visit(func, errors_);
	}
	
	template<typename... Ts_>
	template<typename R>
	R const& Error<Ts_...>::common() const {
		auto func{[](auto const& exception) -> R const& { return exception; }};
		return std::visit(func, errors_);
	}
	
	template<typename T>
	void except(const T& exception) {
		if constexpr(is_error<T>) {
			exception.except();
		} else {
			throw exception;
		}
	}
}
