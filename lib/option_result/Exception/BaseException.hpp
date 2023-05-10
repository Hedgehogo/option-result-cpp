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
		virtual std::string get_note() const;
		
		/// @brief Gets an error description.
		///
		/// @return Error description.
		virtual std::string get_description() const = 0;
		
		/// @brief Gets a full description of the error.
		///
		/// @return Error note + description.
		std::string get_full_description() const;
		
		const char* what() const noexcept final;
	};
	
	std::ostream& operator<<(std::ostream& stream, const BaseException& exception);
}
