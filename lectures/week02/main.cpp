#include "linked_list.cpp"

// template <typename T>
// T sum (const LList<T> &l) // the typename is to indicate that it is the template, 
// {                                      // otherwise its ambigious
//     T sum = 0;
//     for (ListIterator<int> i = l.begin(); i != l.end(); i++)
//     {
//         sum += *l;
//     }

//     return sum;
// }

int main()
{
    LList<int> l(1,3);
    LList<int> l2(4,6);
    l.append(l2);
    std::cout << l.size();
    // for (int i = 0; i < l.size(); i++)
    // {
    //     std::cout << l[i] << std::endl;
    // }
    // std::cout << sum(l) << std::endl;
}