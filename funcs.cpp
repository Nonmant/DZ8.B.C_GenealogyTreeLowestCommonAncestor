//https://contest.yandex.ru/contest/29403/problems/B/

#include "funcs.h"
#include <bits/stdc++.h>

class TreeNode;

typedef std::set<std::pair<const std::string,TreeNode *>>::iterator ChildIterator;

struct TreeNode{
    std::set<std::pair<const std::string,TreeNode *>>children;

    bool findDirectChild(const std::string & name,
                              ChildIterator & iterator) const{
        //O(log(N))
        iterator = children.upper_bound(std::make_pair(name,nullptr));
        return iterator->first == name;
    }
    [[nodiscard]]
    bool findDirectChild(const std::string & name) const{
        auto iterator = children.upper_bound(std::make_pair(name,nullptr));
        return iterator->first == name;
    }

    //! @return true if added, false otherwise
    bool add(TreeNode * child,
             const std::string & childName,
             const std::string & parent){
        ChildIterator iterator;
        if(findDirectChild(parent,iterator)){
            iterator->second->children.emplace(childName,child);
            return true;
        }
        for(auto & myChild : children){
            if(myChild.second->add(child,childName,parent))
                return true;
        }
        return false;
    }

    [[nodiscard]]
    virtual
    std::string getLCA(const std::string & first,
                       const std::string & second){
        std::list<std::pair<const TreeNode *,const std::string &>> path;
        int rv = findAncestorsOfAny(first,second,path);
        if(rv == 0)
            return {};
        const std::string & searching =
                rv == 1 ? second : first;
        TreeNode const * except = nullptr;
        for(const auto & node : path){
            if(node.first->find(searching,except))
                return node.second;
            except = node.first;
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
        ChildIterator iterator;
        if(findDirectChild(first,iterator)){
            path.emplace_back(iterator->second,first);
            return 1;
        }
        if(findDirectChild(second,iterator)){
            path.emplace_back(iterator->second,second);
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
        if(findDirectChild(givenName))
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
        if(findDirectChild(givenName))
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
        ChildIterator iterator;
        if(findDirectChild(child,iterator)){
            hangingNode = iterator->second;
            children.erase(iterator);
        }
        if(hangingNode == nullptr)
            hangingNode = new TreeNode;
        bool added  = TreeNode::add(hangingNode,child,parent);
        if(!added){
            auto parentNode = new TreeNode;
            parentNode->children.emplace(child,hangingNode);
            children.emplace(parent,parentNode);
        }
    }

    [[nodiscard]]
    std::string getLCA(const std::string & first,
                       const std::string & second) override{
        if(first == second)
            return first;
        return TreeNode::getLCA(first,second);
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
