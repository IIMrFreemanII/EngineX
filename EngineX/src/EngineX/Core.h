#pragma once

#include "Log.h"

#ifdef EX_DEBUG
    #define EX_ENABLE_ASSERTS
#endif

#ifdef EX_ENABLE_ASSERTS
    #define EX_ASSERT(x, ...) { if(!(x)) { EX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EX_CORE_ASSERT(x, ...) { if(!(x)) { EX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define EX_ASSERT(x, ...)
    #define EX_CORE_ASSERT(x, ...)
#endif

namespace EngineX {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}