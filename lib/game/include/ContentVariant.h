#pragma once
//#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <variant>
#include <rva/variant.hpp>

#include <unordered_map>

#include <iostream>

using namespace std;

typedef rva::variant<
    int,
    float,
    string,
    bool,
    vector<rva::self_t>,
    map<string, rva::self_t>
    > myVariant;

#ifndef SAMPLEVISIT_H
#define SAMPLEVISIT_H

struct sampleVisit {
	void operator()(int i) {
		cout << "int";
	}
	void operator()(float f) {
		cout << "int";
	}
	void operator()(string s) {
		cout << "string \n";
	}
	void operator()(bool b) {
		cout << "bool \n";
	}
	void operator()(vector<myVariant> v) {}
	void operator()(map<string, myVariant> m) {}
};

struct doubleVisitor {
	void operator()(int & i) {
		i *= 2;
	}
	void operator()(float & f) {
		f *= 2;
	}
	void operator()(string & s) {
		s += s;
	}
	void operator()(bool b) {
		//error
	}
	void operator()(vector<myVariant> v) {
        auto old = v.size();   
        v.reserve(2 * old);
        copy_n(v.begin(), old, back_inserter(v));     
    }
	void operator()(map<string, myVariant> m) {}
};

#endif

// class times_two
//     : public boost::static_visitor<>
// {
// public:
//     void operator()(int & i) const
//     {
//         i *= 2;
//     }

//     void operator()(float & f) const
//     {
//         f *= 2;
//     }

//     void operator()(std::string & str) const
//     {
//         str += str;
//     }

//     void operator()(bool & b) const {}

//     void operator()(vector<myVariant> & v) const 
//     {
//         auto old = v.size();   
//         v.reserve(2 * old);
//         copy_n(v.begin(), old, back_inserter(v));        
//     }

//     void operator()(unordered_map<string, myVariant> & m) const {}
// };

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