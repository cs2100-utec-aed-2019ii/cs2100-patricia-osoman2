#ifndef TRIENODE_H
#define TRIENODE_H
#include <map>
#include <iostream>
using namespace std;


class TrieNode {
    public:
    map<char,TrieNode*> children;
    bool is_node;

    TrieNode():is_node(false){}
    ~TrieNode();
    TrieNode* get (char key){
        if(children.find(key)==children.end())
        return nullptr;
        else return children.at(key);
    }
};

#endif