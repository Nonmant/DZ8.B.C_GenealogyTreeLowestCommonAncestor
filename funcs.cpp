//https://contest.yandex.ru/contest/29403/problems/B/

#include "funcs.h"
#include <bits/stdc++.h>

struct TreeNode{
    std::vector<TreeNode *> children;
    std::string name;
    explicit TreeNode(const std::string & name):
            name(name){};

    //! @return true if added, false otherwise
    bool add(const std::string & child,
             const std::string & parent){
        if(parent == name){
            children.push_back(new TreeNode(child));
            return true;
        }
        for(auto & myChild : children){
            if(myChild->add(child,parent))
                return true;
        }
        return false;
    }

    [[nodiscard]]
    bool find(const std::string & givenName) const{
        if(name == givenName)
            return true;
        return std::any_of(children.begin(), children.end(),
                    [givenName](const TreeNode * child){
                        return child->find(givenName);
                    });
    }

    [[nodiscard]]
    int getRelationship(const std::string & first,
                        const std::string & second) const{
        if(first == name){
            if(find(second)){
                return 1;
            } else {
                return 0;
            }
        }
        if(second == name){
            if(find(first)){
                return 2;
            } else {
                return 0;
            }
        }
        int rv;
        for(auto & child : children){
            rv = child->getRelationship(first,second);
            if(rv >= 0) return rv;
        }
        return -1;
    }
    ~TreeNode(){
        auto i = children.size();
        while (i--){
            delete children[i];
        }
    }
};

struct Tree{
    TreeNode * root;
public:
    Tree(): root(nullptr){}

    void add(const std::string & child,
             const std::string & parent){
        if(root == nullptr){
            root = new TreeNode(parent);
        }
        root->add(child,parent);
    }

    [[nodiscard]]
    int getRelationship(const std::string & first,
                        const std::string & second) const{
        if(root == nullptr)
            return 0;
        int rv =  root->getRelationship(first,second);
        if(rv == -1)
            return 0;
        return rv;
    }

    ~Tree(){
        delete root;
    }
};

void parseFile(std::istream & input, std::ostream & output){
    Tree tree;

    int n;
    input >> n;
    std::string firstName, secondName;
    for(int i = 1; i<n; ++i){
        input >> firstName >> secondName;
        tree.add(firstName,secondName);
    }
    while (input >> firstName >> secondName){
        output << tree.getRelationship(firstName,secondName) << ' ';
    }
}
