//
// Created by Hasan on 8.11.2023.
//

//#include "AVLSearchTree.h"
#include <string>
#include <iostream>
using namespace std;
string not_found = "item not found";
template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree()
{
    root = NULL;
}

template <class Key, class Value>
int AVLSearchTree<Key,Value>::height(AvlNode<Key,Value> * t) const
{
    if (t == NULL)
        return -1;

    return t->height;
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::insert(const Key &x, const Value &y, AvlNode<Key,Value> *&t) const
{
    if ( t == NULL )
        t = new AvlNode<Key,Value>( x, y, NULL, NULL );

    else if ( x < t->key ) {
        // X should be inserted to the left tree!
        insert( x, y, t->left );

        // Check if the left tree is out of balance (left subtree grew in height!)
        if ( height( t->left ) - height( t->right ) == 2 )
            if ( x < t->left->key )  // X was inserted to the left-left subtree!
                rotateWithLeftChild( t );
            else			     // X was inserted to the left-right subtree!
                doubleWithLeftChild( t );
    }
    else if( t->key < x )
    {    // Otherwise X is inserted to the right subtree
        insert( x, y, t->right );
        if ( height( t->right ) - height( t->left ) == 2 )
            // height of the right subtree increased
            if ( t->right->key < x )
                // X was inserted to right-right subtree
                rotateWithRightChild( t );
            else // X was inserted to right-left subtree
                doubleWithRightChild( t );
    }
    else
        ;  // Duplicate; do nothing

    // update the height the node
    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::rotateWithLeftChild(AvlNode<Key,Value> *&k2) const
{
    AvlNode<Key,Value> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::rotateWithRightChild(AvlNode<Key,Value> *&k1) const
{
    AvlNode<Key,Value> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::doubleWithLeftChild(AvlNode<Key,Value> *&k3) const
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::doubleWithRightChild(AvlNode<Key,Value> *&k1) const
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}

template <class Key, class Value>
const Key & AVLSearchTree<Key,Value>::keyAt(AvlNode<Key,Value> *t) const
{
    if(t != NULL)
    {
        return t->key;
    }
    return not_found;
}

template <class Key, class Value>
Value & AVLSearchTree<Key,Value>::valueOf(Key key) //returns the value object of the tree for the given key
{
    AvlNode<Key, Value> *temp;
    temp = find(key, root);
    return temp->value;
}

template <class Key, class Value>
const Key & AVLSearchTree<Key,Value>::find(const Key &x) const
{
    return keyAt( find( x, root ) );
}

template <class Key, class Value>
const Key & AVLSearchTree<Key,Value>::findMin() const
{
    return keyAt( findMin( root ) );
}

template <class Key, class Value>
AvlNode<Key,Value> * AVLSearchTree<Key,Value>::findMin(AvlNode<Key, Value> *t) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Key, class Value>
const Key & AVLSearchTree<Key,Value>::findMax() const
{
    return keyAt(findMax(root));
}

template <class Key, class Value>
AvlNode<Key,Value> * AVLSearchTree<Key,Value>::findMax(AvlNode<Key, Value> *t) const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;

}

template <class Key, class Value>
AvlNode<Key,Value> * AVLSearchTree<Key,Value>::find(const Key &x, AvlNode<Key,Value> *t) const
{
    if ( t == NULL )
        return NULL;
    else if( x < t->key )
        return find( x, t->left );
    else if( t->key < x )
        return find( x, t->right );
    else
        return t;    // Match
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::insert(const Key &x, const Value &y)
{
    insert(x,y, root);
}

template <class Key, class Value>
bool AVLSearchTree<Key,Value>::isEmpty() const
{
    return root == NULL;
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::makeEmpty()
{
    makeEmpty(root);
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::makeEmpty(AvlNode<Key, Value> *&t) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

template <class Key, class Value>
AVLSearchTree<Key,Value>::~AVLSearchTree()
{
    makeEmpty();
}

template <class Key,class Value>
AvlNode<Key,Value> * AVLSearchTree<Key,Value>::clone(AvlNode<Key, Value> *t) const
{
    if ( t == NULL )
        return NULL;
    else
        return new AvlNode<Key,Value>( t->key, t->value, clone( t->left ), clone( t->right ), t->height);
}

template<class Key, class Value>
AVLSearchTree<Key,Value>::AVLSearchTree(const AVLSearchTree<Key, Value> &rhs)
{
    makeEmpty();
    root = clone(rhs);
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::remove(const Key &x)
{
    remove(x,root);
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::remove(const Key &x, AvlNode<Key, Value> *&t) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if (x < t->key)
    {
        remove(x, t->left);
    }
    else if( t->key < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->key = findMin( t->right )->key;
        t->value = findMin(t->right)->value;
        remove( t->key, t->right );
    }
    else // one or no children
    {
        AvlNode<Key,Value> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
    if(t != NULL)
    {
        t->height = max(height(t->left), height(t->right)) + 1;

        if (height(t->left) - height(t->right) == 2) //deleted from right subtree
        {
            if(t->right == NULL)
            {
                rotateWithLeftChild(t);
            }
            else if (x > t->right->key)//right of right
            {
                doubleWithLeftChild(t);
            } else //left of right
            {
                rotateWithLeftChild(t);
            }
        }
        if (height(t->right) - height(t->left) == 2) //deleted from left subtree
        {
            if(t->left == NULL)
            {
                rotateWithRightChild(t);
            }
            else if (x > t->left->key)//right of left
            {
                rotateWithRightChild(t);
            } else //left of left
            {
                doubleWithRightChild(t);
            }
        }
    }
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::printTree() const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::printTree(AvlNode<Key, Value> *t) const
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->key << endl;
        printTree( t->right );
    }
}

