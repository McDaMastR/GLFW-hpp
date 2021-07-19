// glfw3.hpp - C++ binding for the GLFW library
// ! THIS BINDING IS NOT COMPLETED! MANY FEATURES MAY NOT WORK! MANY MACRO CONFIGURATIONS MAY NOT DO ANYTHING !

/*

=== User Information ===

Supported compilers: gcc, clang & msvc
If you are using a compiler not supported, you will have to define these macros before including this file:

	#define GLFW3_HPP_CPLUSPLUS // Contains the specific c++ standard (e.g. __cplusplus, _MSVC_LANG)
	#define GLFW3_HPP_CPP_VERSION // Contains the actual c++ standard (e.g. 11, 14, 17, 20)
	#define GLFW3_HPP_HAS_ATTRIBUTE(x) // Expands to whether the given attribute is available (e.g. __has_cpp_attribute(nodiscard))
	#define GLFW3_HPP_HAS_FEATURE(x) // Expands to whether the given feature is available (e.g. __has_feature(cxx_unrestricted_unions)) 
	#define GLFW3_HPP_UNRESTRICTED_UNIONS // Whether unrestricted unions are available
	#define GLFW3_HPP_INLINE // The keyword/attribute to force inline functions
	#define GLFW3_HPP_NOEXCEPT // The keyword/attribute to specify that a function will never raise an exception


Before including this file, you can define some macros to configure this file's binding.
Any macros not user defined will be automatically defined.
Macros:

	Basic configurations:
		#define GLFW3_HPP_INCLUDE_NATIVE // Includes glfw3native.h
		#define GLFW3_HPP_DISABLE_STANDARD_CONTAINERS // Disables standard container use (e.g. std::string), and instead uses c-style types (e.g. const char *)
		#define GLFW3_HPP_ASSERT(x) // Triggers an assertion in the program if the condition is false
		#define GLFW3_HPP_EXPLICIT // Enable or disable explicit constuctors and castings (default is explicit)
		#define GLFW3_HPP_NAMESPACE // Change the namespace name (e.g. glfw)

	Advanced configurations:
		#define GLFW3_HPP_NORETURN // The function will not return / will terminate the program (e.g. [[noreturn]])
		#define GLFW3_HPP_DEPRECATED(x) // The function is deprecated and should not be used (e.g. [[deprecated(x)]])
		#define GLFW3_HPP_FALLTHROUGH // The case in a switch statement will fallthrough into the next case (e.g. [[fallthrough]])
		#define GLFW3_HPP_MAYBE_UNUSED // The function/variable may not ever be used (e.g. [[maybe_unused]])
		#define GLFW3_HPP_NO_UNIQUE_ADDRESS // The variable does not take up any space in memory (e.g. [[no_unique_address]])
		#define GLFW3_HPP_LIKELY // The branch (if-else/switch case) is more likely to be gone into than another (e.g. [[likely]])
		#define GLFW3_HPP_UNLIKELY // The branch (if-else/switch case) is less likely to be gone into than another (e.g. [[unlikely]])
		#define GLFW3_HPP_NODISCARD(x) // The return value from a function should always be used (e.g. [[nodiscard(x)]])
		#define GLFW3_HPP_CONSTEVAL // The function must always produce a compile-time constant expression
		#define GLFW3_HPP_CONSTINIT // The static/global variable must be initalized at compile-time
		#define GLFW3_HPP_CONSTEXPR // The function/variable can be used at compile-time
		#define GLFW3_HPP_CONST_OR_CONSTEXPR // The variable should be constexpr, but can be const if constexpr is not usable
		#define GLFW3_HPP_NON_CONST_CONSTEXPR_METHOD // The method can be constexpr even if it is non-const
		#define GLFW3_HPP_CONSTEXPR_LAMBDA // The lambda can be constexpr
		#define GLFW3_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC // The function can use dynamic allocation at compile-time
		#define GLFW3_HPP_CONSTEXPR_DESTRUCTOR // The destructor can be constexpr
		#define GLFW3_HPP_CONSTEVAL_IF(x) // The if-else branch condition must be evaluated at compile-time
		#define GLFW3_HPP_CONSTEXPR_IF(x) // The if-else branch condition can be evaluated at compile-time
		#define GLFW3_HPP_STRINGIFY(x) // Turns the inputted data into a string

*/

