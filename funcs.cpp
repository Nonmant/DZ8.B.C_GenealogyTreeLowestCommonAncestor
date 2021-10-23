//https://contest.yandex.ru/contest/29403/problems/B/

#include "funcs.h"
#include <bits/stdc++.h>

struct TreeNode{
    TreeNode * parentNode = nullptr;
    std::string parentKey;
};

struct Tree{
    std::map<const std::string, TreeNode *> nodes;
public:

    void add(const std::string & child,
             const std::string & parent){
        auto childNode = nodes[child];
        auto parentNode = nodes[parent];

        if(parentNode == nullptr){
            nodes[parent] = parentNode = new TreeNode;
        }
        if(childNode == nullptr){
            nodes[child] = childNode = new TreeNode;
        }
        childNode->parentNode = parentNode;
        //! @todo duplicating data
        childNode->parentKey = parent;
    }

    [[nodiscard]]
    std::vector<std::string *>
            getNodeAncestors(std::string & nodeKey){
        std::vector<std::string *> ans;

        TreeNode * node = nodes[nodeKey];
        if(node == nullptr)
            return ans;
        ans.push_back(&nodeKey);
        while (node->parentNode != nullptr){
            ans.push_back(&node->parentKey);
            node = node->parentNode;
        }
        return ans;
    }

    [[nodiscard]]
    //!@todo this one fails
    std::string getLCA(std::string & first,
                       std::string & second){
        std::vector<std::string *> firstAncestors =
                getNodeAncestors(first);
        std::vector<std::string *> secondAncestors =
                getNodeAncestors(second);

        std::string  ans;

        for(auto & firstParent : firstAncestors){
            for(auto & secondParent : secondAncestors){
                if(firstParent == secondParent){
                    ans = * firstParent;
                }
            }
        }

        return ans;
    }

    ~Tree(){
        for(auto & node : nodes){
            delete node.second;
        }
        nodes.clear();
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
