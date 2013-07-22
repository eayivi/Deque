// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);
    }
    return b;
}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;
        }
    }
    catch (...) {
        destroy(a, p, x);
        throw;
    }
    return x;
}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;
        }
    }
    catch (...) {
        destroy(a, p, b);
        throw;
    }
    return e;
}

// -------
// MyDeque
// -------

template < typename T, typename A = std::allocator<T> >
class MyDeque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::equal()
            return true;
        }

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return true;
        }

    private:
        // ----
        // data
        // ----

        allocator_type _a;

        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;
        }

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename MyDeque::value_type      value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::pointer         pointer;
                typedef typename MyDeque::reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs an iterator reference
                 * @param rhs an iterator reference
                 * @return a bool
                 * checks to see if two iterators are equal to each other
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    if (lhs.p != rhs.p)
                        return false;
                    else
                        return true;
                }

                /**
                 * @param lhs an iterator reference
                 * @param rhs an iterator reference
                 * @return a bool
                 * checks to see if two iterators are not equal to each other
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);
                }

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs an iterator
                 * @param rhs a difference_type
                 * @return an iterator
                 * increments an iterator by rhs
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs an iterator
                 * @param rhs a difference_type
                 * @return an iterator
                 * decrements an iterator by rhs
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

            private:
                // ----
                // data
                // ----

                pointer p;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * @param x a pointer passed by value
                 * @return a new iterator
                 * constructs a new iterator pointing to an element's address
                 */
                iterator (pointer x) : p(x) {
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return a reference to the element being pointed to
                 * dereferences an iterator to access its data
                 */
                reference operator * () const {
                    return *(*this->p);
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * @return a pointer to an element
                 * gives the address an iterator points to
                 */
                pointer operator -> () const {
                    return &**this;
                }

                // -----------
                // operator ++
                // -----------

                /**
                 * @return an iterator reference
                 * increments an iterator by one
                 */
                iterator& operator ++ () {
                    ++(*this->p);
                    assert(valid());
                    return *this;
                }

                /**
                 * @return an iterator
                 * gives a copy of an iterator and increments the original by one
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator --
                // -----------

                /**
                 * @return an iterator reference
                 * decrements an iterator by one
                 */
                iterator& operator -- () {
                    --(*this->p);
                    assert(valid());
                    return *this;
                }

                /**
                 * @return an iterator
                 * gives a copy of an iterator and decrements the original by one
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d a difference_type
                 * @return an iterator reference
                 * increments an iterator by d
                 */
                iterator& operator += (difference_type d) {
                    (*this->p) += d;
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d a difference_type
                 * @return an iterator reference
                 * decrements an iterator by d
                 */
                iterator& operator -= (difference_type d) {
                    (*this->p) -= d;
                    assert(valid());
                    return *this;}
        };

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename MyDeque::value_type      value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::const_pointer   pointer;
                typedef typename MyDeque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs a const_iterator reference
                 * @param rhs a const_iterator reference
                 * @return a bool
                 * checks to see if two const_iterators are equal to each other
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    if (lhs.p != rhs.p)
                        return false;
                    else
                        return true;
                }

                /**
                 * @param lhs a const_iterator reference
                 * @param rhs a const_iterator reference
                 * @return a bool
                 * checks to see if two const_iterators are not equal to each other
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);
                }

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs a const_iterator
                 * @param rhs a difference_type
                 * @return a const_iterator
                 * increments a const_iterator by rhs
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs a const_iterator
                 * @param rhs a difference_type
                 * @return a const_iterator
                 * decrements a const_iterator by rhs
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

            private:
                // ----
                // data
                // ----

                pointer p;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * @param x a pointer passed by value
                 * @return a new const_iterator
                 * constructs a new const_iterator pointing to an element's address
                 */
                const_iterator (pointer x) : p(x) {
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return a reference to the element being pointed to
                 * dereferences a const_iterator to access its data
                 */
                reference operator * () const {
                    return *(*this->p);
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * @return a pointer to an element
                 * gives the address a const_iterator points to
                 */
                pointer operator -> () const {
                    return &**this;
                }

                // -----------
                // operator ++
                // -----------

                /**
                 * @return a const_iterator reference
                 * increments a const_iterator by one
                 */
                const_iterator& operator ++ () {
                    ++(*this->p);
                    assert(valid());
                    return *this;
                }

                /**
                 * @return a const_iterator
                 * gives a copy of a const_iterator and increments the original by one
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator --
                // -----------

                /**
                 * @return a const_iterator reference
                 * decrements a const_iterator by one
                 */
                const_iterator& operator -- () {
                    --(*this->p);
                    assert(valid());
                    return *this;
                }

                /**
                 * @return a const_iterator
                 * gives a copy of a const_iterator and decrements the original by one
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d a difference_type
                 * @return a const_iterator reference
                 * increments a const_iterator by d
                 */
                const_iterator& operator += (difference_type d) {
                    (*this->p) += d;
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d a difference_type
                 * @return a const_iterator reference
                 * decrements a const_iterator by d
                 */
                const_iterator& operator -= (difference_type d) {
                    (*this->p) -= d;
                    assert(valid());
                    return *this;
                }
        };

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        explicit MyDeque (const allocator_type& a = allocator_type()) {
            // <your code>
            assert(valid());
        }

        /**
         * <your documentation>
         */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) {
            // <your code>
            assert(valid());
        }

        /**
         * <your documentation>
         */
        MyDeque (const MyDeque& that) {
            // <your code>
            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~MyDeque () {
            // <your code>
            assert(valid());
        }

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         */
        MyDeque& operator = (const MyDeque& rhs) {
            // <your code>
            assert(valid());
            return *this;
        }

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);
        }

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<MyDeque*>(this)->at(index);
        }

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<MyDeque*>(this)->back();
        }

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {
            // <your code>
            return iterator(/* <your arguments> */);
        }

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(/* <your arguments> */);
        }

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            // <your code>
            assert(valid());
        }

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();
        }

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            // <your code>
            return iterator(/* <your arguments> */);
        }

        /**
         * <your documentation>
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(/* <your arguments> */);
        }

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();
        }

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();
        }

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();
        }

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            // <your code>
            assert(valid());
        }

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());
        }

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference) {
            // <your code>
            assert(valid());
        }

        /**
         * <your documentation>
         */
        void push_front (const_reference) {
            // <your code>
            assert(valid());
        }

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            assert(valid());
        }

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            // <your code>
            return 0;
        }

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (MyDeque&) {
            // <your code>
            assert(valid());
        }
};

#endif // Deque_h
