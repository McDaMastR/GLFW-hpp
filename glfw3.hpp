// glfw3.hpp - C++ binding for the GLFW library
// ! THIS BINDING IS NOT COMPLETED! MANY FEATURES MAY NOT WORK! MANY MACRO CONFIGURATIONS MAY NOT DO ANYTHING !

/*

=== User Information ===

Supported compilers: gcc, clang & msvc
If you are using a compiler not supported, you will have to define these macros before including this file:

	#define GLFW_HPP_CPLUSPLUS // Contains the specific c++ standard (e.g. __cplusplus, _MSVC_LANG)
	#define GLFW_HPP_CPP_VERSION // Contains the actual c++ standard (e.g. 11, 14, 17, 20)
	#define GLFW_HPP_HAS_ATTRIBUTE(x) // Expands to whether the given attribute is available (e.g. __has_cpp_attribute(nodiscard))
	#define GLFW_HPP_HAS_FEATURE(x) // Expands to whether the given feature is available (e.g. __has_feature(cxx_unrestricted_unions)) 
	#define GLFW_HPP_UNRESTRICTED_UNIONS // Whether unrestricted unions are available
	#define GLFW_HPP_INLINE // The keyword/attribute to force inline functions
	#define GLFW_HPP_NOEXCEPT // The keyword/attribute to specify that a function will never raise an exception
	#define GLFW_HPP_ENABLE_HASHING // Creates hashing algorithms for each class


Before including this file, you can define some macros to configure this file's binding.
Any macros not user defined will be automatically defined.
Macros:

	Basic configurations:
		#define GLFW_HPP_INCLUDE_NATIVE // Includes glfw3native.h
		#define GLFW_HPP_DISABLE_STANDARD_CONTAINERS // Disables standard container use (e.g. std::string), and instead uses c-style types (e.g. const char *)
		#define GLFW_HPP_ASSERT(x) // Triggers an assertion in the program if the condition is false
		#define GLFW_HPP_EXPLICIT // Enable or disable explicit constuctors and castings (default is explicit)
		#define GLFW_HPP_NAMESPACE // Change the namespace name (e.g. glfw)

	Advanced configurations:
		#define GLFW_HPP_NORETURN // The function will not return / will terminate the program (e.g. [[noreturn]])
		#define GLFW_HPP_DEPRECATED(x) // The function is deprecated and should not be used (e.g. [[deprecated(x)]])
		#define GLFW_HPP_FALLTHROUGH // The case in a switch statement will fallthrough into the next case (e.g. [[fallthrough]])
		#define GLFW_HPP_MAYBE_UNUSED // The function/variable may not ever be used (e.g. [[maybe_unused]])
		#define GLFW_HPP_NO_UNIQUE_ADDRESS // The variable does not take up any space in memory (e.g. [[no_unique_address]])
		#define GLFW_HPP_LIKELY // The branch (if-else/switch case) is more likely to be gone into than another (e.g. [[likely]])
		#define GLFW_HPP_UNLIKELY // The branch (if-else/switch case) is less likely to be gone into than another (e.g. [[unlikely]])
		#define GLFW_HPP_NODISCARD(x) // The return value from a function should always be used (e.g. [[nodiscard(x)]])
		#define GLFW_HPP_CONSTEVAL // The function must always produce a compile-time constant expression
		#define GLFW_HPP_CONSTINIT // The static/global variable must be initalized at compile-time
		#define GLFW_HPP_CONSTEXPR // The function/variable can be used at compile-time
		#define GLFW_HPP_CONSTEXPR_OR_CONST // The variable should be constexpr, but can be const if constexpr is not usable
		#define GLFW_HPP_CONSTEXPR_NO_STL_CONTAINERS // The function should be constexpr if not using standard library containers
		#define GLFW_HPP_CONSTEXPR_NON_CONST_METHOD // The method can be constexpr even if it is non-const
		#define GLFW_HPP_CONSTEXPR_LAMBDA // The lambda can be constexpr
		#define GLFW_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC // The function can use dynamic allocation at compile-time
		#define GLFW_HPP_CONSTEXPR_DESTRUCTOR // The destructor can be constexpr
		#define GLFW_HPP_CONSTEXPR_TO_STRING // The to_string() function for enums can be constexpr
		#define GLFW_HPP_CONSTEVAL_IF // The first branch will be gone into if the function this is in is evaluated at compile time
		#define GLFW_HPP_CONSTEXPR_IF(x) // The if-else branch condition can be evaluated at compile-time
		#define GLFW_HPP_STRINGIFY(x) // Turns the inputted data into a string

*/

#ifndef GLFW_HPP
#define GLFW_HPP

// === C++ Standard Information ===

#ifndef GLFW_HPP_CPLUSPLUS
	#if   defined(_MSVC_LANG)
		#define GLFW_HPP_CPLUSPLUS _MSVC_LANG
	#elif defined(__cplusplus)
		#define GLFW_HPP_CPLUSPLUS __cplusplus
	#else
		#error "Unknown compiler; GLFW_HPP_CPLUSPLUS requires user definition"
	#endif
#endif

#ifndef GLFW_HPP_CPP_VERSION
	#if   GLFW_HPP_CPLUSPLUS >  202002L
		#define GLFW_HPP_CPP_VERSION 23
	#elif GLFW_HPP_CPLUSPLUS == 202002L
		#define GLFW_HPP_CPP_VERSION 20
	#elif GLFW_HPP_CPLUSPLUS == 201703L
		#define GLFW_HPP_CPP_VERSION 17
	#elif GLFW_HPP_CPLUSPLUS == 201402L
		#define GLFW_HPP_CPP_VERSION 14
	#elif GLFW_HPP_CPLUSPLUS == 201103L
		#define GLFW_HPP_CPP_VERSION 11
	#else 
		#error "glfw3.hpp requires c++ standard of at least c++11"
	#endif
#endif

// === Includes ===

#include <GLFW/glfw3.h>

#ifdef GLFW_HPP_INCLUDE_NATIVE
	#include <GLFW/glfw3native.h>
#endif

#ifdef GLFW_INCLUDE_VULKAN
	#include <vulkan/vulkan.hpp>
#endif

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
	#include <sstream> // Inclues <string> && <string_view>
	#include <array>
	#include <vector>

	#if GLFW_HPP_CPP_VERSION >= 17
		#define GLFW_HPP_STRING std::string_view
	#else
		#define GLFW_HPP_STRING std::string
	#endif
#else
	#include <cstdio>
	#define GLFW_HPP_STRING const char *

	#ifdef GLFW_HPP_ENABLE_HASHING
		#include <utility>
	#endif
#endif

#ifndef GLFW_HPP_ASSERT
	#include <cassert>
	#define GLFW_HPP_ASSERT(x) assert(x)
#endif

#if __cpp_impl_three_way_comparison >= 201907L
	#define GLFW_HPP_INCLUDE_COMPARE
	#include <compare>
#endif

// === Compiler-Specific Configurations ===

#if   defined(__clang__)
	#define GLFW_HPP_CLANG_COMPILER
#elif defined(__GNUC__)
	#define GLFW_HPP_GCC_COMPILER
	#define GLFW_HPP_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
	#define GLFW_HPP_MSVC_COMPILER
	#define GLFW_HPP_COMPILER_VERSION _MSC_VER
#else 
	#define GLFW_HPP_OTHER_COMPILER
#endif

#ifndef GLFW_HPP_HAS_ATTRIBUTE
	#ifdef __has_cpp_attribute
		#define GLFW_HPP_HAS_ATTRIBUTE(x) __has_cpp_attribute(x)
	#else
		#define GLFW_HPP_HAS_ATTRIBUTE(x) 0
	#endif
#endif

#ifndef GLFW_HPP_HAS_FEATURE
	#ifdef __has_feature
		#define GLFW_HPP_HAS_FEATURE(x) __has_feature(x)
	#else
		#define GLFW_HPP_HAS_FEATURE(x) 0
	#endif
#endif

#ifndef GLFW_HPP_NORETURN
	#if GLFW_HPP_HAS_ATTRIBUTE(noreturn) >= 200809L
		#define GLFW_HPP_NORETURN [[noreturn]]
	#else
		#define GLFW_HPP_NORETURN
	#endif
#endif

#ifndef GLFW_HPP_DEPRECATED
	#if GLFW_HPP_HAS_ATTRIBUTE(deprecated) >= 201309L && GLFW_HPP_CPP_VERSION >= 14
		#define GLFW_HPP_DEPRECATED(x) [[deprecated(x)]]
	#else
		#define GLFW_HPP_DEPRECATED(x)
	#endif
#endif

#ifndef GLFW_HPP_FALLTHROUGH
	#if GLFW_HPP_HAS_ATTRIBUTE(fallthrough) >= 201603L && GLFW_HPP_CPP_VERSION >= 17
		#define GLFW_HPP_FALLTHROUGH [[fallthrough]]
	#else
		#define GLFW_HPP_FALLTHROUGH
	#endif
#endif

#ifndef GLFW_HPP_MAYBE_UNUSED
	#if GLFW_HPP_HAS_ATTRIBUTE(maybe_unused) >= 201603L && GLFW_HPP_CPP_VERSION >= 17
		#define GLFW_HPP_MAYBE_UNUSED [[maybe_unused]]
	#else
		#define GLFW_HPP_MAYBE_UNUSED
	#endif
#endif

#ifndef GLFW_HPP_NO_UNIQUE_ADDRESS
	#if GLFW_HPP_HAS_ATTRIBUTE(no_unique_address) >= 201803L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_NO_UNIQUE_ADDRESS [[no_unique_address]]
	#else
		#define GLFW_HPP_NO_UNIQUE_ADDRESS
	#endif
#endif

#ifndef GLFW_HPP_LIKELY
	#if GLFW_HPP_HAS_ATTRIBUTE(likely) >= 201803L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_LIKELY [[likely]]
	#else
		#define GLFW_HPP_LIKELY
	#endif
#endif

#ifndef GLFW_HPP_UNLIKELY
	#if GLFW_HPP_HAS_ATTRIBUTE(unlikely) >= 201803L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_UNLIKELY [[unlikely]]
	#else
		#define GLFW_HPP_UNLIKELY
	#endif
#endif

#ifndef GLFW_HPP_NODISCARD
	#if   GLFW_HPP_HAS_ATTRIBUTE(nodiscard) >= 201907L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_NODISCARD(x) [[nodiscard(x)]]
	#elif GLFW_HPP_HAS_ATTRIBUTE(nodiscard) >= 201603L && GLFW_HPP_CPP_VERSION >= 17
		#define GLFW_HPP_NODISCARD(x) [[nodiscard]]
	#else
		#define GLFW_HPP_NODISCARD(x)
	#endif
#endif

#ifndef GLFW_HPP_EXPLICIT
	#define GLFW_HPP_EXPLICIT explicit // Defaults to explicit constructors and casts
#endif

#ifndef GLFW_HPP_CONSTEVAL
	#if __cpp_consteval >= 201811L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_CONSTEVAL consteval
	#else
		#define GLFW_HPP_CONSTEVAL
	#endif
#endif

#ifndef GLFW_HPP_CONSTINIT
	#if __cpp_constinit >= 201907L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_CONSTINIT constinit
	#else
		#define GLFW_HPP_CONSTINIT
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR
	#if __cpp_constexpr >= 200704L
		#define GLFW_HPP_CONSTEXPR constexpr
	#else
		#define GLFW_HPP_CONSTEXPR
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_OR_CONST
	#if __cpp_constexpr >= 200704L
		#define GLFW_HPP_CONSTEXPR_OR_CONST constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_OR_CONST const
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_NO_STL_CONTAINERS
	#if __cpp_constexpr >= 200704L && defined(GLFW_HPP_DISABLE_STANDARD_CONTAINERS)
		#define GLFW_HPP_CONSTEXPR_NO_STL_CONTAINERS constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_NO_STL_CONTAINERS
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_NON_CONST_METHOD
	#if __cpp_constexpr >= 201304L && GLFW_HPP_CPP_VERSION >= 14
		#define GLFW_HPP_CONSTEXPR_NON_CONST_METHOD constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_NON_CONST_METHOD
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_LAMBDA
	#if __cpp_constexpr >= 201603L && GLFW_HPP_CPP_VERSION >= 17
		#define GLFW_HPP_CONSTEXPR_LAMBDA constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_LAMBDA const
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC
	#if __cpp_constexpr_dynamic_alloc >= 201907L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_DESTRUCTOR
	#if GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_CONSTEXPR_DESTRUCTOR constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_DESTRUCTOR
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_TO_STRING
	#if   defined(GLFW_HPP_DISABLE_STANDARD_CONTAINERS) && GLFW_HPP_CPP_VERSION >= 14
		#define GLFW_HPP_CONSTEXPR_TO_STRING constexpr
	#elif __cpp_constexpr_dynamic_alloc >= 201907L && GLFW_HPP_CPP_VERSION >= 20
		#define GLFW_HPP_CONSTEXPR_TO_STRING constexpr
	#else
		#define GLFW_HPP_CONSTEXPR_TO_STRING
	#endif
#endif

#ifndef GLFW_HPP_CONSTEVAL_IF
	#if   __cpp_if_consteval >= 202106L && GLFW_HPP_CPP_VERSION >= 23
		#define GLFW_HPP_CONSTEVAL_IF if consteval
	#else
		#define GLFW_HPP_CONSTEVAL_IF if(false) GLFW_HPP_UNLIKELY
	#endif
#endif

#ifndef GLFW_HPP_CONSTEXPR_IF
	#if __cpp_if_constexpr >= 201606L && GLFW_HPP_CPP_VERSION >= 17
		#define GLFW_HPP_CONSTEXPR_IF(x) if constexpr(x)
	#else
		#define GLFW_HPP_CONSTEXPR_IF(x) if(x)
	#endif
#endif

#ifndef GLFW_HPP_UNRESTRICTED_UNIONS
	#if   defined(GLFW_HPP_CLANG_COMPILER)
		#if GLFW_HPP_HAS_FEATURE(cxx_unrestricted_unions)
			#define GLFW_HPP_UNRESTRICTED_UNIONS
		#endif
	#elif defined(GLFW_HPP_GCC_COMPILER)
		#if GLFW_HPP_COMPILER_VERSION >= 40600
			#define GLFW_HPP_UNRESTRICTED_UNIONS
		#endif
	#elif defined(GLFW_HPP_MSVC_COMPILER)
		#if GLFW_HPP_COMPILER_VERSION >= 1900
			#define GLFW_HPP_UNRESTRICTED_UNIONS
		#endif
	#endif
#endif

#ifndef GLFW_HPP_INLINE
	#if   defined(GLFW_HPP_CLANG_COMPILER)
		#if GLFW_HPP_HAS_ATTRIBUTE(always_inline)
			#define GLFW_HPP_INLINE __attribute__((always_inline)) __inline__
		#else
			#define GLFW_HPP_INLINE inline
		#endif
	#elif defined(GLFW_HPP_GCC_COMPILER)
		#define GLFW_HPP_INLINE __attribute__((always_inline)) __inline__
	#elif defined(GLFW_HPP_MSVC_COMPILER)
		#define GLFW_HPP_INLINE inline
	#else
		#error "Unknown compiler; GLFW_HPP_INLINE requires user definition"
	#endif
#endif

#ifndef GLFW_HPP_NOEXCEPT
	#if   defined(GLFW_HPP_GCC_COMPILER)
		#define GLFW_HPP_NOEXCEPT noexcept
	#elif defined(GLFW_HPP_CLANG_COMPILER)
		#define GLFW_HPP_NOEXCEPT noexcept
	#elif defined(GLFW_HPP_MSVC_COMPILER)
		#if GLFW_HPP_COMPILER_VERSION > 1800
			#define GLFW_HPP_NOEXCEPT noexcept
		#else
			#define GLFW_HPP_NOEXCEPT
		#endif
	#else
		#error "Unknown compiler; GLFW_HPP_NOEXCEPT requires user definition"
	#endif
#endif

// === Namespace & Version Configurations ===

#ifndef GLFW_HPP_NAMESPACE
	#define GLFW_HPP_NAMESPACE glfw
#endif

#ifndef GLFW_HPP_STRINGIFY
	#define GLFW_HPP_STRINGIFY(x) #x
#endif

static_assert(GLFW_VERSION_MAJOR == 3, "GLFW version major is not correct!");
static_assert(GLFW_VERSION_MINOR == 3, "GLFW version minor is not correct!");

// === Begin the Namespace ===

namespace GLFW_HPP_NAMESPACE
{
	// === Helper Types ===

	using EnumSize 	   	   = int;
	using ScreenCoordinate = int;
	using Pixel		   	   = int;
	using Scancode		   = int;
	using Count			   = int;
	using BitDepth		   = int;
	using Hz			   = int;
	using Version		   = int;
	using Millimetre	   = int;
	using ContentScale 	   = float;
	using GamepadAxisState = float;
	using Exponent		   = float;
	using Opacity		   = float;
	using CursorCoordinate = double;
	using Offset		   = double;
	using Codepoint		   = unsigned int;
	using ArraySize		   = unsigned int;
	using SmallEnumSize    = unsigned char;
	using Response		   = unsigned short;
	using PixelData		   = unsigned char *;

	template <class T>
	class Flags
	{
	public:
		// Contructors and destructor
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags(				) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags(const Flags<T> &) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags(Flags<T> &&	  	) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_CONSTEXPR_DESTRUCTOR			 ~Flags(				) GLFW_HPP_NOEXCEPT = default;

		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT Flags(const T bit		) GLFW_HPP_NOEXCEPT
			: m_flags(static_cast<EnumSize>(bit)) {}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT Flags(const EnumSize bit) GLFW_HPP_NOEXCEPT
			: m_flags(bit) {}

		// Relational operators
#ifdef GLFW_HPP_INCLUDE_COMPARE
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR auto operator<=>(const Flags<T> &) const GLFW_HPP_NOEXCEPT = default;
#else
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator==(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return m_flags == other.m_flags;}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator!=(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return m_flags != other.m_flags;}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator< (const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return m_flags <  other.m_flags;}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator<=(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return m_flags <= other.m_flags;}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator> (const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return m_flags >  other.m_flags;}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator>=(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return m_flags >= other.m_flags;}
#endif

		// Logical operator
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR bool operator!() const GLFW_HPP_NOEXCEPT {return !m_flags;}

		// Bitwise operators
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags<T> operator&(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return {m_flags & other.m_flags};}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags<T> operator|(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return {m_flags | other.m_flags};}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags<T> operator^(const Flags<T> &other) const GLFW_HPP_NOEXCEPT {return {m_flags ^ other.m_flags};}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Flags<T> operator~(					  ) const GLFW_HPP_NOEXCEPT {return {~m_flags};				  }

		// Assignment operators
		GLFW_HPP_CONSTEXPR_NON_CONST_METHOD Flags<T> &operator= (const Flags<T> &	  ) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_CONSTEXPR_NON_CONST_METHOD Flags<T> &operator= (Flags<T> &&		  ) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_CONSTEXPR_NON_CONST_METHOD Flags<T> &operator&=(const Flags<T> &other) GLFW_HPP_NOEXCEPT {m_flags &= other.m_flags; return *this;}
		GLFW_HPP_CONSTEXPR_NON_CONST_METHOD Flags<T> &operator|=(const Flags<T> &other) GLFW_HPP_NOEXCEPT {m_flags |= other.m_flags; return *this;}
		GLFW_HPP_CONSTEXPR_NON_CONST_METHOD Flags<T> &operator^=(const Flags<T> &other) GLFW_HPP_NOEXCEPT {m_flags ^= other.m_flags; return *this;}

		// Cast operators
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT operator bool	 () const GLFW_HPP_NOEXCEPT {return static_cast<bool>(m_flags);}
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT operator EnumSize() const GLFW_HPP_NOEXCEPT {return m_flags;				   }

	private:
		EnumSize m_flags = 0;

#ifdef GLFW_HPP_ENABLE_HASHING
		friend struct std::hash<Flags>;
#endif
	};

	// === Enums ===

	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE GLFW_HPP_STRING invalidValueToString(const EnumSize value) GLFW_HPP_NOEXCEPT
	{
#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		std::stringstream ss;
		ss << std::hex << value;
		return {"Invalid value: " + ss.str()};
#else
		static char string[/* Size of "Invalid value: " */ 15 + /* Max size for string hex value */ 5 + /* Null termination character */ 1] = "Invalid value: ";
		snprintf(string + 15, 5, "%X", value);
		return string;
#endif
	}

	/*! @name Key and button actions 
	 */
	enum class Action : EnumSize
	{
		/*! @brief The key or mouse button was released.
		 *
		 *  The key or mouse button was released.
		 *
		 *  @ingroup input
		 */
		eRelease = GLFW_RELEASE,

		/*! @brief The key or mouse button was pressed.
 		 *
 		 *  The key or mouse button was pressed.
 		 *
 		 *  @ingroup input
 		 */
		ePress   = GLFW_PRESS,

		/*! @brief The key was held down until it repeated.
 		 *
 		 *  The key was held down until it repeated.
 		 *
 		 *  @ingroup input
 		 */
		eRepeat	 = GLFW_REPEAT
	};
 
	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Action value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Action::eRelease: return "Release";
		case Action::ePress:   return "Press";
		case Action::eRepeat:  return "Repeat";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @name Key and button actions 
	 */
	enum class SmallAction : SmallEnumSize
	{
		/*! @brief The key or mouse button was released.
		 *
		 *  The key or mouse button was released.
		 *
		 *  @ingroup input
		 */
		eRelease = GLFW_RELEASE,

		/*! @brief The key or mouse button was pressed.
 		 *
 		 *  The key or mouse button was pressed.
 		 *
 		 *  @ingroup input
 		 */
		ePress   = GLFW_PRESS,

		/*! @brief The key was held down until it repeated.
 		 *
 		 *  The key was held down until it repeated.
 		 *
 		 *  @ingroup input
 		 */
		eRepeat	 = GLFW_REPEAT
	};
 
	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const SmallAction value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case SmallAction::eRelease: return "Release";
		case SmallAction::ePress:   return "Press";
		case SmallAction::eRepeat:  return "Repeat";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup hat_state Joystick hat states
	 *  @brief Joystick hat states.
	 *
	 *  See [joystick hat input](@ref joystick_hat) for how these are used.
	 *
	 *  @ingroup input 
	 */
	enum class Hat : EnumSize
	{
		eCentered  = GLFW_HAT_CENTERED,
		eUp 	   = GLFW_HAT_UP,
		eRight 	   = GLFW_HAT_RIGHT,
		eDown 	   = GLFW_HAT_DOWN,
		eLeft 	   = GLFW_HAT_LEFT,
		eRightUp   = GLFW_HAT_RIGHT_UP,
		eRightDown = GLFW_HAT_RIGHT_DOWN,
		eLeftUp    = GLFW_HAT_LEFT_UP,
		eLeftDown  = GLFW_HAT_LEFT_DOWN
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Hat value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Hat::eCentered:  return "Centered";
		case Hat::eUp: 	   	  return "Up";
		case Hat::eRight: 	  return "Right";
		case Hat::eDown: 	  return "Down";
		case Hat::eLeft: 	  return "Left";
		case Hat::eRightUp:   return "RightUp";
		case Hat::eRightDown: return "RightDown";
		case Hat::eLeftUp:	  return "LeftUp";
		case Hat::eLeftDown:  return "LeftDown";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup keys Keyboard keys
 	 *  @brief Keyboard key IDs.
 	 *
 	 *  See [key input](@ref input_key) for how these are used.
 	 *
 	 *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
 	 *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
 	 *  put in the 256+ range).
 	 *
 	 *  The naming of the key codes follow these rules:
 	 *   - The US keyboard layout is used
 	 *   - Names of printable alpha-numeric characters are used (e.g. "A", "R",
 	 *     "3", etc.)
 	 *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 	 *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 	 *     correspond to the Unicode standard (usually for brevity)
 	 *   - Keys that lack a clear US mapping are named "WORLD_x"
 	 *   - For non-printable keys, custom names are used (e.g. "F4",
 	 *     "BACKSPACE", etc.)
 	 *
 	 *  @ingroup input
 	 */
	enum class Key : EnumSize
	{
		/* The unknown key */
		eUnknown 	  = GLFW_KEY_UNKNOWN,

