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

#include <cstdio>

#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
	#include <sstream>

	#if GLFW_HPP_CPP_VERSION >= 17
		#include <string_view>
		#define GLFW_HPP_STRING std::string_view
	#else
		#include <string>
		#define GLFW_HPP_STRING std::string
	#endif
#else
	#define GLFW_HPP_STRING const char *
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
		#define GLFW_HPP_CONSTEVAL_IF if(false)
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

// === General Value Placement Macros ===

#define GLFW_HPP_MAX_HEX_STRING_LENGTH 5

// === Begin the Namespace ===

namespace GLFW_HPP_NAMESPACE
{
	// === Helper Types ===

	using EnumSize = int;

	// === Enums ===

	GLFW_HPP_NODISCARD("") GLFW_HPP_INLINE GLFW_HPP_STRING invalidValueToString(const EnumSize value) GLFW_HPP_NOEXCEPT
	{
#ifndef GLFW_HPP_DISABLE_STANDARD_CONTAINERS
		std::stringstream ss;
		ss << std::hex << value;
		return {"Invalid value: " + ss.str()};
#else
		static char string[15 + GLFW_HPP_MAX_HEX_STRING_LENGTH + 1] = "Invalid value: ";
		snprintf(string + 15, GLFW_HPP_MAX_HEX_STRING_LENGTH, "%X", value);
		return string;
#endif
	}

	// Key and button actions
	enum class Action : EnumSize
	{
		// The key or mouse button was released
		eRelease = GLFW_RELEASE,

		// The key or mouse button was pressed
		ePress   = GLFW_PRESS,

		// The key was held down until it repeated
		eRepeat	 = GLFW_REPEAT
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Action value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Action::eRelease: return "Release";
		case Action::ePress:   return "Press";
		case Action::eRepeat:  return "Repeat";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Joystick hat states
	// See [joystick hat input](@ref joystick_hat) for how these are used
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

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Hat value) GLFW_HPP_NOEXCEPT
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

	// Keyboard key IDs
	// See [key input](@ref input_key) for how these are used
	enum class Key : EnumSize
	{
		eUnknown 	  = GLFW_KEY_UNKNOWN,
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

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Key value) GLFW_HPP_NOEXCEPT
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

	// Modifier key flags
	enum class Mod : EnumSize
	{
		// If this bit is set one or more Shift keys were held down
		eShift 	  = GLFW_MOD_SHIFT,

		// If this bit is set one or more Control keys were held down
		eControl  = GLFW_MOD_CONTROL,

		// If this bit is set one or more Alt keys were held down
		eAlt 	  = GLFW_MOD_ALT,

		// If this bit is set one or more Super keys were held down
		eSuper 	  = GLFW_MOD_SUPER,

		// If this bit is set the Caps Lock key is enabled
		eCapsLock = GLFW_MOD_CAPS_LOCK,

		// If this bit is set the Num Lock key is enabled
		eNumLock  = GLFW_MOD_NUM_LOCK
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Mod value) GLFW_HPP_NOEXCEPT
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

