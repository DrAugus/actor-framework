// This file is part of CAF, the C++ Actor Framework. See the file LICENSE in
// the main distribution directory for license terms and copyright or visit
// https://github.com/actor-framework/actor-framework/blob/master/LICENSE.

#pragma once

// this header must be generated by the build system (may be empty)
#include "caf/detail/build_config.hpp"

// Platform-specific adjustments.
#define CAF_CACHE_LINE_SIZE 64

// Config pararameters defined by the build system (usually CMake):
//
// CAF_ENABLE_RUNTIME_CHECKS:
//   - check requirements at runtime
//
// CAF_LOG_LEVEL:
//   - denotes the amount of logging, ranging from error messages only (0)
//     to complete traces (4)

/// Denotes version of CAF in the format {MAJOR}{MINOR}{PATCH},
/// whereas each number is a two-digit decimal number without
/// leading zeros (e.g. 900 is version 0.9.0).
#define CAF_VERSION 1901

/// Defined to the major version number of CAF.
#define CAF_MAJOR_VERSION (CAF_VERSION / 10000)

/// Defined to the minor version number of CAF.
#define CAF_MINOR_VERSION ((CAF_VERSION / 100) % 100)

/// Defined to the patch version number of CAF.
#define CAF_PATCH_VERSION (CAF_VERSION % 100)

// This compiler-specific block defines:
// - CAF_DEPRECATED to annotate deprecated functions
// - CAF_PUSH_WARNINGS/CAF_POP_WARNINGS to surround "noisy" header includes
// - CAF_ANNOTATE_FALLTHROUGH to suppress warnings in switch/case statements
// - CAF_COMPILER_VERSION to retrieve the compiler version in CAF_VERSION format
// - One of the following:
//   + CAF_CLANG
//   + CAF_GCC
//   + CAF_MSVC

// sets CAF_DEPRECATED, CAF_ANNOTATE_FALLTHROUGH,
// CAF_PUSH_WARNINGS and CAF_POP_WARNINGS
// clang-format off
#if defined(__clang__)
#  define CAF_CLANG
#  define CAF_LIKELY(x) __builtin_expect((x), 1)
#  define CAF_UNLIKELY(x) __builtin_expect((x), 0)
#  define CAF_DEPRECATED __attribute__((deprecated))
#  define CAF_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#  define CAF_PUSH_WARNINGS                                                    \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wall\"")                              \
    _Pragma("clang diagnostic ignored \"-Wextra\"")                            \
    _Pragma("clang diagnostic ignored \"-Wundef\"")                            \
    _Pragma("clang diagnostic ignored \"-Wshadow\"")                           \
    _Pragma("clang diagnostic ignored \"-Wdeprecated\"")                       \
    _Pragma("clang diagnostic ignored \"-Wextra-semi\"")                       \
    _Pragma("clang diagnostic ignored \"-Wconversion\"")                       \
    _Pragma("clang diagnostic ignored \"-Wcast-align\"")                       \
    _Pragma("clang diagnostic ignored \"-Wfloat-equal\"")                      \
    _Pragma("clang diagnostic ignored \"-Wswitch-enum\"")                      \
    _Pragma("clang diagnostic ignored \"-Wweak-vtables\"")                     \
    _Pragma("clang diagnostic ignored \"-Wdocumentation\"")                    \
    _Pragma("clang diagnostic ignored \"-Wold-style-cast\"")                   \
    _Pragma("clang diagnostic ignored \"-Wsign-conversion\"")                  \
    _Pragma("clang diagnostic ignored \"-Wunused-template\"")                  \
    _Pragma("clang diagnostic ignored \"-Wshorten-64-to-32\"")                 \
    _Pragma("clang diagnostic ignored \"-Wunreachable-code\"")                 \
    _Pragma("clang diagnostic ignored \"-Wdouble-promotion\"")                 \
    _Pragma("clang diagnostic ignored \"-Wc++14-extensions\"")                 \
    _Pragma("clang diagnostic ignored \"-Wunused-parameter\"")                 \
    _Pragma("clang diagnostic ignored \"-Wnested-anon-types\"")                \
    _Pragma("clang diagnostic ignored \"-Wreserved-id-macro\"")                \
    _Pragma("clang diagnostic ignored \"-Wconstant-conversion\"")              \
    _Pragma("clang diagnostic ignored \"-Wimplicit-fallthrough\"")             \
    _Pragma("clang diagnostic ignored \"-Wused-but-marked-unused\"")           \
    _Pragma("clang diagnostic ignored \"-Wdisabled-macro-expansion\"")