		/* Printable keys */
		eSpace 	 	  = GLFW_KEY_SPACE,
		eApostrophe   = GLFW_KEY_APOSTROPHE,
		eComma 	 	  = GLFW_KEY_COMMA,
		eMinus 	 	  = GLFW_KEY_MINUS,
		ePeriod 	  = GLFW_KEY_PERIOD,
		eSlash 	 	  = GLFW_KEY_SLASH,
		e0	 	 	  = GLFW_KEY_0,
		e1	 	 	  = GLFW_KEY_1,
		e2	 	 	  = GLFW_KEY_2,
		e3	 	 	  = GLFW_KEY_3,
		e4	 	 	  = GLFW_KEY_4,
		e5	 	 	  = GLFW_KEY_5,
		e6	 	 	  = GLFW_KEY_6,
		e7	 	 	  = GLFW_KEY_7,
		e8	 	 	  = GLFW_KEY_8,
		e9	 	 	  = GLFW_KEY_9,
		eSemicolon 	  = GLFW_KEY_SEMICOLON,
		eEqual 	 	  = GLFW_KEY_EQUAL,
		eA	 	 	  = GLFW_KEY_A,
		eB	 	 	  = GLFW_KEY_B,
		eC	 	 	  = GLFW_KEY_C,
		eD	 	 	  = GLFW_KEY_D,
		eE	 	 	  = GLFW_KEY_E,
		eF	 	 	  = GLFW_KEY_F,
		eG	 	 	  = GLFW_KEY_G,
		eH	 	 	  = GLFW_KEY_H,
		eI	 	 	  = GLFW_KEY_I,
		eJ	 	 	  = GLFW_KEY_J,
		eK	 	 	  = GLFW_KEY_K,
		eL	 	 	  = GLFW_KEY_L,
		eM	 	 	  = GLFW_KEY_M,
		eN	 	 	  = GLFW_KEY_N,
		eO	 	 	  = GLFW_KEY_O,
		eP	 	 	  = GLFW_KEY_P,
		eQ	 	 	  = GLFW_KEY_Q,
		eR	 	 	  = GLFW_KEY_R,
		eS	 	 	  = GLFW_KEY_S,
		eT	 	 	  = GLFW_KEY_T,
		eU	 	 	  = GLFW_KEY_U,
		eV	 	 	  = GLFW_KEY_V,
		eW	 	 	  = GLFW_KEY_W,
		eX	 	 	  = GLFW_KEY_X,
		eY	 	 	  = GLFW_KEY_Y,
		eZ	 	 	  = GLFW_KEY_Z,
		eLeftBracket  = GLFW_KEY_LEFT_BRACKET,
		eBackslash	  = GLFW_KEY_BACKSLASH,
		eRightBracket = GLFW_KEY_RIGHT_BRACKET,
		eGraveAccent  = GLFW_KEY_GRAVE_ACCENT,
		eWorld1	 	  = GLFW_KEY_WORLD_1,
		eWorld2	 	  = GLFW_KEY_WORLD_2,

		/* Function keys */
		eEscape	 	  = GLFW_KEY_ESCAPE,
		eEnter	  	  = GLFW_KEY_ENTER,
		eTab	 	  = GLFW_KEY_TAB,
		eBackspace	  = GLFW_KEY_BACKSPACE,
		eInsert	 	  = GLFW_KEY_INSERT,
		eDelete	 	  = GLFW_KEY_DELETE,
		eRight	  	  = GLFW_KEY_RIGHT,
		eLeft	  	  = GLFW_KEY_LEFT,
		eDown	  	  = GLFW_KEY_DOWN,
		eUp		  	  = GLFW_KEY_UP,
		ePageUp	  	  = GLFW_KEY_PAGE_UP,
		ePageDown 	  = GLFW_KEY_PAGE_DOWN,
		eHome	  	  = GLFW_KEY_HOME,
		eEnd	  	  = GLFW_KEY_END,
		eCapsLock 	  = GLFW_KEY_CAPS_LOCK,
		eScrollLock	  = GLFW_KEY_SCROLL_LOCK,
		eNumLock	  = GLFW_KEY_NUM_LOCK,
		ePrintScreen  = GLFW_KEY_PRINT_SCREEN,
		ePause	  	  = GLFW_KEY_PAUSE,
		eF1	  	  	  = GLFW_KEY_F1,
		eF2	  	  	  = GLFW_KEY_F2,
		eF3	  	  	  = GLFW_KEY_F3,
		eF4	  	  	  = GLFW_KEY_F4,
		eF5	  	  	  = GLFW_KEY_F5,
		eF6	  	  	  = GLFW_KEY_F6,
		eF7	  	  	  = GLFW_KEY_F7,
		eF8	  	  	  = GLFW_KEY_F8,
		eF9	  	  	  = GLFW_KEY_F9,
		eF10  	  	  = GLFW_KEY_F10,
		eF11  	  	  = GLFW_KEY_F11,
		eF12  	  	  = GLFW_KEY_F12,
		eF13  	  	  = GLFW_KEY_F13,
		eF14  	  	  = GLFW_KEY_F14,
		eF15  	  	  = GLFW_KEY_F15,
		eF16  	  	  = GLFW_KEY_F16,
		eF17  	  	  = GLFW_KEY_F17,
		eF18  	  	  = GLFW_KEY_F18,
		eF19  	  	  = GLFW_KEY_F19,
		eF20  	  	  = GLFW_KEY_F20,
		eF21  	  	  = GLFW_KEY_F21,
		eF22  	  	  = GLFW_KEY_F22,
		eF23  	  	  = GLFW_KEY_F23,
		eF24  	  	  = GLFW_KEY_F24,
		eF25  	  	  = GLFW_KEY_F25,
		eKp0  	  	  = GLFW_KEY_KP_0,
		eKp1  	  	  = GLFW_KEY_KP_1,
		eKp2  	  	  = GLFW_KEY_KP_2,
		eKp3  	  	  = GLFW_KEY_KP_3,
		eKp4  	  	  = GLFW_KEY_KP_4,
		eKp5  	  	  = GLFW_KEY_KP_5,
		eKp6  	  	  = GLFW_KEY_KP_6,
		eKp7  	  	  = GLFW_KEY_KP_7,
		eKp8  	  	  = GLFW_KEY_KP_8,
		eKp9  	  	  = GLFW_KEY_KP_9,
		eKpDecimal    = GLFW_KEY_KP_DECIMAL,
		eKpDivide  	  = GLFW_KEY_KP_DIVIDE,
		eKpMultiply   = GLFW_KEY_KP_MULTIPLY,
		eKpSubtract   = GLFW_KEY_KP_SUBTRACT,
		eKpAdd   	  = GLFW_KEY_KP_ADD,
		eKpEnter  	  = GLFW_KEY_KP_ENTER,
		eKpEqual  	  = GLFW_KEY_KP_EQUAL,
		eLeftShift 	  = GLFW_KEY_LEFT_SHIFT,
		eLeftControl  = GLFW_KEY_LEFT_CONTROL,
		eLeftAlt 	  = GLFW_KEY_LEFT_ALT,
		eLeftSuper 	  = GLFW_KEY_LEFT_SUPER,
		eRightShift   = GLFW_KEY_RIGHT_SHIFT,
		eRightControl = GLFW_KEY_RIGHT_CONTROL,
		eRightAlt 	  = GLFW_KEY_RIGHT_ALT,
		eRightSuper   = GLFW_KEY_RIGHT_SUPER,
		eMenu 		  = GLFW_KEY_MENU,
		eLast	      = GLFW_KEY_LAST
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Key value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Key::eUnknown: 	 return "Unknown";
		case Key::eSpace: 		 return "Space";
		case Key::eApostrophe: 	 return "Apostrophe";
		case Key::eComma: 		 return "Comma";
		case Key::eMinus: 		 return "Minus";
		case Key::ePeriod: 		 return "Period";
		case Key::eSlash: 		 return "Slash";
		case Key::e0: 			 return "0";
		case Key::e1: 			 return "1";
		case Key::e2: 			 return "2";
		case Key::e3: 			 return "3";
		case Key::e4: 			 return "4";
		case Key::e5: 			 return "5";
		case Key::e6: 			 return "6";
		case Key::e7: 			 return "7";
		case Key::e8: 			 return "8";
		case Key::e9: 			 return "9";
		case Key::eSemicolon: 	 return "Semicolon";
		case Key::eEqual: 		 return "Equal";
		case Key::eA: 			 return "A";
		case Key::eB: 			 return "B";
		case Key::eC: 			 return "C";
		case Key::eD: 			 return "D";
		case Key::eE: 			 return "E";
		case Key::eF: 			 return "F";
		case Key::eG: 			 return "G";
		case Key::eH: 			 return "H";
		case Key::eI: 			 return "I";
		case Key::eJ: 			 return "J";
		case Key::eK: 			 return "K";
		case Key::eL: 			 return "L";
		case Key::eM: 			 return "M";
		case Key::eN: 			 return "N";
		case Key::eO: 			 return "O";
		case Key::eP: 			 return "P";
		case Key::eQ: 			 return "Q";
		case Key::eR: 			 return "R";
		case Key::eS: 			 return "S";
		case Key::eT: 			 return "T";
		case Key::eU: 			 return "U";
		case Key::eV: 			 return "V";
		case Key::eW: 			 return "W";
		case Key::eX: 			 return "X";
		case Key::eY: 			 return "Y";
		case Key::eZ: 			 return "Z";
		case Key::eLeftBracket:  return "LeftBracket";
		case Key::eBackslash: 	 return "Backslash";
		case Key::eRightBracket: return "RightBracket";
		case Key::eGraveAccent:  return "GraveAccent";
		case Key::eWorld1: 		 return "World1";
		case Key::eWorld2: 		 return "World2";
		case Key::eEscape: 		 return "Escape";
		case Key::eEnter: 		 return "Enter";
		case Key::eTab: 		 return "Tab";
		case Key::eBackspace: 	 return "Backspace";
		case Key::eInsert: 		 return "Insert";
		case Key::eDelete: 		 return "Delete";
		case Key::eRight: 		 return "Right";
		case Key::eLeft: 		 return "Left";
		case Key::eDown: 		 return "Down";
		case Key::eUp: 			 return "Up";
		case Key::ePageUp: 		 return "PageUp";
		case Key::ePageDown: 	 return "PageDown";
		case Key::eHome: 		 return "Home";
		case Key::eEnd: 		 return "End";
		case Key::eCapsLock: 	 return "CapsLock";
		case Key::eScrollLock: 	 return "ScrollLock";
		case Key::eNumLock: 	 return "NumLock";
		case Key::ePrintScreen:  return "PrintScreen";
		case Key::ePause: 		 return "Pause";
		case Key::eF1: 			 return "F1";
		case Key::eF2: 			 return "F2";
		case Key::eF3: 			 return "F3";
		case Key::eF4: 			 return "F4";
		case Key::eF5: 			 return "F5";
		case Key::eF6: 			 return "F6";
		case Key::eF7: 			 return "F7";
		case Key::eF8: 			 return "F8";
		case Key::eF9: 			 return "F9";
		case Key::eF10: 		 return "F10";
		case Key::eF11: 		 return "F11";
		case Key::eF12: 		 return "F12";
		case Key::eF13: 		 return "F13";
		case Key::eF14: 		 return "F14";
		case Key::eF15: 		 return "F15";
		case Key::eF16: 		 return "F16";
		case Key::eF17: 		 return "F17";
		case Key::eF18: 		 return "F18";
		case Key::eF19: 		 return "F19";
		case Key::eF20: 		 return "F20";
		case Key::eF21: 		 return "F21";
		case Key::eF22: 		 return "F22";
		case Key::eF23: 		 return "F23";
		case Key::eF24: 		 return "F24";
		case Key::eF25: 		 return "F25";
		case Key::eKp0: 		 return "Kp0";
		case Key::eKp1: 		 return "Kp1";
		case Key::eKp2: 		 return "Kp2";
		case Key::eKp3: 		 return "Kp3";
		case Key::eKp4: 		 return "Kp4";
		case Key::eKp5: 		 return "Kp5";
		case Key::eKp6: 		 return "Kp6";
		case Key::eKp7: 		 return "Kp7";
		case Key::eKp8: 		 return "Kp8";
		case Key::eKp9: 		 return "Kp9";
		case Key::eKpDecimal: 	 return "KpDecimal";
		case Key::eKpDivide: 	 return "KpDivide";
		case Key::eKpMultiply: 	 return "KpMultiply";
		case Key::eKpSubtract: 	 return "KpSubtract";
		case Key::eKpAdd: 		 return "KpAdd";
		case Key::eKpEnter: 	 return "KpEnter";
		case Key::eKpEqual: 	 return "KpEqual";
		case Key::eLeftShift: 	 return "LeftShift";
		case Key::eLeftControl:  return "LeftControl";
		case Key::eLeftAlt: 	 return "LeftAlt";
		case Key::eLeftSuper: 	 return "LeftSuper";
		case Key::eRightShift: 	 return "RightShift";
		case Key::eRightControl: return "RightControl";
		case Key::eRightAlt: 	 return "RightAlt";
		case Key::eRightSuper: 	 return "RightSuper";
		case Key::eMenu: 		 return "Menu/Last";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup mods Modifier key flags
 	 *  @brief Modifier key flags.
 	 *
 	 *  See [key input](@ref input_key) for how these are used.
 	 *
 	 *  @ingroup input
 	 */
	enum class Mod : EnumSize
	{
		/*! @brief If this bit is set one or more Shift keys were held down.
 		 *
 		 *  If this bit is set one or more Shift keys were held down.
 		 */
		eShift 	  = GLFW_MOD_SHIFT,

		/*! @brief If this bit is set one or more Control keys were held down.
 		 *
 		 *  If this bit is set one or more Control keys were held down.
 		 */
		eControl  = GLFW_MOD_CONTROL,

		/*! @brief If this bit is set one or more Alt keys were held down.
 		 *
 		 *  If this bit is set one or more Alt keys were held down.
 		 */
		eAlt 	  = GLFW_MOD_ALT,

		/*! @brief If this bit is set one or more Super keys were held down.
 		 *
 		 *  If this bit is set one or more Super keys were held down.
 		 */
		eSuper 	  = GLFW_MOD_SUPER,

		/*! @brief If this bit is set the Caps Lock key is enabled.
 		 *
 		 *  If this bit is set the Caps Lock key is enabled and the @ref
 		 *  GLFW_HPP_NAMESPACE::InputMode::eLockKeyMods input mode is set.
 		 */
		eCapsLock = GLFW_MOD_CAPS_LOCK,

		/*! @brief If this bit is set the Num Lock key is enabled.
 		 *
 		 *  If this bit is set the Num Lock key is enabled and the @ref
 		 *  GLFW_HPP_NAMESPACE::InputMode::eLockKeyMods input mode is set.
 		 */
		eNumLock  = GLFW_MOD_NUM_LOCK
	};

	using ModFlags = Flags<Mod>;

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Mod value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Mod::eShift: 	 return "Shift";
		case Mod::eControl:  return "Control";
		case Mod::eAlt: 	 return "Alt";
		case Mod::eSuper: 	 return "Super";
		case Mod::eCapsLock: return "CapsLock";
		case Mod::eNumLock:  return "NumLock";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup buttons Mouse buttons
 	 *  @brief Mouse button IDs.
 	 *
 	 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 	 *
 	 *  @ingroup input
 	 */
	enum class MouseButton : EnumSize
	{
		e1 		= GLFW_MOUSE_BUTTON_1,
		e2 		= GLFW_MOUSE_BUTTON_2,
		e3 		= GLFW_MOUSE_BUTTON_3,
		e4 		= GLFW_MOUSE_BUTTON_4,
		e5 		= GLFW_MOUSE_BUTTON_5,
		e6 		= GLFW_MOUSE_BUTTON_6,
		e7 		= GLFW_MOUSE_BUTTON_7,
		e8 		= GLFW_MOUSE_BUTTON_8,
		eLast 	= GLFW_MOUSE_BUTTON_LAST,
		eLeft 	= GLFW_MOUSE_BUTTON_LEFT,
		eRight 	= GLFW_MOUSE_BUTTON_RIGHT,
		eMiddle = GLFW_MOUSE_BUTTON_MIDDLE,
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const MouseButton value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case MouseButton::e1: return "1/Left";
		case MouseButton::e2: return "2/Right";
		case MouseButton::e3: return "3/Middle";
		case MouseButton::e4: return "4";
		case MouseButton::e5: return "5";
		case MouseButton::e6: return "6";
		case MouseButton::e7: return "7";
		case MouseButton::e8: return "8/Last";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup joysticks Joysticks
 	 *  @brief Joystick IDs.
 	 *
 	 *  See [joystick input](@ref joystick) for how these are used.
 	 *
 	 *  @ingroup input
 	 */
	enum class Joystick : EnumSize
	{
		e1 	  = GLFW_JOYSTICK_1,
		e2 	  = GLFW_JOYSTICK_2,
		e3 	  = GLFW_JOYSTICK_3,
		e4 	  = GLFW_JOYSTICK_4,
		e5 	  = GLFW_JOYSTICK_5,
		e6 	  = GLFW_JOYSTICK_6,
		e7 	  = GLFW_JOYSTICK_7,
		e8 	  = GLFW_JOYSTICK_8,
		e9 	  = GLFW_JOYSTICK_9,
		e10   = GLFW_JOYSTICK_10,
		e11   = GLFW_JOYSTICK_11,
		e12   = GLFW_JOYSTICK_12,
		e13   = GLFW_JOYSTICK_13,
		e14   = GLFW_JOYSTICK_14,
		e15   = GLFW_JOYSTICK_15,
		e16   = GLFW_JOYSTICK_16,
		eLast = GLFW_JOYSTICK_LAST
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Joystick value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Joystick::e1: 	return "1";
		case Joystick::e2: 	return "2";
		case Joystick::e3: 	return "3";
		case Joystick::e4: 	return "4";
		case Joystick::e5: 	return "5";
		case Joystick::e6: 	return "6";
		case Joystick::e7: 	return "7";
		case Joystick::e8: 	return "8";
		case Joystick::e9: 	return "9";
		case Joystick::e10: return "10";
		case Joystick::e11: return "11";
		case Joystick::e12: return "12";
		case Joystick::e13: return "13";
		case Joystick::e14: return "14";
		case Joystick::e15: return "15";
		case Joystick::e16: return "16/Last";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup gamepad_buttons Gamepad buttons
 	 *  @brief Gamepad buttons.
 	 *
 	 *  See @ref gamepad for how these are used.
 	 *
 	 *  @ingroup input
 	 */
	enum class GamepadButton : EnumSize
	{
		eA 			 = GLFW_GAMEPAD_BUTTON_A,
		eB 			 = GLFW_GAMEPAD_BUTTON_B,
		eX 			 = GLFW_GAMEPAD_BUTTON_X,
		eY 			 = GLFW_GAMEPAD_BUTTON_Y,
		eLeftBumper  = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		eRightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
		eBack 		 = GLFW_GAMEPAD_BUTTON_BACK,
		eStart 		 = GLFW_GAMEPAD_BUTTON_START,
		eGuide 		 = GLFW_GAMEPAD_BUTTON_GUIDE,
		eLeftThumb 	 = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
		eRightThumb  = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
		eDpadUp 	 = GLFW_GAMEPAD_BUTTON_DPAD_UP,
		eDpadRight 	 = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
		eDpadDown 	 = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
		eDpadLeft 	 = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
		eLast 		 = GLFW_GAMEPAD_BUTTON_LAST,
		eCross 		 = GLFW_GAMEPAD_BUTTON_CROSS,
		eCircle 	 = GLFW_GAMEPAD_BUTTON_CIRCLE,
		eSquare 	 = GLFW_GAMEPAD_BUTTON_SQUARE,
		eTriangle 	 = GLFW_GAMEPAD_BUTTON_TRIANGLE
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const GamepadButton value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case GamepadButton::eA: 		  return "A/Cross";
		case GamepadButton::eB: 		  return "B/Circle";
		case GamepadButton::eX: 		  return "X/Square";
		case GamepadButton::eY: 		  return "Y/Triangle";
		case GamepadButton::eLeftBumper:  return "LeftBumper";
		case GamepadButton::eRightBumper: return "RightBumper";
		case GamepadButton::eBack: 		  return "Back";
		case GamepadButton::eStart: 	  return "Start";
		case GamepadButton::eGuide: 	  return "Guide";
		case GamepadButton::eLeftThumb:   return "LeftThumb";
		case GamepadButton::eRightThumb:  return "RightThumb";
		case GamepadButton::eDpadUp: 	  return "DpadUp";
		case GamepadButton::eDpadRight:   return "DpadRight";
		case GamepadButton::eDpadDown: 	  return "DpadDown";
		case GamepadButton::eDpadLeft: 	  return "DpadLeft/Last";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup gamepad_axes Gamepad axes
 	 *  @brief Gamepad axes.
 	 *
 	 *  See @ref gamepad for how these are used.
 	 *
 	 *  @ingroup input
 	 */
	enum class GamepadAxis : EnumSize
	{
		eLeftX 		  = GLFW_GAMEPAD_AXIS_LEFT_X,
		eLeftY 		  = GLFW_GAMEPAD_AXIS_LEFT_Y,
		eRightX 	  = GLFW_GAMEPAD_AXIS_RIGHT_X,
		eRightY 	  = GLFW_GAMEPAD_AXIS_RIGHT_Y,
		eLeftTrigger  = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
		eRightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
		eLast 		  = GLFW_GAMEPAD_AXIS_LAST
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const GamepadAxis value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case GamepadAxis::eLeftX: 		 return "LeftX";
		case GamepadAxis::eLeftY: 		 return "LeftY";
		case GamepadAxis::eRightX: 		 return "RightX";
		case GamepadAxis::eRightY: 		 return "RightY";
		case GamepadAxis::eLeftTrigger:  return "LeftTrigger";
		case GamepadAxis::eRightTrigger: return "RightTrigger/Last";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup errors Error codes
 	 *  @brief Error codes.
 	 *
 	 *  See [error handling](@ref error_handling) for how these are used.
 	 *
 	 *  @ingroup init
 	 */
	enum class Error : EnumSize
	{
		/*! @brief No error has occurred.
 		 *
 		 *  No error has occurred.
 		 *
 		 *  @analysis Yay.
 		 */
		eNone	 			= GLFW_NO_ERROR,

		/*! @brief GLFW has not been initialized.
 		 *
 		 *  This occurs if a GLFW function was called that must not be called unless the
 		 *  library is [initialized](@ref intro_init).
 		 *
 		 *  @analysis Application programmer error.  Initialize GLFW before calling any
 		 *  function that requires initialization.
 		 */
		eNotInitalized 		= GLFW_NOT_INITIALIZED,

		/*! @brief No context is current for this thread.
 		 *
 		 *  This occurs if a GLFW function was called that needs and operates on the
 		 *  current OpenGL or OpenGL ES context but no context is current on the calling
 		 *  thread.  One such function is @ref glfwSwapInterval.
 		 *
 		 *  @analysis Application programmer error.  Ensure a context is current before
 		 *  calling functions that require a current context.
 		 */
		eNoCurrentContext 	= GLFW_NO_CURRENT_CONTEXT,

		/*! @brief One of the arguments to the function was an invalid enum value.
 		 *
 		 *  One of the arguments to the function was an invalid enum value, for example
 		 *  requesting @ref GLFW_RED_BITS with @ref glfwGetWindowAttrib.
 		 *
 		 *  @analysis Application programmer error.  Fix the offending call.
 		 */
		eInvalidEnum 		= GLFW_INVALID_ENUM,

		/*! @brief One of the arguments to the function was an invalid value.
 		 *
 		 *  One of the arguments to the function was an invalid value, for example
 		 *  requesting a non-existent OpenGL or OpenGL ES version like 2.7.
 		 *
 		 *  Requesting a valid but unavailable OpenGL or OpenGL ES version will instead
 		 *  result in a @ref GLFW_HPP_NAMESPACE::Error::eVersionUnavailable error.
 		 *
 		 *  @analysis Application programmer error.  Fix the offending call.
 		 */
		eInvalidValue 		= GLFW_INVALID_VALUE,

		/*! @brief A memory allocation failed.
 		 *
 		 *  A memory allocation failed.
 		 *
 		 *  @analysis A bug in GLFW or the underlying operating system.  Report the bug
 		 *  to our [issue tracker](https://github.com/glfw/glfw/issues).
 		 */
		eOutOfMemory 		= GLFW_OUT_OF_MEMORY,

