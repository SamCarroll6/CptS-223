#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector>
#include <algorithm> // For max() function
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }

    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
       cout << " [!] Destructor called." << endl;
       makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     *  TODO: Implement
     */
    bool isEmpty( ) const
    {
        if (this->root != nullptr)
        return false;
        else
        return true;  // so not correct
    }

    /**
     * Return number of elements in tree.
     */
    int size( )
    {
      return size( root );
    }

    /**
     * Return height of tree.
     *  Null nodes are height -1
     */
    int height( )
    {
      return height( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printInOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in pre order.
     */
    void printPreOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPreOrder( root );
    }

    /**
     * Print the tree contents in post order.
     */
    void printPostOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPostOrder( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert vector of x's into the tree; duplicates are ignored.
     */
    void insert( vector<Comparable> vals)
    {
      for( auto x : vals ) {
        insert( x, root );
      }
    }


    /**
     * Remove x from the tree. Nothing is done if x is not found.
     *  TODO: Implement
     */
    void remove( const Comparable & x )
    {
      AvlNode *hold = this->root, *parent = hold;
      while(hold != nullptr && hold->element != x){
        parent = hold;
        if(x > hold->element)
        hold = hold->right;
        else{
          hold = hold->left;
        }
      }
      if(hold == nullptr)
      cout << "Node Not Found" << endl;
      else{
        //Deleting the root
        if(parent == this->root && hold == this->root){
          AvlNode *temp = findMin(hold->right), *tempP = parent;
          if(temp == hold->right && hold->right != nullptr){
            temp->left = parent->left;
            parent->right = nullptr;
            parent->left = nullptr;
            delete parent;
            this->root = temp;
          }
          else if(hold->right == nullptr){
            temp = hold->left;
            delete hold;
            this->root = temp;
          }
          else{
            tempP = hold->right;
            while(tempP->left != temp){
              tempP = tempP->left;
            }
            tempP->left = temp->right;
            temp->right = parent->right;
            temp->left = parent->left;
            delete parent;
            this->root = temp;
          }
        }
        //No children, or one child
        else if(hold->left == nullptr || hold->right == nullptr){
          AvlNode *temp = hold->left ? hold->left : hold->right;
          //No children
          if(temp == nullptr){
            if(hold->element < parent->element){
              parent->left = nullptr;
              delete hold;
            }
            else{
              parent->right = nullptr;
              delete hold;
            }
          }
          //One child to left
          else if(temp == hold->left){
            if(hold == parent->left){
              parent->left = hold->left;
              hold->left = nullptr;
              delete hold;
            }
            else{
            parent->right = hold->left;
            hold->left = nullptr;
            delete hold;
            }
          }
          //One child to right
          else if(temp == hold->right){
            if(hold == parent->left){
            parent->left = hold->right;
            hold->right = nullptr;
            delete hold;
            }
            else{
            parent->right = hold->right;
            hold->right = nullptr;
            delete hold;
            }
          }
        }
        else if(hold->left != nullptr && hold->right != nullptr){
          // Heavy on left or even
          AvlNode *temp = hold->right, *tempP = hold;
          while(temp->left != nullptr){
            tempP = temp;
            temp = temp->left;
          }
          if(tempP == hold){
            if(parent->left == hold){
            parent->left = temp;
            temp->left = hold->left;
            delete hold;
          }
          else{
            parent->right = temp;
            temp->left = hold->left;
            delete hold;
          }
          }
          else{
          if(parent->left == hold){
            parent->left = temp;
            tempP->left = temp->right;
            temp->right = hold->right;
            temp->left = hold->left;
            delete hold;
          }
          else{
            parent->right = temp;
            tempP->left = temp->right;
            temp->right = hold->right;
            temp->left = hold->left;
            delete hold;
          }
        }
      }
    }
  }


    /**
     * Deep copy. - or copy assignment operator
     *  Will be in part II
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
      cout << " [!] Copy *assignment* operator called." << endl;
      return *this;
    }

    int getBalance(){
      return getBalance(this->root);
    }

/*****************************************************************************/
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }

        ~AvlNode(){
          left = nullptr;
          right = nullptr;
        }
    };

    AvlNode *root;


    /**
     * Internal method to count nodes in tree
     *  TODO: Implement
     */
    int size( AvlNode * & t )
    {
      if(root == nullptr || t == nullptr)
      return(0);
      else{
      return(size(t->left) + 1 + size(t->right));
      }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *  TODO: Implement
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
      if (t == nullptr){
        if(t == root){
          root = new AvlNode(x, nullptr, nullptr);
          return;
        }
          t = new AvlNode(x, nullptr, nullptr);
          return;
      }
      else if(t->element < x){
        t->height++;
        insert(x, t->right);
      }
      else if(t->element >= x){
        t->height++;
        insert(x, t->left);
      }

      if(getBalance(t) == 0 || getBalance(t) == 1 || getBalance(t) == -1){
        return;
      }

      //Heavy on left side
      AvlNode *CheckL = t->left, *CheckR = t->right;
      if(getBalance(t) > 1 && getBalance(CheckL) == 1){
        t = rotateWithLeftChild(t);
      }
      else if(getBalance(t) > 1 && getBalance(CheckL) == -1){
        t = doubleWithLeftChild(t);
      }
      //Heavy on right side
    else if(getBalance(t) < -1 && getBalance(CheckR) == 1){
        t = doubleWithRightChild(t);
    }
    else if(getBalance(t) < -1 && getBalance(CheckR) == -1) {
        t = rotateWithRightChild(t);
      }
    }

    int getBalance(AvlNode *t){
      if(t == nullptr)
      return 0;
      else{
        return height(t->left) - height(t->right);
      }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     *  You'll need this for deletes
     *  TODO: Implement
     */
    AvlNode * findMin( AvlNode *t ) const
    {
      if(t == nullptr){
        return t;
      }
      while (t->left != nullptr){
        t = t->left;
      }
      return t; // placeholder
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     *  TODO: Implement
     */
    AvlNode * findMax( AvlNode *t ) const
    {
      if(t == nullptr){
        return t;
      }
      while (t->right != nullptr){
        t = t->right;
      }
      return t;  // placeholder
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     *  TODO: Implement
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
      while (t != nullptr){
        if(x == t->element)
        {return true;}
        else if(x > t->element)
        {t = t->right;}
        else if(x < t->element)
        {t = t->left;}
      }
      return false;    // Lolz
    }

/******************************************************/

    /**
     * Internal method to make subtree empty.
     *  TODO: implement for destructor
     *
     */
    void makeEmpty( AvlNode * & t )
    {
        if(t == nullptr)
        return;
        else{
          makeEmpty(t->left);
          makeEmpty(t->right);
          delete t;
        }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     *  TODO: Implement
     */
    void printInOrder( AvlNode *t ) const
    {
      //cout << "  [!] Printing In Order";
      if(t != nullptr){
        printInOrder(t->left);
        cout << t->element << " ";
        printInOrder(t->right);
      }
      else{
        return;
      }
    }

    /**
     * Internal method to print a subtree rooted at t in pre order.
     *  TODO: Implement
     */
    void printPreOrder( AvlNode *t ) const
    {
      if(t != nullptr){
        cout << t->element << " ";
        printPreOrder(t->left);
        printPreOrder(t->right);
      }
      else{
        return;
      }
    }

    /**
     * Internal method to print a subtree rooted at t in post order.
     *  TODO: Implement
     */
    void printPostOrder( AvlNode *t ) const
    {
      if(t != nullptr){
        printPreOrder(t->left);
        printPreOrder(t->right);
        cout << t->element << " ";
      }
      else{
        return;
      }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }


    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     *  TODO: Implement
     */
    int height( AvlNode *t ) const
    {
      int SR = 0, SL = 0;
			if (t == nullptr)
      return (-1);
      else{
        if(t->left != nullptr){
          SL = height(t->left) + 1;
        }
        if(t->right != nullptr){
           SR = height(t->right) + 1;
        }
        if(SR > SL)
        return SR;
        else{
          return SL;
        }
      }
    }


    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    AvlNode * rotateWithLeftChild( AvlNode * & k2 )
    {
      AvlNode *temp = k2->left;
      k2->left = temp->right;
      temp->right = k2;
      k2->height = height(k2);
      temp->height = height(temp);
      return temp;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    AvlNode * rotateWithRightChild( AvlNode * & k1 )
    {
      AvlNode *temp = k1->right;
      k1->right = temp->left;
      temp->left = k1;
      k1->height = height(k1);
      temp->height = height(temp);
      return temp;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    AvlNode * doubleWithLeftChild( AvlNode * & k3 )
    {
      AvlNode *temp = k3->left;
      k3->left = rotateWithRightChild(temp);
      return rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    AvlNode * doubleWithRightChild( AvlNode * & k1 )
    {
      AvlNode * temp = k1->right;
      k1->right = rotateWithLeftChild(temp);
      return rotateWithRightChild(k1);
    }
};

#endif
