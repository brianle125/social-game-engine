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
    > dataBucket;

#ifndef SAMPLEVISIT_H
#define SAMPLEVISIT_H

struct toStringVisitor {
	string operator()(int i) const;
	string operator()(float f) const;
	string operator()(string s) const;
	string operator()(bool b) const;
	string operator()(vector<dataBucket> v) const;
	string operator()(map<string, dataBucket> m) const;
};

struct shuffleVisitor {
	void operator()(vector<dataBucket> v);
	template<typename T>
	void operator()(T const) const;
};

// struct addVisitor {
// 	void operator()(int i);
// 	void operator()(float f);
// 	void operator()(string s);
// 	void operator()(bool b);
// 	void operator()(vector<dataBucket> v);
// 	void operator()(map<string, dataBucket> m);
// };

#endif