		/*! @brief GLFW could not find support for the requested API on the system.
 		 *
 		 *  GLFW could not find support for the requested API on the system.
 		 *
 		 *  @analysis The installed graphics driver does not support the requested
 		 *  API, or does not support it via the chosen context creation backend.
 		 *  Below are a few examples.
 		 *
 		 *  @par
 		 *  Some pre-installed Windows graphics drivers do not support OpenGL.  AMD only
 		 *  supports OpenGL ES via EGL, while Nvidia and Intel only support it via
 		 *  a WGL or GLX extension.  macOS does not provide OpenGL ES at all.  The Mesa
 		 *  EGL, OpenGL and OpenGL ES libraries do not interface with the Nvidia binary
 		 *  driver.  Older graphics drivers do not support Vulkan.
 		 */
		eApiUnavailable 	= GLFW_API_UNAVAILABLE,

		/*! @brief The requested OpenGL or OpenGL ES version is not available.
 		 *
 		 *  The requested OpenGL or OpenGL ES version (including any requested context
 		 *  or framebuffer hints) is not available on this machine.
 		 *
 		 *  @analysis The machine does not support your requirements.  If your
 		 *  application is sufficiently flexible, downgrade your requirements and try
 		 *  again.  Otherwise, inform the user that their machine does not match your
 		 *  requirements.
 		 *
 		 *  @par
 		 *  Future invalid OpenGL and OpenGL ES versions, for example OpenGL 4.8 if 5.0
 		 *  comes out before the 4.x series gets that far, also fail with this error and
 		 *  not @ref GLFW_HPP_NAMESPACE::Error::eInvalidValue, because GLFW cannot know what future versions
 		 *  will exist.
 		 */
		eVersionUnavailable = GLFW_VERSION_UNAVAILABLE,

		/*! @brief A platform-specific error occurred that does not match any of the
 		 *  more specific categories.
 		 *
 		 *  A platform-specific error occurred that does not match any of the more
 		 *  specific categories.
 		 *
 		 *  @analysis A bug or configuration error in GLFW, the underlying operating
 		 *  system or its drivers, or a lack of required resources.  Report the issue to
 		 *  our [issue tracker](https://github.com/glfw/glfw/issues).
 		 */
		ePlatform	 		= GLFW_PLATFORM_ERROR,

		/*! @brief The requested format is not supported or available.
 		 *
 		 *  If emitted during window creation, the requested pixel format is not
 		 *  supported.
 		 *
 		 *  If emitted when querying the clipboard, the contents of the clipboard could
 		 *  not be converted to the requested format.
 		 *
 		 *  @analysis If emitted during window creation, one or more
 		 *  [hard constraints](@ref window_hints_hard) did not match any of the
 		 *  available pixel formats.  If your application is sufficiently flexible,
 		 *  downgrade your requirements and try again.  Otherwise, inform the user that
 		 *  their machine does not match your requirements.
 		 *
 		 *  @par
 		 *  If emitted when querying the clipboard, ignore the error or report it to
 		 *  the user, as appropriate.
 		 */
		eFormatUnavailable 	= GLFW_FORMAT_UNAVAILABLE,

		/*! @brief The specified window does not have an OpenGL or OpenGL ES context.
		 *
		 *  A window that does not have an OpenGL or OpenGL ES context was passed to
		 *  a function that requires it to have one.
		 *
		 *  @analysis Application programmer error.  Fix the offending call.
		 */
		eNoWindowContext 	= GLFW_NO_WINDOW_CONTEXT
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Error value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Error::eNone:	 			 return "None";
		case Error::eNotInitalized: 	 return "NotInitalized";
		case Error::eNoCurrentContext: 	 return "NoCurrentContext";
		case Error::eInvalidEnum: 		 return "InvalidEnum";
		case Error::eInvalidValue: 		 return "InvalidValue";
		case Error::eOutOfMemory: 		 return "OutOfMemory";
		case Error::eApiUnavailable: 	 return "ApiUnavailable";
		case Error::eVersionUnavailable: return "VersionUnavailable";
		case Error::ePlatform:		 	 return "Platform";
		case Error::eFormatUnavailable:  return "FormatUnavailable";
		case Error::eNoWindowContext: 	 return "NoWindowContext";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @addtogroup window
	 */
	enum class WindowHint : EnumSize
	{
		/*! @brief Input focus window hint and attribute
 		 *
 		 *  Input focus [window hint](@ref GLFW_FOCUSED_hint) or
 		 *  [window attribute](@ref GLFW_FOCUSED_attrib).
 		 */
		eFocused   	  			= GLFW_FOCUSED,

		/*! @brief Window resize-ability window hint and attribute
 		 *
 		 *  Window resize-ability [window hint](@ref GLFW_RESIZABLE_hint) and
 		 *  [window attribute](@ref GLFW_RESIZABLE_attrib).
 		 */
		eResizable 	  			= GLFW_RESIZABLE,

		/*! @brief Window visibility window hint and attribute
 		 *
 		 *  Window visibility [window hint](@ref GLFW_VISIBLE_hint) and
 		 *  [window attribute](@ref GLFW_VISIBLE_attrib).
 		 */
		eVisible   	  			= GLFW_VISIBLE,

		/*! @brief Window decoration window hint and attribute
 		 *
 		 *  Window decoration [window hint](@ref GLFW_DECORATED_hint) and
 		 *  [window attribute](@ref GLFW_DECORATED_attrib).
 		 */
		eDecorated 	  			= GLFW_DECORATED,

		/*! @brief Window auto-iconification window hint and attribute
 		 *
 		 *  Window auto-iconification [window hint](@ref GLFW_AUTO_ICONIFY_hint) and
 		 *  [window attribute](@ref GLFW_AUTO_ICONIFY_attrib).
 		 */
		eAutoIconify  			= GLFW_AUTO_ICONIFY,

		/*! @brief Window decoration window hint and attribute
 		 *
 		 *  Window decoration [window hint](@ref GLFW_FLOATING_hint) and
 		 *  [window attribute](@ref GLFW_FLOATING_attrib).
 		 */
		eFloating 	  			= GLFW_FLOATING,

		/*! @brief Window maximization window hint and attribute
 		 *
 		 *  Window maximization [window hint](@ref GLFW_MAXIMIZED_hint) and
 		 *  [window attribute](@ref GLFW_MAXIMIZED_attrib).
 		 */
		eMaximized    			= GLFW_MAXIMIZED,

		/*! @brief Cursor centering window hint
 		 *
 		 *  Cursor centering [window hint](@ref GLFW_CENTER_CURSOR_hint).
 		 */
		eCenterCursor 			= GLFW_CENTER_CURSOR,

		/*! @brief Window framebuffer transparency hint and attribute
 		 *
 		 *  Window framebuffer transparency
 		 *  [window hint](@ref GLFW_TRANSPARENT_FRAMEBUFFER_hint) and
 		 *  [window attribute](@ref GLFW_TRANSPARENT_FRAMEBUFFER_attrib).
 		 */
		eTransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,