	// Mouse button IDs
	// See [mouse button input](@ref input_mouse_button) for how these are used
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

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const MouseButton value) GLFW_HPP_NOEXCEPT
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

	// Joystick IDs
	// See [joystick input](@ref joystick) for how these are used
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

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Joystick value) GLFW_HPP_NOEXCEPT
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

	// Gamepad buttons
	// See @ref gamepad for how these are used
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

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const GamepadButton value) GLFW_HPP_NOEXCEPT
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

	// Gamepad axes
	// See @ref gamepad for how these are used
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

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const GamepadAxis value) GLFW_HPP_NOEXCEPT
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

	// Error codes
	enum class Error : EnumSize
	{
		// No error has occurred
		eNone	 			= GLFW_NO_ERROR,

		// GLFW has not been initialized
		eNotInitalized 		= GLFW_NOT_INITIALIZED,

		// No context is current for this thread
		eNoCurrentContext 	= GLFW_NO_CURRENT_CONTEXT,

		// One of the arguments to the function was an invalid enum value
		eInvalidEnum 		= GLFW_INVALID_ENUM,

		// One of the arguments to the function was an invalid value
		eInvalidValue 		= GLFW_INVALID_VALUE,

		// A memory allocation failed
		eOutOfMemory 		= GLFW_OUT_OF_MEMORY,

		// GLFW could not find support for the requested API on the system
		eApiUnavailable 	= GLFW_API_UNAVAILABLE,

		// The requested OpenGL or OpenGL ES version is not available
		eVersionUnavailable = GLFW_VERSION_UNAVAILABLE,

		// A platform-specific error occurred that does not match any of the more specific categories
		ePlatform	 		= GLFW_PLATFORM_ERROR,

		// The requested format is not supported or available
		eFormatUnavailable 	= GLFW_FORMAT_UNAVAILABLE,

		// The specified window does not have an OpenGL or OpenGL ES context
		eNoWindowContext 	= GLFW_NO_WINDOW_CONTEXT
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Error value) GLFW_HPP_NOEXCEPT
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

	// Hints related to window creation
	enum class WindowHint : EnumSize
	{
		// Input focus window hint
		eFocused   	  			= GLFW_FOCUSED,

		// Window resize-ability window hint
		eResizable 	  			= GLFW_RESIZABLE,

		// Window visibility window hint
		eVisible   	  			= GLFW_VISIBLE,

		// Window decoration window hint
		eDecorated 	  			= GLFW_DECORATED,

		// Window auto-iconification window hint
		eAutoIconify  			= GLFW_AUTO_ICONIFY,

		// Window decoration window hint
		eFloating 	  			= GLFW_FLOATING,

		// Window maximization window hint
		eMaximized    			= GLFW_MAXIMIZED,

		// Cursor centering window hint
		eCenterCursor 			= GLFW_CENTER_CURSOR,

		// Window framebuffer transparency hint
		eTransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,

		// Input focus on calling show window hint
		eFocusOnShow			= GLFW_FOCUS_ON_SHOW,

		// Framebuffer bit depth hint
		eRedBits				= GLFW_RED_BITS,

		// Framebuffer bit depth hint
		eGreenBits				= GLFW_GREEN_BITS,

		// Framebuffer bit depth hint
		eBlueBits				= GLFW_BLUE_BITS,

		// Framebuffer bit depth hint
		eAlphaBits				= GLFW_ALPHA_BITS,

		// Framebuffer bit depth hint
		eDepthBits				= GLFW_DEPTH_BITS,

		// Framebuffer bit depth hint
		eStencilBits			= GLFW_STENCIL_BITS,

		// Framebuffer bit depth hint
		eAccumRedBits			= GLFW_ACCUM_RED_BITS,

		// Framebuffer bit depth hint
		eAccumGreenBits			= GLFW_ACCUM_GREEN_BITS,

		// Framebuffer bit depth hint
		eAccumBlueBits			= GLFW_ACCUM_BLUE_BITS,

		// Framebuffer bit depth hint
		eAccumAlphaBits			= GLFW_ACCUM_ALPHA_BITS,

		// Framebuffer auxiliary buffer hint
		eAuxBuffers				= GLFW_AUX_BUFFERS,

		// OpenGL stereoscopic rendering hint
		eStereo					= GLFW_STEREO,

		// Framebuffer MSAA samples hint
		eSamples				= GLFW_SAMPLES,

		// Framebuffer sRGB hint
		eSrgbCapable			= GLFW_SRGB_CAPABLE,

		// Monitor refresh rate hint
		eRefreshRate			= GLFW_REFRESH_RATE,

		// Framebuffer double buffering hint
		eDoublebuffer			= GLFW_DOUBLEBUFFER,

		// Context client API hint
		eClientApi 				= GLFW_CLIENT_API,

		// Context client API major version hint
		eContextVersionMajor	= GLFW_CONTEXT_VERSION_MAJOR,

		// Context client API minor version hint
		eContextVersionMinor	= GLFW_CONTEXT_VERSION_MINOR,

		// Context client API revision number hint
		eContextRevision		= GLFW_CONTEXT_REVISION,

		// Context robustness hint
		eContextRobustness		= GLFW_CONTEXT_ROBUSTNESS,

		// OpenGL forward-compatibility hint
		eOpenglForwardCompat	= GLFW_OPENGL_FORWARD_COMPAT,

		// Debug mode context hint
		eOpenglDebugContext		= GLFW_OPENGL_DEBUG_CONTEXT,

		// OpenGL profile hint
		eOpenglProfile			= GLFW_OPENGL_PROFILE,

		// Context flush-on-release hint
		eContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,

		// Context error suppression hint
		eContextNoError			= GLFW_CONTEXT_NO_ERROR,

		// Context creation API hint
		eContextCreationApi		= GLFW_CONTEXT_CREATION_API,

		// Window content area scaling window
		eScaleToMonitor			= GLFW_SCALE_TO_MONITOR,

		// macOS specific
		eCocoaRetinaFramebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,

		// macOS specific
		eCocoaFrameName			= GLFW_COCOA_FRAME_NAME,

		// macOS specific
		eCocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,

		// X11 specific
		eX11ClassName			= GLFW_X11_CLASS_NAME,

		// X11 specific
		eX11InstanceName		= GLFW_X11_INSTANCE_NAME
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const WindowHint value) GLFW_HPP_NOEXCEPT
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

	// Attributes related to window creation
	enum class WindowAttribute : EnumSize
	{
		// Input focus window attribute
		eFocused   	  			= GLFW_FOCUSED,

		// Window iconification window attribute
		eIconified				= GLFW_ICONIFIED,

		// Window resize-ability window attribute
		eResizable 	  			= GLFW_RESIZABLE,

		// Window visibility window attribute
		eVisible   	  			= GLFW_VISIBLE,

		// Window decoration window attribute
		eDecorated 	  			= GLFW_DECORATED,

		// Window auto-iconification window attribute
		eAutoIconify  			= GLFW_AUTO_ICONIFY,

		// Window decoration window attribute
		eFloating 	  			= GLFW_FLOATING,

		// Window maximization window attribute
		eMaximized    			= GLFW_MAXIMIZED,

		// Window framebuffer transparency attribute
		eTransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,

		// Mouse cursor hover window attribute
		eHovered				= GLFW_HOVERED,

		// Input focus on calling show window attribute
		eFocusOnShow			= GLFW_FOCUS_ON_SHOW,

		// Context client API attribute
		eClientApi 				= GLFW_CLIENT_API,

		// Context client API major version attribute
		eContextVersionMajor	= GLFW_CONTEXT_VERSION_MAJOR,

		// Context client API minor version attribute
		eContextVersionMinor	= GLFW_CONTEXT_VERSION_MINOR,

		// Context client API revision number attribute
		eContextRevision		= GLFW_CONTEXT_REVISION,

		// Context robustness attribute
		eContextRobustness		= GLFW_CONTEXT_ROBUSTNESS,

		// OpenGL forward-compatibility attribute
		eOpenglForwardCompat	= GLFW_OPENGL_FORWARD_COMPAT,

		// Debug mode context attribute
		eOpenglDebugContext		= GLFW_OPENGL_DEBUG_CONTEXT,

		// OpenGL profile attribute
		eOpenglProfile			= GLFW_OPENGL_PROFILE,

		// Context flush-on-release attribute
		eContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,

		// Context error suppression attribute
		eContextNoError			= GLFW_CONTEXT_NO_ERROR,

		// Context creation API attribute
		eContextCreationApi		= GLFW_CONTEXT_CREATION_API
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const WindowAttribute value) GLFW_HPP_NOEXCEPT
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

	// Client APIs
	enum class ClientApi : EnumSize
	{
		eNone 	  = GLFW_NO_API,
		eOpengl   = GLFW_OPENGL_API,
		eOpenglEs = GLFW_OPENGL_ES_API
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const ClientApi value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case ClientApi::eNone: 	   return "None";
		case ClientApi::eOpengl:   return "Opengl";
		case ClientApi::eOpenglEs: return "OpenglEs";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Robustness strategy
	enum class Robustness : EnumSize
	{
		eNone 				 = GLFW_NO_ROBUSTNESS,
		eNoResetNotification = GLFW_NO_RESET_NOTIFICATION,
		eLoseContextOnReset  = GLFW_LOSE_CONTEXT_ON_RESET
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Robustness value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Robustness::eNone: 			   return "None";
		case Robustness::eNoResetNotification: return "NoResetNotification";
		case Robustness::eLoseContextOnReset:  return "LoseContextOnReset";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// OpenGL profiles
	enum class OpenglProfile : EnumSize
	{
		eAny 	= GLFW_OPENGL_ANY_PROFILE,
		eCore 	= GLFW_OPENGL_CORE_PROFILE,
		eCompat = GLFW_OPENGL_COMPAT_PROFILE
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const OpenglProfile value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case OpenglProfile::eAny: 	 return "Any";
		case OpenglProfile::eCore: 	 return "Core";
		case OpenglProfile::eCompat: return "Compat";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Input modes
	enum class InputMode : EnumSize
	{
		eCursor = GLFW_CURSOR,
		eStickyKeys = GLFW_STICKY_KEYS,
		eStickyMouseButtons = GLFW_STICKY_MOUSE_BUTTONS,
		eLockKeyMods = GLFW_LOCK_KEY_MODS,
		eRawMouseMotion = GLFW_RAW_MOUSE_MOTION
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const InputMode value) GLFW_HPP_NOEXCEPT
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

	// Cursor modes
	enum class CursorMode : EnumSize
	{
		eNormal   = GLFW_CURSOR_NORMAL,
		eHidden   = GLFW_CURSOR_HIDDEN,
		eDisabled = GLFW_CURSOR_DISABLED
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const CursorMode value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case CursorMode::eNormal: 	return "Normal";
		case CursorMode::eHidden: 	return "Hidden";
		case CursorMode::eDisabled: return "Disabled";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Release behaviors
	enum class ReleaseBehavior : EnumSize
	{
		eAny   = GLFW_ANY_RELEASE_BEHAVIOR,
		eFlush = GLFW_RELEASE_BEHAVIOR_FLUSH,
		eNone  = GLFW_RELEASE_BEHAVIOR_NONE
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const ReleaseBehavior value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case ReleaseBehavior::eAny:   return "Any";
		case ReleaseBehavior::eFlush: return "Flush";
		case ReleaseBehavior::eNone:  return "None";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Context creation APIs
	enum class ContextApi : EnumSize
	{
		eNative = GLFW_NATIVE_CONTEXT_API,
		eEgl 	= GLFW_EGL_CONTEXT_API,
		eOsmesa = GLFW_OSMESA_CONTEXT_API
	}; 

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const ContextApi value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case ContextApi::eNative: return "Native";
		case ContextApi::eEgl: 	  return "Egl";
		case ContextApi::eOsmesa: return "Osmesa";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Standard system cursor shapes
	enum class CursorShape : EnumSize
	{
		// The regular arrow cursor shape
		eArrow 	   = GLFW_ARROW_CURSOR,

		// The text input I-beam cursor shape
		eIbeam 	   = GLFW_IBEAM_CURSOR,

		// The crosshair shape
		eCrosshair = GLFW_CROSSHAIR_CURSOR,

		// The hand shape
		eHand 	   = GLFW_HAND_CURSOR,

		// The horizontal resize arrow shape
		eHresize   = GLFW_HRESIZE_CURSOR,

		// The vertical resize arrow shape
		eVresize   = GLFW_VRESIZE_CURSOR
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const CursorShape value) GLFW_HPP_NOEXCEPT
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

	// Connection events
	enum class Connection : EnumSize
	{
		eConnected 	  = GLFW_CONNECTED,
		eDisconnected = GLFW_DISCONNECTED
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const Connection value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case Connection::eConnected:	return "Connected";
		case Connection::eDisconnected:	return "Disconnected";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}

	// Init hints
	enum class InitHint : EnumSize
	{
		// Joystick hat buttons init hint
		eJoystickHatButtons  = GLFW_JOYSTICK_HAT_BUTTONS,

		// macOS specific init hint
		eCocoaChdirResources = GLFW_COCOA_CHDIR_RESOURCES,

		// macOS specific init hint
		eCocoaMenubar 		 = GLFW_COCOA_MENUBAR
	};

	GLFW_HPP_NODISCARD("") GLFW_HPP_CONSTEXPR_TO_STRING GLFW_HPP_STRING to_string(const InitHint value) GLFW_HPP_NOEXCEPT
	{
		switch(value)
		{
		case InitHint::eJoystickHatButtons:	 return "JoystickHatButtons";
		case InitHint::eCocoaChdirResources: return "CocoaChdirResources";
		case InitHint::eCocoaMenubar:		 return "CocoaMenubar";
		}

		return invalidValueToString(static_cast<EnumSize>(value));
	}
}

#endif // #ifndef GLFW_HPP
