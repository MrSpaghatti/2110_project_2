// Purpose: Implements department insertion, search, and the tree traversals. Author: Matthew Ojeh Jr.
#include "DepartmentTree.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
void DepartmentTree::collectPreorder(const Node* node, std::vector<std::string>& out) const {
    if (!node) return;
    out.push_back(node->name);
    for (const auto& child:node->children) collectPreorder(child.get(),out);
}
void DepartmentTree::collectPostorder(const Node* node, std::vector<std::string>& out) const {
    if (!node) return;
    for (const auto& child:node->children) collectPostorder(child.get(),out);
    out.push_back(node->name);
}
DepartmentTree::Node* DepartmentTree::findNode(const std::string& name) const {
    std::vector<std::string> unused;
    if (!root_) return nullptr;
    std::vector<Node*> stack{root_.get()};
    auto norm=[](const std::string& x){ std::string y=x; for(char& c:y)c=static_cast<char>(std::tolower(static_cast<unsigned char>(c))); return y; };
    while(!stack.empty()) {
        Node* n=stack.back(); stack.pop_back();
        if(norm(n->name)==norm(name)) return n;
        for(auto it=n->children.rbegin();it!=n->children.rend();++it) stack.push_back(it->get());
    }
    return nullptr;
}
bool DepartmentTree::add(const std::string& name, const std::string& parent, std::string& reason) {
    if(name.empty()) { reason="department name cannot be blank"; return false; }
    if(findNode(name)) { reason="duplicate department: "+name; return false; }
    if(!root_) {
        if(!parent.empty() && parent!="NONE") { reason="the root must have parent NONE"; return false; }
        root_=std::make_unique<Node>(name,nullptr); return true;
    }
    Node* p=findNode(parent);
    if(!p) { reason="unknown parent: "+parent; return false; }
    p->children.push_back(std::make_unique<Node>(name,p));
    return true;
}
bool DepartmentTree::contains(const std::string& name) const { return findNode(name)!=nullptr; }
void DepartmentTree::search(const std::string& name) const {
    Node* n=findNode(name);
    if(!n) { std::cout<<"Department not found: "<<name<<"\n"; return; }
    int depth=0; for(Node* p=n->parent;p;p=p->parent) ++depth;
    std::cout<<"Name: "<<n->name<<"\nParent: "<<(n->parent?n->parent->name:"None")
             <<"\nDirect children: "<<n->children.size()<<"\nDepth: "<<depth<<"\n";
}
void DepartmentTree::printIndented(const Node* node,int depth) const {
    if(!node)return;
    for(int i=0;i<depth;++i) std::cout<<"    ";
    std::cout<<node->name<<"\n";
    for(const auto& child:node->children) printIndented(child.get(),depth+1);
}
void DepartmentTree::displayHierarchy() const {
    if(!root_) { std::cout<<"No departments are loaded.\n"; return; }
    printIndented(root_.get(),0);
}
void DepartmentTree::preorder() const {
    if(!root_) { std::cout<<"No departments are loaded.\n"; return; }
    std::vector<std::string> names; collectPreorder(root_.get(),names);
    for(std::size_t i=0;i<names.size();++i) std::cout<<(i?" -> ":"")<<names[i];
    std::cout<<"\n";
}
void DepartmentTree::postorder() const {
    if(!root_) { std::cout<<"No departments are loaded.\n"; return; }
    std::vector<std::string> names; collectPostorder(root_.get(),names);
    for(std::size_t i=0;i<names.size();++i) std::cout<<(i?" -> ":"")<<names[i];
    std::cout<<"\n";
}
void DepartmentTree::levelOrder() const {
    if(!root_) { std::cout<<"No departments are loaded.\n"; return; }
    std::queue<const Node*> q;
    q.push(root_.get());
    bool first=true;
    while(!q.empty()) {
        const Node* n=q.front(); q.pop();
        std::cout<<(first?"":" -> ")<<n->name;
        first=false;
        for(const auto& child:n->children) q.push(child.get());
    }
    std::cout<<"\n";
}
int DepartmentTree::heightOf(const Node* node) {
    if(!node) return -1;
    int best=0;
    for(const auto& child:node->children) best=std::max(best,1+heightOf(child.get()));
    return best;
}
void DepartmentTree::statistics() const {
    std::size_t total=0, leaves=0;
    std::queue<const Node*> q;
    if(root_) q.push(root_.get());
    while(!q.empty()) {
        const Node* n=q.front(); q.pop();
        ++total;
        if(n->children.empty()) ++leaves;
        for(const auto& child:n->children) q.push(child.get());
    }
    std::cout<<"Total departments: "<<total<<"\n"
             <<"Leaf departments: "<<leaves<<"\n";
    if(!root_) std::cout<<"Height: N/A\n";
    else std::cout<<"Height: "<<heightOf(root_.get())<<"\n";
}
bool DepartmentTree::empty() const { return !root_; }
