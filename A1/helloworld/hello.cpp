#include <iostream>

/* This program prints hello world to stdout. */

int main()
{
    /* cout is not defined in the global namespace so we must use std and the
     * scope operator "::" in order to use this standard library function.
     */
    std::cout << "Hello World\n";
    return 0;
}
