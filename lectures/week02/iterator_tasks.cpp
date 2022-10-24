
template <typename T>
typename T::value_type sum (const T &l) // the typename is to indicate that it is the template, 
{                                      // otherwise its ambigious
    typename T::value_type sum = 0;
    for (typename T::iterator i = l.begin(); i != l.end(); ++i)
    {
        sum += *i;
    }

    return sum;
}

// template <typename T>
// typename T::value_type reverse_sum (const T &l) // the typename is to indicate that it is the template, 
// {                                      // otherwise its ambigious
//     std::cout << "HA" << std::endl;
//     typename T::value_type sum = 0;
//     for (typename T::iterator i = l.end(); i != l.begin(); --i)
//     {
//         std::cout << *i << std::endl;
//         sum += *i;
//     }
//     return sum;
// }

template <typename T>
T square(T a)
{
    return a*a;
}

template <typename T>
T& map(T& l, typename T::value_type (*func)(typename T::value_type))
{
    for (typename T::iterator i = l.begin(); i != l.end(); ++i)
    {
        *i = func(*i);
    }
    return l;
}

template <typename T>
bool dublicates(T l)
{
    for (typename T::iterator i = l.begin(); i != l.end(); ++i)
    {
        for (typename T::iterator j(i.current->next, i.current->next); j != l.end(); ++j)
        {
            if (*j == *i)
            {
                return true;
            }
        }
    }
    return false;
}