#  define CAF_PUSH_UNUSED_LABEL_WARNING                                        \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wunused-label\"")
#  define CAF_PUSH_NON_VIRTUAL_DTOR_WARNING                                    \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wnon-virtual-dtor\"")
#  define CAF_PUSH_DEPRECATED_WARNING                                          \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#  define CAF_POP_WARNINGS                                                     \
    _Pragma("clang diagnostic pop")
#  define CAF_ANNOTATE_FALLTHROUGH [[clang::fallthrough]]
#  define CAF_COMPILER_VERSION                                                 \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
#  define CAF_GCC
#  define CAF_LIKELY(x) __builtin_expect((x), 1)
#  define CAF_UNLIKELY(x) __builtin_expect((x), 0)
#  define CAF_DEPRECATED __attribute__((deprecated))
#  define CAF_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#  define CAF_PUSH_WARNINGS                                                    \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wshadow\"")                             \
    _Pragma("GCC diagnostic ignored \"-Wpragmas\"")                            \
    _Pragma("GCC diagnostic ignored \"-Wpedantic\"")                           \
    _Pragma("GCC diagnostic ignored \"-Wcast-qual\"")                          \
    _Pragma("GCC diagnostic ignored \"-Wconversion\"")                         \
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")                        \
    _Pragma("GCC diagnostic ignored \"-Wc++14-extensions\"")
#  define CAF_PUSH_UNUSED_LABEL_WARNING                                        \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wunused-label\"")
#  define CAF_PUSH_NON_VIRTUAL_DTOR_WARNING                                    \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wnon-virtual-dtor\"")
#  define CAF_PUSH_DEPRECATED_WARNING                                          \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#  define CAF_POP_WARNINGS                                                     \
    _Pragma("GCC diagnostic pop")
