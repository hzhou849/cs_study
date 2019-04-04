// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_OS_UTILITIES_ALIGNED_H
#define EINSTEIN_OS_UTILITIES_ALIGNED_H

#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace einstein  //SUPPRESS: Code Before #include
//REASON:   Including the implementation of inline methods at the end of the file is required by
//          the coding standard.
{
namespace os
{
namespace utilities
{

/// \throw std::invalid_argument if pointer is not aligned the same as T
/// \return The unmodified pointer
template <class T>
const void * AssertAligned(const void * pointer);

/// \throw std::invalid_argument if pointer is not aligned the same as T
/// \return The unmodified pointer
template <class T>
void * AssertAligned(void * pointer);

}
}
}

#include "AssertAligned-inl.h"

#endif //EINSTEIN_OS_UTILITIES_ALIGNED_H