#ifndef GLFW3_HPP
#define GLFW3_HPP

// === C++ Standard Information ===

#ifndef GLFW3_HPP_CPLUSPLUS
	#if   defined(_MSVC_LANG)
		#define GLFW3_HPP_CPLUSPLUS _MSVC_LANG
	#elif defined(__cplusplus)
		#define GLFW3_HPP_CPLUSPLUS __cplusplus
	#else
		#error "Unknown compiler; GLFW3_HPP_CPLUSPLUS requires user definition"
	#endif
#endif

#ifndef GLFW3_HPP_CPP_VERSION
	#if   GLFW3_HPP_CPLUSPLUS >  202002L
		#define GLFW3_HPP_CPP_VERSION 23
	#elif GLFW3_HPP_CPLUSPLUS == 202002L
		#define GLFW3_HPP_CPP_VERSION 20
	#elif GLFW3_HPP_CPLUSPLUS == 201703L
		#define GLFW3_HPP_CPP_VERSION 17
	#elif GLFW3_HPP_CPLUSPLUS == 201402L
		#define GLFW3_HPP_CPP_VERSION 14
	#elif GLFW3_HPP_CPLUSPLUS == 201103L
		#define GLFW3_HPP_CPP_VERSION 11
	#else 
		#error "glfw3.hpp requires c++ standard of at least c++11"
	#endif
#endif

// === Includes ===

#include <GLFW/glfw3.h>

#ifdef GLFW3_HPP_INCLUDE_NATIVE
	#include <GLFW/glfw3native.h>
#endif

#ifndef GLFW3_HPP_DISABLE_STANDARD_CONTAINERS
	#if GLFW3_HPP_CPP_VERSION >= 17
		#include <string_view>
		#define GLfW3_HPP_STRING std::string_view
	#else
		#include <string>
		#define GLfW3_HPP_STRING std::string
	#endif
#else
	#define GLfW3_HPP_STRING const char *
#endif

#ifndef GLFW3_HPP_ASSERT
	#include <cassert>
	#define GLFW3_HPP_ASSERT(x) assert(x)
#endif

#if __cpp_impl_three_way_comparison >= 201907L
	#define GLFW3_HPP_INCLUDE_COMPARE
	#include <compare>
#endif

// === Compiler-Specific Configurations ===

#if   defined(__clang__)
	#define GLFW3_HPP_CLANG_COMPILER
#elif defined(__GNUC__)
	#define GLFW3_HPP_GCC_COMPILER
	#define GLFW3_HPP_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
	#define GLFW3_HPP_MSVC_COMPILER
	#define GLFW3_HPP_COMPILER_VERSION _MSC_VER
#else 
	#define GLFW3_HPP_OTHER_COMPILER
#endif

#ifndef GLFW3_HPP_HAS_ATTRIBUTE
	#ifdef __has_cpp_attribute
		#define GLFW3_HPP_HAS_ATTRIBUTE(x) __has_cpp_attribute(x)
	#else
		#define GLFW3_HPP_HAS_ATTRIBUTE(x) 0
	#endif
#endif

#ifndef GLFW3_HPP_HAS_FEATURE
	#ifdef __has_feature
		#define GLFW3_HPP_HAS_FEATURE(x) __has_feature(x)
	#else
		#define GLFW3_HPP_HAS_FEATURE(x) 0
	#endif
#endif

#ifndef GLFW3_HPP_NORETURN
	#if GLFW3_HPP_HAS_ATTRIBUTE(noreturn) >= 200809L
		#define GLFW3_HPP_NORETURN [[noreturn]]
	#else
		#define GLFW3_HPP_NORETURN
	#endif
#endif

#ifndef GLFW3_HPP_DEPRECATED
	#if GLFW3_HPP_HAS_ATTRIBUTE(deprecated) >= 201309L
		#define GLFW3_HPP_DEPRECATED(x) [[deprecated(x)]]
	#else
		#define GLFW3_HPP_DEPRECATED(x)
	#endif
