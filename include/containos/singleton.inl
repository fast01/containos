/*=============================================================================

Copyright (c) 2007-2013 Ville Ruusutie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

=============================================================================*/
#pragma once
#ifndef containos_singleton_inl
#define containos_singleton_inl

namespace containos {

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
__forceinline void Singleton<T>::createInstance()
{
    containos_assert(!hasInstance());
    Singleton<T>::instance = containos_new(T)();
}

template<typename T>
__forceinline void Singleton<T>::deleteInstance()
{
    containos_assert(hasInstance());
    containos_delete(Singleton<T>::instance);
    Singleton<T>::instance = nullptr;
}

template<typename T>
__forceinline bool Singleton<T>::hasInstance()
{
    return Singleton<T>::instance != nullptr;
}

template<typename T>
__forceinline T& Singleton<T>::getInstance()
{
    containos_assert(hasInstance());
    return *(Singleton<T>::instance);
}

} // end of korppu

#endif
