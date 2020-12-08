#include <stdlib.h> /* for abort() */

int add(int,int);
int sub(int,int);
int mult(int,int);

#ifdef TESTING
#include "stest.h"

TEST(add)
    expect(add(1,2) == 3);
    { int i;
      for (i = 0; i < 100; i++) {
          expect(add(i,0) == i);
      }
    }
ENDTEST

TEST(sub)
    expect(sub(2,1) == 1);
    expect(sub(0,10) == -11);
ENDTEST

TEST(mult)
    expect(mult(2,3) == (2 + 2 + 2));
ENDTEST

TEST(foo)
    abort();
ENDTEST

#endif

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mult(int a, int b) {
    return a * b;
}
