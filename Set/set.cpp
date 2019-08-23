
// Lab Exercise 4.

#include "set.h"

/* Initializer */
set::set (std::initializer_list<std::string> init)
    : set()
{
    for (auto i : init)
        insert(i);
}

/* Equality of the strings */
bool set::equal (const std::string& s1, const std::string& s2)
{
    if (s1.size() == s2.size())
    {
        for (size_t i = 0; i != s1.size(); ++i)
        {
            if (std::tolower(s1[i]) != std::tolower(s2[i]))
                return false;
        }
        return true;
    }

    return false;
}

/* Whether set contains that element */
bool set::contains (const std::string& el) const
{
    for (auto& c : data)
    {
        if (equal(c, el))
            return true;
    }

    return false;
}

/* Element insertion into the current set */
bool set::insert (const std::string& el)
{
    if (contains(el))
    {
      return false;
    }
    else
    {
        data.push_back(el);
        return true;
    }
}

/* Inserting a set to the current one */
size_t set::insert (const set& s)
{
    size_t count; 
    count = 0;
    for (auto& i : s)
    {
        if (insert(i))
            count += 1;
    }

    return count;
}

/* Element removal from the current set */
bool set::remove (const std::string& el)
{
    for (auto& i : data)
    {
        if (equal(i, el))
        {
            std::swap(i, data.back());
            data.pop_back();
            return true;
        }
    }

    return false;
}

/* Removing a set from the current one */
size_t set::remove (const set& s)
{
    size_t count;
    count = 0;
    for (auto& r : s)
    {
        if (remove(r))
            count += 1;
    }

    return count;
}

/* Printing the current set */
std::ostream& operator << ( std::ostream& out, const set& s )
{
    out << "{";
    for (auto p = s.begin(); p != s.end(); ++p)
    {
        if (p != s.begin())
            out << ",";
        out << " " << *p;
    }
    out << " }";

    return out;
}

/* Whether set is subset of another set */
bool subset( const set& s1, const set& s2 )
{
    for (auto i = s1.begin(); i != s1.end(); ++i)
    {
        if (!s2.contains(*i))
            return false;
    }

    return true;
}
