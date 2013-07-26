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

        p_pointer _top;         // Top of the outer container (beyond filled area)
        p_pointer _bottom; 
        
        size_type _u_top;       //top of filled area in outer container
        size_type _u_bottom;
        
        pointer _b;             // beginning of filled area in inner container
        pointer _e;
        
        size_type block_size;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return (!_top && !_bottom && !_b && !_e) || ((_top <= _bottom) && (_b <= _e));
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
                    return lhs.i == rhs.i && lhs.j == rhs.j;
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

                MyDeque*  p;
                size_type i;
                size_type j;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return i >= 0 && j >= 0;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * @param x a MyDeque pointer
                 * @param y a size_type
                 * @param z a size_type
                 * @return a new iterator
                 * constructs a new iterator pointing to an element's address
                 */
                iterator (MyDeque* x, size_type y, size_type z) : p(x) {
                    i = y;
                    j = z;
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
                    return *(p->_top[i] + j);
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
                    if (&p->_top[i][j] == &p->_top[i][BLOCK_WIDTH - 1]) {
                        ++i;
                        j = 0;
                    }
                    else {
                        ++j;
                    }
                    
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
                    if (&p->_top[i][j] == &p->_top[i][0]) {
                        --i;
                        j = BLOCK_WIDTH;
                    }
                    else {
                        --j;
                    }
                    
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
                    if ( (&p->_top[i][j] - &p->_top[i][0]) + d > BLOCK_WIDTH ) {
                        size_type block_jump = ( (&p->_top[i][j] - &p->_top[i][0]) + d) / BLOCK_WIDTH;
                        i += block_jump;
                        
                        size_type temp = (BLOCK_WIDTH * ++block_jump) - d;
                        j = BLOCK_WIDTH - temp;
                    }
                    else {
                        j += d;
                    }
                    
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
                    if ( -(&p->_top[i][j] - &p->_top[i][0]) - d < 0 ) {
                        size_type block_jump = ( -(&p->_top[i][j] - &p->_top[i][0]) - d) / BLOCK_WIDTH;
                        i += block_jump;
                        j = BLOCK_WIDTH * -block_jump - d + 1;
                    }
                    else {
                        j -= d;
                    }
                    
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
                    return lhs.i == rhs.i && lhs.j == rhs.j;
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

                const MyDeque*  p;
                size_type i;
                size_type j;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return i >= 0 && j >= 0;
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * @param x a MyDeque pointer
                 * @param y a size_type
                 * @param z a size_type
                 * @return a new const_iterator
                 * constructs a new const_iterator pointing to an element's address
                 */
                const_iterator (const MyDeque* x, size_type y, size_type z) : p(x) {
                    i = y;
                    j = z;
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
                    return p->_top[i][j];
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
                    if (&p->_top[i][j] == &p->_top[i][BLOCK_WIDTH - 1]) {
                        ++i;
                        j = 0;
                    }
                    else {
                        ++j;
                    }
                    
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
                    if (&p->_top[i][j] == &p->_top[i][0]) {
                        --i;
                        j = BLOCK_WIDTH;
                    }
                    else {
                        --j;
                    }
                    
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
                    if ( (&p->_top[i][j] - &p->_top[i][0]) + d > BLOCK_WIDTH ) {
                        size_type block_jump = ( (&p->_top[i][j] - &p->_top[i][0]) + d) / BLOCK_WIDTH;
                        i += block_jump;
                        j = BLOCK_WIDTH * block_jump - d;
                    }
                    else {
                        j += d;
                    }
                    
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
                    if ( -(&p->_top[i][j] - &p->_top[i][0]) - d < 0 ) {
                        size_type block_jump = ( -(&p->_top[i][j] - &p->_top[i][0]) - d) / BLOCK_WIDTH;
                        i += block_jump;
                        j = BLOCK_WIDTH * -block_jump - d + 1;
                    }
                    else {
                        j -= d;
                    }
                    
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
            block_size = _u_top = _u_bottom = 0;
            
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
                        
            _top = _p.allocate(num_blocks);
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
            
            _u_top = 0;
            _u_bottom = num_blocks - 1;
            
            uninitialized_fill(_a, begin(), end(), v);
            
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
                        
            block_size = that.block_size;
            
            std::cout << "BLOCK_SIZE: " << block_size << std::endl;
            
            p_pointer temp = _top;
            while (_top != _bottom) {
                *_top = _a.allocate(BLOCK_WIDTH);
                ++_top;
            }
            _top = temp;

            _u_top = that._u_top;
            _u_bottom = that._u_bottom;
            
            std::cout << "_U_TOP: " << _u_top << std::endl;
            std::cout << "_U_BOTTOM: " << _u_bottom << std::endl;
            
            _b = _top[_u_top] + (that._b - that._top[that._u_top]);
            _e = _top[_u_bottom];// + (that._e - that._bottom[that._u_bottom]);
            
            uninitialized_copy(_a, that.begin(), that.end(), begin());
            
            int i = 0;
            for(typename MyDeque::iterator x = begin(); x != end(); ++x) {
                std::cout << *x << " ";
                ++i;
                if (i == BLOCK_WIDTH) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
                    
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
                std::cout << "CASE 1\n";
                std::copy(rhs.begin(), rhs.end(), begin());
            }
            else if (rhs.size() < size()) {
                std::cout << "CASE 2\n";
                std::copy(rhs.begin(), rhs.end(), begin());
                
//                int i = 0;
//                for(typename MyDeque::iterator x = begin(); x != end(); ++x) {
//                    std::cout << *x << " ";
//                    ++i;
//                    if (i == BLOCK_WIDTH) {
//                        std::cout << std::endl;
//                    }
//                }
//                std::cout << std::endl;
                
                resize(rhs.size());
            }
            else if (rhs.size() <= capacity) {
                std::cout << "CASE 3\n";
                std::copy(rhs.begin(), rhs.begin() + size(), begin());
                _e = &*uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());
            }
            else {
                std::cout << "CASE 4\n";
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
//            // <your code>
//            // dummy is just to be able to compile the skeleton, remove it
//            static value_type dummy;
//            return dummy;
            
            if (index == 0) {
                return *_b;
            }
            
            reference result = *_b;
            
            if ((_b - _top[_u_top]) + index > BLOCK_WIDTH) {
                size_type block_jump = ((_b - _top[_u_top]) + index) / BLOCK_WIDTH;
                pointer temp = _top[_u_top + block_jump];
                size_type offset = BLOCK_WIDTH * block_jump - index;
                if (offset < 0) {
                    offset *= -1;
                }
                result = *(temp + offset);
            }
            else {
                result = *(_b + index - 1);
            }
            
            return result;
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
         * @return a reference
         * gives a reference to last element in the container
         */
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
//            static value_type dummy;
//            return dummy;
            
            assert(!empty());
            
            return *(end() - 1);
        }

        /**
         * @return a const_reference
         * gives a const_reference to last element in the container
         */
        const_reference back () const {
            return const_cast<MyDeque*>(this)->back();
        }

        // -----
        // begin
        // -----

        /**
         * @return an iterator
         * gives an iterator that points to the first element in a MyDeque
         */
        iterator begin () {
            //std::cout << "BEGIN: " << _u_top << " " << _b - _top[_u_top] << std::endl;
            return iterator(this, _u_top, _b - _top[_u_top]);
        }

        /**
         * @return an const_iterator
         * gives an const_iterator that points to the first element in a MyDeque
         */
        const_iterator begin () const {
            //std::cout << "CONST_BEGIN: " << _u_top << " " << _b - _top[_u_top] << std::endl;
            return const_iterator(this, _u_top, _b - _top[_u_top]);
        }

        // -----
        // clear
        // -----

        /**
         * removes all elements from MyDeque
         */
        void clear () {
            // <your code>
            std::cout << "CLEAR\n";
            resize(0);
            assert(valid());
        }

        // -----
        // empty
        // -----

        /**
         * @return a bool
         * checks if a MyDeque is empty
         */
        bool empty () const {
            return !size();
        }

        // ---
        // end
        // ---

        /**
         * @return an iterator
         * gives an iterator that points to the last element in a MyDeque
         */
        iterator end () {
//            std::cout << "END: " << _u_bottom << " " << _e - _top[_u_bottom] - 1 << std::endl;
            return iterator(this, _u_bottom, _e - _top[_u_bottom]);
        }

        /**
         * @return an const_iterator
         * gives an const_iterator that points to the last element in a MyDeque
         */
        const_iterator end () const {
//            std::cout << "CONST_END: " << _u_bottom << " " << _e - _top[_u_bottom] - 1 << std::endl;
            return const_iterator(this, _u_bottom, _e - _top[_u_bottom]);
        }

        // -----
        // erase
        // -----

        /**
         * @param p an iterator
         * @return an iterator
         * removes an element from the MyDeque at position pointed to by p
         */
        iterator erase (iterator p) {
            // <your code>
            if (p == end() - 1) {
                pop_back();
            }
            else {
                std::copy(p + 1, end(), p);
                resize(size() - 1);
            }
            
            assert(valid());
            return iterator(this);
        }

        // -----
        // front
        // -----

        /**
         * @return a reference
         * gives a reference to the first element in a MyDeque container
         */
        reference front () {
            // <your code>
            assert(!empty());
            return *begin();;
        }

        /**
         * @return a const_reference
         * gives a const_reference to the first element in a MyDeque container
         */
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();
        }

        // ------
        // insert
        // ------

        /**
         * @param p an iterator
         * @param v a const_reference
         * @return an iterator
         * adds an element of value v to the MyDeque at position pointed to by p
         */
        iterator insert (iterator p, const_reference v) {
            // <your code>
            if (p == end()) {
                push_back(v);
            }
            else {
                resize(size()+1);
		std::copy(p, end(), p+1);
		*p = v;
            }
            
            assert(valid());
            return iterator();
        }

        // ---
        // pop
        // ---

        /**
         * removes the last element from a MyDeque
         */
        void pop_back () {
            // <your code>
            assert(!empty());
            resize(size() - 1);
            assert(valid());
        }

        /**
         * removes the first element from a MyDeque
         */
        void pop_front () {
            //<your code>
            destroy(_a, begin(), begin() + 1);
            if (_b - _top[_u_top] ==  BLOCK_WIDTH) {
                ++_u_top;
                _b = _top[_u_top];
            }
            else {
                ++_b;
            }
            
            assert(valid());
        }

        // ----
        // push
        // ----

        /**
         * @param v a const_reference
         * adds an element of value v to the end of a MyDeque
         */
        void push_back (const_reference v) {
            // <your code>
            size_type update = size() + 1;
             std::cout << update << std::endl;
            resize(update, v);
            assert(valid());
        }

        /**
         * @param v a const_reference
         * adds an element of value v to the beginning of a MyDeque
         */
        void push_front (const_reference v) {
            // <your code>
            if (_top[_u_top] == _b) {
                resize(size() + 1);
                pop_back();
                --_u_top;
                _b = _top[_u_top] + BLOCK_WIDTH;
            }
            else {
                --_b;
            }
            _a.construct(&*begin(), v);
            
            assert(valid());
        }

        // ------
        // resize
        // ------

        /**
         * @param s a size_type
         * @param v a const_reference
         * resizes a MyDeque so it contains s elements
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            if (s == size()) {
                return ;
            }
            std::cout << "IN RESIZE: " << s << " SIZE: " << size() << std::endl;
            size_type capacity = block_size * BLOCK_WIDTH;
            std::cout << "CAPACITY: " << capacity << std::endl;
            if ( s < size()) {                
                int i = 0;
                for(typename MyDeque::iterator x = begin() + s; x != end(); ++x) {
                    std::cout << *x << " ";
                    ++i;
                    if (i == BLOCK_WIDTH) {
                        std::cout << std::endl;
                    }
                }
                std::cout << std::endl;
                
                _e = &*destroy(_a, begin() + s, end());
            }
            else if (s <= capacity) {
                _e = &*uninitialized_fill(_a, end(), begin() + s, v);
            }
            else {
                size_type capacity = std::max(2 * size(), s);
                MyDeque copy(capacity, v);
                std::copy(begin(), end(), copy.begin());
                swap(copy);
            }
            
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
            
//            std::cout << "SIZE: " << _e - _b << std::endl;
//            return _e - _b;
            size_type i = (_e - _top[_u_bottom]);
            size_type j = BLOCK_WIDTH - (_b - _top[_u_top]);
            size_type result = i + j;
//            std::cout << "OFFSET: " << i << std::endl;
//            std::cout << "BLOCK: " << j << std::endl;
//            std::cout << "SIZE: " << result << std::endl;
            return result; 
        }

        // ----
        // swap
        // ----

        /**
         * @param rhs a MyDeque reference
         * Switches the contents of two MyDeque objects
         */
        void swap (MyDeque& rhs) {
            // <your code>
            if (_a == rhs._a && _p == rhs._p) {
                std::swap(_top, rhs._top);
                std::swap(_bottom, rhs._bottom);
                std::swap(_u_top, rhs._u_top);
                std::swap(_u_bottom, rhs._u_bottom);
                std::swap(block_size, rhs.block_size);
                std::swap(_b, rhs._b);
                std::swap(_e, rhs._e);
            }
            else {
                MyDeque x(*this);
                *this = rhs;
                rhs = x;
            }
            
            assert(valid());
        }
};

#endif // Deque_h
