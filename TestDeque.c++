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



 //-=-=-=  New unit tests //



#include <cstring>   // strcmp
#include <deque>     // deque
#include <algorithm> // equal
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include "Deque.h"
#include "gtest/gtest.h"
#include <deque>
#include <stdexcept> // invalid_argument
#include <memory>   // allocator
#include <cstdlib>   // rand

#define private public
#define protected public

using namespace std;


    // -----------
    // constructors
    // -----------
TEST(Constructor, default_case) {
    MyDeque<int> x;
    deque<int> y;
    ASSERT_EQ(x.size(), 0);
    ASSERT_EQ(y.size(), 0);
}


TEST(Constructor, fill_constructor_1) {
    MyDeque<int> x (10);
    deque<int> y(10);
    ASSERT_EQ(x.size(), 10);
    ASSERT_EQ(y.size(), 10);
}

TEST(Constructor, fill_constructor_2) {
    MyDeque<int> x (999);
    deque<int> y(999);
    ASSERT_EQ(x.size(), 999);
    ASSERT_EQ(y.size(), 999);
}


    // ----------------
    // Copy Constructor
    // ----------------


TEST(CopyConstructor, test_1) {
    MyDeque<int> x (33, 100);
    MyDeque<int> y (x);
    // cout << "y.size is " << y.size();
    ASSERT_TRUE(x.size() == 33);
    ASSERT_TRUE(y.size() == 33);
}

TEST(CopyConstructor, test_2) {
    MyDeque<int> x (6, 35);
    MyDeque<int> y(x);
    // cout << "y.size is " << y.size();
 
    ASSERT_EQ(x.size(), 6);
    ASSERT_EQ(y.size(), 6);
}

TEST(CopyConstructor, Test3) {
    MyDeque<int> x (66, 50);
    MyDeque<int> z(x);

    ASSERT_EQ(x.size(), 66);
    ASSERT_EQ(z.size(), 66);
}


    // ----------------
    // Copy Assignment
    // ----------------

TEST(CopyAssignment, Assign1) {
    MyDeque<int> x (5, 50);
    MyDeque<int> z(3, 10);
    z = x;
    ASSERT_EQ(x.size(), 5);
    ASSERT_EQ(z.size(), 5);
}



TEST(CopyAssignment, Assign2) {
    MyDeque<int> x (26, 50);
    MyDeque<int> z(2, 10);
    z = x;
    ASSERT_EQ(x.size(), 26);
    ASSERT_EQ(z.size(), 26);
}


TEST(CopyAssignment, Assign3) {
    MyDeque<int> x (25, 5);
    MyDeque<int> z(10, 6);
    z = x;
    ASSERT_EQ(x.size(), 25);
    ASSERT_EQ(z.size(), 25);
}

TEST(CopyAssignment, Assign4) {
    MyDeque<int> x (2, 5);
    MyDeque<int> z(9, 6);
    z = x;
    ASSERT_EQ(x.size(), 2);
    ASSERT_EQ(z.size(), 2);
}

TEST(CopyAssignment, Assign5) {
    MyDeque<int> x (19, 5);
    MyDeque<int> z(9, 6);
    z = x;
    ASSERT_EQ(x.size(), 19);
    ASSERT_EQ(z.size(), 19);
}
    // ----------
    // iterators
    // ----------
   
TEST(Iterator, 1Row) {
    MyDeque<int> x (4, 100);
    deque<int> y(4, 100);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != e) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 4);
    ASSERT_EQ(x.size(), 4);
    ASSERT_EQ(y.size(), 4);
}

TEST(Iterator, MultiRow) {
    MyDeque<int> x (15, 100);
    deque<int> y(15, 100);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != e) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 15);
    ASSERT_EQ(x.size(), 15);
    ASSERT_EQ(y.size(), 15);
}

TEST(Iterator, Back1Row) {
    MyDeque<int> x (4, 100);
    deque<int> y(4, 100);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    --e;
    --b;
    while(b != e) {
        ASSERT_EQ(*e, 100);
        --e;
        ++count;
    }
    ASSERT_EQ(count, 4);
    ASSERT_EQ(x.size(), 4);
    ASSERT_EQ(y.size(), 4);
}




