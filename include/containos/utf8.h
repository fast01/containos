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
#ifndef containos_utf8_h
#define containos_utf8_h

#include "containos/common.h"
#include "containos/allocator.h"

namespace containos {

// Slice of utf8 container
struct Utf8Slice
{
    bool operator==(Utf8Slice const& slice) const;
    bool operator!=(Utf8Slice const& slice) const;
    bool operator==(char const* str) const;
    bool operator!=(char const* str) const;
    bool operator==(wchar_t const* str) const;
    bool operator!=(wchar_t const* str) const;

    uint8_t const* data() const;
    size_t dataCount() const;
    size_t length() const;

    uint8_t const* m_begin;
    uint8_t const* m_end;
};

// Utf8 container
class Utf8
{
public:
    struct const_iterator {
        const_iterator(uint8_t const* ptr);
        bool operator==(const_iterator const& other) const;
        bool operator!=(const_iterator const& other) const;
        uint8_t const* ptr() const;
        uint32_t operator*() const;
        bool isRejected() const;
        void operator++();
    private:
        uint8_t const* m_ptr;
        uint32_t m_state;
    };

    ~Utf8();
    Utf8();
    Utf8(size_t capacity);
    Utf8(size_t capacity, Allocator* allocator);
    Utf8(Utf8 const& other);
    Utf8(Utf8Slice const& other);
    explicit Utf8(char const* str);
    explicit Utf8(char const* str, size_t count);
    explicit Utf8(wchar_t const* str);
    explicit Utf8(wchar_t const* str, size_t count);
    explicit Utf8(uint8_t const* str);
    explicit Utf8(uint8_t const* str, size_t count);
    explicit Utf8(uint16_t const* str);
    explicit Utf8(uint16_t const* str, size_t count);
    explicit Utf8(uint32_t const* str);
    explicit Utf8(uint32_t const* str, size_t count);
    template<size_t Count> Utf8(char const (&str)[Count]);
    template<size_t Count> Utf8(wchar_t const (&str)[Count]);

    void reserve(size_t capacity);
    void reserve(size_t capacity, Allocator* allocator);
    void clear();

    void set(Utf8 const& other);
    void set(Utf8Slice const& other);
    void set(char const* str);
    void set(char const* str, size_t count);
    void set(wchar_t const* str);
    void set(wchar_t const* str, size_t count);
    void set(uint8_t const* str);
    void set(uint8_t const* str, size_t count);
    void set(uint16_t const* str);
    void set(uint16_t const* str, size_t count);
    void set(uint32_t const* str);
    void set(uint32_t const* str, size_t count);
    template<size_t Count> void set(char const (&str)[Count]);
    template<size_t Count> void set(wchar_t const (&str)[Count]);

    void append(char ch);
    void append(wchar_t ch);
    void append(uint32_t codepoint);
    void append(Utf8 const& other);
    void append(Utf8Slice const& slice);
    void append(char const* str);
    void append(char const* str, size_t count);
    void append(wchar_t const* str);
    void append(wchar_t const* str, size_t count);
    void append(uint8_t const* str);
    void append(uint8_t const* str, size_t count);
    void append(uint16_t const* str);
    void append(uint16_t const* str, size_t count);
    void append(uint32_t const* str);
    void append(uint32_t const* str, size_t count);
    template<size_t Count> void append(char const (&str)[Count]);
    template<size_t Count> void append(wchar_t const (&str)[Count]);

    void clone(Utf8 const& from);
    void replace(char from, char to);
    void trim(Utf8Slice const& slice);
    void fix();

    bool convertTo(char* buffer, size_t count) const;
    void convertTo(wchar_t* buffer, size_t count) const;
    void convertTo(uint16_t* buffer, size_t count) const;
    void convertTo(uint32_t* buffer, size_t count) const;

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator findFirst(uint32_t codepoint) const;
    const_iterator findLast(uint32_t codepoint) const;
    const_iterator findFirst(const_iterator start, uint32_t codepoint) const;
    const_iterator findLast(const_iterator start, uint32_t codepoint) const;
    Utf8Slice slice(const_iterator begin, const_iterator end) const;
    Utf8Slice slice(const_iterator end) const;
    Utf8Slice slice() const;

    uint8_t const* data() const;
    size_t dataCount() const;
    size_t capacity() const;
    size_t length() const;
    bool isValid() const;

    void operator=(Utf8 const& other);
    void operator=(Utf8Slice const& slice);

    bool operator==(Utf8 const& other) const;
    bool operator!=(Utf8 const& other) const;
    bool operator==(Utf8Slice const& slice) const;
    bool operator!=(Utf8Slice const& slice) const;
    bool operator==(char const* str) const;
    bool operator!=(char const* str) const;
    bool operator==(wchar_t const* str) const;
    bool operator!=(wchar_t const* str) const;
    bool operator==(uint8_t const* str) const;
    bool operator!=(uint8_t const* str) const;
    bool operator==(uint16_t const* str) const;
    bool operator!=(uint16_t const* str) const;
    bool operator==(uint32_t const* str) const;
    bool operator!=(uint32_t const* str) const;

private:
    void destruct();

    struct Buffer;
    Buffer* m_buffer;
    size_t m_length;
};

} // end of containos

#include "containos/utf8.inl"

#endif
