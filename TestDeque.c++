/*
 * TestDeque
 *
 * To compile this, use the command
 * g++ -pedantic -std=c++0x -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread
 *
 * Then it can run with
 * TestDeque
 *
 * It will work on any machine with gtest and the precompiled libraries installed
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
#include <memory>	 // allocator
#include <cstdlib>	 // rand

#include "gtest/gtest.h"

#include "Deque.h"

template <typename C>
class IntTest : public testing::Test {
	protected:
		C x;
	//	C y;

		IntTest(): x(0){};//, y(0){}
};
typedef testing::Types<std::deque<int>, MyDeque<int> > IntTypes;	// we are typedef-ing this line so we can pass it all
TYPED_TEST_CASE(IntTest, IntTypes);		// without the commas appearing as separate arguments


// Type fixture to support testing both deque and MyDeque without doubling code
// Type <string>
template <typename C>
class StringTest : public testing::Test {
	protected:
		C x;
		C y;

		StringTest(): x(0), y(0){}
};
typedef testing::Types<std::deque<std::string>, MyDeque<std::string> > StringTypes;
TYPED_TEST_CASE(StringTest, StringTypes);


//---------------
// Start testing
//---------------


// Size testing
TYPED_TEST(IntTest, size_2) {
	ASSERT_TRUE(this->x.size() == 0);
}

// TYPED_TEST(IntTest, size_3) {
// 	this->x.push_back(5);
// 	ASSERT_TRUE(this->x.size() == 1);
// }

// TYPED_TEST(IntTest, size_4) {
// 	this->x.push_back(5);
// 	this->x.push_back(5);
// 	ASSERT_TRUE(this->x.size() == 2);
// }

// TYPED_TEST(IntTest, size_5) {
// 	this->x.push_back(0);
// 	this->x.push_back(2);
// 	this->x.push_back(0);
// 	ASSERT_TRUE(this->x.size() == 3);
// }

// TYPED_TEST(StringTest, size_6) {
// 	this->x.push_back("abc");
// 	this->x.push_front("tuv");
// 	ASSERT_TRUE(this->x.size() == 2);
// }