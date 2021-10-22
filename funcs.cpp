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
    std::string getLCA(const std::string & first,
                       const std::string & second){
        std::list<const TreeNode *> path;
        int rv = findAncestorsOfAny(first,second,path);
        if(rv == 0)
            return {};
        const std::string & searching =
                rv == 1 ? second : first;
        TreeNode const * except = nullptr;
        for(auto node=path.rbegin(); node!=path.rend();++node){
            if((*node)->find(searching,except))
                return (*node)->name;
            except = *node;
        }
        return {};
    }

    ~TreeNode(){
        for(auto child : children){
            delete child;
        }
        children.clear();
    }

protected:
    //! @return 0 - not found, 1 - found first, 2 - found second
    int findAncestorsOfAny(const std::string & first,
                            const std::string & second,
                            std::list<const TreeNode *> & path) const{
        path.push_back(this);
        if(name == first){
            return 1;
        }
        if(name == second){
            return 2;
        }

        for(const auto & child: children ){
            int rv = child->findAncestorsOfAny(first,second,path);
            if(rv!=0)
                return rv;
        }
        path.pop_back();
        return 0;
    }

    [[nodiscard]]
    bool find(const std::string & givenName,
              const TreeNode * except) const{
        if(name == givenName)
            return true;
        return std::any_of(children.begin(), children.end(),
                           [givenName, &except](const TreeNode * child){
                               return child != except && child->find(givenName);
                           });
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
    std::string getLCA(const std::string & first,
                       const std::string & second) const {
        std::string ans;
        for(auto root : roots){
            ans = root->getLCA(first,second);
            if(!ans.empty())
                return ans;
        }
        return ans;
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
        output << tree.getLCA(firstName,secondName) << '\n';
    }
}
