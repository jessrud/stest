# stest.h
A quick and dirty single header c test runner

The secret sauce that makes this trivial to implement is the 
`__atribute__((constructor))`, bit in the `TEST` macro. This makes it unnecessary
to manually construct a list of test functions; each test function gets a tiny 
constructor that adds itself to a table in the test runner at startup.

Additionally, the test runner traps SIGABRT which is generated by assertion
failure. This way it can exit gracefully, reporting how many tests were 
invoked, how many succeeded, and in which test the abort signal was generated.

see `example.c` and the accompanying `Makefile` for example usage.

----

Copyright 2020 Jesse Rudolph <jesse.rudolph@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