#endif

#ifndef GLFW3_HPP_FALLTHROUGH
	#if GLFW3_HPP_HAS_ATTRIBUTE(fallthrough) >= 201603L
		#define GLFW3_HPP_FALLTHROUGH [[fallthrough]]
	#else
		#define GLFW3_HPP_FALLTHROUGH
	#endif
#endif

#ifndef GLFW3_HPP_MAYBE_UNUSED
	#if GLFW3_HPP_HAS_ATTRIBUTE(maybe_unused) >= 201603L
		#define GLFW3_HPP_MAYBE_UNUSED [[maybe_unused]]
	#else
		#define GLFW3_HPP_MAYBE_UNUSED
	#endif
#endif

#ifndef GLFW3_HPP_NO_UNIQUE_ADDRESS
	#if GLFW3_HPP_HAS_ATTRIBUTE(no_unique_address) >= 201803L
		#define GLFW3_HPP_NO_UNIQUE_ADDRESS [[no_unique_address]]
	#else
		#define GLFW3_HPP_NO_UNIQUE_ADDRESS
	#endif
#endif

#ifndef GLFW3_HPP_LIKELY
	#if GLFW3_HPP_HAS_ATTRIBUTE(likely) >= 201803L
		#define GLFW3_HPP_LIKELY [[likely]]
	#else
		#define GLFW3_HPP_LIKELY
	#endif
#endif

#ifndef GLFW3_HPP_UNLIKELY
	#if GLFW3_HPP_HAS_ATTRIBUTE(unlikely) >= 201803L
		#define GLFW3_HPP_UNLIKELY [[unlikely]]
	#else
		#define GLFW3_HPP_UNLIKELY
	#endif
#endif

#ifndef GLFW3_HPP_NODISCARD
	#if   GLFW3_HPP_HAS_ATTRIBUTE(nodiscard) >= 201907L
		#define GLFW3_HPP_NODISCARD(x) [[nodiscard(x)]]
	#elif GLFW3_HPP_HAS_ATTRIBUTE(nodiscard) >= 201603L
		#define GLFW3_HPP_NODISCARD(x) [[nodiscard]]
	#else
		#define GLFW3_HPP_NODISCARD(x)
	#endif
#endif

#ifndef GLFW3_HPP_EXPLICIT
	#define GLFW3_HPP_EXPLICIT explicit // Defaults to explicit constructors and casts
#endif

#ifndef GLFW3_HPP_CONSTEVAL
	#if __cpp_consteval >= 201811L
		#define GLFW3_HPP_CONSTEVAL consteval
	#else
		#define GLFW3_HPP_CONSTEVAL
	#endif
#endif

#ifndef GLFW3_HPP_CONSTINIT
	#if __cpp_constinit >= 201907L
		#define GLFW3_HPP_CONSTINIT constinit
	#else
		#define GLFW3_HPP_CONSTINIT
	#endif
#endif

#ifndef GLFW3_HPP_CONSTEXPR
	#if __cpp_constexpr >= 200704L
		#define GLFW3_HPP_CONSTEXPR constexpr
	#else
		#define GLFW3_HPP_CONSTEXPR
	#endif
#endif

#ifndef GLFW3_HPP_CONST_OR_CONSTEXPR
	#if __cpp_constexpr >= 200704L
		#define GLFW3_HPP_CONST_OR_CONSTEXPR constexpr
	#else
		#define GLFW3_HPP_CONST_OR_CONSTEXPR const
	#endif
#endif

#ifndef GLFW3_HPP_NON_CONST_CONSTEXPR_METHOD
	#if __cpp_constexpr >= 201304L
		#define GLFW3_HPP_NON_CONST_CONSTEXPR_METHOD constexpr
	#else
		#define GLFW3_HPP_NON_CONST_CONSTEXPR_METHOD
	#endif
#endif

#ifndef GLFW3_HPP_CONSTEXPR_LAMBDA
	#if __cpp_constexpr >= 201603L
		#define GLFW3_HPP_CONSTEXPR_LAMBDA constexpr
	#else
		#define GLFW3_HPP_CONSTEXPR_LAMBDA const
	#endif
