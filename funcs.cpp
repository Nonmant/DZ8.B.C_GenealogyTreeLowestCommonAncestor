//https://contest.yandex.ru/contest/29403/problems/B/

#include "funcs.h"
#include <bits/stdc++.h>

struct TreeNode{
    std::unordered_set<TreeNode *> children;
    std::string name;
    explicit TreeNode(const std::string & name):
            name(name){};

    //! @return true if added, false otherwise
    bool add(TreeNode * child,
             const std::string & parent){
        if(parent == name){
            children.insert(child);
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
        for(auto child : children){
            delete child;
        }
        children.clear();
    }
};

struct Tree{
    std::unordered_set<TreeNode *> roots;
public:

    void add(const std::string & child,
             const std::string & parent){
        TreeNode * hangingNode = nullptr;
        for(auto root : roots){
            if(child == root->name){
                hangingNode = root;
                roots.erase(root);
                break;
            }
        }
        if(hangingNode == nullptr)
            hangingNode = new TreeNode(child);
        for(auto root : roots){
            if(root->add(hangingNode,parent))
                return;
        }

        auto addedRoot = new TreeNode(parent);
        addedRoot->add(hangingNode, parent);
        roots.insert(addedRoot);
    }

    [[nodiscard]]
    int getRelationship(const std::string & first,
                        const std::string & second) const{
        int rv = -1;
        for(auto root : roots){
            rv = root->getRelationship(first,second);
            if(rv!=-1)
                break;
        }
        if(rv == -1)
            return 0;
        return rv;
    }

    ~Tree(){
        for(auto root : roots){
            delete root;
        }
        roots.clear();
        roots.clear();
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
