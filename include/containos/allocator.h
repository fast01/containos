/*=============================================================================

Copyright (c) 2013 Ville Ruusutie

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
#ifndef containos_allocator_h
#define containos_allocator_h

namespace containos {

class Allocator
{
public:
    virtual ~Allocator() {}

    virtual void* alloc(size_t size, size_t alignment) = 0;
    virtual void* realloc(void* oldPtr, size_t size, size_t alignment) = 0;
    virtual void  dealloc(void* ptr) = 0;
};
//----------------------------------------------------------------------------

struct DefaultAllocator : public Allocator
{
    virtual ~DefaultAllocator();

    virtual void* alloc(size_t size, size_t alignment);
    virtual void* realloc(void* oldPtr, size_t size, size_t alignment);
    virtual void  dealloc(void* ptr);

    static DefaultAllocator* instance();
};

} // end of containos

#endif