// TEST(Iterator, BackMultiRow) {
//     MyDeque<int> x (101, 100);
//     MyDeque<int>::iterator b = x.begin();
//     MyDeque<int>::iterator e = x.end();
//     int count = 0;
//     --e;
//     --b;
//     while(b != e) {

//         --e;
//         ++count;
//     }
//     ASSERT_EQ(count, 101);
//     ASSERT_EQ(x.size(), 101);

// }

TEST(Iterator, BackMultiRow2) {
    MyDeque<int> x (101, 100);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    --e;
    while(b != e) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    ASSERT_EQ(++count, 101);
    ASSERT_EQ(x.size(), 101);

}


TEST(Iterator, 1RowConst) {
    const MyDeque<int> x (4, 100);
    deque<int> y(4, 100);
    MyDeque<int>::const_iterator b = x.begin();
    MyDeque<int>::const_iterator e = x.end();
    int count = 0;
    while(b != e) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 4);
    ASSERT_EQ(x.size(), 4);
    ASSERT_EQ(y.size(), 4);
}

     // ----------
     // Resize
     // ----------

TEST(Resize, Test1) {
    MyDeque<int> x (19, 100);
    x.resize(10);

    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != e) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 10);
    ASSERT_EQ(x.size(), 10);
}

TEST(Resize, Test2) {
    MyDeque<int> x (25, 100);
    x.resize(15);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != e) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 15);
    ASSERT_EQ(x.size(), 15);
}

TEST(Resize, Test3) {
    MyDeque<int> x (25, 100);
    MyDeque<int>::iterator it = x.end();
    x.resize(30);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != it) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    while(b != e) {
        ASSERT_EQ(*b, 0);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 30);
    ASSERT_EQ(x.size(), 30);
}

TEST(Resize, Test4) {
    MyDeque<int> x (25, 100);
    MyDeque<int>::iterator it = x.end();
    x.resize(35);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != it) {
        ASSERT_EQ(*b, 100);
        ++b;
        ++count;
    }
    while(b != e) {
        ASSERT_EQ(*b, 0);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 35);
    ASSERT_EQ(x.size(), 35);
}

TEST(Resize, Test5) {
    MyDeque<int> x;
    x.resize(37);
    MyDeque<int>::iterator b = x.begin();
    MyDeque<int>::iterator e = x.end();
    int count = 0;
    while(b != e) {
        ASSERT_EQ(*b, 0);
        ++b;
        ++count;
    }
    ASSERT_EQ(count, 37);
    ASSERT_EQ(x.size(), 37);
}


     // ----------
     // Push_back
     // ----------



TEST(Push_Back, Test1) {
    MyDeque<int> x;
    x.push_back(9);
    ASSERT_EQ(x.size(), 1);
    ASSERT_EQ(x.front(), 9);
    ASSERT_EQ(x.back(), 9);
}

TEST(Push_Back, Test2) {
    MyDeque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    x.push_back(6);
    x.push_back(7);
    x.push_back(8);
    x.push_back(9);
    x.push_back(10);
    ASSERT_EQ(x.size(), 10);
    ASSERT_EQ(x.front(), 1);
    ASSERT_EQ(x.back(), 10);
}

TEST(Push_Back, Test3) {
    MyDeque<int> x (2, 11);
    x.push_back(9);
    ASSERT_EQ(x.front(), 11);
    ASSERT_EQ(x.back(), 9);
}

/*TEST(Push_Back, Test4) {
    MyDeque<int> x(0);
    x.push_back(9);
    // cout << "x.front is " << x.front() << "\n";
    ASSERT_EQ(x.size(), 1);
    ASSERT_EQ(x.front(), 9);
    ASSERT_EQ(x.back(), 9);
}*/

    // ----------
    // Clear
    // ----------

 TEST(Clear, Test1) {
     MyDeque<int> x;
     x.resize(37);
     x.clear();
     ASSERT_EQ(x.size(), 0);
 }

 TEST(Clear, Test2) {
     MyDeque<int> x;
     x.clear();
     ASSERT_EQ(x.size(), 0);
 }

 TEST(Clear, Test3) {
     MyDeque<int> x(33, 22);
     x.clear();
     ASSERT_EQ(x.size(), 0);
 }

 TEST(Clear, Test4) {
     MyDeque<int> x(33, 66);
     MyDeque<int> y(x);
     MyDeque<int>::iterator b = x.begin();
     MyDeque<int>::iterator e = x.end();
     x.clear();
     int count = 0;
     while(b != e) {
         ASSERT_EQ(*b, 66);
         ++b;
         ++count;
     }
     ASSERT_EQ(x.size(), 0);
     ASSERT_EQ(y.size(), 33);
 }

