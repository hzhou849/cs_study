// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.


#include <cstdint>
#include <stdexcept>
#include <type_traits>


/// \throw std::invalid_argument if pointer is not aligned the same as T
/// \return The unmodified pointer
template <class T>
const void * AssertAligned(const void * pointer);

/// \throw std::invalid_argument if pointer is not aligned the same as T
/// \return The unmodified pointer
template <class T>
void * AssertAligned(void * pointer);


#include "AssertAligned-inl.h"


