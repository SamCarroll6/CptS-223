/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *
 */

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
using namespace std;

/*
 *  Node datastructure for single tree node
 */
template <class T>
struct Node {

private:
    Node *leftnode;
    Node *rightnode;
    T val;
public:
    Node(){
      leftnode = nullptr;
      rightnode = nullptr;
    }
    Node(T value){
      leftnode = nullptr;
      rightnode = nullptr;
      val = value;
    }
    ~Node(){
      leftnode = nullptr;
      rightnode = nullptr;
      val = 0;
    }
    Node *getright(){
      return rightnode;
    }
    Node *getleft(){
      return leftnode;
    }
    T &getval(){
      return val;
    }
    void setright(Node<T> *newright){
      rightnode = newright;
    }
    void setleft(Node<T> *newleft){
      leftnode = newleft;
    }
    void setval(T newval){
      val = newval;
    }
};


/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {

    private:
    Node<T> *root;

    void addPri(T val, Node<T> *LorR) {
      //cout << " [!] BST::add currently unimplemented." << endl;
      if(this->root == nullptr)
      {
        setroot(new Node<T> (val));
      }
      else if(root->getval() < val || root->getval() == val)
      {
       if(LorR->getright() == nullptr)
        {
         LorR->setright(new Node<T> (val));
        }
        else
        addPri(val, LorR->getright());
      }
      else if(root->getval() > val)
      {
       if(LorR->getleft() == nullptr)
        {
         LorR->setleft(new Node<T> (val));
        }
        else
        addPri(val, LorR->getleft());
      }
    }

    void printPreOrder(Node<T> *LorR) {
      //cout << " [!] BST::printPreOrder currently unimplemented." << endl;
      if(LorR != nullptr){
        cout << LorR->getval() << " ";
        printPreOrder(LorR->getleft());
        printPreOrder(LorR->getright());
      }
      else{
        return;
      }
    }

    int heightPri(Node<T> *LorR) {
      //cout << " [!] BST::height currently unimplemented." << endl;
      if(LorR == nullptr)
      return( -1 );
      int left = heightPri(LorR->getleft());
      int right = heightPri(LorR->getright());
      if(left > right)
      return left + 1;
      else
      return right +1;
    }

    int nodesCountPri(Node<T> *LorR) {
      if(LorR == nullptr)
      return( 0 );
      return 1 + nodesCountPri(LorR->getright()) + nodesCountPri(LorR->getleft());
    }

    public:
    BST(){
      this->root = nullptr;
    }
    ~BST(){
      deleteBST(root);
    }
    void deleteBST(Node<T> *LorR){
      if(LorR != nullptr){
        deleteBST(LorR->getleft());
        deleteBST(LorR->getright());
        delete LorR;
      }
      else{
        return;
      }
    }
    Node<T> *getroot(){
      return root;
    }
    void setroot(Node<T> *newroot){
      this->root = newroot;
    }
    void add(T val) {
      //cout << "Implementing addPri" << endl;
      this->addPri(val, root);
    }

    void print() {
			this->printPreOrder(root);
    }

    int nodesCount() {
      return this->nodesCountPri(root);
    }

    int height() {
      if(root == nullptr){
        return 0;
      }
      else
      return heightPri(root) + 1;
    }
};

#endif
