///*
// * TestDeque
// *
// * To compile this, use the command
// * g++ -pedantic -std=c++0x -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread
// *
// * Then it can run with
// * TestDeque
// *
// * It will work on any machine with gtest and the precompiled libraries installed
// */
//
// // --------
//// includes
//// --------
//
//#include <algorithm> // equal
//#include <cstring>   // strcmp
//#include <deque>     // deque
//#include <sstream>   // ostringstream
//#include <stdexcept> // invalid_argument
//#include <string>    // ==
//#include <memory>	 // allocator
//#include <cstdlib>	 // rand
//
//#include "gtest/gtest.h"
//
//#include "Deque.h"
//
//template <typename C>
//class IntTest : public testing::Test {
//	protected:
//		C x;
//		C y;
//
//		IntTest(): x(0), y(0){}
//};
//typedef testing::Types<std::deque<int>, MyDeque<int> > IntTypes;	// we are typedef-ing this line so we can pass it all
//TYPED_TEST_CASE(IntTest, IntTypes);		// without the commas appearing as separate arguments
//
//
//// Type fixture to support testing both deque and MyDeque without doubling code
//// Type <string>
//template <typename C>
//class StringTest : public testing::Test {
//	protected:
//		C x;
//		C y;
//
//		StringTest(): x(0), y(0){}
//};
//typedef testing::Types<std::deque<std::string>, MyDeque<std::string> > StringTypes;
//TYPED_TEST_CASE(StringTest, StringTypes);
//
//
////---------------
//// Start testing
////---------------
//
//
//// Size testing
//TYPED_TEST(IntTest, size_2) {
//	ASSERT_TRUE(this->x.size() == 0);
//}
//
//TYPED_TEST(IntTest, size_3) {
//	this->x.push_back(5);
//	ASSERT_TRUE(this->x.size() == 1);
//}
//
//TYPED_TEST(IntTest, size_4) {
//	this->x.push_back(5);
//	this->x.push_back(5);
//	ASSERT_TRUE(this->x.size() == 2);
//}
//
//TYPED_TEST(IntTest, size_5) {
//	this->x.push_back(0);
//	this->x.push_back(2);
//	this->x.push_back(0);
//	ASSERT_TRUE(this->x.size() == 3);
//}
//
//TYPED_TEST(StringTest, size_4) {
//	this->x.push_back("abc");
//	this->x.push_front("tuv");
//	ASSERT_TRUE(this->x.size() == 2);
//}

// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Deque.c++ TestDeque.c++ -o TestDeque -lcppunit -ldl
    % valgrind TestDeque > TestDeque.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {
    // ----
    // size
    // ----

    void test_size_1 () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);
    }
    
    void test_size_2 () {
//        const C x(10000, 9);
//        CPPUNIT_ASSERT(x.size() == 10000);
    }
    
    void test_size_3 () {
        const C x(1000, 1);
        const C y(x);
        std::cout << "ELEMENT: " << y[0] << " " << y[500] << " " << y[5] << std::endl;
        CPPUNIT_ASSERT(y.size() != 1047);
    }
    
    // ---
    // ==
    // ---
    
    void test_equal_1 () {
        const C x(10, 5);
        const C y(10, 5);
        
        CPPUNIT_ASSERT(x == y);
    }
    
    void test_equal_2 () {
        const C x(10, 5);
        
        CPPUNIT_ASSERT(x == x);
    }
    
    void test_equal_3 () {
        const C x(10);
        const C y(10);
        
        CPPUNIT_ASSERT(x == y);
    }
    
    // ---
    //  <
    // ---
    
    void test_less_than_1 () {
        const C x;
        const C y(1, 5);
        
        CPPUNIT_ASSERT(x < y);
    }
    
    void test_less_than_2 () {
        const C x(1, 5);
        const C y;
        
        CPPUNIT_ASSERT(!(x < y));
    }
    
    void test_less_than_3 () {
        const C x(10, 5);
        const C y(5, 10);
        
        CPPUNIT_ASSERT(x < y);
    }
    
    // ---
    //  = 
    // ---
    
    void test_assignment_1 () {
        C x;
        const C y(10, 10);
        
        x = y;
        CPPUNIT_ASSERT(x.size() == 10);
        CPPUNIT_ASSERT(x == y);
    }
    
    void test_assignment_2 () {
        C x(5, 10);
        const C y(10, 10);
        
        x = y;
        CPPUNIT_ASSERT(x.size() != 5);
        CPPUNIT_ASSERT(x == y);
    }
    
    void test_assignment_3 () {
        C x;
        C y;
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        
        x = y;
        CPPUNIT_ASSERT(x.size() == 4);
        CPPUNIT_ASSERT(x == y);
    }
    
    // ---
    // []
    // ---
    
    void test_index_1 () {
        const C x(5, 5);
        
        CPPUNIT_ASSERT(x[3] == 5);
    }
    
    void test_index_2 () {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        
        CPPUNIT_ASSERT(x[2] == 2);
    }
    
    void test_index_3 () {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        
        CPPUNIT_ASSERT(x[3] == 3);
        
        x.pop_front();
        
        CPPUNIT_ASSERT(x[3] == 4);
    }
    
    // ---
    // at
    // ---
    
    void test_at_1 () {
        const C x(5, 5);
        
        CPPUNIT_ASSERT(x.at(3) == 5);
    }
    
    void test_at_2 () {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        
        CPPUNIT_ASSERT(x.at(2) == 2);
    }
    
    void test_at_3 () {
        try {
            const C x(10, 10);
            x[11];
            
            CPPUNIT_ASSERT(false);
        }
        catch (std::out_of_range& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Index is out of range." ) == 0);
        }
    }
    
    // ----
    // back
    // ----
    
    void test_back_1 () {
        const C x(5, 5);
        
        CPPUNIT_ASSERT(x.back() == 5);
    }
    
    void test_back_2 () {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        
        CPPUNIT_ASSERT(x.back() == 4);
    }

    void test_back_3 () {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        
        CPPUNIT_ASSERT(x.back() == 4);
        
        x.pop_back();
        
        CPPUNIT_ASSERT(x.back() == 3);
    }
    
    // -----
    // begin
    // -----
    
//    void test_begin_1 () {
//        const C x(5, 5);
//        
//        typename C::iterator i = x.begin(); 
//        
//        CPPUNIT_ASSERT(*i == 5);
//    }
    
//    void test_begin_2 () {
//        C x;
//        x.push_back(1);
//        x.push_back(2);
//        x.push_back(3);
//        x.push_back(4);
//        
//        typename C::iterator i = x.begin(); 
//        
//        CPPUNIT_ASSERT(*i == 1);
//    }
//        
//    void test_begin_3 () {
//        C x;
//        x.push_back(1);
//        x.push_back(2);
//        x.push_back(3);
//        x.push_back(4);
//        
//        x.pop_front();
//        
//        typename C::iterator i = x.begin(); 
//        
//        CPPUNIT_ASSERT(*i == 2);
//    }
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
//    CPPUNIT_TEST(test_size_1);
//    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
//    CPPUNIT_TEST(test_equal_1);
//    CPPUNIT_TEST(test_equal_2);
//    CPPUNIT_TEST(test_equal_3);
//    CPPUNIT_TEST(test_less_than_1);
//    CPPUNIT_TEST(test_less_than_2);
//    CPPUNIT_TEST(test_less_than_3);
//    CPPUNIT_TEST(test_assignment_1);
//    CPPUNIT_TEST(test_assignment_2);
//    CPPUNIT_TEST(test_assignment_3);
//    CPPUNIT_TEST(test_index_1);
//    CPPUNIT_TEST(test_index_2);
//    CPPUNIT_TEST(test_index_3);
//    CPPUNIT_TEST(test_at_1);
//    CPPUNIT_TEST(test_at_2);
//    CPPUNIT_TEST(test_at_3);
//    CPPUNIT_TEST(test_back_1);
//    CPPUNIT_TEST(test_back_2);
//    CPPUNIT_TEST(test_back_3);
//    CPPUNIT_TEST(test_begin_1);
//    CPPUNIT_TEST(test_begin_2);
//    CPPUNIT_TEST(test_begin_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
    cout << "TestDeque.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    //tr.addTest(TestDeque<   deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
