
#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef boost::variant<int, string, bool> subVariant;//, vector<myVariant>, map<string, myVariant>> myVariant; 
typedef boost::variant<int, string, bool, vector<subVariant>, map<string, subVariant>>  myVariant;

class times_two
    : public boost::static_visitor<>
{
public:

    void operator()(int & i) const
    {
        i *= 2;
    }

    void operator()(std::string & str) const
    {
        str += str;
    }

    void operator()(bool & b) const {}

    void operator()(vector<subVariant> & v) const {
        auto old = v.size();   
        v.reserve(2 * old);
        copy_n(v.begin(), old, back_inserter(v));        
    }

    void operator()(map<string, subVariant> & m) const {}


};

// class addX
//     : public boost::static_visitor<>
// {
// public:
//     void operator()(int & i, int & X) const
//     {
//         i += X;
//     }

//     void operator()(string & i, string & X) const
//     {
//         i += X;
//     }

//     void operator()(bool & i, bool & X) const {}

//     void operator()(vector<subVariant> & i, vector<subVariant> & X) const
//     {
//         i.insert(i.end(), X.begin(), X.end());
//     }

//     void operator()(map<string, subVariant> & i, map<string, subVariant> & X) const { }

// };