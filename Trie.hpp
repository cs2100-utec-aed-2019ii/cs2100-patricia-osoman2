#ifndef TRIE_H
#define TRIE_H
#include "TrieNode.hpp"
#include "PtrieNode.hpp"
#include "Patricia.hpp"
#include <string>
#include <fstream>

class Trie
{
public:
 
    TrieNode* root;

    Trie():root(nullptr){};
    
    ~Trie(){}


    void desde_ar_n(string n_archivo){
        ifstream archivo(n_archivo);
        string cadena;
        while(getline(archivo,cadena)){
            insert(cadena);
        }
        archivo.close();
    }

    void insert(string cad){
        if (search_by_complete_word(cad))
            return; 
        else insert(0,root,cad);
    }
    void insert(int indice,TrieNode* &nodo,string cad){
        if(cad.length()==indice){
            if(nodo) {nodo->is_node = true; return;}
        }
        if(nodo){
                auto aux = cad[indice];
                TrieNode* hijo = nodo->get(aux);
                if(hijo==nullptr){
                    hijo = new TrieNode();
                    nodo->children.insert({aux,hijo});
                    insert(indice+1,hijo,cad);
                }
                else{
                    insert(indice+1,hijo,cad);
                }
        }
        else{
            nodo = new TrieNode();
            TrieNode* hijo = new TrieNode();
            nodo->children.insert({cad[indice],hijo});
            insert(indice+1,hijo,cad);
        }
    }


    bool search_by_prefix(string cad){
        return search_by_prefix(0,cad,root); 
    }
    
    bool search_by_prefix(int indice,string cad,TrieNode* &nodo){
        if(nodo){
            auto aux = cad[indice];
            TrieNode *hijo = nodo->get(aux);
            if(hijo){
                if(cad.length()==indice+1) return true;
                else return search_by_prefix(indice+1,cad,hijo);
            }
            else return false;
        }
        else return false;
    }



    void patricia(){
        string cad;
        Patricia ptree;
        for (auto i = root->children.begin(); i!=root->children.end(); ++i)
        {
            cad = cad+i->first;
        }
        patricia_helper(root,cad,ptree.root);
    }
    void patricia_helper(TrieNode *nodo,string cadena,TrieNodeP* &pnodo){
        auto elem = nodo->children;
        if (elem.size()==1)
        {
            if(nodo->is_node==true){        
                if(elem.empty()==true){
                    TrieNodeP* nodosolo = new TrieNodeP;
                    TrieNodeP* nodosolohijo = new TrieNodeP;
                    nodosolohijo->completo = true;
                    nodosolo->children.insert({cadena,nodosolohijo});
                }
                else
                {
                    for (auto i = elem.begin() ; i != elem.end(); ++i)
                    {
                        return patricia_helper(i->second,cadena);
                    }
                    
                }    
            }
        }
          
        
        else{
            for (auto i = elem.begin(); i != elem.end(); ++i)
            {
                auto hijo = i->second;
                if(hijo->is_node==true){
                    TrieNodeP* nuevo = new TrieNodeP;
                    if (hijo->children.empty())
                    {   TrieNodeP* hijo = new TrieNodeP;
                        hijo->completo = true;
                        nuevo->children.insert({cadena,hijo});
                    }
                    else{

                    }
                }
            }
        }
    }

    bool estaenelnodo(char letra,TrieNode* &nodo ){
        if(nodo->children.find(letra)==nodo->children.end())return false;
        return true;
    }


    bool search_by_complete_word(string cad){
        return search_by_complete_word(0,cad,root); 
    }
    bool search_by_complete_word(int indice,string cad,TrieNode* &nodo){
        if(nodo){
            auto aux = cad[indice];
            TrieNode *hijo = nodo->get(aux);
            if(hijo){
                if(cad.length()==indice+1){
                    if(hijo->is_node) return true;
                    else return false;
                } 
                else return search_by_complete_word(indice+1,cad,hijo);
            }
            else return false;
        }
        else return false;
    }

    
    void delete_(string cad){
        if(search_by_complete_word(cad)==false){cout<<"No existe esa palabra"<<endl;return;}
        else delete_(root,cad,0);
    }
    void delete_(TrieNode* nodo,string cad,int indice){
        if(nodo){
            auto aux = cad[indice];
            auto hijo = nodo->get(aux);

            if (nodo->children.size()==1){
                if(indice+1==cad.length()){
                    if (hijo->children.size()==0){
                        hijo = nullptr;
                        nodo->children.clear();
                        if(search_by_complete_word(redudele(cad)))return;
                        else delete_(root,redudele(cad),0);
                    }
                    else {hijo->is_node = false;return;}
                    
                }
                else delete_(hijo,cad,indice+1);
            }
            else{
                if(indice+1==cad.length()) hijo->is_node =false;
                else delete_(hijo,cad,indice+1);
            }
        }
    }
    string redudele(string cad){
        string a;
        for (int i = 0; i < cad.length()-1; i++)
        {
            a = a+cad[i];
        }
        return a;
    }
    
    void print(){
        
        TrieNode* temp = root;
        
        string palabra;
        for (auto i = temp->children.begin(); i != temp->children.end(); ++i)
            {   
                palabra.push_back(i->first);
                
                print(palabra,i->second);
                palabra.clear(); 
            }  
    }
    void print(string cadena, TrieNode* nodo){
        if(nodo->children.empty() && nodo->is_node ){
            cout<<cadena<<endl;
            return;
        }
        if(nodo->is_node){
            cout<<cadena<<endl;
        }
        
        for (auto i = nodo->children.begin(); i != nodo->children.end(); ++i)
        {
           cadena.push_back(i->first); 
           print(cadena,i->second);
           cadena.pop_back();
        }        
    }
    TrieNodeP* patricia(){
        if(root){
        TrieNode* temp = root;
        TrieNodeP* proot = new TrieNodeP(); 
        string palabra;
        for (auto i = temp->children.begin(); i != temp->children.end(); ++i)
            {   
                palabra.push_back(i->first);
                proot = patricia(palabra,i->second,proot);
                palabra.clear(); 
            }
            return proot;  
        }
        else return nullptr;
    }
    TrieNodeP* patricia(string cadena, TrieNode* nodo,TrieNodeP* pnodo){
        if(nodo->children.empty() && nodo->is_node ){
            pnodo->completo = cadena;
            pnodo->children.clear();
            return pnodo;
        }
        TrieNodeP* nuevo = new TrieNodeP();
        if(nodo->is_node){
            for (auto i = nodo->children.begin(); i != nodo->children.end(); ++i)
            {   
                nuevo->completo = i->first;
                pnodo->children.insert({cadena,nuevo});
            } 
        }
        for (auto i = nodo->children.begin(); i != nodo->children.end(); ++i)
        {

           cadena.push_back(i->first); 
            nuevo->completo = i->first;
           patricia(cadena,i->second,nuevo);
           cadena.pop_back();
        }       
    }


};


#endif