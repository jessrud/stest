#ifndef STEST_H
#define STEST_H
/* A quick and dirty single header c test runner
 * Copyright 2020 © Jesse Rudolph <jesse.rudolph@gmail.com>
 * License: MIT
*/

#include <stddef.h>
#include <stdio.h>

typedef void (*STestFP)();
extern STestFP stest_func[10000];
extern char* stest_name[10000];
extern size_t stest_count;
extern size_t stest_next;
extern size_t stest_failed;


#define THIS_TEST_NAME (stest_name[stest_next - 1])

#define TEST_NAME(name) stest_##name

#define TEST_CTOR_NAME(name) stest_ctor_##name

#define TEST(name)                                         \
static void TEST_NAME(name)();                             \
void __attribute__((constructor)) TEST_CTOR_NAME(name)() { \
    stest_name[stest_count] = #name;                       \
    stest_func[stest_count++] = TEST_NAME(name);           \
}                                                          \
static void TEST_NAME(name)() {

#define ENDTEST }


#define expect(cond)                                              \
    if ( !(cond) ) {                                              \
        fprintf( stderr,                                          \
                "%s:%d: test '%s' failed. expected `" #cond "`\n" \
        ,__FILE__,__LINE__,THIS_TEST_NAME);                       \
        stest_failed++;                                           \
        return;                                                   \
	}

/* this guard tells the compiler to omit the following implementation; useful 
 * when you want to make a single runner for tests in many interdependent
 * compilation units. See example Makefile for usage.
*/
#ifndef STEST_EXTERN

#include <signal.h>
#include <setjmp.h>

STestFP stest_func[10000];
char* stest_name[10000];
size_t stest_count = 0;
size_t stest_next = 0;
size_t stest_failed = 0;
jmp_buf stest_env;

static void handle_abnormal(int signum) {
    (void) signum;
    longjmp(stest_env,-1);
}

int main() {
    int last_reason = 0;
    if (stest_count == 0) {
        fprintf(stderr,"No tests to run.\n");
        return 0;
    }
/* the purpose of most of this is to handle assertion failure gracefully. */
    signal(SIGABRT,&handle_abnormal);
    fprintf(stderr, "Running tests..\n");

/* this is is where the abort handler returns */
    last_reason = setjmp(stest_env);

    if (last_reason != 0) {
        stest_failed++;

        fprintf( stderr,
            "abnormal termination in test '%s'. stopping\n",
            THIS_TEST_NAME
        );
        goto summary;
    }

/* this is constructed in a way that you should be able to recover from 
 * certain exceptions in the above if statements and the while loop will
 * continue chugging through tests as if nothing happened.
 */
    while(stest_next < stest_count) {
    	stest_func[stest_next++]();
    }
  summary:
    fprintf(stderr,"%zu of %zu test(s) invoked.\n", stest_next, stest_count);
    fprintf(stderr,"%zu invoked test(s) passed.\n", stest_next - stest_failed);
    return stest_failed;

}

#endif
#endif
