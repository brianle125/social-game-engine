#include "include/ContentVariant.h"
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

//toStringVisitors
std::string toStringVisitor::operator()(int i) const {
    return std::to_string(i);
}

std::string toStringVisitor::operator()(float f) const {
    return std::to_string(f); //to_string aint great, should be changed
}

std::string toStringVisitor::operator()(std::string s) const {
    return s;
}

std::string toStringVisitor::operator()(bool b) const {
    return b ? "true" : "false";
}

std::string toStringVisitor::operator()(vector<dataVariant> v) const {
    std::string s = "[";
    int n = v.size();
    int i;
    for(i = 0; i < n - 1; i++) {
        s += rva::visit(toStringVisitor{}, v[i]) + ", ";
    }
    if (n != 0) {
        s += rva::visit(toStringVisitor{}, v[i]);
    }
    s += "]";
    return s;
}

std::string toStringVisitor::operator()(map<std::string, dataVariant> m) const {
    std::string s = "(";
    auto i = m.begin();
    auto i2 = m.begin();
    i2++;

    if (i == m.end()) {
        return s += ")";
    }

    while (i2 != m.end()) {
        s += "(" + i->first + ": " + rva::visit(toStringVisitor{}, i->second) + "), ";
        i++;
        i2++;
    }
    s += "(" + i->first + ": " + rva::visit(toStringVisitor{}, i->second) + ")";
    s += ")";

    return s;
}


//toIntVisitors
int toIntVisitor::operator()(int i) const {
    return i;
}


int toIntVisitor::operator()(float f) const {
    return (int)f;
}


//toFloatVisitors
float toFloatVisitor::operator()(int i) const {
    return (float)i;
}


float toFloatVisitor::operator()(float f) const {
    return f;
}




//Shuffle visitors

void shuffleVisitor::operator()(vector<dataVariant> v) {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    std::shuffle(v.begin(), v.end(), default_random_engine(seed));
}

template<typename T> 
void shuffleVisitor::operator()(T const) const {
    //error handling of some sort
}





dataVariant addVisitor::operator()(int first, int second) const{
    return dataVariant(first+second);
}

dataVariant addVisitor::operator()(int first, float second) const{
    return dataVariant(first+second);
}

dataVariant addVisitor::operator()(float first, int second) const{
    return dataVariant(first+second);
}

dataVariant addVisitor::operator()(float first, float second) const{
    return dataVariant(first+second);
}



dataVariant addVisitor::operator()(int first, int second) const{
    return dataVariant(first+second);
}



template <typename T, typename U>
dataVariant addVisitor::operator()(T, U) const
{
    throw std::invalid_argument{"invalid"};
}

//Add visitors

// void addVisitor::operator()(int i) {

// }

// void addVisitor::operator()(vector<dataVariant> v) {

// }





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

// struct addVisitor {
//     int addVal_;

//     addVisitor(int& addVal) : addVal_{addVal} {}

//     void operator()(int & i) {
//         //i + addVal_;
//     }
//     void operator()(auto& t) {}
// };