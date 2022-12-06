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

void shuffleVisitor::operator()(vector<dataVariant> &v) {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    std::shuffle(v.begin(), v.end(), default_random_engine(seed));
}


//Add Visitor

dataVariant addVisitor::operator()(int i1, int i2) const{
    return dataVariant(i1+i2);
}

dataVariant addVisitor::operator()(int i, float f) const{
    return dataVariant(i+f);
}

dataVariant addVisitor::operator()(float f, int i) const{
    return dataVariant(f+i);
}

dataVariant addVisitor::operator()(float f1, float f2) const{
    return dataVariant(f1+f2);
}


//Append Visitor

dataVariant appendVisitor::operator()(string s1, string s2) const{
    return dataVariant(s1+s2);
}


dataVariant appendVisitor::operator()(vector<dataVariant> v, float f) const{
    v.push_back(f);
    return dataVariant(v);
}


dataVariant appendVisitor::operator()(vector<dataVariant> v, int i) const{
    v.push_back(i);
    return dataVariant(v);
}

dataVariant appendVisitor::operator()(vector<dataVariant> v, bool b) const{
    v.push_back(b);
    return dataVariant(v);
}


dataVariant appendVisitor::operator()(vector<dataVariant> v, string s) const{
    v.push_back(s);
    return dataVariant(v);
}


dataVariant appendVisitor::operator()(vector<dataVariant> v1, vector<dataVariant> v2) const{
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

// Reverse Visitor

void reverseVisitor::operator()(vector<dataVariant> &v) {
    std::reverse(v.begin(), v.end());
}

dataVariant searchVisitor::operator()(std::vector<dataVariant> v, string s) const {
    vector<dataVariant> newList;
    dataVariant key(s);
    for(dataVariant var : v) {
        dataVariant temp = rva::visit(searchVisitor{}, var, key);
        newList.push_back(temp);
    }

    return dataVariant(newList);
}

dataVariant searchVisitor::operator()(map<std::string, dataVariant> m, string s) const {
    auto variable = m.find(s);
    if(variable != m.end()) {
        return variable->second;
    }
    throw std::invalid_argument("Variable Not Found");
}

dataVariant sizeVisitor::operator()(std::vector<dataVariant> &v) const {
    int size = v.size();
    return dataVariant(size);
}

dataVariant sizeVisitor::operator()(std::map<std::string, dataVariant> &m) const {
    int size = m.size();
    return dataVariant(size);
}

//WIP
dataVariant containsVisitor::operator()(std::vector<dataVariant> v, string s) const {
    auto variable = std::find(v.begin(), v.end(), s);
    if(variable == v.end()) {
        return false;
    }
    return true;
}

dataVariant containsVisitor::operator()(map<std::string, dataVariant> m, string s) const {
    auto variable = m.find(s);
    if(variable == m.end()) {
        return false;
    }
    return true;
}