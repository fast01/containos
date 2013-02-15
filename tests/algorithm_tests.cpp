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
#include "unitos/unitos.h"
#include "containos/algorithm.h"
#include "containos/list.h"

namespace c = containos;

namespace {

struct Mallocator
{
    static void* alloc(size_t size, size_t align)   { return ::malloc(size); }
    static void  dealloc(void* ptr)                 { ::free(ptr); }
};

struct Complex
{
    Complex() : m_i(666) { m_value = new int(333); }
    Complex(int i, int value) : m_i(i) { m_value = new int(value); }
    ~Complex() { delete m_value; }
    int i() const { return m_i; }
    int& value() const { return *m_value; }
private:
    int m_i;
    int* m_value;
};

}

TEST_SUITE(Algorithm)
{
    TEST(SortList)
    {
        c::List<int,Mallocator> list(5);
        list.insert(5);
        list.insert(1);
        list.insert(8);
        list.insert(2);
        list.insert(5);

        c::sort(list.begin(), list.end(),
            [](int a, int b) -> bool {
                return a < b;
            } );
        EXPECT_EQUAL(list[0], 1);
        EXPECT_EQUAL(list[1], 2);
        EXPECT_EQUAL(list[2], 5);
        EXPECT_EQUAL(list[3], 5);
        EXPECT_EQUAL(list[4], 8);
    }

    TEST(UniqueList)
    {
        c::List<int,Mallocator> list(6);
        list.insert(1);
        list.insert(3);
        list.insert(3);
        list.insert(3);
        list.insert(2);
        list.insert(2);
        
        c::List<int,Mallocator>::iterator newEnd = c::unique(list.begin(), list.end(),
            [](int a, int b) -> bool {
                return a == b;
            } );
        EXPECT_EQUAL(list.size(), 6);
        list.resize(newEnd);
        EXPECT_EQUAL(list.size(), 3);
        EXPECT_EQUAL(list[0], 1);
        EXPECT_EQUAL(list[1], 3);
        EXPECT_EQUAL(list[2], 2);
    }

    TEST(MergeList)
    {
        c::List<Complex,Mallocator> list(6);
        list.insert(Complex(1,10));
        list.insert(Complex(2,4));
        list.insert(Complex(2,8));
        list.insert(Complex(3,1));
        list.insert(Complex(3,100));
        list.insert(Complex(3,2));

        c::List<Complex,Mallocator>::iterator newEnd = c::mergeSame(list.begin(), list.end(),
            [](const Complex& a, const Complex& b) -> bool {
                return a.i() == b.i();
            },
            [](Complex& a, const Complex& b) {
                a.value() += b.value();
            } );
        EXPECT_EQUAL(list.size(), 6);
        list.resizeNoCopy(newEnd);
        EXPECT_EQUAL(list.size(), 3);
        EXPECT_EQUAL(list[0].i(), 1);
        EXPECT_EQUAL(list[1].i(), 2);
        EXPECT_EQUAL(list[2].i(), 3);
        EXPECT_EQUAL(list[0].value(), 10);
        EXPECT_EQUAL(list[1].value(), 12);
        EXPECT_EQUAL(list[2].value(), 103);
    }
}
