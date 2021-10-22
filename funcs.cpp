//https://contest.yandex.ru/contest/29403/problems/B/

#include "funcs.h"
#include <bits/stdc++.h>

struct TreeNode{
    std::map<const std::string,TreeNode *>children;

    //! @return true if added, false otherwise
    bool add(TreeNode * child,
             const std::string & childName,
             const std::string & parent){
        if(children.count(parent)){
            children.at(parent)->children[childName] = new TreeNode;
        }
        for(auto & myChild : children){
            if(myChild.second->add(child,childName,parent))
                return true;
        }
        return false;
    }

    [[nodiscard]]
    std::string getLCA(const std::string & first,
                       const std::string & second){
        std::list<std::pair<const TreeNode *,const std::string &>> path;
        int rv = findAncestorsOfAny(first,second,path);
        if(rv == 0)
            return {};
        const std::string & searching =
                rv == 1 ? second : first;
        TreeNode const * except = nullptr;
        for(auto node=path.rbegin(); node!=path.rend();++node){
            if((*node).first->find(searching,except))
                return (*node).second;
            except = (*node).first;
        }
        return {};
    }

    ~TreeNode(){
        for(auto child : children){
            delete child.second;
        }
        children.clear();
    }

protected:
    //! @return 0 - not found, 1 - found first, 2 - found second
    int findAncestorsOfAny(const std::string & first,
                            const std::string & second,
                            std::list<std::pair<const TreeNode *,const std::string &>> & path) const{
        if(children.count(first)){
            path.emplace_back(children.at(first),first);
            return 1;
        }
        if(children.count(first)){
            path.emplace_back(children.at(second),second);
            return 2;
        }

        for(const auto & child: children ){
            int rv = child.second->findAncestorsOfAny(first,second,path);
            if(rv!=0){
                path.emplace_back(child.second,child.first);
                return rv;
            }

        }
        return 0;
    }

    [[nodiscard]]
    bool find(const std::string & givenName) const{
        if(children.count(givenName))
            return true;
        for(const auto & child : children){
            if(child.second->find(givenName))
                return true;
        }
        return false;
    }

    [[nodiscard]]
    bool find(const std::string & givenName,
              const TreeNode * except) const{
        if(children.count(givenName))
            return true;
        for(const auto & child : children){
            if(child.second == except)
                continue;
            if(child.second->find(givenName))
                return true;
        }
        return false;
    }
};

struct Tree : public TreeNode{
public:

    void add(const std::string & child,
             const std::string & parent){
        TreeNode * hangingNode = nullptr;
        if(children.count(child)){
            hangingNode = children[child];
            children.erase(child);
        }
        if(hangingNode == nullptr)
            hangingNode = new TreeNode;
        bool added  = TreeNode::add(hangingNode,child,parent);
        if(!added){
            children[child] = hangingNode;
        }
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
