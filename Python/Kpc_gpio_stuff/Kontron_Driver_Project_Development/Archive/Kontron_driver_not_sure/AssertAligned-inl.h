// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.


template <class T>
inline const void * AssertAligned(const void * pointer)
{
    if (reinterpret_cast<std::uintptr_t>(pointer) % std::alignment_of<T>::value != 0)
    {
        throw std::invalid_argument("pointer is not aligned properly.");
    }
    return pointer;
}

template <class T>
inline void * AssertAligned(void * pointer)
{
    if (reinterpret_cast<std::uintptr_t>(pointer) % std::alignment_of<T>::value != 0)
    {
        throw std::invalid_argument("pointer is not aligned properly.");
    }
    return pointer;
}


