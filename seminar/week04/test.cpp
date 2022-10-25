#include "iostream"

int main()
{
    int x = 256;
    int* int_p = &x;
    void* void_p = int_p;
    // std::cout << *void_p << std::endl; pointer must be a complete object type
}