// TEST(Clear, Test5) {
//     MyDeque<int> x(33, 22);
//     x.clear();
//     x.push_back(4);
//     x.push_back(5);
//     x.push_back(6);
//     ASSERT_EQ(x.size(), 3);
// }

     // ----------
     // Back/Front
     // ----------

 TEST(Back_Front, Test1) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator b = x.begin();
     MyDeque<int>::iterator e = x.end();
     int count = 0;
     while(b != e) {
         ASSERT_EQ(*b, 100);
         ++b;
         ++count;
     }
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Back_Front, Test2) {
     MyDeque<int> x;
     x.push_back(10);
     ASSERT_EQ(x.front(), 10);
     ASSERT_EQ(x.back(), 10);
 }

 TEST(Back_Front, Test3) {
     MyDeque<int> x;
     x.push_back(10);
     x.push_front(7);
     ASSERT_EQ(x.front(), 7);
     ASSERT_EQ(x.back(), 10);
 }

     // ----------
     // Pop_back
     // ----------
    
 TEST(Pop_Back, Test1) {
     MyDeque<int> x (10, 100);
     x.pop_back();
     ASSERT_EQ(x.size(), 9);
     ASSERT_EQ(x.front(), 100);
 }

 TEST(Pop_Back, Test2) {
     MyDeque<int> x(1,1);
     x.pop_back();
     ASSERT_EQ(x.size(), 0);
 }

 TEST(Pop_Back, Test3) {
     MyDeque<int> x (10, 100);
     x.pop_back();
     x.pop_back();
     x.pop_back();
     x.pop_back();
     x.pop_back();
     ASSERT_EQ(x.size(), 5);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Pop_Back, Test4) {
     MyDeque<int> x (10, 100);
     x.pop_back();
     x.pop_back();
     x.pop_back();
     x.pop_back();
     x.pop_back();
     MyDeque<int>::iterator b = x.begin();
     MyDeque<int>::iterator e = x.end();
     int count = 0;
     while(b != e) {
         ASSERT_EQ(*b, 100);
         ++b;
         ++count;
     }
     ASSERT_EQ(count, 5);
     ASSERT_EQ(x.size(), 5);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

     // ----------
     // Push_front
     // ----------

 TEST(Push_Front, Test1) {
     MyDeque<int> x (10, 100);
     x.push_front(9);
     MyDeque<int>::iterator b = x.begin();
     MyDeque<int>::iterator e = x.end();
     int count = 0;
     while(b != e) {
         ++b;
         ++count;
     }
     ASSERT_EQ(x.front(), 9);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Push_Front, Test2) {
     MyDeque<int> x;
     x.push_front(9);
     ASSERT_EQ(x.size(), 1);
     ASSERT_EQ(x.front(), 9);
     ASSERT_EQ(x.back(), 9);
 }

 TEST(Push_Front, Test3) {
     MyDeque<int> x;
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     x.push_front(9);
     ASSERT_EQ(x.size(), 10);
     ASSERT_EQ(x.front(), 9);
     ASSERT_EQ(x.back(), 9);
 }

// TEST(Push_Front, Test4) {
//     MyDeque<int> x(0);
//     x.push_front(9);
//     ASSERT_EQ(x.size(), 1);
//     ASSERT_EQ(x.front(), 9);
//     ASSERT_EQ(x.back(), 9);
// }

     // ----------
     // Pop_front
     // ----------
    
 TEST(Pop_Front, Test1) {
     MyDeque<int> x (10, 100);
     x.pop_front();
     ASSERT_EQ(x.size(), 9);
     ASSERT_EQ(x.front(), 100);
 }

 TEST(Pop_Front, Test2) {
     MyDeque<int> x(1,1);
     x.pop_front();
     ASSERT_EQ(x.size(), 0);
 }

 TEST(Pop_Front, Test3) {
     MyDeque<int> x (10, 100);
     x.pop_front();
     x.pop_front();
     x.pop_front();
     x.pop_front();
     x.pop_front();
     ASSERT_EQ(x.size(), 5);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Pop_Front, Test4) {
     MyDeque<int> x (10, 100);
     x.push_front(5);
     x.pop_front();
     MyDeque<int>::iterator b = x.begin();
     MyDeque<int>::iterator e = x.end();
     int count = 0;
     while(b != e) {
         ASSERT_EQ(*b, 100);
         ++b;
         ++count;
     }
     ASSERT_EQ(count, 10);
     ASSERT_EQ(x.size(), 10);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

     // ----------
     //   Insert
     // ----------

 TEST(Insert, Test1) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator b = x.begin();
     x.insert(b, 99);
     ASSERT_EQ(x.size(), 11);
     ASSERT_EQ(x.front(), 99);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Insert, Test2) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator b = x.end();
     x.insert(b, 99);
     ASSERT_EQ(x.size(), 11);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 99);
 }

 TEST(Insert, Test3) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator it = x.begin()+5;
     MyDeque<int>::iterator b = x.begin();
     it = x.insert(it, 99);
     MyDeque<int>::iterator e = x.end();
     int count = 0;
     while(b != e) {
         if(b == it) {
             ASSERT_EQ(*b, 99);
         }
         else {
             ASSERT_EQ(*b, 100);
         }
         ++b;
         ++count;
     }
     ASSERT_EQ(x.size(), 11);
     ASSERT_EQ(*it, 99);
 }

     // ----------
     //   Erase
     // ----------

 TEST(Erase, Test1) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator b = x.begin();
     x.erase(b);
     ASSERT_EQ(x.size(), 9);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Erase, Test2) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator b = x.end()-1;
     x.erase(b);
     ASSERT_EQ(x.size(), 9);
     ASSERT_EQ(x.front(), 100);
     ASSERT_EQ(x.back(), 100);
 }

 TEST(Erase, Test3) {
     MyDeque<int> x (10, 100);
     MyDeque<int>::iterator it = x.begin()+5;
     MyDeque<int>::iterator b = x.begin();
     it = x.erase(it);
     MyDeque<int>::iterator e = x.end();
     int count = 0;
     while(b != e) {
         ASSERT_EQ(*b, 100);
         ++b;
         ++count;
     }
     ASSERT_EQ(x.size(), 9);
     ASSERT_EQ(*it, 100);
 }

     // -----------------
     // Access element []
     // -----------------

 TEST(Access_element, Test1) {
   MyDeque<int> x (10, 100);
   for(int i = 0; i < (int) x.size(); ++i) {
       ASSERT_EQ(x[i], 100);
   }
 }

 TEST(Access_element, Test2) {
   MyDeque<int> x (25, 5);
   x.push_back(9);
   for(int i = 0; i < (int) x.size(); ++i) {
       ASSERT_EQ(x[i], 5);
   }
   ASSERT_EQ(x[24], 5);
 }

 TEST(Access_element, Test3) {
   MyDeque<int> x;
   x.push_back(9);
   x.push_back(9);
   x.push_back(9);
   x.push_back(9);
   x.push_back(9);
   x.push_back(9);
   for(int i = 0; i < (int) x.size(); ++i) {
       ASSERT_EQ(x[i], 9);
   }
 }

     // -----------------
     // Access element at
     // -----------------

 TEST(Access_element_at, Test1) {
   MyDeque<int> x (10, 100);
   for(int i = 0; i < (int)x.size(); i++) {
       ASSERT_EQ(x.at(i), 100);
   }
 }

 TEST(Access_element_at, Test2) {
   MyDeque<int> x (26, 5);
   x.push_back(9);
   for(int i = 0; i < (int)x.size()-1; i++) {
       ASSERT_EQ(x.at(i), 5);
   }
   ASSERT_EQ(x[x.size()-1], 9);
 }

 TEST(Access_element_at, Test3) {
   MyDeque<int> x (37, 5);
   x.push_back(9);
   ASSERT_THROW(x.at(39), out_of_range);
 }

    
     // ---------
     // equals_to
     // ---------

 TEST(Equals, Test1) {
   MyDeque<int> x (10, 100);
   MyDeque<int> y (10, 100);
 	ASSERT_TRUE(x == y);
 }

 TEST(Equals, Test2) {
   MyDeque<int> x (10, 100);
   MyDeque<int> y(x);
 	ASSERT_TRUE(x == y);
 }

 TEST(Equals, Test3) {
   MyDeque<int> x (10, 100);
   MyDeque<int> y (8, 100);
   y.push_back(100);
   y.push_front(100);
 	ASSERT_TRUE(x == y);
 }

 TEST(Equals, Test4) {
   MyDeque<int> x (10, 100);
   MyDeque<int> y (10, 9);
 	ASSERT_TRUE(x != y);
 }

     // ---------
     // less_than
     // ---------

 TEST(Less_than, Test1) {
   MyDeque<int> x (3, 100);
   MyDeque<int> y (2, 200);
 	ASSERT_TRUE(x < y);
 }

 TEST(Less_than, Test2) {
   MyDeque<int> x (3, 100);
   MyDeque<int> y (2, 200);
 	ASSERT_TRUE(x <= y);
 }

 TEST(Less_than, Test3) {
   MyDeque<int> x (3, 300);
   MyDeque<int> y (2, 200);
 	ASSERT_TRUE(x > y);
 }

 TEST(Less_than, Test4) {
   MyDeque<int> x (3, 300);
   MyDeque<int> y (2, 200);
 	ASSERT_TRUE(x >= y);
 }

     //----
     //Swap
     //----
    
 TEST(Swap, Test1) {
    MyDeque<int> x(15,1);
    MyDeque<int> y(25,2);
    x.swap(y);
    ASSERT_EQ(x.size(), 25);
    ASSERT_EQ(y.size(), 15);
 }
    
 TEST(Swap, Test2) {
    MyDeque<int> x(70,1);
    MyDeque<int> y(90,2);
    x.swap(y);
    x.swap(y);
    ASSERT_EQ(x.size(), 70);
    ASSERT_EQ(y.size(), 90);
 }

 TEST(Swap, Test3) {
    MyDeque<int> x(10,1);
    x.swap(x);
    ASSERT_EQ(x.size(), 10);
 }


     //------------------
     //Testing everything
     //------------------
    
 TEST(Everything, Test1) {
   MyDeque<int> x(10, 10);
   MyDeque<int> y(x);
   ASSERT_EQ(x.size(), y.size());
   y.pop_front();
   x.pop_front();
   MyDeque<int>::iterator b1 = x.begin();
   MyDeque<int>::iterator e1 = x.end();
   MyDeque<int>::iterator b2 = y.begin();
   int count = 0;
   while(b1 != e1) {
       ASSERT_EQ(*b1, *b2);
       ++b1;
       ++b2;
       ++count;
   }
   ASSERT_EQ(count, x.size());
   x.clear();
   y.clear();
   ASSERT_EQ(x.size(), y.size());
   MyDeque<int> z(10, 5);
 }

 TEST(Everything, Test2) {
  MyDeque<int> x;
  MyDeque<int> y (10, 1);
  for (int i = 0; i < 10; ++i){
    x.push_back(i);
  }
  for(int i = 0; i < 10; i++){
    x.push_front(i);
    x.pop_back();
    x.push_back(i);
    x.pop_front();
  }
  ASSERT_EQ(x.size(), 10);
  ASSERT_TRUE(!x.empty());
 }


 TEST(Everything, Test3) {
   MyDeque<double> x(1);
   MyDeque<double> y(x);
   x.push_back(1.1);
   x.push_back(1.2);
   MyDeque< MyDeque<double> > z (5, x);
   ASSERT_EQ(z[0].size(), x.size());
   ASSERT_EQ(z[0], x);
   z.clear();
   ASSERT_EQ(z.size(), 0);
   MyDeque<double> w(10, 10.15);
   MyDeque<double>::iterator temp1 = w.begin();
   MyDeque<double>::iterator temp2 = w.end();
   while(temp1 != temp2){
     ASSERT_EQ(*temp1, 10.15);
     ++temp1;
   }
   MyDeque< MyDeque<double> > k (5, w);
   MyDeque<MyDeque<double> >::iterator b1 = k.begin();
   ASSERT_EQ(w, *b1);
   for(int i = 0; i < 10; ++i)
   ASSERT_EQ((*b1)[i], 10.15);
 }