#  if __GNUC__ >= 7
#    define CAF_ANNOTATE_FALLTHROUGH __attribute__((fallthrough))
#  else
#    define CAF_ANNOTATE_FALLTHROUGH static_cast<void>(0)
#  endif
#  define CAF_COMPILER_VERSION                                                 \
     (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
    // disable thread_local on GCC/macOS due to heap-use-after-free bug:
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=67135
#elif defined(_MSC_VER)
#  define CAF_MSVC
#  define CAF_LIKELY(x) x
#  define CAF_UNLIKELY(x) x
#  define CAF_DEPRECATED
#  define CAF_DEPRECATED_MSG(msg)
#  define CAF_PUSH_WARNINGS                                                    \
    __pragma(warning(push))
#  define CAF_PUSH_UNUSED_LABEL_WARNING                                        \
    __pragma(warning(push))                                                    \
    __pragma(warning(disable: 4102))
#  define CAF_PUSH_DEPRECATED_WARNING                                          \
    __pragma(warning(push))
#  define CAF_PUSH_NON_VIRTUAL_DTOR_WARNING                                    \
    __pragma(warning(push))
#  define CAF_POP_WARNINGS __pragma(warning(pop))
#  define CAF_ANNOTATE_FALLTHROUGH static_cast<void>(0)
#  define CAF_COMPILER_VERSION _MSC_FULL_VER
#  pragma warning( disable : 4624 )
#  pragma warning( disable : 4800 )
#  pragma warning( disable : 4503 )
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif // NOMINMAX
#else
#  define CAF_LIKELY(x) x
#  define CAF_UNLIKELY(x) x
#  define CAF_DEPRECATED
#  define CAF_PUSH_WARNINGS
#  define CAF_PUSH_NON_VIRTUAL_DTOR_WARNING
#  define CAF_PUSH_DEPRECATED_WARNING
#  define CAF_POP_WARNINGS
#  define CAF_ANNOTATE_FALLTHROUGH static_cast<void>(0)
#endif
// clang-format on

// This OS-specific block defines one of the following:
// - CAF_MACOS
// - CAF_LINUX
// - CAF_BSD
// - CAF_WINDOWS
// It also defines CAF_POSIX for POSIX-compatible systems
#if defined(__APPLE__)
#  include "TargetConditionals.h"
#  if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#    define CAF_IOS
#  else
#    define CAF_MACOS
#    if defined(CAF_GCC) && !defined(_GLIBCXX_HAS_GTHREADS)
#      define _GLIBCXX_HAS_GTHREADS
#    endif
#  endif
#elif defined(__ANDROID__)
#  define CAF_ANDROID
#elif defined(__linux__)
#  define CAF_LINUX
#  include <linux/version.h>
#  if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 16)
#    define CAF_POLL_IMPL
#  endif
#elif defined(__FreeBSD__)
#  define CAF_BSD
#  define CAF_FREE_BSD
#elif defined(__NetBSD__)
#  define CAF_BSD
#  define CAF_NET_BSD
#elif defined(__OpenBSD__)
#  define CAF_BSD
#  define CAF_OPEN_BSD
#elif defined(__CYGWIN__)
#  define CAF_CYGWIN
#elif defined(WIN32) || defined(_WIN32)
#  define CAF_WINDOWS
#else
#  error Platform and/or compiler not supported
#endif
#if defined(CAF_MACOS) || defined(CAF_LINUX) || defined(CAF_BSD)               \
  || defined(CAF_CYGWIN) || defined(CAF_NET_BSD)
#  define CAF_POSIX
#endif

#if defined(CAF_WINDOWS) && defined(CAF_CLANG)
// Fix for issue with static_cast<> in objbase.h.
// See: https://github.com/philsquared/Catch/issues/690.
struct IUnknown;
#endif

#include <cstdio>
#include <cstdlib>

// Optionally enable CAF_ASSERT
#ifndef CAF_ENABLE_RUNTIME_CHECKS
#  define CAF_ASSERT(unused) static_cast<void>(0)
#elif defined(CAF_WINDOWS) || defined(CAF_BSD)
#  define CAF_ASSERT(stmt)                                                     \
    if (static_cast<bool>(stmt) == false) {                                    \
      printf("%s:%u: requirement failed '%s'\n", __FILE__, __LINE__, #stmt);   \
      ::abort();                                                               \
    }                                                                          \
    static_cast<void>(0)
#else // defined(CAF_LINUX) || defined(CAF_MACOS)
#  include <execinfo.h>
#  define CAF_ASSERT(stmt)                                                     \
    if (static_cast<bool>(stmt) == false) {                                    \
      printf("%s:%u: requirement failed '%s'\n", __FILE__, __LINE__, #stmt);   \
      void* array[20];                                                         \
      auto caf_bt_size = ::backtrace(array, 20);                               \
      ::backtrace_symbols_fd(array, caf_bt_size, 2);                           \
      ::abort();                                                               \
    }                                                                          \
    static_cast<void>(0)
#endif

// CAF_DEBUG_STMT(stmt): evaluates to stmt when compiling with runtime checks
//                       and to an empty expression otherwise.
#ifndef CAF_ENABLE_RUNTIME_CHECKS
#  define CAF_DEBUG_STMT(stmt) static_cast<void>(0)
#else
#  define CAF_DEBUG_STMT(stmt) stmt
#endif

// Convenience macros.
#define CAF_IGNORE_UNUSED(x) static_cast<void>(x)

/// Prints `error` to `stderr` and aborts program execution.
#define CAF_CRITICAL(error)                                                    \
  do {                                                                         \
    fprintf(stderr, "[FATAL] critical error (%s:%d): %s\n", __FILE__,          \
            __LINE__, error);                                                  \
    ::abort();                                                                 \
  } while (false)

/// Prints `error` to `stderr` and aborts program execution.
#define CAF_CRITICAL_FMT(fmt_str, ...)                                         \
  do {                                                                         \
    fprintf(stderr, "[FATAL] critical error (%s:%d): " fmt_str "\n", __FILE__, \
            __LINE__, __VA_ARGS__);                                            \
    ::abort();                                                                 \
  } while (false)
