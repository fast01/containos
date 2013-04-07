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
#ifndef containos_undolist_h
#define containos_undolist_h

#include "containos/container.h"
#include "containos/list.h"

namespace containos {

class UndoCommand
{
public:
    virtual ~UndoCommand() {};
    virtual void reverse() = 0;
};

template<typename Allocator = Mallocator>
class UndoList : protected Container<Allocator>
{
    typedef Container<Allocator> Base;
public:
    ~UndoList();
    UndoList(size_t capacity = 0);

    template<typename T>
    void add();
    template<typename T,typename A>
    void add(A a);
    template<typename T,typename A,typename B>
    void add(A a, B b);
    template<typename T,typename A,typename B,typename C>
    void add(A a, B b, C c);
    template<typename T,typename A,typename B,typename C,typename D>
    void add(A a, B b, C c, D d);
    void undo(size_t count = 1);
    void redo(size_t count = 1);

    void clearHistory();
    void clearFuture();
    void clear();

    size_t undoCount() const;
    size_t redoCount() const;
    bool isUndoAllowed() const;
    bool isRedoAllowed() const;

private:
    typedef List<UndoCommand*,Allocator,ListGrowRule<64> > CommandStack;
    CommandStack m_commandStack;
    size_t m_currentIndex;
};

} // end of containos

#include "containos/undolist.inl"

#endif