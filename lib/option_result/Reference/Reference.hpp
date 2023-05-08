#pragma once
#include <functional>

namespace orl {
	namespace detail {
		template<typename T>
		class Option;
		
		template<typename T>
		struct MetaFn {
			using type = T;
		};
		
		template<typename T>
		struct Reference : public MetaFn<T> {};
		template<typename T>
		struct Reference<T&> : public MetaFn<std::reference_wrapper<T>> {};
	}
	
	template<typename T>
	using ref = typename detail::Reference<T>::type;
}

