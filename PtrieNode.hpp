#ifndef PTRIENODE_H
#define PTRIENODE_H
#include <map>
#include <iostream>
#include <string>
using namespace std;


class TrieNodeP {
    public:
    map<string,TrieNodeP*> children;
    string completo;

    TrieNodeP():completo(""){}
    ~TrieNodeP();
    TrieNodeP* get (string key){
        if(children.find(key)==children.end())
        return nullptr;
        else return children.at(key);
    }
};

#endif