// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h
#define BLOCK_WIDTH 20

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

        typedef A                                                   allocator_type;
        typedef typename allocator_type::value_type                 value_type;

        typedef typename allocator_type::size_type                  size_type;
        typedef typename allocator_type::difference_type            difference_type;

        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        
        typedef typename allocator_type::template rebind<T*>::other p_allocator_type;
        typedef typename p_allocator_type::pointer                  p_pointer;
        
    public:
        // -----------
        // operator ==
        // -----------

        /**
         * @param lhs a MyDeque reference
         * @param rhs a MyDeque reference
         * @return a bool
         * checks if two MyDeque objects are equal to each other
         */
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        // ----------
        // operator <
        // ----------

        /**
         * @param lhs a MyDeque reference
         * @param rhs a MyDeque reference
         * @return a bool
         * checks if a MyDeque object is less than the other
         */
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

    private:
        // ----
        // data
        // ----

        allocator_type _a;
        p_allocator_type _p;

        p_pointer _top;
        p_pointer _bottom;
        
        pointer _b;
        pointer _e;
        
        size_type block_size;
        
        pointer _beg_total;     // total allocated space
        pointer _end_total;
        pointer _beg_used;      // total used space
        pointer _end_used;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return (!_top && !_bottom && !_b && !_e /*&& !_beg_total && !_end_total && !_beg_used && !_end_used*/) || 
                    ((_top <= _bottom) && (_b <= _e) /*&& (_beg_total <= _beg_used) && (_end_used <= _end_total)*/);
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
         * @param a an allocator_type reference
         * @return a MyDeque object
         * makes a new MyDeque object from an allocator_type
         */
        explicit MyDeque (const allocator_type& a = allocator_type()) :
                _a (a), _p () {
            _top = _bottom = 0;
            _b = _e = 0;
            _beg_total = _end_total = _beg_used = _end_used = 0;
            block_size = 0;
            
            assert(valid());
        }

        /**
         * @param s a size_type
         * @param v a const_reference
         * @param a an allocator_type reference
         * @return a MyDeque object
         * makes a new MyDeque object of size s and fills it with value v
         */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) :
                _a (a), _p () {
            size_type num_blocks = s / BLOCK_WIDTH;
            if (s % BLOCK_WIDTH) {
                ++num_blocks;
            }
            block_size = num_blocks;
                        
            _top = _p.allocate(2 * num_blocks);
            _bottom = _top + num_blocks;
            
            p_pointer temp = _top;
            while (_top != _bottom) {
                *_top = _a.allocate(BLOCK_WIDTH);
                ++_top;
            }
            _top = temp;
            
            _b = _top[0];
            
            size_type remainder = BLOCK_WIDTH;
            if (s % BLOCK_WIDTH != 0) {
                remainder -= BLOCK_WIDTH * num_blocks - s;
            }
            _e = _top[num_blocks - 1] + remainder;
            
            //uninitialized_fill(_a, begin(), end(), v);
            
            assert(valid());
        }

        /**
         * @param that a MyDeque reference
         * @return a MyDeque object
         * makes a new MyDeque object with the contents of another MyDeque object
         */
        MyDeque (const MyDeque& that) :
                _a (that._a), _p (that._p) {
            _top = _p.allocate(that.block_size);
            _bottom = _top + that.block_size;
            
            p_pointer temp = _top;
            while (_top != _bottom) {
                *_top = _a.allocate(BLOCK_WIDTH);
                ++_top;
            }
            _top = temp;
            
            _b = that._b;
            _e = that._e;
            
            //uninitialized_copy(_a, that.begin(), that.end(), begin());
                    
            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
         * destroys a MyDeque object
         */
        ~MyDeque () {
            if (_top) {
                clear();
                
                p_pointer temp = _top;
                while (_top != _bottom) {
                    _a.deallocate(*_top, BLOCK_WIDTH);
                    ++_top;
                }
                _top = temp;
                
                _p.deallocate(_top, block_size);
            }
            
            assert(valid());
        }

        // ----------
        // operator =
        // ----------

        /**
         * @param rhs a MyDeque reference
         * @return a MyDeque reference
         * assigns the contents of one MyDeque object to another
         */
        MyDeque& operator = (const MyDeque& rhs) {
            if (this == &rhs) {
                return *this;
            }
            
            size_type capacity = block_size * BLOCK_WIDTH;
            if (rhs.size() == size()) {
                std::copy(rhs.begin(), rhs.end(), begin());
            }
            else if (rhs.size() < size()) {
                std::copy(rhs.begin(), rhs.end(), begin());
                resize(rhs.size());
            }
            else if (rhs.size() <= capacity) {
                std::copy(rhs.begin(), rhs.begin() + size(), begin());
                _e = uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());}
            else {
                clear();
                MyDeque copy(rhs.size());
                swap(copy);
            }
            
            assert(valid());
            return *this;
        }

        // -----------
        // operator []
        // -----------

        /**
         * @param index a size_type
         * @return a reference
         * gives the element a MyDeque contains at index
         */
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * @param index a size_type
         * @return a const_reference
         * gives the element a MyDeque contains at index
         */
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);
        }

        // --
        // at
        // --

        /**
         * @param index a size_type
         * @return a reference
         * @throws out_of_range if (index < 0) or (index >= size())
         * gives the element a MyDeque contains at index
         */
        reference at (size_type index) {
            if ( (index < 0) || (index >= size()) ) {
                throw std::out_of_range("ERROR: invalid index!");
            }
            return (*this)[index];
        }

        /**
         * @param index a size_type
         * @return a const_reference
         * gives the element a MyDeque contains at index
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
         * @return a size_type
         * gives current number of elements in a MyDeque
         */
        size_type size () const {
            if (_top == 0) {
                return 0;
            }
            
            size_type offset = BLOCK_WIDTH - (_e - _top[block_size-1]);
            size_type result = block_size * BLOCK_WIDTH - offset;
            return result;
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