		/*! @brief Input focus on calling show window hint and attribute
 		 *
 		 *  Input focus [window hint](@ref GLFW_FOCUS_ON_SHOW_hint) or
 		 *  [window attribute](@ref GLFW_FOCUS_ON_SHOW_attrib).
 		 */
		eFocusOnShow			= GLFW_FOCUS_ON_SHOW,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_RED_BITS).
 		 */
		eRedBits				= GLFW_RED_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_GREEN_BITS).
 		 */
		eGreenBits				= GLFW_GREEN_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_BLUE_BITS).
 		 */
		eBlueBits				= GLFW_BLUE_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_ALPHA_BITS).
 		 */
		eAlphaBits				= GLFW_ALPHA_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_DEPTH_BITS).
 		 */
		eDepthBits				= GLFW_DEPTH_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_STENCIL_BITS).
 		 */
		eStencilBits			= GLFW_STENCIL_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_ACCUM_RED_BITS).
 		 */
		eAccumRedBits			= GLFW_ACCUM_RED_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_ACCUM_GREEN_BITS).
 		 */
		eAccumGreenBits			= GLFW_ACCUM_GREEN_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_ACCUM_BLUE_BITS).
 		 */
		eAccumBlueBits			= GLFW_ACCUM_BLUE_BITS,

		/*! @brief Framebuffer bit depth hint.
 		 *
 		 *  Framebuffer bit depth [hint](@ref GLFW_ACCUM_ALPHA_BITS).
 		 */
		eAccumAlphaBits			= GLFW_ACCUM_ALPHA_BITS,

		/*! @brief Framebuffer auxiliary buffer hint.
 		 *
 		 *  Framebuffer auxiliary buffer [hint](@ref GLFW_AUX_BUFFERS).
 		 */
		eAuxBuffers				= GLFW_AUX_BUFFERS,

		/*! @brief OpenGL stereoscopic rendering hint.
 		 *
 		 *  OpenGL stereoscopic rendering [hint](@ref GLFW_STEREO).
 		 */
		eStereo					= GLFW_STEREO,

		/*! @brief Framebuffer MSAA samples hint.
 		 *
 		 *  Framebuffer MSAA samples [hint](@ref GLFW_SAMPLES).
 		 */
		eSamples				= GLFW_SAMPLES,

		/*! @brief Framebuffer sRGB hint.
 		 *
 		 *  Framebuffer sRGB [hint](@ref GLFW_SRGB_CAPABLE).
 		 */
		eSrgbCapable			= GLFW_SRGB_CAPABLE,

		/*! @brief Monitor refresh rate hint.
 		 *
 		 *  Monitor refresh rate [hint](@ref GLFW_REFRESH_RATE).
 		 */
		eRefreshRate			= GLFW_REFRESH_RATE,

		/*! @brief Framebuffer double buffering hint.
 		 *
 		 *  Framebuffer double buffering [hint](@ref GLFW_DOUBLEBUFFER).
 		 */
		eDoublebuffer			= GLFW_DOUBLEBUFFER,

		/*! @brief Context client API hint and attribute.
 		 *
 		 *  Context client API [hint](@ref GLFW_CLIENT_API_hint) and
 		 *  [attribute](@ref GLFW_CLIENT_API_attrib).
 		 */
		eClientApi 				= GLFW_CLIENT_API,

		/*! @brief Context client API major version hint and attribute.
 		 *
 		 *  Context client API major version [hint](@ref GLFW_CONTEXT_VERSION_MAJOR_hint)
 		 *  and [attribute](@ref GLFW_CONTEXT_VERSION_MAJOR_attrib).
 		 */
		eContextVersionMajor	= GLFW_CONTEXT_VERSION_MAJOR,

		/*! @brief Context client API minor version hint and attribute.
 		 *
 		 *  Context client API minor version [hint](@ref GLFW_CONTEXT_VERSION_MINOR_hint)
 		 *  and [attribute](@ref GLFW_CONTEXT_VERSION_MINOR_attrib).
 		 */
		eContextVersionMinor	= GLFW_CONTEXT_VERSION_MINOR,

		/*! @brief Context client API revision number hint and attribute.
 		 *
 		 *  Context client API revision number
 		 *  [attribute](@ref GLFW_CONTEXT_REVISION_attrib).
 		 */
		eContextRevision		= GLFW_CONTEXT_REVISION,

		/*! @brief Context robustness hint and attribute.
 		 *
 		 *  Context client API revision number [hint](@ref GLFW_CONTEXT_ROBUSTNESS_hint)
 		 *  and [attribute](@ref GLFW_CONTEXT_ROBUSTNESS_attrib).
 		 */
		eContextRobustness		= GLFW_CONTEXT_ROBUSTNESS,

		/*! @brief OpenGL forward-compatibility hint and attribute.
 		 *
 		 *  OpenGL forward-compatibility [hint](@ref GLFW_OPENGL_FORWARD_COMPAT_hint)
 		 *  and [attribute](@ref GLFW_OPENGL_FORWARD_COMPAT_attrib).
 		 */
		eOpenglForwardCompat	= GLFW_OPENGL_FORWARD_COMPAT,

		/*! @brief Debug mode context hint and attribute.
 		 *
 		 *  Debug mode context [hint](@ref GLFW_OPENGL_DEBUG_CONTEXT_hint) and
 		 *  [attribute](@ref GLFW_OPENGL_DEBUG_CONTEXT_attrib).
 		 */
		eOpenglDebugContext		= GLFW_OPENGL_DEBUG_CONTEXT,

		/*! @brief OpenGL profile hint and attribute.
 		 *
 		 *  OpenGL profile [hint](@ref GLFW_OPENGL_PROFILE_hint) and
 		 *  [attribute](@ref GLFW_OPENGL_PROFILE_attrib).
 		 */
		eOpenglProfile			= GLFW_OPENGL_PROFILE,

		/*! @brief Context flush-on-release hint and attribute.
 		 *
 		 *  Context flush-on-release [hint](@ref GLFW_CONTEXT_RELEASE_BEHAVIOR_hint) and
 		 *  [attribute](@ref GLFW_CONTEXT_RELEASE_BEHAVIOR_attrib).
 		 */
		eContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,

		/*! @brief Context error suppression hint and attribute.
 		 *
 		 *  Context error suppression [hint](@ref GLFW_CONTEXT_NO_ERROR_hint) and
 		 *  [attribute](@ref GLFW_CONTEXT_NO_ERROR_attrib).
 		 */
		eContextNoError			= GLFW_CONTEXT_NO_ERROR,

		/*! @brief Context creation API hint and attribute.
 		 *
 		 *  Context creation API [hint](@ref GLFW_CONTEXT_CREATION_API_hint) and
 		 *  [attribute](@ref GLFW_CONTEXT_CREATION_API_attrib).
 		 */
		eContextCreationApi		= GLFW_CONTEXT_CREATION_API,

		/*! @brief Window content area scaling window
 		 *  [window hint](@ref GLFW_SCALE_TO_MONITOR).
 		 */
		eScaleToMonitor			= GLFW_SCALE_TO_MONITOR,

		/*! @brief macOS specific
 		 *  [window hint](@ref GLFW_COCOA_RETINA_FRAMEBUFFER_hint).
 		 */
		eCocoaRetinaFramebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,

		/*! @brief macOS specific
 		 *  [window hint](@ref GLFW_COCOA_FRAME_NAME_hint).
 		 */
		eCocoaFrameName			= GLFW_COCOA_FRAME_NAME,

		/*! @brief macOS specific
 		 *  [window hint](@ref GLFW_COCOA_GRAPHICS_SWITCHING_hint).
 		 */
		eCocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,

		/*! @brief X11 specific
 		 *  [window hint](@ref GLFW_X11_CLASS_NAME_hint).
 		 */
		eX11ClassName			= GLFW_X11_CLASS_NAME,

		/*! @brief X11 specific
 		 *  [window hint](@ref GLFW_X11_INSTANCE_NAME_hint).
 		 */
		eX11InstanceName		= GLFW_X11_INSTANCE_NAME
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const WindowHint value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case WindowHint::eFocused:   	  		  return "Focused";
		case WindowHint::eResizable: 	  		  return "Resizable";
		case WindowHint::eVisible:   	  		  return "Visible";
		case WindowHint::eDecorated: 	  		  return "Decorated";
		case WindowHint::eAutoIconify:  		  return "AutoIconify";
		case WindowHint::eFloating: 	  		  return "Floating";
		case WindowHint::eMaximized: 	  		  return "Maximized";
		case WindowHint::eCenterCursor: 		  return "CenterCursor";
		case WindowHint::eTransparentFramebuffer: return "TransparentFramebuffer";
		case WindowHint::eFocusOnShow: 			  return "FocusOnShow";
		case WindowHint::eRedBits: 				  return "RedBits";
		case WindowHint::eGreenBits: 			  return "GreenBits";
		case WindowHint::eBlueBits: 			  return "BlueBits";
		case WindowHint::eAlphaBits: 			  return "AlphaBits";
		case WindowHint::eDepthBits: 			  return "DepthBits";
		case WindowHint::eStencilBits: 			  return "StencilBits";
		case WindowHint::eAccumRedBits: 		  return "AccumRedBits";
		case WindowHint::eAccumGreenBits: 		  return "AccumGreenBits";
		case WindowHint::eAccumBlueBits: 		  return "AccumBlueBits";
		case WindowHint::eAccumAlphaBits: 		  return "AccumAlphaBits";
		case WindowHint::eAuxBuffers: 			  return "AuxBuffers";
		case WindowHint::eStereo: 				  return "Stereo";
		case WindowHint::eSamples: 				  return "Samples";
		case WindowHint::eSrgbCapable: 			  return "SrgbCapable";
		case WindowHint::eRefreshRate: 			  return "RefreshRate";
		case WindowHint::eDoublebuffer: 		  return "Doublebuffer";
		case WindowHint::eClientApi: 			  return "ClientApi";
		case WindowHint::eContextVersionMajor: 	  return "ContextVersionMajor";
		case WindowHint::eContextVersionMinor: 	  return "ContextVersionMinor";
		case WindowHint::eContextRevision:	 	  return "ContextRevision";
		case WindowHint::eContextRobustness:	  return "ContextRobustness";
		case WindowHint::eOpenglForwardCompat: 	  return "OpenglForwardCompat";
		case WindowHint::eOpenglDebugContext: 	  return "OpenglDebugContext";
		case WindowHint::eOpenglProfile: 		  return "OpenglProfile";
		case WindowHint::eContextReleaseBehavior: return "ContextReleaseBehavior";
		case WindowHint::eContextNoError:		  return "ContextNoError";
		case WindowHint::eContextCreationApi:	  return "ContexCreationApi";
		case WindowHint::eScaleToMonitor:		  return "ScaleToMonitor";
		case WindowHint::eCocoaRetinaFramebuffer: return "CocoaRetinaFramebuffer";
		case WindowHint::eCocoaFrameName:		  return "CocoaFrameName";
		case WindowHint::eCocoaGraphicsSwitching: return "CocoaGraphicsSwitching";
		case WindowHint::eX11ClassName:			  return "X11ClassName";
		case WindowHint::eX11InstanceName:		  return "X11InstanceName";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @addtogroup window
	 */
	enum class WindowAttribute : EnumSize
	{
		/*! @brief Input focus window hint and attribute
 		 *
 		 *  Input focus [window hint](@ref GLFW_FOCUSED_hint) or
 		 *  [window attribute](@ref GLFW_FOCUSED_attrib).
 		 */
		eFocused   	  			= GLFW_FOCUSED,

		/*! @brief Window iconification window attribute
 		 *
 		 *  Window iconification [window attribute](@ref GLFW_ICONIFIED_attrib).
 		 */
		eIconified				= GLFW_ICONIFIED,

		/*! @brief Window resize-ability window hint and attribute
 		 *
 		 *  Window resize-ability [window hint](@ref GLFW_RESIZABLE_hint) and
 		 *  [window attribute](@ref GLFW_RESIZABLE_attrib).
 		 */
		eResizable 	  			= GLFW_RESIZABLE,

		/*! @brief Window visibility window hint and attribute
 		 *
 		 *  Window visibility [window hint](@ref GLFW_VISIBLE_hint) and
 		 *  [window attribute](@ref GLFW_VISIBLE_attrib).
 		 */
		eVisible   	  			= GLFW_VISIBLE,

		/*! @brief Window decoration window hint and attribute
 		 *
 		 *  Window decoration [window hint](@ref GLFW_DECORATED_hint) and
 		 *  [window attribute](@ref GLFW_DECORATED_attrib).
 		 */
		eDecorated 	  			= GLFW_DECORATED,

		/*! @brief Window auto-iconification window hint and attribute
 		 *
 		 *  Window auto-iconification [window hint](@ref GLFW_AUTO_ICONIFY_hint) and
 		 *  [window attribute](@ref GLFW_AUTO_ICONIFY_attrib).
 		 */
		eAutoIconify  			= GLFW_AUTO_ICONIFY,

		/*! @brief Window decoration window hint and attribute
 		 *
 		 *  Window decoration [window hint](@ref GLFW_FLOATING_hint) and
 		 *  [window attribute](@ref GLFW_FLOATING_attrib).
 		 */
		eFloating 	  			= GLFW_FLOATING,

		/*! @brief Window maximization window hint and attribute
 		 *
 		 *  Window maximization [window hint](@ref GLFW_MAXIMIZED_hint) and
 		 *  [window attribute](@ref GLFW_MAXIMIZED_attrib).
 		 */
		eMaximized    			= GLFW_MAXIMIZED,

		/*! @brief Window framebuffer transparency hint and attribute
 		 *
 		 *  Window framebuffer transparency
 		 *  [window hint](@ref GLFW_TRANSPARENT_FRAMEBUFFER_hint) and
 		 *  [window attribute](@ref GLFW_TRANSPARENT_FRAMEBUFFER_attrib).
 		 */
		eTransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,

		/*! @brief Mouse cursor hover window attribute.
 		 *
 		 *  Mouse cursor hover [window attribute](@ref GLFW_HOVERED_attrib).
 		 */
		eHovered				= GLFW_HOVERED,

		/*! @brief Input focus on calling show window hint and attribute
 		 *
 		 *  Input focus [window hint](@ref GLFW_FOCUS_ON_SHOW_hint) or
 		 *  [window attribute](@ref GLFW_FOCUS_ON_SHOW_attrib).
 		 */
		eFocusOnShow			= GLFW_FOCUS_ON_SHOW,

		/*! @brief Context client API hint and attribute.
 		 *
 		 *  Context client API [hint](@ref GLFW_CLIENT_API_hint) and
 		 *  [attribute](@ref GLFW_CLIENT_API_attrib).
 		 */
		eClientApi 				= GLFW_CLIENT_API,

		/*! @brief Context client API major version hint and attribute.
 		 *
 		 *  Context client API major version [hint](@ref GLFW_CONTEXT_VERSION_MAJOR_hint)
 		 *  and [attribute](@ref GLFW_CONTEXT_VERSION_MAJOR_attrib).
 		 */
		eContextVersionMajor	= GLFW_CONTEXT_VERSION_MAJOR,

		/*! @brief Context client API minor version hint and attribute.
 		 *
 		 *  Context client API minor version [hint](@ref GLFW_CONTEXT_VERSION_MINOR_hint)
 		 *  and [attribute](@ref GLFW_CONTEXT_VERSION_MINOR_attrib).
 		 */
		eContextVersionMinor	= GLFW_CONTEXT_VERSION_MINOR,

		/*! @brief Context client API revision number hint and attribute.
 		 *
 		 *  Context client API revision number
 		 *  [attribute](@ref GLFW_CONTEXT_REVISION_attrib).
 		 */
		eContextRevision		= GLFW_CONTEXT_REVISION,

		/*! @brief Context robustness hint and attribute.
 		 *
 		 *  Context client API revision number [hint](@ref GLFW_CONTEXT_ROBUSTNESS_hint)
 		 *  and [attribute](@ref GLFW_CONTEXT_ROBUSTNESS_attrib).
 		 */
		eContextRobustness		= GLFW_CONTEXT_ROBUSTNESS,

		/*! @brief OpenGL forward-compatibility hint and attribute.
 		 *
 		 *  OpenGL forward-compatibility [hint](@ref GLFW_OPENGL_FORWARD_COMPAT_hint)
 		 *  and [attribute](@ref GLFW_OPENGL_FORWARD_COMPAT_attrib).
 		 */
		eOpenglForwardCompat	= GLFW_OPENGL_FORWARD_COMPAT,

		/*! @brief Debug mode context hint and attribute.
 		 *
 		 *  Debug mode context [hint](@ref GLFW_OPENGL_DEBUG_CONTEXT_hint) and
 		 *  [attribute](@ref GLFW_OPENGL_DEBUG_CONTEXT_attrib).
 		 */
		eOpenglDebugContext		= GLFW_OPENGL_DEBUG_CONTEXT,

		/*! @brief OpenGL profile hint and attribute.
 		 *
 		 *  OpenGL profile [hint](@ref GLFW_OPENGL_PROFILE_hint) and
 		 *  [attribute](@ref GLFW_OPENGL_PROFILE_attrib).
 		 */
		eOpenglProfile			= GLFW_OPENGL_PROFILE,

		/*! @brief Context flush-on-release hint and attribute.
 		 *
 		 *  Context flush-on-release [hint](@ref GLFW_CONTEXT_RELEASE_BEHAVIOR_hint) and
 		 *  [attribute](@ref GLFW_CONTEXT_RELEASE_BEHAVIOR_attrib).
 		 */
		eContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,

		/*! @brief Context error suppression hint and attribute.
 		 *
 		 *  Context error suppression [hint](@ref GLFW_CONTEXT_NO_ERROR_hint) and
 		 *  [attribute](@ref GLFW_CONTEXT_NO_ERROR_attrib).
 		 */
		eContextNoError			= GLFW_CONTEXT_NO_ERROR,

		/*! @brief Context creation API hint and attribute.
 		 *
 		 *  Context creation API [hint](@ref GLFW_CONTEXT_CREATION_API_hint) and
 		 *  [attribute](@ref GLFW_CONTEXT_CREATION_API_attrib).
 		 */
		eContextCreationApi		= GLFW_CONTEXT_CREATION_API
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const WindowAttribute value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case WindowAttribute::eFocused:   	  		   return "Focused";
		case WindowAttribute::eIconified:   	  	   return "Iconified";
		case WindowAttribute::eResizable: 	  		   return "Resizable";
		case WindowAttribute::eVisible:   	  		   return "Visible";
		case WindowAttribute::eDecorated: 	  		   return "Decorated";
		case WindowAttribute::eAutoIconify:  		   return "AutoIconify";
		case WindowAttribute::eFloating: 	  		   return "Floating";
		case WindowAttribute::eMaximized: 	  		   return "Maximized";
		case WindowAttribute::eTransparentFramebuffer: return "TransparentFramebuffer";
		case WindowAttribute::eHovered: 			   return "Hovered";
		case WindowAttribute::eFocusOnShow: 		   return "FocusOnShow";
		case WindowAttribute::eClientApi: 			   return "ClientApi";
		case WindowAttribute::eContextVersionMajor:    return "ContextVersionMajor";
		case WindowAttribute::eContextVersionMinor:    return "ContextVersionMinor";
		case WindowAttribute::eContextRevision:	 	   return "ContextRevision";
		case WindowAttribute::eContextRobustness:	   return "ContextRobustness";
		case WindowAttribute::eOpenglForwardCompat:    return "OpenglForwardCompat";
		case WindowAttribute::eOpenglDebugContext: 	   return "OpenglDebugContext";
		case WindowAttribute::eOpenglProfile: 		   return "OpenglProfile";
		case WindowAttribute::eContextReleaseBehavior: return "ContextReleaseBehavior";
		case WindowAttribute::eContextNoError:		   return "ContextNoError";
		case WindowAttribute::eContextCreationApi:	   return "ContexCreationApi";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class ClientApi : EnumSize
	{
		eNone 	  = GLFW_NO_API,
		eOpengl   = GLFW_OPENGL_API,
		eOpenglEs = GLFW_OPENGL_ES_API
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const ClientApi value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case ClientApi::eNone: 	   return "None";
		case ClientApi::eOpengl:   return "Opengl";
		case ClientApi::eOpenglEs: return "OpenglEs";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class Robustness : EnumSize
	{
		eNone 				 = GLFW_NO_ROBUSTNESS,
		eNoResetNotification = GLFW_NO_RESET_NOTIFICATION,
		eLoseContextOnReset  = GLFW_LOSE_CONTEXT_ON_RESET
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Robustness value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Robustness::eNone: 			   return "None";
		case Robustness::eNoResetNotification: return "NoResetNotification";
		case Robustness::eLoseContextOnReset:  return "LoseContextOnReset";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class OpenglProfile : EnumSize
	{
		eAny 	= GLFW_OPENGL_ANY_PROFILE,
		eCore 	= GLFW_OPENGL_CORE_PROFILE,
		eCompat = GLFW_OPENGL_COMPAT_PROFILE
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const OpenglProfile value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case OpenglProfile::eAny: 	 return "Any";
		case OpenglProfile::eCore: 	 return "Core";
		case OpenglProfile::eCompat: return "Compat";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class InputMode : EnumSize
	{
		eCursor = GLFW_CURSOR,
		eStickyKeys = GLFW_STICKY_KEYS,
		eStickyMouseButtons = GLFW_STICKY_MOUSE_BUTTONS,
		eLockKeyMods = GLFW_LOCK_KEY_MODS,
		eRawMouseMotion = GLFW_RAW_MOUSE_MOTION
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const InputMode value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case InputMode::eCursor: return "Cursor";
		case InputMode::eStickyKeys: return "StickyKeys";
		case InputMode::eStickyMouseButtons: return "StickyMouseButtons";
		case InputMode::eLockKeyMods: return "LockKeyMods";
		case InputMode::eRawMouseMotion: return "RawMouseMotion";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class CursorMode : EnumSize
	{
		eNormal   = GLFW_CURSOR_NORMAL,
		eHidden   = GLFW_CURSOR_HIDDEN,
		eDisabled = GLFW_CURSOR_DISABLED
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const CursorMode value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case CursorMode::eNormal: 	return "Normal";
		case CursorMode::eHidden: 	return "Hidden";
		case CursorMode::eDisabled: return "Disabled";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class ReleaseBehavior : EnumSize
	{
		eAny   = GLFW_ANY_RELEASE_BEHAVIOR,
		eFlush = GLFW_RELEASE_BEHAVIOR_FLUSH,
		eNone  = GLFW_RELEASE_BEHAVIOR_NONE
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const ReleaseBehavior value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case ReleaseBehavior::eAny:   return "Any";
		case ReleaseBehavior::eFlush: return "Flush";
		case ReleaseBehavior::eNone:  return "None";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class ContextApi : EnumSize
	{
		eNative = GLFW_NATIVE_CONTEXT_API,
		eEgl 	= GLFW_EGL_CONTEXT_API,
		eOsmesa = GLFW_OSMESA_CONTEXT_API
	}; 

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const ContextApi value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case ContextApi::eNative: return "Native";
		case ContextApi::eEgl: 	  return "Egl";
		case ContextApi::eOsmesa: return "Osmesa";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @defgroup shapes Standard cursor shapes
 	 *  @brief Standard system cursor shapes.
 	 *
 	 *  See [standard cursor creation](@ref cursor_standard) for how these are used.
 	 *
 	 *  @ingroup input
 	 */
	enum class CursorShape : EnumSize
	{
		/*! @brief The regular arrow cursor shape.
 		 *
 		 *  The regular arrow cursor.
 		 */
		eArrow 	   = GLFW_ARROW_CURSOR,

		/*! @brief The text input I-beam cursor shape.
 		 *
 		 *  The text input I-beam cursor shape.
 		 */
		eIbeam 	   = GLFW_IBEAM_CURSOR,

		/*! @brief The crosshair shape.
 		 *
 		 *  The crosshair shape.
 		 */
		eCrosshair = GLFW_CROSSHAIR_CURSOR,

		/*! @brief The hand shape.
 		 *
 		 *  The hand shape.
 		 */
		eHand 	   = GLFW_HAND_CURSOR,

		/*! @brief The horizontal resize arrow shape.
 		 *
 		 *  The horizontal resize arrow shape.
 		 */
		eHresize   = GLFW_HRESIZE_CURSOR,

		/*! @brief The vertical resize arrow shape.
 		 *
 		 *  The vertical resize arrow shape.
 		 */
		eVresize   = GLFW_VRESIZE_CURSOR
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const CursorShape value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case CursorShape::eArrow: 	  return "Arrow";
		case CursorShape::eIbeam: 	  return "Ibeam";
		case CursorShape::eCrosshair: return "Crosshair";
		case CursorShape::eHand: 	  return "Hand";
		case CursorShape::eHresize:   return "Hresize";
		case CursorShape::eVresize:   return "Vresize";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	enum class Event : EnumSize
	{
		eConnected 	  = GLFW_CONNECTED,
		eDisconnected = GLFW_DISCONNECTED
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const Event value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Event::eConnected:	return "Connected";
		case Event::eDisconnected:	return "Disconnected";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	/*! @addtogroup init
	 */
	enum class InitHint : EnumSize
	{
		/*! @brief Joystick hat buttons init hint.
 		 *
 		 *  Joystick hat buttons [init hint](@ref GLFW_JOYSTICK_HAT_BUTTONS).
 		 */
		eJoystickHatButtons  = GLFW_JOYSTICK_HAT_BUTTONS,

		/*! @brief macOS specific init hint.
 		 *
 		 *  macOS specific [init hint](@ref GLFW_COCOA_CHDIR_RESOURCES_hint).
 		 */
		eCocoaChdirResources = GLFW_COCOA_CHDIR_RESOURCES,

		/*! @brief macOS specific init hint.
 		 *
 		 *  macOS specific [init hint](@ref GLFW_COCOA_MENUBAR_hint).
 		 */
		eCocoaMenubar 		 = GLFW_COCOA_MENUBAR
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_INLINE GLFW_HPP_STRING to_string(const InitHint value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case InitHint::eJoystickHatButtons:	 return "JoystickHatButtons";
		case InitHint::eCocoaChdirResources: return "CocoaChdirResources";
		case InitHint::eCocoaMenubar:		 return "CocoaMenubar";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// === Forward Declarations ===

	class Monitor;

	class Window;

	class Cursor;

	// === Function Types ===

	/*! @brief Client API function pointer type.
 	 *
 	 *  Generic function pointer used for returning client API function pointers
 	 *  without forcing a cast from a regular pointer.
 	 *
 	 *  @sa @ref context_glext
 	 *  @sa @ref glfwGetProcAddress
 	 *
 	 *  @since Added in version 3.0.
 	 *
 	 *  @ingroup context
 	 */
	using Glproc = void (*)(void);

	/*! @brief Vulkan API function pointer type.
 	 *
 	 *  Generic function pointer used for returning Vulkan API function pointers
 	 *  without forcing a cast from a regular pointer.
 	 *
 	 *  @sa @ref vulkan_proc
 	 *  @sa @ref glfwGetInstanceProcAddress
 	 *
 	 *  @since Added in version 3.2.
 	 *
 	 *  @ingroup vulkan
 	 */
	using Vkproc = void (*)(void);

	/*! @brief The function pointer type for error callbacks.
 	 *
 	 *  This is the function pointer type for error callbacks.  An error callback
 	 *  function has the following signature:
 	 *  @code
 	 *  void callback_name(GLFW_HPP_NAMESPACE::Error error_code, GLFW_HPP_NAMESPACE::GLFW_HPP_STRING const &description)
 	 *  @endcode
 	 *
 	 *  @param[in] error_code An [error code](@ref errors).  Future releases may add
 	 *  more error codes.
 	 *  @param[in] description A UTF-8 encoded string describing the error.
 	 *
 	 *  @pointer_lifetime The error description string is valid until the callback
 	 *  function returns.
 	 *
 	 *  @sa @ref error_handling
 	 *  @sa @ref glfwSetErrorCallback
 	 *
 	 *  @since Added in version 3.0.
 	 *
 	 *  @ingroup init
 	 */
	using Errorfun = void (*)(Error, GLFW_HPP_STRING const &);

	/*! @brief The function pointer type for window position callbacks.
 	 *
 	 *  This is the function pointer type for window position callbacks.  A window
 	 *  position callback function has the following signature:
 	 *  @code
 	 *  void callback_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::ScreenCoordinate xpos, GLFW_HPP_NAMESPACE::ScreenCoordinate ypos)
 	 *  @endcode
 	 *
 	 *  @param[in] window The window that was moved.
 	 *  @param[in] xpos The new x-coordinate, in screen coordinates, of the
 	 *  upper-left corner of the content area of the window.
 	 *  @param[in] ypos The new y-coordinate, in screen coordinates, of the
 	 *  upper-left corner of the content area of the window.
 	 *
 	 *  @sa @ref window_pos
 	 *  @sa @ref glfwSetWindowPosCallback
 	 *
 	 *  @since Added in version 3.0.
 	 *
 	 *  @ingroup window
 	 */
	using Windowposfun = void (*)(Window, ScreenCoordinate, ScreenCoordinate);

	/*! @brief The function pointer type for window size callbacks.
 	 *
 	 *  This is the function pointer type for window size callbacks.  A window size
 	 *  callback function has the following signature:
 	 *  @code
 	 *  void callback_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::ScreenCoordinate width, GLFW_HPP_NAMESPACE::ScreenCoordinate height)
 	 *  @endcode
 	 *
 	 *  @param[in] window The window that was resized.
 	 *  @param[in] width The new width, in screen coordinates, of the window.
 	 *  @param[in] height The new height, in screen coordinates, of the window.
 	 *
 	 *  @sa @ref window_size
 	 *  @sa @ref glfwSetWindowSizeCallback
 	 *
 	 *  @since Added in version 1.0.
 	 *  @glfw3 Added window handle parameter.
 	 *
 	 *  @ingroup window
 	 */
	using Windowsizefun = void (*)(Window, ScreenCoordinate, ScreenCoordinate);

	/*! @brief The function pointer type for window close callbacks.
	 *
	 *  This is the function pointer type for window close callbacks.  A window
	 *  close callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window)
	 *  @endcode
	 *
	 *  @param[in] window The window that the user attempted to close.
	 *
	 *  @sa @ref window_close
	 *  @sa @ref glfwSetWindowCloseCallback
	 *
	 *  @since Added in version 2.5.
	 *  @glfw3 Added window handle parameter.
	 *
	 *  @ingroup window
	 */
	using Windowclosefun = void (*)(Window);

	/*! @brief The function pointer type for window content refresh callbacks.
	 *
	 *  This is the function pointer type for window content refresh callbacks.
	 *  A window content refresh callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window);
	 *  @endcode
	 *
	 *  @param[in] window The window whose content needs to be refreshed.
	 *
	 *  @sa @ref window_refresh
	 *  @sa @ref glfwSetWindowRefreshCallback
	 *
	 *  @since Added in version 2.5.
	 *  @glfw3 Added window handle parameter.
	 *
	 *  @ingroup window
	 */
	using Windowrefreshfun = void (*)(Window);

	/*! @brief The function pointer type for window focus callbacks.
	 *
	 *  This is the function pointer type for window focus callbacks.  A window
	 *  focus callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool focused)
	 *  @endcode
	 *
	 *  @param[in] window The window that gained or lost input focus.
	 *  @param[in] focused `true` if the window was given input focus, or
	 *  `false` if it lost it.
	 *
	 *  @sa @ref window_focus
	 *  @sa @ref glfwSetWindowFocusCallback
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup window
	 */
	using Windowfocusfun = void (*)(Window, bool);

	/*! @brief The function pointer type for window iconify callbacks.
	 *
	 *  This is the function pointer type for window iconify callbacks.  A window
	 *  iconify callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool iconified)
	 *  @endcode
	 *
	 *  @param[in] window The window that was iconified or restored.
	 *  @param[in] iconified `true` if the window was iconified, or
	 *  `false` if it was restored.
	 *
	 *  @sa @ref window_iconify
	 *  @sa @ref glfwSetWindowIconifyCallback
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup window
	 */
	using Windowiconifyfun = void (*)(Window, bool);

	/*! @brief The function pointer type for window maximize callbacks.
	 *
	 *  This is the function pointer type for window maximize callbacks.  A window
	 *  maximize callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool maximized)
	 *  @endcode
	 *
	 *  @param[in] window The window that was maximized or restored.
	 *  @param[in] maximized `true` if the window was maximized, or
	 *  `false` if it was restored.
	 *
	 *  @sa @ref window_maximize
	 *  @sa glfwSetWindowMaximizeCallback
	 *
	 *  @since Added in version 3.3.
	 *
	 *  @ingroup window
	 */
	using Windowmaximizefun = void (*)(Window, bool);

	/*! @brief The function pointer type for framebuffer size callbacks.
	 *
	 *  This is the function pointer type for framebuffer size callbacks.
	 *  A framebuffer size callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Pixel width, GLFW_HPP_NAMESPACE::Pixel height)
	 *  @endcode
	 *
	 *  @param[in] window The window whose framebuffer was resized.
	 *  @param[in] width The new width, in pixels, of the framebuffer.
	 *  @param[in] height The new height, in pixels, of the framebuffer.
	 *
	 *  @sa @ref window_fbsize
	 *  @sa @ref glfwSetFramebufferSizeCallback
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup window
	 */
	using Framebuffersizefun = void (*)(Window, Pixel, Pixel);

	/*! @brief The function pointer type for window content scale callbacks.
	 *
	 *  This is the function pointer type for window content scale callbacks.
	 *  A window content scale callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::ContentScale xscale, GLFW_HPP_NAMESPACE::ContentScale yscale)
	 *  @endcode
	 *
	 *  @param[in] window The window whose content scale changed.
	 *  @param[in] xscale The new x-axis content scale of the window.
	 *  @param[in] yscale The new y-axis content scale of the window.
	 *
	 *  @sa @ref window_scale
	 *  @sa @ref glfwSetWindowContentScaleCallback
	 *
	 *  @since Added in version 3.3.
	 *
	 *  @ingroup window
	 */
	using Windowcontentscalefun = void (*)(Window, ContentScale, ContentScale);

	/*! @brief The function pointer type for mouse button callbacks.
	 *
	 *  This is the function pointer type for mouse button callback functions.
	 *  A mouse button callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::MouseButton button, GLFW_HPP_NAMESPACE::Action action, GLFW_HPP_NAMESPACE::ModFlags mods)
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] button The [mouse button](@ref buttons) that was pressed or
	 *  released.
	 *  @param[in] action One of `GLFW_HPP_NAMESPACE::Action::ePress` or `GLFW_HPP_NAMESPACE::Action::eRelease`.  Future releases
	 *  may add more actions.
	 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
	 *  held down.
	 *
	 *  @sa @ref input_mouse_button
	 *  @sa @ref glfwSetMouseButtonCallback
	 *
	 *  @since Added in version 1.0.
	 *  @glfw3 Added window handle and modifier mask parameters.
	 *
	 *  @ingroup input
	 */
	using Mousebuttonfun = void (*)(Window, MouseButton, Action, ModFlags);

	/*! @brief The function pointer type for cursor position callbacks.
	 *
	 *  This is the function pointer type for cursor position callbacks.  A cursor
	 *  position callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::CursorCoordinate xpos, GLFW_HPP_NAMESPACE::CursorCoordinate ypos);
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] xpos The new cursor x-coordinate, relative to the left edge of
	 *  the content area.
	 *  @param[in] ypos The new cursor y-coordinate, relative to the top edge of the
	 *  content area.
	 *
	 *  @sa @ref cursor_pos
	 *  @sa @ref glfwSetCursorPosCallback
	 *
	 *  @since Added in version 3.0.  Replaces `GLFWmouseposfun`.
	 *
	 *  @ingroup input
	 */
	using Cursorposfun = void (*)(Window, CursorCoordinate, CursorCoordinate);

	/*! @brief The function pointer type for cursor enter/leave callbacks.
	 *
	 *  This is the function pointer type for cursor enter/leave callbacks.
	 *  A cursor enter/leave callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool entered)
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] entered `true` if the cursor entered the window's content
	 *  area, or `false` if it left it.
	 *
	 *  @sa @ref cursor_enter
	 *  @sa @ref glfwSetCursorEnterCallback
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup input
	 */
	using Cursorenterfun = void (*)(Window, bool);

	/*! @brief The function pointer type for scroll callbacks.
	 *
	 *  This is the function pointer type for scroll callbacks.  A scroll callback
	 *  function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Offset xoffset, GLFW_HPP_NAMESPACE::Offset yoffset)
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] xoffset The scroll offset along the x-axis.
	 *  @param[in] yoffset The scroll offset along the y-axis.
	 *
	 *  @sa @ref scrolling
	 *  @sa @ref glfwSetScrollCallback
	 *
	 *  @since Added in version 3.0.  Replaces `GLFWmousewheelfun`.
	 *
	 *  @ingroup input
	 */
	using Scrollfun = void (*)(Window, Offset, Offset);

	/*! @brief The function pointer type for keyboard key callbacks.
	 *
	 *  This is the function pointer type for keyboard key callbacks.  A keyboard
	 *  key callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Key key, GLFW_HPP_NAMESPACE::Scancode scancode, GLFW_HPP_NAMESPACE::Action action, GLFW_HPP_NAMESPACE::ModFlags mods)
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
	 *  @param[in] scancode The system-specific scancode of the key.
	 *  @param[in] action `GLFW_HPP_NAMESPACE::Action::ePress`, `GLFW_HPP_NAMESPACE::Action::eRelease` or `GLFW_HPP_NAMESPACE::Action::eRepeat`.  Future
	 *  releases may add more actions.
	 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
	 *  held down.
	 *
	 *  @sa @ref input_key
	 *  @sa @ref glfwSetKeyCallback
	 *
	 *  @since Added in version 1.0.
	 *  @glfw3 Added window handle, scancode and modifier mask parameters.
	 *
	 *  @ingroup input
	 */
	using Keyfun = void (*)(Window, Key, Scancode, Action, ModFlags);

	/*! @brief The function pointer type for Unicode character callbacks.
	 *
	 *  This is the function pointer type for Unicode character callbacks.
	 *  A Unicode character callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Codepoint codepoint)
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] codepoint The Unicode code point of the character.
	 *
	 *  @sa @ref input_char
	 *  @sa @ref glfwSetCharCallback
	 *
	 *  @since Added in version 2.4.
	 *  @glfw3 Added window handle parameter.
	 *
	 *  @ingroup input
	 */
	using Charfun = void (*)(Window, Codepoint);

	/*! @brief The function pointer type for Unicode character with modifiers
	 *  callbacks.
	 *
	 *  This is the function pointer type for Unicode character with modifiers
	 *  callbacks.  It is called for each input character, regardless of what
	 *  modifier keys are held down.  A Unicode character with modifiers callback
	 *  function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Codepoint codepoint, GLFW_HPP_NAMESPACE::ModFlags mods)
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] codepoint The Unicode code point of the character.
	 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
	 *  held down.
	 *
	 *  @sa @ref input_char
	 *  @sa @ref glfwSetCharModsCallback
	 *
	 *  @deprecated Scheduled for removal in version 4.0.
	 *
	 *  @since Added in version 3.1.
	 *
	 *  @ingroup input
	 */
	using Charmodsfun = void (*)(Window, Codepoint, ModFlags);

	/*! @brief The function pointer type for path drop callbacks.
	 *
	 *  This is the function pointer type for path drop callbacks.  A path drop
	 *  callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Count path_count, GLFW_HPP_NAMESPACE::GLFW_HPP_STRING paths[])
	 *  @endcode
	 *
	 *  @param[in] window The window that received the event.
	 *  @param[in] path_count The number of dropped paths.
	 *  @param[in] paths The UTF-8 encoded file and/or directory path names.
	 *
	 *  @pointer_lifetime The path array and its strings are valid until the
	 *  callback function returns.
	 *
	 *  @sa @ref path_drop
	 *  @sa @ref glfwSetDropCallback
	 *
	 *  @since Added in version 3.1.
	 *
	 *  @ingroup input
	 */
	using Dropfun = void (*)(Window, Count, GLFW_HPP_STRING const []);

	/*! @brief The function pointer type for monitor configuration callbacks.
	 *
	 *  This is the function pointer type for monitor configuration callbacks.
	 *  A monitor callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Monitor monitor, GLFW_HPP_NAMESPACE::Event event)
	 *  @endcode
	 *
	 *  @param[in] monitor The monitor that was connected or disconnected.
	 *  @param[in] event One of `GLFW_HPP_NAMESPACE::Event::eConnected` or `GLFW_HPP_NAMESPACE::Event::eDisconnected`.  Future
	 *  releases may add more events.
	 *
	 *  @sa @ref monitor_event
	 *  @sa @ref glfwSetMonitorCallback
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup monitor
	 */
	using Monitorfun = void (*)(Monitor, Event);

	/*! @brief The function pointer type for joystick configuration callbacks.
	 *
	 *  This is the function pointer type for joystick configuration callbacks.
	 *  A joystick configuration callback function has the following signature:
	 *  @code
	 *  void function_name(GLFW_HPP_NAMESPACE::Joystick jid, GLFW_HPP_NAMESPACE::Event event)
	 *  @endcode
	 *
	 *  @param[in] jid The joystick that was connected or disconnected.
	 *  @param[in] event One of `GLFW_HPP_NAMESPACE::Event::eConnected` or `GLFW_HPP_NAMESPACE::Event::eDisconnected`.  Future
	 *  releases may add more events.
	 *
	 *  @sa @ref joystick_event
	 *  @sa @ref glfwSetJoystickCallback
	 *
	 *  @since Added in version 3.2.
	 *
	 *  @ingroup input
	 */
	using Joystickfun = void (*)(Joystick, Event);

	// === Structures ===

	/*! @brief Video mode type.
	 *
	 *  This describes a single video mode.
	 *
	 *  @sa @ref monitor_modes
	 *  @sa @ref glfwGetVideoMode
	 *  @sa @ref glfwGetVideoModes
	 *
	 *  @since Added in version 1.0.
	 *  @glfw3 Added refresh rate member.
	 *
	 *  @ingroup monitor
	 */
	struct Vidmode
	{
		/*! The width, in screen coordinates, of the video mode.
		 */
		ScreenCoordinate width;
		/*! The height, in screen coordinates, of the video mode.
		 */
		ScreenCoordinate height;
		/*! The bit depth of the red channel of the video mode.
		 */
		BitDepth redBits;
		/*! The bit depth of the green channel of the video mode.
		 */
		BitDepth greenBits;
		/*! The bit depth of the blue channel of the video mode.
		 */
		BitDepth blueBits;
		/*! The refresh rate, in Hz, of the video mode.
		 */
		Hz refreshRate;
	};

	static_assert(sizeof(Vidmode) == sizeof(GLFWvidmode), "Vidmode structure and original structure are different sizes!");

	/*! @brief Gamma ramp.
	 *
	 *  This describes the gamma ramp for a monitor.
	 *
	 *  @sa @ref monitor_gamma
	 *  @sa @ref glfwGetGammaRamp
	 *  @sa @ref glfwSetGammaRamp
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup monitor
	 */
	struct Gammaramp
	{
		/*! An array of value describing the response of the red channel.
		 */
		Response* red;
		/*! An array of value describing the response of the green channel.
		 */
		Response* green;
		/*! An array of value describing the response of the blue channel.
		 */
		Response* blue;
		/*! The number of elements in each array.
		 */
		ArraySize size;
	};

	static_assert(sizeof(Gammaramp) == sizeof(GLFWgammaramp), "Gammaramp structure and original structure are different sizes!");

	/*! @brief Image data.
	 *
	 *  This describes a single 2D image.  See the documentation for each related
	 *  function what the expected pixel format is.
	 *
	 *  @sa @ref cursor_custom
	 *  @sa @ref window_icon
	 *
	 *  @since Added in version 2.1.
	 *  @glfw3 Removed format and bytes-per-pixel members.
	 *
	 *  @ingroup window
	 */
	struct Image
	{
		/*! The width, in pixels, of this image.
		 */
		Pixel width;
		/*! The height, in pixels, of this image.
		 */
		Pixel height;
		/*! The pixel data of this image, arranged left-to-right, top-to-bottom.
		 */
		PixelData pixels;
	};

	static_assert(sizeof(Image) == sizeof(GLFWimage), "Image structure and original structure are different sizes!");

	/*! @brief Gamepad input state
	 *
	 *  This describes the input state of a gamepad.
	 *
	 *  @sa @ref gamepad
	 *  @sa @ref glfwGetGamepadState
	 *
	 *  @since Added in version 3.3.
	 *
	 *  @ingroup input
	 */
	struct Gamepadstate
	{
		/*! The states of each [gamepad button](@ref gamepad_buttons), `GLFW_HPP_NAMESPACE::SmallAction::ePress`
		 *  or `GLFW_HPP_NAMESPACE::SmallAction::eRelease`.
		 */
		SmallAction buttons[15];
		/*! The states of each [gamepad axis](@ref gamepad_axes), in the range -1.0
		 *  to 1.0 inclusive.
		 */
		GamepadAxisState axes[6];
	};

	static_assert(sizeof(Gamepadstate) == sizeof(GLFWgamepadstate), "Gamepadstate structure and original structure are different sizes!");

	// === API Functions ===

	/*! @brief Initializes the GLFW library.
	 *
	 *  This function initializes the GLFW library.  Before most GLFW functions can
	 *  be used, GLFW must be initialized, and before an application terminates GLFW
	 *  should be terminated in order to free any resources allocated during or
	 *  after initialization.
	 *
	 *  If this function fails, it calls @ref glfwTerminate before returning.  If it
	 *  succeeds, you should call @ref glfwTerminate before the application exits.
	 *
	 *  Additional calls to this function after successful initialization but before
	 *  termination will return `true` immediately.
	 *
	 *  @return `true` if successful, or `false` if an
	 *  [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
	 *
	 *  @remark @macos This function will change the current directory of the
	 *  application to the `Contents/Resources` subdirectory of the application's
	 *  bundle, if present.  This can be disabled with the @ref
	 *  GLFW_HPP_NAMESPACE::InitHint::eCocoaChdirResources init hint.
	 *
	 *  @remark @x11 This function will set the `LC_CTYPE` category of the
	 *  application locale according to the current environment if that category is
	 *  still "C".  This is because the "C" locale breaks Unicode text input.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 *
	 *  @sa @ref intro_init
	 *  @sa @ref glfwTerminate
	 *
	 *  @since Added in version 1.0.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_INLINE bool Init() GLFW_HPP_NOEXCEPT
	{
		return glfwInit();
	}

	/*! @brief Terminates the GLFW library.
	 *
	 *  This function destroys all remaining windows and cursors, restores any
	 *  modified gamma ramps and frees any other allocated resources.  Once this
	 *  function is called, you must again call @ref glfwInit successfully before
	 *  you will be able to use most GLFW functions.
	 *
	 *  If GLFW has been successfully initialized, this function should be called
	 *  before the application exits.  If initialization fails, there is no need to
	 *  call this function, as it is called by @ref glfwInit before it returns
	 *  failure.
	 *
	 *  This function has no effect if GLFW is not initialized.
	 *
	 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
	 *
	 *  @remark This function may be called before @ref glfwInit.
	 *
	 *  @warning The contexts of any remaining windows must not be current on any
	 *  other thread when this function is called.
	 *
	 *  @reentrancy This function must not be called from a callback.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 *
	 *  @sa @ref intro_init
	 *  @sa @ref glfwInit
	 *
	 *  @since Added in version 1.0.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_INLINE void Terminate() GLFW_HPP_NOEXCEPT
	{
		glfwTerminate();
	};

	/*! @brief Sets the specified init hint to the desired value.
	 *
	 *  This function sets hints for the next initialization of GLFW.
	 *
	 *  The values you set hints to are never reset by GLFW, but they only take
	 *  effect during initialization.  Once GLFW has been initialized, any values
	 *  you set will be ignored until the library is terminated and initialized
	 *  again.
	 *
	 *  Some hints are platform specific.  These may be set on any platform but they
	 *  will only affect their specific platform.  Other platforms will ignore them.
	 *  Setting these hints requires no platform specific headers or functions.
	 *
	 *  @param[in] hint The [init hint](@ref init_hints) to set.
	 *  @param[in] value The new value of the init hint.
	 *
	 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eInvalidEnum and @ref
	 *  GLFW_HPP_NAMESPACE::Error::eInvalidValue.
	 *
	 *  @remarks This function may be called before @ref glfwInit.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 *
	 *  @sa init_hints
	 *  @sa glfwInit
	 *
	 *  @since Added in version 3.3.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_INLINE void InitHint(const InitHint hint, const bool value) GLFW_HPP_NOEXCEPT
	{
		glfwInitHint(static_cast<int>(hint), value);
	};

	template <enum InitHint hint, bool value>
	GLFW_HPP_INLINE void InitHint() GLFW_HPP_NOEXCEPT
	{
		glfwInitHint(static_cast<int>(hint), value);
	};

	/*! @brief Retrieves the version of the GLFW library.
	 *
	 *  This function retrieves the major, minor and revision numbers of the GLFW
	 *  library.  It is intended for when you are using GLFW as a shared library and
	 *  want to ensure that you are using the minimum required version.
	 *
	 *  Any or all of the version arguments may be `nullptr`.
	 *
	 *  @param[out] major Where to store the major version number, or `nullptr`.
	 *  @param[out] minor Where to store the minor version number, or `nullptr`.
	 *  @param[out] rev Where to store the revision number, or `nullptr`.
	 *
	 *  @errors None.
	 *
	 *  @remark This function may be called before @ref glfwInit.
	 *
	 *  @thread_safety This function may be called from any thread.
	 *
	 *  @sa @ref intro_version
	 *  @sa @ref glfwGetVersionString
	 *
	 *  @since Added in version 1.0.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_INLINE void GetVersion(Version * const major, Version * const minor = nullptr, Version * const rev = nullptr) GLFW_HPP_NOEXCEPT
	{
		glfwGetVersion(major, minor, rev);
	}

	GLFW_HPP_INLINE void GetVersion(Version &major, Version &minor, Version &rev) GLFW_HPP_NOEXCEPT
	{
		glfwGetVersion(&major, &minor, &rev);
	}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<Version, 3> GetVersion() GLFW_HPP_NOEXCEPT
	{
		std::array<Version, 3> version;
		glfwGetVersion(&version[0], &version[1], &version[2]);
		return version;
	}

	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<Version> GetVersionVector() GLFW_HPP_NOEXCEPT
	{
		std::vector<Version> version(3);
		glfwGetVersion(&version[0], &version[1], &version[2]);
		return version;
	}
#endif

	/*! @brief Returns a string describing the compile-time configuration.
	 *
	 *  This function returns the compile-time generated
	 *  [version string](@ref intro_version_string) of the GLFW library binary.  It
	 *  describes the version, platform, compiler and any platform-specific
	 *  compile-time options.  It should not be confused with the OpenGL or OpenGL
	 *  ES version string, queried with `glGetString`.
	 *
	 *  __Do not use the version string__ to parse the GLFW library version.  The
	 *  @ref glfwGetVersion function provides the version of the running library
	 *  binary in numerical format.
	 *
	 *  @return The ASCII encoded GLFW version string.
	 *
	 *  @errors None.
	 *
	 *  @remark This function may be called before @ref glfwInit.
	 *
	 *  @pointer_lifetime The returned string is static and compile-time generated.
	 *
	 *  @thread_safety This function may be called from any thread.
	 *
	 *  @sa @ref intro_version
	 *  @sa @ref glfwGetVersion
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE GLFW_HPP_STRING GetVersionString() GLFW_HPP_NOEXCEPT
	{
		return glfwGetVersionString();
	}

	/*! @brief Returns and clears the last error for the calling thread.
	 *
	 *  This function returns and clears the [error code](@ref errors) of the last
	 *  error that occurred on the calling thread, and optionally a UTF-8 encoded
	 *  human-readable description of it.  If no error has occurred since the last
	 *  call, it returns @ref GLFW_HPP_NAMESPACE::Error::eNone (zero) and the description pointer is
	 *  set to `nullptr`.
	 *
	 *  @param[in] description Where to store the error description pointer, or `nullptr`.
	 *  @return The last error code for the calling thread, or @ref GLFW_HPP_NAMESPACE::Error::eNone
	 *  (zero).
	 *
	 *  @errors None.
	 *
	 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
	 *  should not free it yourself.  It is guaranteed to be valid only until the
	 *  next error occurs or the library is terminated.
	 *
	 *  @remark This function may be called before @ref glfwInit.
	 *
	 *  @thread_safety This function may be called from any thread.
	 *
	 *  @sa @ref error_handling
	 *  @sa @ref glfwSetErrorCallback
	 *
	 *  @since Added in version 3.3.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE Error GetError(GLFW_HPP_STRING * const string = nullptr) GLFW_HPP_NOEXCEPT
	{
#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		if (string) {
			const char *pure_string;
			const Error error = static_cast<Error>(glfwGetError(&pure_string));

	#if GLFW_HPP_CPP_VERSION >= 17
			GLFW_HPP_STRING other_string{pure_string}; 
			std::swap(*string, other_string);
	#else
			*string = pure_string;
	#endif
			return error;
		}

		return static_cast<Error>(glfwGetError(nullptr));
#else
		return static_cast<Error>(glfwGetError(string));
#endif
	}

	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE Error GetError(GLFW_HPP_STRING &string) GLFW_HPP_NOEXCEPT
	{
#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		const char *pure_string;
		const Error error = static_cast<Error>(glfwGetError(&pure_string));

	#if GLFW_HPP_CPP_VERSION >= 17
		GLFW_HPP_STRING other_string{pure_string};
		std::swap(string, other_string);
	#else
		string = pure_string;
	#endif

		return error;
#else
		return static_cast<Error>(glfwGetError(&string));
#endif
	}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::pair<Error, GLFW_HPP_STRING const> GetError() GLFW_HPP_NOEXCEPT
	{
		const char *string;
		const Error error = static_cast<Error>(glfwGetError(&string));
		return {error, string};
	}
#endif

	/*! @brief Sets the error callback.
	 *
	 *  This function sets the error callback, which is called with an error code
	 *  and a human-readable description each time a GLFW error occurs.
	 *
	 *  The error code is set before the callback is called.  Calling @ref
	 *  glfwGetError from the error callback will return the same value as the error
	 *  code argument.
	 *
	 *  The error callback is called on the thread where the error occurred.  If you
	 *  are using GLFW from multiple threads, your error callback needs to be
	 *  written accordingly.
	 *
	 *  Because the description string may have been generated specifically for that
	 *  error, it is not guaranteed to be valid after the callback has returned.  If
	 *  you wish to use it after the callback returns, you need to make a copy.
	 *
	 *  Once set, the error callback remains set even after the library has been
	 *  terminated.
	 *
	 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *  @return The previously set callback, or `nullptr` if no callback was set.
	 *
	 *  @callback_signature
	 *  @code
	 *  void callback_name(GLFW_HPP_NAMESPACE::Error error_code, GLFW_HPP_NAMESPACE::GLFW_HPP_STRING description)
	 *  @endcode
	 *  For more information about the callback parameters, see the
	 *  [callback pointer type](@ref GLFW_HPP_NAMESPACE::Errorfun).
	 *
	 *  @errors None.
	 *
	 *  @remark This function may be called before @ref glfwInit.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 *
	 *  @sa @ref error_handling
	 *  @sa @ref glfwGetError
	 *
	 *  @since Added in version 3.0.
	 *
	 *  @ingroup init
	 */
	GLFW_HPP_INLINE Errorfun SetErrorCallback(Errorfun callback = nullptr) GLFW_HPP_NOEXCEPT
	{
		return reinterpret_cast<Errorfun>(glfwSetErrorCallback(reinterpret_cast<GLFWerrorfun>(callback)));
	}

	template <Errorfun callback = nullptr>
	GLFW_HPP_INLINE Errorfun SetErrorCallback() GLFW_HPP_NOEXCEPT
	{
		return reinterpret_cast<Errorfun>(glfwSetErrorCallback(reinterpret_cast<GLFWerrorfun>(callback)));
	}

	// === Classes ===

	/*! @brief Opaque monitor object.
 	 *
 	 *  Opaque monitor object.
 	 *
 	 *  @see @ref monitor_object
 	 *
 	 *  @since Added in version 3.0.
 	 *
 	 *  @ingroup monitor
 	 */
	class Monitor
	{
	public:
		// Constructors and destructor
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Monitor(			   	 ) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Monitor(const Monitor &) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Monitor(Monitor &&	 ) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_CONSTEXPR_DESTRUCTOR 			 ~Monitor(			   	 ) GLFW_HPP_NOEXCEPT = default;

		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT operator const GLFWmonitor *() const GLFW_HPP_NOEXCEPT
		{
			return m_monitor;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_NON_CONST_METHOD GLFW_HPP_EXPLICIT operator GLFWmonitor *() GLFW_HPP_NOEXCEPT
		{
			return m_monitor;
		}

	private:
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT Monitor(GLFWmonitor * const pointer) GLFW_HPP_NOEXCEPT
			: m_monitor(pointer) {}
	
	public:

		/*! @brief Returns the currently connected monitors.
		 *
		 *  This function returns an array of handles for all currently connected
		 *  monitors.  The primary monitor is always first in the returned array.  If no
		 *  monitors were found, this function returns `nullptr`.
		 *
		 *  @param[out] count Where to store the number of monitors in the returned
		 *  array.  This is set to zero if an error occurred.
		 *  @return An array of monitor handles, or `nullptr` if no monitors were found or
		 *  if an [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
		 *  should not free it yourself.  It is guaranteed to be valid only until the
		 *  monitor configuration changes or the library is terminated.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_monitors
		 *  @sa @ref monitor_event
		 *  @sa @ref glfwGetPrimaryMonitor
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Monitor *GetAll(Count * const count) GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Monitor *>(glfwGetMonitors(count));
		}

		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Monitor *GetAll(Count &count) GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Monitor *>(glfwGetMonitors(&count));
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE std::vector<Monitor> GetAll() GLFW_HPP_NOEXCEPT
		{
			Count count;
			Monitor * const monitors = reinterpret_cast<Monitor *>(glfwGetMonitors(&count));

			if (monitors) GLFW_HPP_LIKELY
				return {monitors, (monitors + count)};
			return {};
		}
#endif

		/*! @brief Returns the primary monitor.
		 *
		 *  This function returns the primary monitor.  This is usually the monitor
		 *  where elements like the task bar or global menu bar are located.
		 *
		 *  @return The primary monitor, or `nullptr` if no monitors were found or if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @remark The primary monitor is always first in the array returned by @ref
		 *  glfwGetMonitors.
		 *
		 *  @sa @ref monitor_monitors
		 *  @sa @ref glfwGetMonitors
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Monitor GetPrimary() GLFW_HPP_NOEXCEPT
		{
			return Monitor{glfwGetPrimaryMonitor()};
		}

		/*! @brief Returns the position of the monitor's viewport on the virtual screen.
		 *
		 *  This function returns the position, in screen coordinates, of the upper-left
		 *  corner of the specified monitor.
		 *
		 *  Any or all of the position arguments may be `nullptr`.  If an error occurs, all
		 *  non-`nullptr` position arguments will be set to zero.
		 *
		 *  @param[out] xpos Where to store the monitor x-coordinate, or `nullptr`.
		 *  @param[out] ypos Where to store the monitor y-coordinate, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_properties
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE void GetPos(ScreenCoordinate * const xpos, ScreenCoordinate * const ypos = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorPos(m_monitor, xpos, ypos);
		}

		GLFW_HPP_INLINE void GetPos(ScreenCoordinate &xpos, ScreenCoordinate &ypos) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorPos(m_monitor, &xpos, &ypos);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ScreenCoordinate, 2> GetPos() const GLFW_HPP_NOEXCEPT
		{
			std::array<ScreenCoordinate, 2> position;
			glfwGetMonitorPos(m_monitor, &position[0], &position[1]);
			return position;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ScreenCoordinate> GetPosVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ScreenCoordinate> position(2);
			glfwGetMonitorPos(m_monitor, &position[0], &position[1]);
			return position;
		}
#endif

		/*! @brief Retrieves the work area of the monitor.
		 *
		 *  This function returns the position, in screen coordinates, of the upper-left
		 *  corner of the work area of the specified monitor along with the work area
		 *  size in screen coordinates. The work area is defined as the area of the
		 *  monitor not occluded by the operating system task bar where present. If no
		 *  task bar exists then the work area is the monitor resolution in screen
		 *  coordinates.
		 *
		 *  Any or all of the position and size arguments may be `nullptr`.  If an error
		 *  occurs, all non-`nullptr` position and size arguments will be set to zero.
		 *
		 *  @param[out] xpos Where to store the monitor x-coordinate, or `nullptr`.
		 *  @param[out] ypos Where to store the monitor y-coordinate, or `nullptr`.
		 *  @param[out] width Where to store the monitor width, or `nullptr`.
		 *  @param[out] height Where to store the monitor height, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_workarea
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE void GetWorkarea(ScreenCoordinate * const xpos, ScreenCoordinate * const ypos = nullptr, ScreenCoordinate * const width = nullptr, ScreenCoordinate * const height = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorWorkarea(m_monitor, xpos, ypos, width, height);
		}

		GLFW_HPP_INLINE void GetWorkarea(ScreenCoordinate &xpos, ScreenCoordinate &ypos, ScreenCoordinate &width, ScreenCoordinate &height) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorWorkarea(m_monitor, &xpos, &ypos, &width, &height);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ScreenCoordinate, 4> GetWorkarea() const GLFW_HPP_NOEXCEPT
		{
			std::array<ScreenCoordinate, 4> workarea;
			glfwGetMonitorWorkarea(m_monitor, &workarea[0], &workarea[1], &workarea[2], &workarea[3]);
			return workarea;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ScreenCoordinate> GetWorkareaVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ScreenCoordinate> workarea(4);
			glfwGetMonitorWorkarea(m_monitor, &workarea[0], &workarea[1], &workarea[2], &workarea[3]);
			return workarea;
		}
#endif

		/*! @brief Returns the physical size of the monitor.
		 *
		 *  This function returns the size, in millimetres, of the display area of the
		 *  specified monitor.
		 *
		 *  Some systems do not provide accurate monitor size information, either
		 *  because the monitor
		 *  [EDID](https://en.wikipedia.org/wiki/Extended_display_identification_data)
		 *  data is incorrect or because the driver does not report it accurately.
		 *
		 *  Any or all of the size arguments may be `nullptr`.  If an error occurs, all
		 *  non-`nullptr` size arguments will be set to zero.
		 *
		 *  @param[out] widthMM Where to store the width, in millimetres, of the
		 *  monitor's display area, or `nullptr`.
		 *  @param[out] heightMM Where to store the height, in millimetres, of the
		 *  monitor's display area, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @remark @win32 calculates the returned physical size from the
		 *  current resolution and system DPI instead of querying the monitor EDID data.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_properties
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE void GetPhysicalSize(Millimetre * const widthMM, Millimetre * const heightMM = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorPhysicalSize(m_monitor, widthMM, heightMM);
		}

		GLFW_HPP_INLINE void GetPhysicalSize(Millimetre &widthMM, Millimetre &heightMM) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorPhysicalSize(m_monitor, &widthMM, &heightMM);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<Millimetre, 2> GetPhysicalSize() const GLFW_HPP_NOEXCEPT
		{
			std::array<Millimetre, 2> physicalsize;
			glfwGetMonitorPhysicalSize(m_monitor, &physicalsize[0], &physicalsize[1]);
			return physicalsize;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<Millimetre> GetPhysicalSizeVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<Millimetre> physicalsize(2);
			glfwGetMonitorPhysicalSize(m_monitor, &physicalsize[0], &physicalsize[1]);
			return physicalsize;
		}
#endif

		/*! @brief Retrieves the content scale for the specified monitor.
		 *
		 *  This function retrieves the content scale for the specified monitor.  The
		 *  content scale is the ratio between the current DPI and the platform's
		 *  default DPI.  This is especially important for text and any UI elements.  If
		 *  the pixel dimensions of your UI scaled by this look appropriate on your
		 *  machine then it should appear at a reasonable size on other machines
		 *  regardless of their DPI and scaling settings.  This relies on the system DPI
		 *  and scaling settings being somewhat correct.
		 *
		 *  The content scale may depend on both the monitor resolution and pixel
		 *  density and on user settings.  It may be very different from the raw DPI
		 *  calculated from the physical size and current resolution.
		 *
		 *  @param[out] xscale Where to store the x-axis content scale, or `nullptr`.
		 *  @param[out] yscale Where to store the y-axis content scale, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_scale
		 *  @sa @ref glfwGetWindowContentScale
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE void GetContentScale(ContentScale * const xscale, ContentScale * const yscale = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorContentScale(m_monitor, xscale, yscale);
		}

		GLFW_HPP_INLINE void GetContentScale(ContentScale &xscale, ContentScale &yscale) const GLFW_HPP_NOEXCEPT
		{
			glfwGetMonitorContentScale(m_monitor, &xscale, &yscale);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ContentScale, 2> GetContentScale() const GLFW_HPP_NOEXCEPT
		{
			std::array<ContentScale, 2> contentscale;
			glfwGetMonitorContentScale(m_monitor, &contentscale[0], &contentscale[1]);
			return contentscale;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ContentScale> GetContentScaleVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ContentScale> contentscale(2);
			glfwGetMonitorContentScale(m_monitor, &contentscale[0], &contentscale[1]);
			return contentscale;
		}
#endif

		/*! @brief Returns the name of the specified monitor.
		 *
		 *  This function returns a human-readable name, encoded as UTF-8, of the
		 *  specified monitor.  The name typically reflects the make and model of the
		 *  monitor and is not guaranteed to be unique among the connected monitors.
		 *
		 *  @return The UTF-8 encoded name of the monitor, or `nullptr` if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
		 *  should not free it yourself.  It is valid until the specified monitor is
		 *  disconnected or the library is terminated.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_properties
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE GLFW_HPP_STRING GetName() const GLFW_HPP_NOEXCEPT
		{
			return glfwGetMonitorName(m_monitor);
		}

		/*! @brief Sets the user pointer of the specified monitor.
		 *
		 *  This function sets the user-defined pointer of the specified monitor.  The
		 *  current value is retained until the monitor is disconnected.  The initial
		 *  value is `nullptr`.
		 *
		 *  This function may be called from the monitor callback, even for a monitor
		 *  that is being disconnected.
		 *
		 *  @param[in] pointer The new value.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function may be called from any thread.  Access is not
		 *  synchronized.
		 *
		 *  @sa @ref monitor_userptr
		 *  @sa @ref glfwGetMonitorUserPointer
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup monitor
		 */
		template <class T>
		GLFW_HPP_INLINE void SetUserPointer(T * const pointer = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwSetMonitorUserPointer(m_monitor, static_cast<void *>(pointer));
		}

		template <class T>
		GLFW_HPP_INLINE void SetUserPointer(T &pointer) const GLFW_HPP_NOEXCEPT
		{
			glfwSetMonitorUserPointer(m_monitor, static_cast<void *>(&pointer));
		}

		/*! @brief Returns the user pointer of the specified monitor.
		 *
		 *  This function returns the current value of the user-defined pointer of the
		 *  specified monitor.  The initial value is `nullptr`.
		 *
		 *  This function may be called from the monitor callback, even for a monitor
		 *  that is being disconnected.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function may be called from any thread.  Access is not
		 *  synchronized.
		 *
		 *  @sa @ref monitor_userptr
		 *  @sa @ref glfwSetMonitorUserPointer
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup monitor
		 */
		template <class T>
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE T *GetUserPointer() const GLFW_HPP_NOEXCEPT
		{
			return static_cast<T *>(glfwGetMonitorUserPointer(m_monitor));
		}

		template <class T>
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE T &GetUserPointerRef() const GLFW_HPP_NOEXCEPT
		{
			T * const pointer = static_cast<T *>(glfwGetMonitorUserPointer(m_monitor));
			GLFW_HPP_ASSERT(pointer && "Returning null reference!");
			return *pointer;
		}

		/*! @brief Sets the monitor configuration callback.
		 *
		 *  This function sets the monitor configuration callback, or removes the
		 *  currently set callback.  This is called when a monitor is connected to or
		 *  disconnected from the system.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Monitor monitor, GLFW_HPP_NAMESPACE::Event event)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWmonitorfun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_event
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE Monitorfun SetCallback(Monitorfun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Monitorfun>(glfwSetMonitorCallback(reinterpret_cast<GLFWmonitorfun>(callback)));
		}

		template <Monitorfun callback = nullptr>
		GLFW_HPP_INLINE Monitorfun SetCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Monitorfun>(glfwSetMonitorCallback(reinterpret_cast<GLFWmonitorfun>(callback)));
		}

		/*! @brief Returns the available video modes for the specified monitor.
		 *
		 *  This function returns an array of all video modes supported by the specified
		 *  monitor.  The returned array is sorted in ascending order, first by color
		 *  bit depth (the sum of all channel depths) and then by resolution area (the
		 *  product of width and height).
		 *
		 *  @param[out] count Where to store the number of video modes in the returned
		 *  array.  This is set to zero if an error occurred.
		 *  @return An array of video modes, or `nullptr` if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
		 *  should not free it yourself.  It is valid until the specified monitor is
		 *  disconnected, this function is called again for that monitor or the library
		 *  is terminated.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_modes
		 *  @sa @ref glfwGetVideoMode
		 *
		 *  @since Added in version 1.0.
		 *  @glfw3 Changed to return an array of modes for a specific monitor.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE const Vidmode *GetVideoModes(Count * const count) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<const Vidmode *>(glfwGetVideoModes(m_monitor, count));
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE const Vidmode *GetVideoModes(Count &count) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<const Vidmode *>(glfwGetVideoModes(m_monitor, &count));
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<const Vidmode> GetVideoModes() const GLFW_HPP_NOEXCEPT
		{
			Count count;
			const Vidmode * const videomodes = reinterpret_cast<const Vidmode *>(glfwGetVideoModes(m_monitor, &count));

			if (videomodes) GLFW_HPP_LIKELY
				return {videomodes, (videomodes + count)};
			return {};
		}
#endif

		/*! @brief Returns the current mode of the specified monitor.
		 *
		 *  This function returns the current video mode of the specified monitor.  If
		 *  you have created a full screen window for that monitor, the return value
		 *  will depend on whether that window is iconified.
		 *
		 *  @return The current mode of the monitor, or `nullptr` if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
		 *  should not free it yourself.  It is valid until the specified monitor is
		 *  disconnected or the library is terminated.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_modes
		 *  @sa @ref glfwGetVideoModes
		 *
		 *  @since Added in version 3.0.  Replaces `glfwGetDesktopMode`.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE const Vidmode *GetVideoMode() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<const Vidmode *>(glfwGetVideoMode(m_monitor));
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE const Vidmode &GetVideoModeRef() const GLFW_HPP_NOEXCEPT
		{
			const Vidmode * const videomode = reinterpret_cast<const Vidmode *>(glfwGetVideoMode(m_monitor));
			GLFW_HPP_ASSERT(videomode && "Returning null reference!");
			return *videomode;
		}

		/*! @brief Generates a gamma ramp and sets it for the specified monitor.
		 *
		 *  This function generates an appropriately sized gamma ramp from the specified
		 *  exponent and then calls @ref glfwSetGammaRamp with it.  The value must be
		 *  a finite number greater than zero.
		 *
		 *  The software controlled gamma ramp is applied _in addition_ to the hardware
		 *  gamma correction, which today is usually an approximation of sRGB gamma.
		 *  This means that setting a perfectly linear ramp, or gamma 1.0, will produce
		 *  the default (usually sRGB-like) behavior.
		 *
		 *  For gamma correct rendering with OpenGL or OpenGL ES, see the @ref
		 *  GLFW_HPP_NAMESPACE::WindowHint::eSrgbCapable hint.
		 *
		 *  @param[in] gamma The desired exponent.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidValue and @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland Gamma handling is a privileged protocol, this function
		 *  will thus never be implemented and emits @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_gamma
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE void SetGamma(const Exponent gamma) const GLFW_HPP_NOEXCEPT
		{
			glfwSetGamma(m_monitor, gamma);
		}

		/*! @brief Returns the current gamma ramp for the specified monitor.
		 *
		 *  This function returns the current gamma ramp of the specified monitor.
		 *
		 *  @return The current gamma ramp, or `nullptr` if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland Gamma handling is a privileged protocol, this function
		 *  will thus never be implemented and emits @ref GLFW_HPP_NAMESPACE::Error::ePlatform while
		 *  returning `nullptr`.
		 *
		 *  @pointer_lifetime The returned structure and its arrays are allocated and
		 *  freed by GLFW.  You should not free them yourself.  They are valid until the
		 *  specified monitor is disconnected, this function is called again for that
		 *  monitor or the library is terminated.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_gamma
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE const Gammaramp *GetGammaRamp() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<const Gammaramp *>(glfwGetGammaRamp(m_monitor));
		}

		GLFW_HPP_INLINE const Gammaramp &GetGammaRampRef() const GLFW_HPP_NOEXCEPT
		{
			const Gammaramp * const gammaramp = reinterpret_cast<const Gammaramp *>(glfwGetGammaRamp(m_monitor));
			GLFW_HPP_ASSERT(gammaramp && "Returning null reference!");
			return *gammaramp;
		}

		/*! @brief Sets the current gamma ramp for the specified monitor.
		 *
		 *  This function sets the current gamma ramp for the specified monitor.  The
		 *  original gamma ramp for that monitor is saved by GLFW the first time this
		 *  function is called and is restored by @ref glfwTerminate.
		 *
		 *  The software controlled gamma ramp is applied _in addition_ to the hardware
		 *  gamma correction, which today is usually an approximation of sRGB gamma.
		 *  This means that setting a perfectly linear ramp, or gamma 1.0, will produce
		 *  the default (usually sRGB-like) behavior.
		 *
		 *  For gamma correct rendering with OpenGL or OpenGL ES, see the @ref
		 *  GLFW_HPP_NAMESPACE::WindowHint::eSrgbCapable hint.
		 *
		 *  @param[in] ramp The gamma ramp to use.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark The size of the specified gamma ramp should match the size of the
		 *  current ramp for that monitor.
		 *
		 *  @remark @win32 The gamma ramp size must be 256.
		 *
		 *  @remark @wayland Gamma handling is a privileged protocol, this function
		 *  will thus never be implemented and emits @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @pointer_lifetime The specified gamma ramp is copied before this function
		 *  returns.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref monitor_gamma
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup monitor
		 */
		GLFW_HPP_INLINE void SetGammaRamp(const Gammaramp * const ramp) const GLFW_HPP_NOEXCEPT
		{
			glfwSetGammaRamp(m_monitor, reinterpret_cast<const GLFWgammaramp *>(ramp));
		}

		GLFW_HPP_INLINE void SetGammaRamp(const Gammaramp &ramp) const GLFW_HPP_NOEXCEPT
		{
			glfwSetGammaRamp(m_monitor, reinterpret_cast<const GLFWgammaramp *>(&ramp));
		}
		
	private:
		GLFWmonitor *m_monitor = nullptr;

		friend class Window;
#ifdef GLFW_HPP_ENABLE_HASHING
		friend struct std::hash<Monitor>;
#endif
	};

	static_assert(sizeof(Monitor) == sizeof(GLFWmonitor *), "Monitor class and original pointer are different sizes!");


	/*! @brief Opaque window object.
 	 *
 	 *  Opaque window object.
 	 *
 	 *  @see @ref window_object
 	 *
 	 *  @since Added in version 3.0.
 	 *
 	 *  @ingroup window
 	 */
	class Window
	{
	public:
		// Constructors and destructor
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Window(			   ) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Window(const Window &) GLFW_HPP_NOEXCEPT = default;
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR Window(Window &&	   ) GLFW_HPP_NOEXCEPT = default;

		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT operator const GLFWwindow *() const GLFW_HPP_NOEXCEPT
		{
			return m_window;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_NON_CONST_METHOD GLFW_HPP_EXPLICIT operator GLFWwindow *() GLFW_HPP_NOEXCEPT
		{
			return m_window;
		}

	private:
		GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR GLFW_HPP_EXPLICIT Window(GLFWwindow * const pointer) GLFW_HPP_NOEXCEPT
			: m_window(pointer) {}
	
	public:
		/*! @brief Resets all window hints to their default values.
		 *
		 *  This function resets all window hints to their
		 *  [default values](@ref window_hints_values).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_hints
		 *  @sa @ref glfwWindowHint
		 *  @sa @ref glfwWindowHintString
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		static GLFW_HPP_INLINE void DefaultHints() GLFW_HPP_NOEXCEPT
		{
			glfwDefaultWindowHints();
		}

		/*! @brief Sets the specified window hint to the desired value.
		 *
		 *  This function sets hints for the next call to @ref glfwCreateWindow.  The
		 *  hints, once set, retain their values until changed by a call to this
		 *  function or @ref glfwDefaultWindowHints, or until the library is terminated.
		 *
		 *  Only integer value hints can be set with this function.  String value hints
		 *  are set with @ref glfwWindowHintString.
		 *
		 *  This function does not check whether the specified hint values are valid.
		 *  If you set hints to invalid values this will instead be reported by the next
		 *  call to @ref glfwCreateWindow.
		 *
		 *  Some hints are platform specific.  These may be set on any platform but they
		 *  will only affect their specific platform.  Other platforms will ignore them.
		 *  Setting these hints requires no platform specific headers or functions.
		 *
		 *  @param[in] hint The [window hint](@ref window_hints) to set.
		 *  @param[in] value The new value of the window hint.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidEnum.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_hints
		 *  @sa @ref glfwWindowHintString
		 *  @sa @ref glfwDefaultWindowHints
		 *
		 *  @since Added in version 3.0.  Replaces `glfwOpenWindowHint`.
		 *
		 *  @ingroup window
		 */
		template <class T>
		static GLFW_HPP_INLINE void Hint(const WindowHint hint, const T value) GLFW_HPP_NOEXCEPT
		{
			glfwWindowHint(static_cast<int>(hint), static_cast<int>(value));
		}

		static GLFW_HPP_INLINE void Hint(const ClientApi value) GLFW_HPP_NOEXCEPT
		{
			glfwWindowHint(static_cast<int>(WindowHint::eClientApi), static_cast<int>(value));
		}

		static GLFW_HPP_INLINE void Hint(const ContextApi value) GLFW_HPP_NOEXCEPT
		{
			glfwWindowHint(static_cast<int>(WindowHint::eContextCreationApi), static_cast<int>(value));
		}

		static GLFW_HPP_INLINE void Hint(const Robustness value) GLFW_HPP_NOEXCEPT
		{
			glfwWindowHint(static_cast<int>(WindowHint::eContextRobustness), static_cast<int>(value));
		}

		static GLFW_HPP_INLINE void Hint(const ReleaseBehavior value) GLFW_HPP_NOEXCEPT
		{
			glfwWindowHint(static_cast<int>(WindowHint::eContextReleaseBehavior), static_cast<int>(value));
		}

		static GLFW_HPP_INLINE void Hint(const OpenglProfile value) GLFW_HPP_NOEXCEPT
		{
			glfwWindowHint(static_cast<int>(WindowHint::eOpenglProfile), static_cast<int>(value));
		}

		/*! @brief Sets the specified window hint to the desired value.
		 *
		 *  This function sets hints for the next call to @ref glfwCreateWindow.  The
		 *  hints, once set, retain their values until changed by a call to this
		 *  function or @ref glfwDefaultWindowHints, or until the library is terminated.
		 *
		 *  Only string type hints can be set with this function.  Integer value hints
		 *  are set with @ref glfwWindowHint.
		 *
		 *  This function does not check whether the specified hint values are valid.
		 *  If you set hints to invalid values this will instead be reported by the next
		 *  call to @ref glfwCreateWindow.
		 *
		 *  Some hints are platform specific.  These may be set on any platform but they
		 *  will only affect their specific platform.  Other platforms will ignore them.
		 *  Setting these hints requires no platform specific headers or functions.
		 *
		 *  @param[in] hint The [window hint](@ref window_hints) to set.
		 *  @param[in] value The new value of the window hint.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidEnum.
		 *
		 *  @pointer_lifetime The specified string is copied before this function
		 *  returns.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_hints
		 *  @sa @ref glfwWindowHint
		 *  @sa @ref glfwDefaultWindowHints
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		static GLFW_HPP_INLINE void Hint(const WindowHint hint, GLFW_HPP_STRING const * const value) GLFW_HPP_NOEXCEPT
		{
#if defined(GLFW_HPP_DISABLE_STANDARD_CONTAINERS)
			glfwWindowHintString(static_cast<int>(hint), *value);
#elif GLFW_HPP_CPP_VERSION >= 17
			glfwWindowHintString(static_cast<int>(hint), value->data());
#else
			glfwWindowHintString(static_cast<int>(hint), value->c_str());
#endif
		}

		static GLFW_HPP_INLINE void Hint(const WindowHint hint, GLFW_HPP_STRING const &value) GLFW_HPP_NOEXCEPT
		{
#if defined(GLFW_HPP_DISABLE_STANDARD_CONTAINERS)
			glfwWindowHintString(static_cast<int>(hint), value);
#elif GLFW_HPP_CPP_VERSION >= 17
			glfwWindowHintString(static_cast<int>(hint), value.data());
#else
			glfwWindowHintString(static_cast<int>(hint), value.c_str());
#endif
		}

		template <WindowHint hint>
		static GLFW_HPP_INLINE void Hint(GLFW_HPP_STRING const &value) GLFW_HPP_NOEXCEPT
		{
#if defined(GLFW_HPP_DISABLE_STANDARD_CONTAINERS)
			glfwWindowHintString(static_cast<int>(hint), value);
#elif GLFW_HPP_CPP_VERSION >= 17
			glfwWindowHintString(static_cast<int>(hint), value.data());
#else
			glfwWindowHintString(static_cast<int>(hint), value.c_str());
#endif
		}

		/*! @brief Creates a window and its associated context.
		 *
		 *  This function creates a window and its associated OpenGL or OpenGL ES
		 *  context.  Most of the options controlling how the window and its context
		 *  should be created are specified with [window hints](@ref window_hints).
		 *
		 *  Successful creation does not change which context is current.  Before you
		 *  can use the newly created context, you need to
		 *  [make it current](@ref context_current).  For information about the `share`
		 *  parameter, see @ref context_sharing.
		 *
		 *  The created window, framebuffer and context may differ from what you
		 *  requested, as not all parameters and hints are
		 *  [hard constraints](@ref window_hints_hard).  This includes the size of the
		 *  window, especially for full screen windows.  To query the actual attributes
		 *  of the created window, framebuffer and context, see @ref
		 *  glfwGetWindowAttrib, @ref glfwGetWindowSize and @ref glfwGetFramebufferSize.
		 *
		 *  To create a full screen window, you need to specify the monitor the window
		 *  will cover.  If no monitor is specified, the window will be windowed mode.
		 *  Unless you have a way for the user to choose a specific monitor, it is
		 *  recommended that you pick the primary monitor.  For more information on how
		 *  to query connected monitors, see @ref monitor_monitors.
		 *
		 *  For full screen windows, the specified size becomes the resolution of the
		 *  window's _desired video mode_.  As long as a full screen window is not
		 *  iconified, the supported video mode most closely matching the desired video
		 *  mode is set for the specified monitor.  For more information about full
		 *  screen windows, including the creation of so called _windowed full screen_
		 *  or _borderless full screen_ windows, see @ref window_windowed_full_screen.
		 *
		 *  Once you have created the window, you can switch it between windowed and
		 *  full screen mode with @ref glfwSetWindowMonitor.  This will not affect its
		 *  OpenGL or OpenGL ES context.
		 *
		 *  By default, newly created windows use the placement recommended by the
		 *  window system.  To create the window at a specific position, make it
		 *  initially invisible using the [GLFW_VISIBLE](@ref GLFW_HPP_NAMESPACE::WindowHint::eVisible) window
		 *  hint, set its [position](@ref window_pos) and then [show](@ref window_hide)
		 *  it.
		 *
		 *  As long as at least one full screen window is not iconified, the screensaver
		 *  is prohibited from starting.
		 *
		 *  Window systems put limits on window sizes.  Very large or very small window
		 *  dimensions may be overridden by the window system on creation.  Check the
		 *  actual [size](@ref window_size) after creation.
		 *
		 *  The [swap interval](@ref buffer_swap) is not set during window creation and
		 *  the initial value may vary depending on driver settings and defaults.
		 *
		 *  @param[in] width The desired width, in screen coordinates, of the window.
		 *  This must be greater than zero.
		 *  @param[in] height The desired height, in screen coordinates, of the window.
		 *  This must be greater than zero.
		 *  @param[in] title The initial, UTF-8 encoded window title.
		 *  @param[in] monitor The monitor to use for full screen mode, or `nullptr` for
		 *  windowed mode.
		 *  @param[in] share The window whose context to share resources with, or `nullptr`
		 *  to not share resources.
		 *  @return The handle of the created window, or `nullptr` if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidEnum, @ref GLFW_HPP_NAMESPACE::Error::eInvalidValue, @ref GLFW_HPP_NAMESPACE::Error::eApiUnavailable, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eVersionUnavailable, @ref GLFW_HPP_NAMESPACE::Error::eFormatUnavailable and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @win32 Window creation will fail if the Microsoft GDI software
		 *  OpenGL implementation is the only one available.
		 *
		 *  @remark @win32 If the executable has an icon resource named `GLFW_ICON,` it
		 *  will be set as the initial icon for the window.  If no such icon is present,
		 *  the `IDI_APPLICATION` icon will be used instead.  To set a different icon,
		 *  see @ref glfwSetWindowIcon.
		 *
		 *  @remark @win32 The context to share resources with must not be current on
		 *  any other thread.
		 *
		 *  @remark @macos The OS only supports forward-compatible core profile contexts
		 *  for OpenGL versions 3.2 and later.  Before creating an OpenGL context of
		 *  version 3.2 or later you must set the
		 *  [GLFW_OPENGL_FORWARD_COMPAT](@ref GLFW_HPP_NAMESPACE::WindowHint::eOpenglForwardCompat) and
		 *  [GLFW_OPENGL_PROFILE](@ref GLFW_HPP_NAMESPACE::WindowHint::eOpenglProfile) hints accordingly.
		 *  OpenGL 3.0 and 3.1 contexts are not supported at all on macOS.
		 *
		 *  @remark @macos The GLFW window has no icon, as it is not a document
		 *  window, but the dock icon will be the same as the application bundle's icon.
		 *  For more information on bundles, see the
		 *  [Bundle Programming Guide](https://developer.apple.com/library/mac/documentation/CoreFoundation/Conceptual/CFBundles/)
		 *  in the Mac Developer Library.
		 *
		 *  @remark @macos The first time a window is created the menu bar is created.
		 *  If GLFW finds a `MainMenu.nib` it is loaded and assumed to contain a menu
		 *  bar.  Otherwise a minimal menu bar is created manually with common commands
		 *  like Hide, Quit and About.  The About entry opens a minimal about dialog
		 *  with information from the application's bundle.  Menu bar creation can be
		 *  disabled entirely with the @ref GLFW_HPP_NAMESPACE::InitHint::CocoaMenubar init hint.
		 *
		 *  @remark @macos On OS X 10.10 and later the window frame will not be rendered
		 *  at full resolution on Retina displays unless the
		 *  [GLFW_COCOA_RETINA_FRAMEBUFFER](@ref GLFW_HPP_NAMESPACE::WindowHint::eCocoaRetinaFramebuffer)
		 *  hint is `true` and the `NSHighResolutionCapable` key is enabled in the
		 *  application bundle's `Info.plist`.  For more information, see
		 *  [High Resolution Guidelines for OS X](https://developer.apple.com/library/mac/documentation/GraphicsAnimation/Conceptual/HighResolutionOSX/Explained/Explained.html)
		 *  in the Mac Developer Library.  The GLFW test and example programs use
		 *  a custom `Info.plist` template for this, which can be found as
		 *  `CMake/MacOSXBundleInfo.plist.in` in the source tree.
		 *
		 *  @remark @macos When activating frame autosaving with
		 *  [GLFW_COCOA_FRAME_NAME](@ref GLFW_HPP_NAMESPACE::WindowHint::eCocoaFrameName), the specified
		 *  window size and position may be overridden by previously saved values.
		 *
		 *  @remark @x11 Some window managers will not respect the placement of
		 *  initially hidden windows.
		 *
		 *  @remark @x11 Due to the asynchronous nature of X11, it may take a moment for
		 *  a window to reach its requested state.  This means you may not be able to
		 *  query the final size, position or other attributes directly after window
		 *  creation.
		 *
		 *  @remark @x11 The class part of the `WM_CLASS` window property will by
		 *  default be set to the window title passed to this function.  The instance
		 *  part will use the contents of the `RESOURCE_NAME` environment variable, if
		 *  present and not empty, or fall back to the window title.  Set the
		 *  [GLFW_X11_CLASS_NAME](@ref GLFW_HPP_NAMESPACE::WindowHint::eX11ClassName) and
		 *  [GLFW_X11_INSTANCE_NAME](@ref GLFW_HPP_NAMESPACE::WindowHint::eX11InstanceName) window hints to
		 *  override this.
		 *
		 *  @remark @wayland Compositors should implement the xdg-decoration protocol
		 *  for GLFW to decorate the window properly.  If this protocol isn't
		 *  supported, or if the compositor prefers client-side decorations, a very
		 *  simple fallback frame will be drawn using the wp_viewporter protocol.  A
		 *  compositor can still emit close, maximize or fullscreen events, using for
		 *  instance a keybind mechanism.  If neither of these protocols is supported,
		 *  the window won't be decorated.
		 *
		 *  @remark @wayland A full screen window will not attempt to change the mode,
		 *  no matter what the requested size or refresh rate.
		 *
		 *  @remark @wayland Screensaver inhibition requires the idle-inhibit protocol
		 *  to be implemented in the user's compositor.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_creation
		 *  @sa @ref glfwDestroyWindow
		 *
		 *  @since Added in version 3.0.  Replaces `glfwOpenWindow`.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Window Create(const ScreenCoordinate width, const ScreenCoordinate height, GLFW_HPP_STRING const * const title, Monitor * const monitor = nullptr, Window * const share = nullptr) GLFW_HPP_NOEXCEPT
		{
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			return Window{glfwCreateWindow(width, height, *title, static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))};
#elif GLFW_HPP_CPP_VERSION >= 17
			return Window{glfwCreateWindow(width, height, title->data(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))};
#else
			return Window{glfwCreateWindow(width, height, title->c_str(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))};
#endif
		}

		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Window Create(const ScreenCoordinate width, const ScreenCoordinate height, GLFW_HPP_STRING const &title, Monitor &monitor, Window &share) GLFW_HPP_NOEXCEPT
		{
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			return Window{glfwCreateWindow(width, height, title, static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))};
#elif GLFW_HPP_CPP_VERSION >= 17
			return Window{glfwCreateWindow(width, height, title.data(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))};
#else
			return Window{glfwCreateWindow(width, height, title.c_str(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))};
#endif
		}

		template <ScreenCoordinate width, ScreenCoordinate height>
		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Window Create(GLFW_HPP_STRING const * const title, Monitor * const monitor = nullptr, Window * const share = nullptr) GLFW_HPP_NOEXCEPT
		{
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			return Window{glfwCreateWindow(width, height, *title, static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))};
#elif GLFW_HPP_CPP_VERSION >= 17
			return Window{glfwCreateWindow(width, height, title->data(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))};
#else
			return Window{glfwCreateWindow(width, height, title->c_str(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))};
#endif
		}

		template <ScreenCoordinate width, ScreenCoordinate height>
		GLFW_HPP_NODISCARD("") static GLFW_HPP_INLINE Window Create(GLFW_HPP_STRING const &title, Monitor &monitor, Window &share) GLFW_HPP_NOEXCEPT
		{
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			return Window{glfwCreateWindow(width, height, title, static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))};
#elif GLFW_HPP_CPP_VERSION >= 17
			return Window{glfwCreateWindow(width, height, title.data(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))};
#else
			return Window{glfwCreateWindow(width, height, title.c_str(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))};
#endif
		}

		GLFW_HPP_NODISCARD("") Window(const ScreenCoordinate width, const ScreenCoordinate height, GLFW_HPP_STRING const * const title, Monitor * const monitor = nullptr, Window * const share = nullptr) GLFW_HPP_NOEXCEPT
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			: m_window(glfwCreateWindow(width, height, *title, static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))) {}
#elif GLFW_HPP_CPP_VERSION >= 17
			: m_window(glfwCreateWindow(width, height, title->data(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))) {}
#else
			: m_window(glfwCreateWindow(width, height, title->c_str(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))) {}
#endif
		
		GLFW_HPP_NODISCARD("") Window(const ScreenCoordinate width, const ScreenCoordinate height, GLFW_HPP_STRING const &title, Monitor &monitor, Window &share) GLFW_HPP_NOEXCEPT
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			: m_window(glfwCreateWindow(width, height, title, static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))) {}
#elif GLFW_HPP_CPP_VERSION >= 17
			: m_window(glfwCreateWindow(width, height, title.data(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))) {}
#else
			: m_window(glfwCreateWindow(width, height, title.c_str(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))) {}
#endif

		template <ScreenCoordinate width, ScreenCoordinate height>
		GLFW_HPP_NODISCARD("") Window(GLFW_HPP_STRING const * const title, Monitor * const monitor = nullptr, Window * const share = nullptr) GLFW_HPP_NOEXCEPT
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			: m_window(glfwCreateWindow(width, height, *title, static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))) {}
#elif GLFW_HPP_CPP_VERSION >= 17
			: m_window(glfwCreateWindow(width, height, title->data(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))) {}
#else
			: m_window(glfwCreateWindow(width, height, title->c_str(), static_cast<GLFWmonitor *>(*monitor), static_cast<GLFWwindow *>(*share))) {}
#endif
		
		template <ScreenCoordinate width, ScreenCoordinate height>
		GLFW_HPP_NODISCARD("") Window(GLFW_HPP_STRING const &title, Monitor &monitor, Window &share) GLFW_HPP_NOEXCEPT
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			: m_window(glfwCreateWindow(width, height, title, static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))) {}
#elif GLFW_HPP_CPP_VERSION >= 17
			: m_window(glfwCreateWindow(width, height, title.data(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))) {}
#else
			: m_window(glfwCreateWindow(width, height, title.c_str(), static_cast<GLFWmonitor *>(monitor), static_cast<GLFWwindow *>(share))) {}
#endif

		/*! @brief Destroys the specified window and its context.
		 *
		 *  This function destroys the specified window and its context.  On calling
		 *  this function, no further callbacks will be called for that window.
		 *
		 *  If the context of the specified window is current on the main thread, it is
		 *  detached before being destroyed.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @note The context of the specified window must not be current on any other
		 *  thread when this function is called.
		 *
		 *  @reentrancy This function must not be called from a callback.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_creation
		 *  @sa @ref glfwCreateWindow
		 *
		 *  @since Added in version 3.0.  Replaces `glfwCloseWindow`.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Destroy() const GLFW_HPP_NOEXCEPT
		{
			GLFW_HPP_ASSERT(m_window && "Destroying null window!");
			glfwDestroyWindow(m_window);
		}

		~Window() GLFW_HPP_NOEXCEPT
		{
			GLFW_HPP_ASSERT(m_window && "Destroying null window!");
			glfwDestroyWindow(m_window);
		}

		/*! @brief Checks the close flag of the specified window.
		 *
		 *  This function returns the value of the close flag of the specified window.
		 *
		 *  @return The value of the close flag.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function may be called from any thread.  Access is not
		 *  synchronized.
		 *
		 *  @sa @ref window_close
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE bool ShouldClose() const GLFW_HPP_NOEXCEPT
		{
			return glfwWindowShouldClose(m_window);
		}

		/*! @brief Sets the close flag of the specified window.
		 *
		 *  This function sets the value of the close flag of the specified window.
		 *  This can be used to override the user's attempt to close the window, or
		 *  to signal that it should be closed.
		 *
		 *  @param[in] value The new value.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function may be called from any thread.  Access is not
		 *  synchronized.
		 *
		 *  @sa @ref window_close
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetShouldClose(const bool value) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowShouldClose(m_window, value);
		}

		template <bool value>
		GLFW_HPP_INLINE void SetShouldClose() const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowShouldClose(m_window, value);
		}

		/*! @brief Sets the title of the specified window.
		 *
		 *  This function sets the window title, encoded as UTF-8, of the specified
		 *  window.
		 *
		 *  @param[in] title The UTF-8 encoded window title.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @macos The window title will not be updated until the next time you
		 *  process events.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_title
		 *
		 *  @since Added in version 1.0.
		 *  @glfw3 Added window handle parameter.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetTitle(GLFW_HPP_STRING const * const title) const GLFW_HPP_NOEXCEPT
		{
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			glfwSetWindowTitle(m_window, *title);
#elif GLFW_HPP_CPP_VERSION >= 17
			glfwSetWindowTitle(m_window, title->data());
#else
			glfwSetWindowTitle(m_window, title->c_str());
#endif
		}

		GLFW_HPP_INLINE void SetTitle(GLFW_HPP_STRING const &title) const GLFW_HPP_NOEXCEPT
		{
#ifdef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
			glfwSetWindowTitle(m_window, title);
#elif GLFW_HPP_CPP_VERSION >= 17
			glfwSetWindowTitle(m_window, title.data());
#else
			glfwSetWindowTitle(m_window, title.c_str());
#endif
		}

		/*! @brief Sets the icon for the specified window.
		 *
		 *  This function sets the icon of the specified window.  If passed an array of
		 *  candidate images, those of or closest to the sizes desired by the system are
		 *  selected.  If no images are specified, the window reverts to its default
		 *  icon.
		 *
		 *  The pixels are 32-bit, little-endian, non-premultiplied RGBA, i.e. eight
		 *  bits per channel with the red channel first.  They are arranged canonically
		 *  as packed sequential rows, starting from the top-left corner.
		 *
		 *  The desired image sizes varies depending on platform and system settings.
		 *  The selected images will be rescaled as needed.  Good sizes include 16x16,
		 *  32x32 and 48x48.
		 *
		 *  @param[in] count The number of images in the specified array, or zero to
		 *  revert to the default window icon.
		 *  @param[in] images The images to create the icon from.  This is ignored if
		 *  count is zero.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @pointer_lifetime The specified image data is copied before this function
		 *  returns.
		 *
		 *  @remark @macos The GLFW window has no icon, as it is not a document
		 *  window, so this function does nothing.  The dock icon will be the same as
		 *  the application bundle's icon.  For more information on bundles, see the
		 *  [Bundle Programming Guide](https://developer.apple.com/library/mac/documentation/CoreFoundation/Conceptual/CFBundles/)
		 *  in the Mac Developer Library.
		 *
		 *  @remark @wayland There is no existing protocol to change an icon, the
		 *  window will thus inherit the one defined in the application's desktop file.
		 *  This function always emits @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_icon
		 *
		 *  @since Added in version 3.2.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetIcon(const Count count, const Image * const images) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowIcon(m_window, count, reinterpret_cast<const GLFWimage *>(images));
		}

		template <Count count>
		GLFW_HPP_INLINE void SetIcon(const Image * const images) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowIcon(m_window, count, reinterpret_cast<const GLFWimage *>(images));
		}

		template <Count count = 1>
		GLFW_HPP_INLINE void SetIcon(const Image &image) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowIcon(m_window, count, reinterpret_cast<const GLFWimage *>(&image));
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		template <size_t count>
		GLFW_HPP_INLINE void SetIcon(const std::array<Image, count> &images) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowIcon(m_window, count, reinterpret_cast<const GLFWimage *>(images.data()));
		}

		GLFW_HPP_INLINE void SetIcon(const std::vector<Image> &images) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowIcon(m_window, static_cast<Count>(images.size()), reinterpret_cast<const GLFWimage *>(images.data()));
		}
#endif

		/*! @brief Retrieves the position of the content area of the specified window.
		 *
		 *  This function retrieves the position, in screen coordinates, of the
		 *  upper-left corner of the content area of the specified window.
		 *
		 *  Any or all of the position arguments may be `nullptr`.  If an error occurs, all
		 *  non-`nullptr` position arguments will be set to zero.
		 *
		 *  @param[out] xpos Where to store the x-coordinate of the upper-left corner of
		 *  the content area, or `nullptr`.
		 *  @param[out] ypos Where to store the y-coordinate of the upper-left corner of
		 *  the content area, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland There is no way for an application to retrieve the global
		 *  position of its windows, this function will always emit @ref
		 *  GLFW_PLATFORM_ERROR.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_pos
		 *  @sa @ref glfwSetWindowPos
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void GetPos(ScreenCoordinate * const xpos, ScreenCoordinate * const ypos = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowPos(m_window, xpos, ypos);
		}

		GLFW_HPP_INLINE void GetPos(ScreenCoordinate &xpos, ScreenCoordinate &ypos) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowPos(m_window, &xpos, &ypos);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ScreenCoordinate, 2> GetPos() const GLFW_HPP_NOEXCEPT
		{
			std::array<ScreenCoordinate, 2> position;
			glfwGetWindowPos(m_window, &position[0], &position[1]);
			return position;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ScreenCoordinate> GetPosVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ScreenCoordinate> position(2);
			glfwGetWindowPos(m_window, &position[0], &position[1]);
			return position;
		}
#endif

		/*! @brief Sets the position of the content area of the specified window.
		 *
		 *  This function sets the position, in screen coordinates, of the upper-left
		 *  corner of the content area of the specified windowed mode window.  If the
		 *  window is a full screen window, this function does nothing.
		 *
		 *  __Do not use this function__ to move an already visible window unless you
		 *  have very good reasons for doing so, as it will confuse and annoy the user.
		 *
		 *  The window manager may put limits on what positions are allowed.  GLFW
		 *  cannot and should not override these limits.
		 *
		 *  @param[in] xpos The x-coordinate of the upper-left corner of the content area.
		 *  @param[in] ypos The y-coordinate of the upper-left corner of the content area.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland There is no way for an application to set the global
		 *  position of its windows, this function will always emit @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_pos
		 *  @sa @ref glfwGetWindowPos
		 *
		 *  @since Added in version 1.0.
		 *  @glfw3 Added window handle parameter.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetPos(const ScreenCoordinate xpos, const ScreenCoordinate ypos) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowPos(m_window, xpos, ypos);
		}

		template <ScreenCoordinate xpos, ScreenCoordinate ypos>
		GLFW_HPP_INLINE void SetPos() const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowPos(m_window, xpos, ypos);
		}

		/*! @brief Retrieves the size of the content area of the specified window.
		 *
		 *  This function retrieves the size, in screen coordinates, of the content area
		 *  of the specified window.  If you wish to retrieve the size of the
		 *  framebuffer of the window in pixels, see @ref glfwGetFramebufferSize.
		 *
		 *  Any or all of the size arguments may be `nullptr`.  If an error occurs, all
		 *  non-`nullptr` size arguments will be set to zero.
		 *
		 *  @param[out] width Where to store the width, in screen coordinates, of the
		 *  content area, or `nullptr`.
		 *  @param[out] height Where to store the height, in screen coordinates, of the
		 *  content area, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_size
		 *  @sa @ref glfwSetWindowSize
		 *
		 *  @since Added in version 1.0.
		 *  @glfw3 Added window handle parameter.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void GetSize(ScreenCoordinate * const width, ScreenCoordinate * const height = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowSize(m_window, width, height);
		}

		GLFW_HPP_INLINE void GetSize(ScreenCoordinate &width, ScreenCoordinate &height) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowSize(m_window, &width, &height);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ScreenCoordinate, 2> GetSize() const GLFW_HPP_NOEXCEPT
		{
			std::array<ScreenCoordinate, 2> size;
			glfwGetWindowSize(m_window, &size[0], &size[1]);
			return size;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ScreenCoordinate> GetSizeVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ScreenCoordinate> size(2);
			glfwGetWindowSize(m_window, &size[0], &size[1]);
			return size;
		}
#endif

		/*! @brief Sets the size limits of the specified window.
		 *
		 *  This function sets the size limits of the content area of the specified
		 *  window.  If the window is full screen, the size limits only take effect
		 *  once it is made windowed.  If the window is not resizable, this function
		 *  does nothing.
		 *
		 *  The size limits are applied immediately to a windowed mode window and may
		 *  cause it to be resized.
		 *
		 *  The maximum dimensions must be greater than or equal to the minimum
		 *  dimensions and all must be greater than or equal to zero.
		 *
		 *  @param[in] minwidth The minimum width, in screen coordinates, of the content
		 *  area, or `GLFW_DONT_CARE`.
		 *  @param[in] minheight The minimum height, in screen coordinates, of the
		 *  content area, or `GLFW_DONT_CARE`.
		 *  @param[in] maxwidth The maximum width, in screen coordinates, of the content
		 *  area, or `GLFW_DONT_CARE`.
		 *  @param[in] maxheight The maximum height, in screen coordinates, of the
		 *  content area, or `GLFW_DONT_CARE`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidValue and @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark If you set size limits and an aspect ratio that conflict, the
		 *  results are undefined.
		 *
		 *  @remark @wayland The size limits will not be applied until the window is
		 *  actually resized, either by the user or by the compositor.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_sizelimits
		 *  @sa @ref glfwSetWindowAspectRatio
		 *
		 *  @since Added in version 3.2.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetSizeLimits(const ScreenCoordinate minwidth = GLFW_DONT_CARE, const ScreenCoordinate minheight = GLFW_DONT_CARE, const ScreenCoordinate maxwidth = GLFW_DONT_CARE, const ScreenCoordinate maxheight = GLFW_DONT_CARE) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowSizeLimits(m_window, minwidth, minheight, maxwidth, maxheight);
		}

		template <ScreenCoordinate minwidth = GLFW_DONT_CARE, ScreenCoordinate minheight = GLFW_DONT_CARE, ScreenCoordinate maxwidth = GLFW_DONT_CARE, ScreenCoordinate maxheight = GLFW_DONT_CARE>
		GLFW_HPP_INLINE void SetSizeLimits() const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowSizeLimits(m_window, minwidth, minheight, maxwidth, maxheight);
		}

		/*! @brief Sets the aspect ratio of the specified window.
		 *
		 *  This function sets the required aspect ratio of the content area of the
		 *  specified window.  If the window is full screen, the aspect ratio only takes
		 *  effect once it is made windowed.  If the window is not resizable, this
		 *  function does nothing.
		 *
		 *  The aspect ratio is specified as a numerator and a denominator and both
		 *  values must be greater than zero.  For example, the common 16:9 aspect ratio
		 *  is specified as 16 and 9, respectively.
		 *
		 *  If the numerator and denominator is set to `GLFW_DONT_CARE` then the aspect
		 *  ratio limit is disabled.
		 *
		 *  The aspect ratio is applied immediately to a windowed mode window and may
		 *  cause it to be resized.
		 *
		 *  @param[in] numer The numerator of the desired aspect ratio, or
		 *  `GLFW_DONT_CARE`.
		 *  @param[in] denom The denominator of the desired aspect ratio, or
		 *  `GLFW_DONT_CARE`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidValue and @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark If you set size limits and an aspect ratio that conflict, the
		 *  results are undefined.
		 *
		 *  @remark @wayland The aspect ratio will not be applied until the window is
		 *  actually resized, either by the user or by the compositor.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_sizelimits
		 *  @sa @ref glfwSetWindowSizeLimits
		 *
		 *  @since Added in version 3.2.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetAspectRatio(const ScreenCoordinate numer = GLFW_DONT_CARE, const ScreenCoordinate denom = GLFW_DONT_CARE) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowAspectRatio(m_window, numer, denom);
		}

		template <ScreenCoordinate numer = GLFW_DONT_CARE, ScreenCoordinate denom = GLFW_DONT_CARE>
		GLFW_HPP_INLINE void SetAspectRatio() const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowAspectRatio(m_window, numer, denom);
		}

		/*! @brief Sets the size of the content area of the specified window.
		 *
		 *  This function sets the size, in screen coordinates, of the content area of
		 *  the specified window.
		 *
		 *  For full screen windows, this function updates the resolution of its desired
		 *  video mode and switches to the video mode closest to it, without affecting
		 *  the window's context.  As the context is unaffected, the bit depths of the
		 *  framebuffer remain unchanged.
		 *
		 *  If you wish to update the refresh rate of the desired video mode in addition
		 *  to its resolution, see @ref glfwSetWindowMonitor.
		 *
		 *  The window manager may put limits on what sizes are allowed.  GLFW cannot
		 *  and should not override these limits.
		 *
		 *  @param[in] width The desired width, in screen coordinates, of the window
		 *  content area.
		 *  @param[in] height The desired height, in screen coordinates, of the window
		 *  content area.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland A full screen window will not attempt to change the mode,
		 *  no matter what the requested size.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_size
		 *  @sa @ref glfwGetWindowSize
		 *  @sa @ref glfwSetWindowMonitor
		 *
		 *  @since Added in version 1.0.
		 *  @glfw3 Added window handle parameter.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetSize(const ScreenCoordinate width, const ScreenCoordinate height) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowSize(m_window, width, height);
		}

		template <ScreenCoordinate width, ScreenCoordinate height>
		GLFW_HPP_INLINE void SetSize() const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowSize(m_window, width, height);
		}

		/*! @brief Retrieves the size of the framebuffer of the specified window.
		 *
		 *  This function retrieves the size, in pixels, of the framebuffer of the
		 *  specified window.  If you wish to retrieve the size of the window in screen
		 *  coordinates, see @ref glfwGetWindowSize.
		 *
		 *  Any or all of the size arguments may be `nullptr`.  If an error occurs, all
		 *  non-`nullptr` size arguments will be set to zero.
		 *
		 *  @param[out] width Where to store the width, in pixels, of the framebuffer,
		 *  or `nullptr`.
		 *  @param[out] height Where to store the height, in pixels, of the framebuffer,
		 *  or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_fbsize
		 *  @sa @ref glfwSetFramebufferSizeCallback
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void GetFramebufferSize(Pixel * const width, Pixel * const height = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetFramebufferSize(m_window, width, height);
		}

		GLFW_HPP_INLINE void GetFramebufferSize(Pixel &width, Pixel &height) const GLFW_HPP_NOEXCEPT
		{
			glfwGetFramebufferSize(m_window, &width, &height);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<Pixel, 2> GetFramebufferSize() const GLFW_HPP_NOEXCEPT
		{
			std::array<Pixel, 2> framebuffersize;
			glfwGetFramebufferSize(m_window, &framebuffersize[0], &framebuffersize[1]);
			return framebuffersize;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<Pixel> GetFramebufferSizeVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<Pixel> framebuffersize(2);
			glfwGetFramebufferSize(m_window, &framebuffersize[0], &framebuffersize[1]);
			return framebuffersize;
		}
#endif

		/*! @brief Retrieves the size of the frame of the window.
		 *
		 *  This function retrieves the size, in screen coordinates, of each edge of the
		 *  frame of the specified window.  This size includes the title bar, if the
		 *  window has one.  The size of the frame may vary depending on the
		 *  [window-related hints](@ref window_hints_wnd) used to create it.
		 *
		 *  Because this function retrieves the size of each window frame edge and not
		 *  the offset along a particular coordinate axis, the retrieved values will
		 *  always be zero or positive.
		 *
		 *  Any or all of the size arguments may be `nullptr`.  If an error occurs, all
		 *  non-`nullptr` size arguments will be set to zero.
		 *
		 *  @param[out] left Where to store the size, in screen coordinates, of the left
		 *  edge of the window frame, or `nullptr`.
		 *  @param[out] top Where to store the size, in screen coordinates, of the top
		 *  edge of the window frame, or `nullptr`.
		 *  @param[out] right Where to store the size, in screen coordinates, of the
		 *  right edge of the window frame, or `nullptr`.
		 *  @param[out] bottom Where to store the size, in screen coordinates, of the
		 *  bottom edge of the window frame, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_size
		 *
		 *  @since Added in version 3.1.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void GetFrameSize(ScreenCoordinate * const left, ScreenCoordinate * const top = nullptr, ScreenCoordinate * const right = nullptr, ScreenCoordinate * const bottom = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowFrameSize(m_window, left, top, right, bottom);
		}

		GLFW_HPP_INLINE void GetFrameSize(ScreenCoordinate &left, ScreenCoordinate &top, ScreenCoordinate &right, ScreenCoordinate &bottom) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ScreenCoordinate, 4> GetFrameSize() const GLFW_HPP_NOEXCEPT
		{
			std::array<ScreenCoordinate, 4> framesize;
			glfwGetWindowFrameSize(m_window, &framesize[0], &framesize[1], &framesize[2], &framesize[3]);
			return framesize;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ScreenCoordinate> GetFrameSizeVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ScreenCoordinate> framesize(4);
			glfwGetWindowFrameSize(m_window, &framesize[0], &framesize[1], &framesize[2], &framesize[3]);
			return framesize;
		}
#endif

		/*! @brief Retrieves the content scale for the specified window.
		 *
		 *  This function retrieves the content scale for the specified window.  The
		 *  content scale is the ratio between the current DPI and the platform's
		 *  default DPI.  This is especially important for text and any UI elements.  If
		 *  the pixel dimensions of your UI scaled by this look appropriate on your
		 *  machine then it should appear at a reasonable size on other machines
		 *  regardless of their DPI and scaling settings.  This relies on the system DPI
		 *  and scaling settings being somewhat correct.
		 *
		 *  On systems where each monitors can have its own content scale, the window
		 *  content scale will depend on which monitor the system considers the window
		 *  to be on.
		 *
		 *  @param[out] xscale Where to store the x-axis content scale, or `nullptr`.
		 *  @param[out] yscale Where to store the y-axis content scale, or `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_scale
		 *  @sa @ref glfwSetWindowContentScaleCallback
		 *  @sa @ref glfwGetMonitorContentScale
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void GetContentScale(ContentScale * const xscale, ContentScale * const yscale = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowContentScale(m_window, xscale, yscale);
		}

		GLFW_HPP_INLINE void GetContentScale(ContentScale &xscale, ContentScale &yscale) const GLFW_HPP_NOEXCEPT
		{
			glfwGetWindowContentScale(m_window, &xscale, &yscale);
		}

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::array<ContentScale, 2> GetContentScale() const GLFW_HPP_NOEXCEPT
		{
			std::array<ContentScale, 2> contentscale;
			glfwGetWindowContentScale(m_window, &contentscale[0], &contentscale[1]);
			return contentscale;
		}

		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE std::vector<ContentScale> GetContentScaleVector() const GLFW_HPP_NOEXCEPT
		{
			std::vector<ContentScale> contentscale(2);
			glfwGetWindowContentScale(m_window, &contentscale[0], &contentscale[1]);
			return contentscale;
		}
#endif

		/*! @brief Returns the opacity of the whole window.
		 *
		 *  This function returns the opacity of the window, including any decorations.
		 *
		 *  The opacity (or alpha) value is a positive finite number between zero and
		 *  one, where zero is fully transparent and one is fully opaque.  If the system
		 *  does not support whole window transparency, this function always returns one.
		 *
		 *  The initial opacity value for newly created windows is one.
		 *
		 *  @return The opacity value of the specified window.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_transparency
		 *  @sa @ref glfwSetWindowOpacity
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE Opacity GetOpacity() const GLFW_HPP_NOEXCEPT
		{
			return glfwGetWindowOpacity(m_window);
		}
	
		/*! @brief Sets the opacity of the whole window.
		 *
		 *  This function sets the opacity of the window, including any decorations.
		 *
		 *  The opacity (or alpha) value is a positive finite number between zero and
		 *  one, where zero is fully transparent and one is fully opaque.
		 *
		 *  The initial opacity value for newly created windows is one.
		 *
		 *  A window created with framebuffer transparency may not use whole window
		 *  transparency.  The results of doing this are undefined.
		 *
		 *  @param[in] opacity The desired opacity of the specified window.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_transparency
		 *  @sa @ref glfwGetWindowOpacity
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetOpacity(const Opacity opacity) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowOpacity(m_window, opacity);
		}
	
		/*! @brief Iconifies the specified window.
		 *
		 *  This function iconifies (minimizes) the specified window if it was
		 *  previously restored.  If the window is already iconified, this function does
		 *  nothing.
		 *
		 *  If the specified window is a full screen window, the original monitor
		 *  resolution is restored until the window is restored.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland There is no concept of iconification in wl_shell, this
		 *  function will emit @ref GLFW_HPP_NAMESPACE::Error::ePlatform when using this deprecated
		 *  protocol.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_iconify
		 *  @sa @ref glfwRestoreWindow
		 *  @sa @ref glfwMaximizeWindow
		 *
		 *  @since Added in version 2.1.
		 *  @glfw3 Added window handle parameter.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Iconify() const GLFW_HPP_NOEXCEPT
		{
			glfwIconifyWindow(m_window);
		}

		/*! @brief Restores the specified window.
		 *
		 *  This function restores the specified window if it was previously iconified
		 *  (minimized) or maximized.  If the window is already restored, this function
		 *  does nothing.
		 *
		 *  If the specified window is a full screen window, the resolution chosen for
		 *  the window is restored on the selected monitor.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_iconify
		 *  @sa @ref glfwIconifyWindow
		 *  @sa @ref glfwMaximizeWindow
		 *
		 *  @since Added in version 2.1.
		 *  @glfw3 Added window handle parameter.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Restore() const GLFW_HPP_NOEXCEPT
		{
			glfwRestoreWindow(m_window);
		}

		/*! @brief Maximizes the specified window.
		 *
		 *  This function maximizes the specified window if it was previously not
		 *  maximized.  If the window is already maximized, this function does nothing.
		 *
		 *  If the specified window is a full screen window, this function does nothing.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @par Thread Safety
		 *  This function may only be called from the main thread.
		 *
		 *  @sa @ref window_iconify
		 *  @sa @ref glfwIconifyWindow
		 *  @sa @ref glfwRestoreWindow
		 *
		 *  @since Added in GLFW 3.2.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Maximize() const GLFW_HPP_NOEXCEPT
		{
			glfwMaximizeWindow(m_window);
		}

		/*! @brief Makes the specified window visible.
		 *
		 *  This function makes the specified window visible if it was previously
		 *  hidden.  If the window is already visible or is in full screen mode, this
		 *  function does nothing.
		 *
		 *  By default, windowed mode windows are focused when shown
		 *  Set the [GLFW_FOCUS_ON_SHOW](@ref GLFW_HPP_NAMESPACE::WindowHint::eFocusOnShow) window hint
		 *  to change this behavior for all newly created windows, or change the
		 *  behavior for an existing window with @ref glfwSetWindowAttrib.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_hide
		 *  @sa @ref glfwHideWindow
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Show() const GLFW_HPP_NOEXCEPT
		{
			glfwShowWindow(m_window);
		}

		/*! @brief Hides the specified window.
		 *
		 *  This function hides the specified window if it was previously visible.  If
		 *  the window is already hidden or is in full screen mode, this function does
		 *  nothing.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_hide
		 *  @sa @ref glfwShowWindow
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Hide() const GLFW_HPP_NOEXCEPT
		{
			glfwHideWindow(m_window);
		}

		/*! @brief Brings the specified window to front and sets input focus.
		 *
		 *  This function brings the specified window to front and sets input focus.
		 *  The window should already be visible and not iconified.
		 *
		 *  By default, both windowed and full screen mode windows are focused when
		 *  initially created.  Set the [GLFW_FOCUSED](@ref GLFW_HPP_NAMESPACE::WindowHint::eFocused) to
		 *  disable this behavior.
		 *
		 *  Also by default, windowed mode windows are focused when shown
		 *  with @ref glfwShowWindow. Set the
		 *  [GLFW_FOCUS_ON_SHOW](@ref GLFW_HPP_NAMESPACE::WindowHint::eFocusOnShow) to disable this behavior.
		 *
		 *  __Do not use this function__ to steal focus from other applications unless
		 *  you are certain that is what the user wants.  Focus stealing can be
		 *  extremely disruptive.
		 *
		 *  For a less disruptive way of getting the user's attention, see
		 *  [attention requests](@ref window_attention).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @wayland It is not possible for an application to bring its windows
		 *  to front, this function will always emit @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_focus
		 *  @sa @ref window_attention
		 *
		 *  @since Added in version 3.2.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void Focus() const GLFW_HPP_NOEXCEPT
		{
			glfwFocusWindow(m_window);
		}

		/*! @brief Requests user attention to the specified window.
		 *
		 *  This function requests user attention to the specified window.  On
		 *  platforms where this is not supported, attention is requested to the
		 *  application as a whole.
		 *
		 *  Once the user has given attention, usually by focusing the window or
		 *  application, the system will end the request automatically.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark @macos Attention is requested to the application as a whole, not the
		 *  specific window.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_attention
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void RequestAttention() const GLFW_HPP_NOEXCEPT
		{
			glfwRequestWindowAttention(m_window);
		}

		/*! @brief Returns the monitor that the window uses for full screen mode.
		 *
		 *  This function returns the handle of the monitor that the specified window is
		 *  in full screen on.
		 *
		 *  @return The monitor, or `nullptr` if the window is in windowed mode or an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_monitor
		 *  @sa @ref glfwSetWindowMonitor
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE Monitor GetMonitor() const GLFW_HPP_NOEXCEPT
		{
			return Monitor{glfwGetWindowMonitor(m_window)};
		}

		/*! @brief Sets the mode, monitor, video mode and placement of a window.
		 *
		 *  This function sets the monitor that the window uses for full screen mode or,
		 *  if the monitor is `nullptr`, makes it windowed mode.
		 *
		 *  When setting a monitor, this function updates the width, height and refresh
		 *  rate of the desired video mode and switches to the video mode closest to it.
		 *  The window position is ignored when setting a monitor.
		 *
		 *  When the monitor is `nullptr`, the position, width and height are used to
		 *  place the window content area.  The refresh rate is ignored when no monitor
		 *  is specified.
		 *
		 *  If you only wish to update the resolution of a full screen window or the
		 *  size of a windowed mode window, see @ref glfwSetWindowSize.
		 *
		 *  When a window transitions from full screen to windowed mode, this function
		 *  restores any previous window settings such as whether it is decorated,
		 *  floating, resizable, has size or aspect ratio limits, etc.
		 *
		 *  @param[in] monitor The desired monitor, or `nullptr` to set windowed mode.
		 *  @param[in] xpos The desired x-coordinate of the upper-left corner of the
		 *  content area.
		 *  @param[in] ypos The desired y-coordinate of the upper-left corner of the
		 *  content area.
		 *  @param[in] width The desired with, in screen coordinates, of the content
		 *  area or video mode.
		 *  @param[in] height The desired height, in screen coordinates, of the content
		 *  area or video mode.
		 *  @param[in] refreshRate The desired refresh rate, in Hz, of the video mode,
		 *  or `GLFW_DONT_CARE`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized and @ref
		 *  GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark The OpenGL or OpenGL ES context will not be destroyed or otherwise
		 *  affected by any resizing or mode switching, although you may need to update
		 *  your viewport if the framebuffer size has changed.
		 *
		 *  @remark @wayland The desired window position is ignored, as there is no way
		 *  for an application to set this property.
		 *
		 *  @remark @wayland Setting the window to full screen will not attempt to
		 *  change the mode, no matter what the requested size or refresh rate.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_monitor
		 *  @sa @ref window_full_screen
		 *  @sa @ref glfwGetWindowMonitor
		 *  @sa @ref glfwSetWindowSize
		 *
		 *  @since Added in version 3.2.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetMonitor(Monitor monitor, const ScreenCoordinate xpos, const ScreenCoordinate ypos, const ScreenCoordinate width, const ScreenCoordinate height, const Hz refreshRate = GLFW_DONT_CARE) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowMonitor(m_window, static_cast<GLFWmonitor *>(monitor), xpos, ypos, width, height, refreshRate);
		}

		template <ScreenCoordinate xpos, ScreenCoordinate ypos, ScreenCoordinate width, ScreenCoordinate height, Hz refreshRate = GLFW_DONT_CARE>
		GLFW_HPP_INLINE void SetMonitor(Monitor monitor) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowMonitor(m_window, static_cast<GLFWmonitor *>(monitor), xpos, ypos, width, height, refreshRate);
		}

		/*! @brief Returns an attribute of the specified window.
		 *
		 *  This function returns the value of an attribute of the specified window or
		 *  its OpenGL or OpenGL ES context.
		 *
		 *  @param[in] attrib The [window attribute](@ref window_attribs) whose value to
		 *  return.
		 *  @return The value of the attribute, or zero if an
		 *  [error](@ref error_handling) occurred.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidEnum and @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark Framebuffer related hints are not window attributes.  See @ref
		 *  window_attribs_fb for more information.
		 *
		 *  @remark Zero is a valid value for many window and context related
		 *  attributes so you cannot use a return value of zero as an indication of
		 *  errors.  However, this function should not fail as long as it is passed
		 *  valid arguments and the library has been [initialized](@ref intro_init).
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_attribs
		 *  @sa @ref glfwSetWindowAttrib
		 *
		 *  @since Added in version 3.0.  Replaces `glfwGetWindowParam` and
		 *  `glfwGetGLVersion`.
		 *
		 *  @ingroup window
		 */
		template <class T>
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE T GetAttrib(const WindowAttribute attrib) const GLFW_HPP_NOEXCEPT
		{
			return static_cast<T>(glfwGetWindowAttrib(m_window, static_cast<int>(attrib)));
		}

		template <class T, WindowAttribute attrib>
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE T GetAttrib() const GLFW_HPP_NOEXCEPT
		{
			return static_cast<T>(glfwGetWindowAttrib(m_window, static_cast<int>(attrib)));
		}

		/*! @brief Sets an attribute of the specified window.
		 *
		 *  This function sets the value of an attribute of the specified window.
		 *
		 *  The supported attributes are [GLFW_DECORATED](@ref GLFW_HPP_NAMESPACE::WindowAttribute::eDecorated),
		 *  [GLFW_RESIZABLE](@ref GLFW_HPP_NAMESPACE::WindowAttribute::eResizable),
		 *  [GLFW_FLOATING](@ref GLFW_HPP_NAMESPACE::WindowAttribute::eFloating),
		 *  [GLFW_AUTO_ICONIFY](@ref GLFW_HPP_NAMESPACE::WindowAttribute::eAutoIconify) and
		 *  [GLFW_FOCUS_ON_SHOW](@ref GLFW_HPP_NAMESPACE::WindowAttribute::eFocusOnShow).
		 *
		 *  Some of these attributes are ignored for full screen windows.  The new
		 *  value will take effect if the window is later made windowed.
		 *
		 *  Some of these attributes are ignored for windowed mode windows.  The new
		 *  value will take effect if the window is later made full screen.
		 *
		 *  @param[in] attrib A supported window attribute.
		 *  @param[in] value `true` or `false`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized, @ref
		 *  GLFW_HPP_NAMESPACE::Error::eInvalidEnum, @ref GLFW_HPP_NAMESPACE::Error::eInvalidValue and @ref GLFW_HPP_NAMESPACE::Error::ePlatform.
		 *
		 *  @remark Calling @ref glfwGetWindowAttrib will always return the latest
		 *  value, even if that value is ignored by the current mode of the window.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_attribs
		 *  @sa @ref glfwGetWindowAttrib
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE void SetAttrib(const WindowAttribute attrib, const bool value) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowAttrib(m_window, static_cast<int>(attrib), value);
		}

		template <WindowAttribute attrib, bool value>
		GLFW_HPP_INLINE void SetAttrib() const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowAttrib(m_window, static_cast<int>(attrib), value);
		}

		/*! @brief Sets the user pointer of the specified window.
		 *
		 *  This function sets the user-defined pointer of the specified window.  The
		 *  current value is retained until the window is destroyed.  The initial value
		 *  is `nullptr`.
		 *
		 *  @param[in] pointer The new value.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function may be called from any thread.  Access is not
		 *  synchronized.
		 *
		 *  @sa @ref window_userptr
		 *  @sa @ref glfwGetWindowUserPointer
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		template <class T>
		GLFW_HPP_INLINE void SetUserPointer(T * const pointer = nullptr) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowUserPointer(m_window, static_cast<void *>(pointer));
		}

		template <class T>
		GLFW_HPP_INLINE void SetUserPointer(T &pointer) const GLFW_HPP_NOEXCEPT
		{
			glfwSetWindowUserPointer(m_window, static_cast<void *>(&pointer));
		}

		/*! @brief Returns the user pointer of the specified window.
		 *
		 *  This function returns the current value of the user-defined pointer of the
		 *  specified window.  The initial value is `nullptr`.
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function may be called from any thread.  Access is not
		 *  synchronized.
		 *
		 *  @sa @ref window_userptr
		 *  @sa @ref glfwSetWindowUserPointer
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		template <class T>
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE T *GetUserPointer() const GLFW_HPP_NOEXCEPT
		{
			return static_cast<T *>(glfwGetWindowUserPointer(m_window));
		}

		template <class T>
		GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE T &GetUserPointerRef() const GLFW_HPP_NOEXCEPT
		{
			T * const pointer = static_cast<T *>(glfwGetWindowUserPointer(m_window));
			GLFW_HPP_ASSERT(pointer && "Returning null reference!");
			return *pointer;
		}

		/*! @brief Sets the position callback for the specified window.
		 *
		 *  This function sets the position callback of the specified window, which is
		 *  called when the window is moved.  The callback is provided with the
		 *  position, in screen coordinates, of the upper-left corner of the content
		 *  area of the window.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::ScreenCoordinate xpos, GLFW_HPP_NAMESPACE::ScreenCoordinate ypos)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFW_HPP_NAMESPACE::Windowposfun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @remark @wayland This callback will never be called, as there is no way for
		 *  an application to know its global position.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_pos
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowposfun SetPosCallback(Windowposfun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowposfun>(glfwSetWindowPosCallback(m_window, reinterpret_cast<GLFWwindowposfun>(callback)));
		}

		template <Windowposfun callback = nullptr>
		GLFW_HPP_INLINE Windowposfun SetPosCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowposfun>(glfwSetWindowPosCallback(m_window, reinterpret_cast<GLFWwindowposfun>(callback)));
		}

		/*! @brief Sets the size callback for the specified window.
		 *
		 *  This function sets the size callback of the specified window, which is
		 *  called when the window is resized.  The callback is provided with the size,
		 *  in screen coordinates, of the content area of the window.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::ScreenCoordinate width, GLFW_HPP_NAMESPACE::ScreenCoordinate height)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowsizefun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_size
		 *
		 *  @since Added in version 1.0.
		 *  @glfw3 Added window handle parameter and return value.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowsizefun SetSizeCallback(Windowsizefun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowsizefun>(glfwSetWindowSizeCallback(m_window, reinterpret_cast<GLFWwindowsizefun>(callback)));
		}

		template <Windowsizefun callback = nullptr>
		GLFW_HPP_INLINE Windowsizefun SetSizeCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowsizefun>(glfwSetWindowSizeCallback(m_window, reinterpret_cast<GLFWwindowsizefun>(callback)));
		}

		/*! @brief Sets the close callback for the specified window.
		 *
		 *  This function sets the close callback of the specified window, which is
		 *  called when the user attempts to close the window, for example by clicking
		 *  the close widget in the title bar.
		 *
		 *  The close flag is set before this callback is called, but you can modify it
		 *  at any time with @ref glfwSetWindowShouldClose.
		 *
		 *  The close callback is not triggered by @ref glfwDestroyWindow.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowclosefun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @remark @macos Selecting Quit from the application menu will trigger the
		 *  close callback for all windows.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_close
		 *
		 *  @since Added in version 2.5.
		 *  @glfw3 Added window handle parameter and return value.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowclosefun SetCloseCallback(Windowclosefun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowclosefun>(glfwSetWindowCloseCallback(m_window, reinterpret_cast<GLFWwindowclosefun>(callback)));
		}

		template <Windowclosefun callback = nullptr>
		GLFW_HPP_INLINE Windowclosefun SetCloseCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowclosefun>(glfwSetWindowCloseCallback(m_window, reinterpret_cast<GLFWwindowclosefun>(callback)));
		}

		/*! @brief Sets the refresh callback for the specified window.
		 *
		 *  This function sets the refresh callback of the specified window, which is
		 *  called when the content area of the window needs to be redrawn, for example
		 *  if the window has been exposed after having been covered by another window.
		 *
		 *  On compositing window systems such as Aero, Compiz, Aqua or Wayland, where
		 *  the window contents are saved off-screen, this callback may be called only
		 *  very infrequently or never at all.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window);
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowrefreshfun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_refresh
		 *
		 *  @since Added in version 2.5.
		 *  @glfw3 Added window handle parameter and return value.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowrefreshfun SetRefreshCallback(Windowrefreshfun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowrefreshfun>(glfwSetWindowRefreshCallback(m_window, reinterpret_cast<GLFWwindowrefreshfun>(callback)));
		}

		template <Windowrefreshfun callback = nullptr>
		GLFW_HPP_INLINE Windowrefreshfun SetRefreshCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowrefreshfun>(glfwSetWindowRefreshCallback(m_window, reinterpret_cast<GLFWwindowrefreshfun>(callback)));
		}

		/*! @brief Sets the focus callback for the specified window.
		 *
		 *  This function sets the focus callback of the specified window, which is
		 *  called when the window gains or loses input focus.
		 *
		 *  After the focus callback is called for a window that lost input focus,
		 *  synthetic key and mouse button release events will be generated for all such
		 *  that had been pressed.  For more information, see @ref glfwSetKeyCallback
		 *  and @ref glfwSetMouseButtonCallback.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool focused)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowfocusfun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_focus
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowfocusfun SetFocusCallback(Windowfocusfun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowfocusfun>(glfwSetWindowFocusCallback(m_window, reinterpret_cast<GLFWwindowfocusfun>(callback)));
		}

		template <Windowfocusfun callback = nullptr>
		GLFW_HPP_INLINE Windowfocusfun SetFocusCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowfocusfun>(glfwSetWindowFocusCallback(m_window, reinterpret_cast<GLFWwindowfocusfun>(callback)));
		}

		/*! @brief Sets the iconify callback for the specified window.
		 *
		 *  This function sets the iconification callback of the specified window, which
		 *  is called when the window is iconified or restored.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool iconified)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowiconifyfun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @remark @wayland The wl_shell protocol has no concept of iconification,
		 *  this callback will never be called when using this deprecated protocol.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_iconify
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowiconifyfun SetIconifyCallback(Windowiconifyfun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowiconifyfun>(glfwSetWindowIconifyCallback(m_window, reinterpret_cast<GLFWwindowiconifyfun>(callback)));
		}

		template <Windowiconifyfun callback = nullptr>
		GLFW_HPP_INLINE Windowiconifyfun SetIconifyCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowiconifyfun>(glfwSetWindowIconifyCallback(m_window, reinterpret_cast<GLFWwindowiconifyfun>(callback)));
		}

		/*! @brief Sets the maximize callback for the specified window.
		 *
		 *  This function sets the maximization callback of the specified window, which
		 *  is called when the window is maximized or restored.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, bool maximized)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowmaximizefun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_maximize
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowmaximizefun SetMaximizeCallback(Windowmaximizefun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowmaximizefun>(glfwSetWindowMaximizeCallback(m_window, reinterpret_cast<GLFWwindowmaximizefun>(callback)));
		}

		template <Windowmaximizefun callback = nullptr>
		GLFW_HPP_INLINE Windowmaximizefun SetMaximizeCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowmaximizefun>(glfwSetWindowMaximizeCallback(m_window, reinterpret_cast<GLFWwindowmaximizefun>(callback)));
		}

		/*! @brief Sets the framebuffer resize callback for the specified window.
		 *
		 *  This function sets the framebuffer resize callback of the specified window,
		 *  which is called when the framebuffer of the specified window is resized.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::Pixel width, GLFW_HPP_NAMESPACE::Pixel height)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWframebuffersizefun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_fbsize
		 *
		 *  @since Added in version 3.0.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Framebuffersizefun SetFramebufferSizeCallback(Framebuffersizefun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Framebuffersizefun>(glfwSetFramebufferSizeCallback(m_window, reinterpret_cast<GLFWframebuffersizefun>(callback)));
		}

		template <Framebuffersizefun callback = nullptr>
		GLFW_HPP_INLINE Framebuffersizefun SetFramebufferSizeCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Framebuffersizefun>(glfwSetFramebufferSizeCallback(m_window, reinterpret_cast<GLFWframebuffersizefun>(callback)));
		}

		/*! @brief Sets the window content scale callback for the specified window.
		 *
		 *  This function sets the window content scale callback of the specified window,
		 *  which is called when the content scale of the specified window changes.
		 *
		 *  @param[in] callback The new callback, or `nullptr` to remove the currently set
		 *  callback.
		 *  @return The previously set callback, or `nullptr` if no callback was set or the
		 *  library had not been [initialized](@ref intro_init).
		 *
		 *  @callback_signature
		 *  @code
		 *  void function_name(GLFW_HPP_NAMESPACE::Window window, GLFW_HPP_NAMESPACE::ContentScale xscale, GLFW_HPP_NAMESPACE::ContentScale yscale)
		 *  @endcode
		 *  For more information about the callback parameters, see the
		 *  [function pointer type](@ref GLFWwindowcontentscalefun).
		 *
		 *  @errors Possible errors include @ref GLFW_HPP_NAMESPACE::Error::eNotInitalized.
		 *
		 *  @thread_safety This function must only be called from the main thread.
		 *
		 *  @sa @ref window_scale
		 *  @sa @ref glfwGetWindowContentScale
		 *
		 *  @since Added in version 3.3.
		 *
		 *  @ingroup window
		 */
		GLFW_HPP_INLINE Windowcontentscalefun SetContentScaleCallback(Windowcontentscalefun callback = nullptr) const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowcontentscalefun>(glfwSetWindowContentScaleCallback(m_window, reinterpret_cast<GLFWwindowcontentscalefun>(callback)));
		}

		template <Windowcontentscalefun callback = nullptr>
		GLFW_HPP_INLINE Windowcontentscalefun SetContentScaleCallback() const GLFW_HPP_NOEXCEPT
		{
			return reinterpret_cast<Windowcontentscalefun>(glfwSetWindowContentScaleCallback(m_window, reinterpret_cast<GLFWwindowcontentscalefun>(callback)));
		}

	private:
		GLFWwindow *m_window = nullptr;

#ifdef GLFW_HPP_ENABLE_HASHING
		friend struct std::hash<Window>;
#endif
	};

	static_assert(sizeof(Window) == sizeof(GLFWwindow *), "Window class and original pointer are different sizes!");


	/*! @brief Opaque cursor object.
 	*
 	*  Opaque cursor object.
 	*
 	*  @see @ref cursor_object
 	*
 	*  @since Added in version 3.1.
 	*
 	*  @ingroup input
 	*/
	class Cursor
	{
	private:
		GLFWcursor *m_cursor = nullptr;

#ifdef GLFW_HPP_ENABLE_HASHING
		friend struct std::hash<Cursor>;
#endif
	};

	static_assert(sizeof(Cursor) == sizeof(GLFWcursor *), "Cursor class and original pointer are different sizes!");
}

// TODO: Implement hashing functions
#ifdef GLFW_HPP_ENABLE_HASHING

namespace std
{
	template <>
	struct hash<GLFW_HPP_NAMESPACE::ModFlags>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Vidmode>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Gammaramp>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Image>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Gamepadstate>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Monitor>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Window>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};

	template <>
	struct hash<GLFW_HPP_NAMESPACE::Cursor>
	{
		GLFW_HPP_CONSTEXPR size_t operator()() const GLFW_HPP_NOEXCEPT
		{
			return 0;
		}
	};
}

#endif // #ifdef GLFW_HPP_ENABLE_HASHING

#endif // #ifndef GLFW_HPP
