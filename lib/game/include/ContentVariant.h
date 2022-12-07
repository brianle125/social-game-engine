#pragma once
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

	template <typename T>
    int operator()(T) const{
    throw std::invalid_argument{"invalid"};
	}
};


struct toFloatVisitor{
	float operator()(int i) const;
	float operator()(float f) const;

	template <typename T>
    int operator()(T) const{
    throw std::invalid_argument{"invalid"};
	}
};


struct shuffleVisitor {
	void operator()(vector<dataVariant> &v);
	template<typename T>
	void operator()(T const) const{
    throw std::invalid_argument{"invalid"};
	}
};


struct addVisitor
{
    dataVariant operator()(int i1, int i2) const;
	dataVariant operator()(int i, float f) const;
	dataVariant operator()(float f, int i) const;
	dataVariant operator()(float f1, float f2) const;

    // all other overloads invalid
    template <typename T, typename U>
    dataVariant operator()(T, U) const{
    throw std::invalid_argument{"invalid"};
}
};


struct appendVisitor
{
    dataVariant operator()(string s1, string s2) const;
	dataVariant operator()(vector<dataVariant> v, float f) const;
	dataVariant operator()(vector<dataVariant> v, int i) const;
	dataVariant operator()(vector<dataVariant> v, bool b) const;
	dataVariant operator()(vector<dataVariant> v, string s) const;
	dataVariant operator()(vector<dataVariant> v1, vector<dataVariant> v2) const;

    // all other overloads invalid
    template <typename T, typename U>
    dataVariant operator()(T, U) const{
    throw std::invalid_argument{"invalid"};
}
};

struct reverseVisitor {
	void operator()(vector<dataVariant> &v);
	template <typename T>
	void operator()(T const) const {}
};

struct sizeVisitor {
	dataVariant operator()(std::vector<dataVariant> &v) const;
	dataVariant operator()(std::map<std::string, dataVariant> &m) const;
	template <typename T>
	dataVariant operator()(T const) const {
		throw std::invalid_argument{"Size is only valid for Lists and Maps"};
	}
};

struct searchVisitor {
	dataVariant operator()(std::vector<dataVariant> v, string s) const;
	dataVariant operator()(map<std::string, dataVariant> m, string s) const;
	template <typename T, typename U>
	dataVariant operator()(T, U) const {
		throw std::invalid_argument{"Search is only valid for Lists and Maps"};
	}
};

struct containsVisitor {
	dataVariant operator()(std::vector<dataVariant> v, std::string object) const;
	dataVariant operator()(map<std::string, dataVariant> m, std::string s) const;
	template <typename T, typename U>
	dataVariant operator()(T, U) const {
		throw std::invalid_argument{"Contains is only valid for Lists and Maps"};
	}
};

#endif