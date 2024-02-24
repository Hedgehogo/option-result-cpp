#pragma once

#include <exception>
#include <string>

namespace orl {
	/// @brief A base class, for convenient exception handling
	class BaseException : public std::exception {
	public:
		/// @brief Gets an error note.
		///
		/// @return Error note.
		virtual auto get_note() const -> std::string;
		
		/// @brief Gets an error description.
		///
		/// @return Error description.
		virtual auto get_description() const -> std::string = 0;
		
		/// @brief Gets a full description of the error.
		///
		/// @return Error note + description.
		auto get_full_description() const -> std::string;
		
		auto what() const noexcept -> const char* final;
	};
	
	auto operator<<(std::ostream& stream, const BaseException& exception) -> std::ostream&;
}
