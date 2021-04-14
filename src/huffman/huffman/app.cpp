#ifndef TEST_BUILD

/*
*   This file is only active in non-test builds (i.e., builds where TEST_BUILD is not defined).
*/

#include <iostream>


/*
* This is the main entry point of your application.
* Note that it will only work in non-test builds.
*/
int main()
{
    std::cout << "Hello world!";
}

#endif