//included into Error.hpp

namespace orl {
	template<typename T_, typename... Ts_>
	template<typename... A>
	Error<T_, Ts_...>::Error(A&&... args) : exceptions_(std::forward<A>(args)...) {
	}
	
	template<typename T_, typename... Ts_>
	std::string Error<T_, Ts_...>::get_note() const {
		return std::to_string(exceptions_.index()) + std::string(": ");
	}
	
	template<typename T_, typename... Ts_>
	std::string Error<T_, Ts_...>::get_description() const {
		auto func{[](const auto& exception) -> std::string { return exception.get_description(); }};
		return std::visit(func, exceptions_);
	}
	
	template<typename T_, typename... Ts_>
	template<typename R>
	R& Error<T_, Ts_...>::common() {
		auto func{[](auto& exception) mutable -> R& { return exception; }};
		return std::visit(func, exceptions_);
	}
	
	template<typename T_, typename... Ts_>
	template<typename R>
	const R& Error<T_, Ts_...>::common() const {
		auto func{[](const auto& exception) -> const R& { return exception; }};
		return std::visit(func, exceptions_);
	}
}