#endif

#ifndef GLFW3_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC
	#if __cpp_constexpr_dynamic_alloc >= 201907L
		#define GLFW3_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC constexpr
	#else
		#define GLFW3_HPP_CONSTEXPR_WITH_DYNAMIC_ALLOC
	#endif
#endif

#ifndef GLFW3_HPP_CONSTEXPR_DESTRUCTOR
	#if GLFW3_HPP_CPP_VERSION >= 20
		#define GLFW3_HPP_CONSTEXPR_DESTRUCTOR constexpr
	#else
		#define GLFW3_HPP_CONSTEXPR_DESTRUCTOR
	#endif
#endif

#ifndef GLFW3_HPP_CONSTEVAL_IF
	#if   __cpp_if_consteval >= 202106L
		#define GLFW3_HPP_CONSTEVAL_IF(x) if consteval(x)
	#elif __cpp_if_constexpr >= 201606L
		#define GLFW3_HPP_CONSTEVAL_IF(x) if constexpr(x)
	#else
		#define GLFW3_HPP_CONSTEVAL_IF(x) if(x)
	#endif
#endif

#ifndef GLFW3_HPP_CONSTEXPR_IF
	#if __cpp_if_constexpr >= 201606L
		#define GLFW3_HPP_CONSTEXPR_IF(x) if constexpr(x)
	#else
		#define GLFW3_HPP_CONSTEXPR_IF(x) if(x)
	#endif
#endif

#ifndef GLFW3_HPP_UNRESTRICTED_UNIONS
	#if   defined(GLFW3_HPP_CLANG_COMPILER)
		#if GLFW3_HPP_HAS_FEATURE(cxx_unrestricted_unions)
			#define GLFW3_HPP_UNRESTRICTED_UNIONS
		#endif
	#elif defined(GLFW3_HPP_GCC_COMPILER)
		#if GLFW3_HPP_COMPILER_VERSION >= 40600
			#define GLFW3_HPP_UNRESTRICTED_UNIONS
		#endif
	#elif defined(GLFW3_HPP_MSVC_COMPILER)
		#if GLFW3_HPP_COMPILER_VERSION >= 1900
			#define GLFW3_HPP_UNRESTRICTED_UNIONS
		#endif
	#endif
#endif

#ifndef GLFW3_HPP_INLINE
	#if   defined(GLFW3_HPP_CLANG_COMPILER)
		#if GLFW3_HPP_HAS_ATTRIBUTE(always_inline)
			#define GLFW3_HPP_INLINE __attribute__((always_inline)) __inline__
		#else
			#define GLFW3_HPP_INLINE inline
		#endif
	#elif defined(GLFW3_HPP_GCC_COMPILER)
		#define GLFW3_HPP_INLINE __attribute__((always_inline)) __inline__
	#elif defined(GLFW3_HPP_MSVC_COMPILER)
		#define GLFW3_HPP_INLINE inline
	#else
		#error "Unknown compiler; GLFW3_HPP_INLINE requires user definition"
	#endif
#endif

#ifndef GLFW3_HPP_NOEXCEPT
	#if   defined(GLFW3_HPP_GCC_COMPILER)
		#define GLFW3_HPP_NOEXCEPT noexcept
	#elif defined(GLFW3_HPP_CLANG_COMPILER)
		#define GLFW3_HPP_NOEXCEPT noexcept
	#elif defined(GLFW3_HPP_MSVC_COMPILER)
		#if GLFW3_HPP_COMPILER_VERSION > 1800
			#define GLFW3_HPP_NOEXCEPT noexcept
		#else
			#define GLFW3_HPP_NOEXCEPT
		#endif
	#endif
#endif

// === Namespace Configurations ===

#ifndef GLFW3_HPP_NAMESPACE
	#define GLFW3_HPP_NAMESPACE glfw
#endif

#ifndef GLFW3_HPP_STRINGIFY
	#define GLFW3_HPP_STRINGIFY(x) #x
#endif

// === Begin the Namespace ===

namespace GLFW3_HPP_NAMESPACE
{
	
}

#endif // #ifndef GLFW3_HPP
