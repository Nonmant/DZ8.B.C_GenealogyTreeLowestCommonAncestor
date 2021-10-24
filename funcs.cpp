//https://contest.yandex.ru/contest/29403/problems/C/

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
    std::list<std::pair<std::string *, TreeNode *>>
            getNodeAncestors(std::string & nodeKey){
        std::list<std::pair<std::string *, TreeNode *>> ans;

        TreeNode * node = nodes[nodeKey];
        if(node == nullptr)
            return ans;
        ans.emplace_front(&nodeKey,node);
        while (node->parentNode != nullptr){
            ans.emplace_front(&node->parentKey, node->parentNode);
            node = node->parentNode;
        }
        return ans;
    }

    [[nodiscard]]
    std::string getLCA(std::string & first,
                       std::string & second){
        std::list<std::pair<std::string *, TreeNode *>> firstAncestors =
                getNodeAncestors(first);
        std::list<std::pair<std::string *, TreeNode *>> secondAncestors =
                getNodeAncestors(second);

        std::string * ans = nullptr;

        for(auto firstParent = firstAncestors.begin(),
                    secondParent = secondAncestors.begin();
            firstParent != firstAncestors.end() && secondParent != secondAncestors.end();
            ++firstParent, ++secondParent){
            if(firstParent->second == secondParent->second)
                ans = firstParent->first;
            else
                break;
        }

        if(ans == nullptr)
            return {};

        return *ans;
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
