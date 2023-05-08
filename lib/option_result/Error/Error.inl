//included into Error.hpp

namespace orl {
	namespace detail {
		template<std::size_t N, typename T_, typename... Ts_>
		struct GetDescription {
			template<typename T, typename... Ts>
			static std::string getDescription(const std::variant<T, Ts...>& exceptions) {
				if(exceptions.index() == N) {
					return std::get<N>(exceptions).getFullDescription();
				}
				return GetDescription<N + 1, Ts_...>::getDescription(exceptions);
			}
		};
		
		template<std::size_t N, typename T_>
		struct GetDescription<N, T_> {
			template<typename T, typename... Ts>
			static std::string getDescription(const std::variant<T, Ts...>& exceptions) {
				if(exceptions.index() == N) {
					return std::get<N>(exceptions).getFullDescription();
				}
				return {};
			}
		};
		
		template<typename T, typename... Ts>
		std::string getDescription(const std::variant<T, Ts...>& exceptions) {
			return detail::GetDescription<0, T, Ts...>::getDescription(exceptions);
		}
	}
	
	template<typename T_, typename... Ts_>
	template<typename... A>
	Error<T_, Ts_...>::Error(A&&... args) : exceptions(std::forward<A>(args)...) {
	}
	
	template<typename T_, typename... Ts_>
	std::string Error<T_, Ts_...>::getNote() const {
		return std::to_string(exceptions.index()) + std::string(": ");
	}
	
	template<typename T_, typename... Ts_>
	std::string Error<T_, Ts_...>::getDescription() const {
		return detail::getDescription(exceptions);
	}
}
