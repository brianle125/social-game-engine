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
    > dataVariant;

#ifndef SAMPLEVISIT_H
#define SAMPLEVISIT_H

struct toStringVisitor {
	string operator()(int i) const;
	string operator()(float f) const;
	string operator()(string s) const;
	string operator()(bool b) const;
	string operator()(vector<dataVariant> v) const;
	string operator()(map<string, dataVariant> m) const;
};

struct toIntVisitor {
	int operator()(int i) const;
	int operator()(float f) const;
}


struct toFloatVisitor{
	float operator()(int i) const;
	float operator()(float f) const;
}


struct shuffleVisitor {
	void operator()(vector<dataVariant> v);
	template<typename T>
	void operator()(T const) const;
};

// struct addVisitor {
// 	void operator()(int i);
// 	void operator()(float f);
// 	void operator()(string s);
// 	void operator()(bool b);
// 	void operator()(vector<dataVariant> v);
// 	void operator()(map<string, dataVariant> m);
// };

#endif