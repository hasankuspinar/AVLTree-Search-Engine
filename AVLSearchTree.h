//
// Created by Hasan on 8.11.2023.
//

#ifndef CS300HW2_AVLSEARCHTREE_H
#define CS300HW2_AVLSEARCHTREE_H

template <class Key, class Value>
struct AvlNode
{
    Key key;
    Value value;
    AvlNode   		*left;
    AvlNode   		*right;
    int        		height;

    AvlNode( const Key & theKey, const Value & theValue,
             AvlNode *lt, AvlNode *rt, int h = 0 )
            : key( theKey ),value( theValue ), left( lt ), right( rt ), height( h ) { }

};
template <class Key, class Value>
class AVLSearchTree
{
private:
    AvlNode<Key,Value> * root;

    const Key & keyAt( AvlNode<Key,Value> *t ) const;

    void insert( const Key & x, const Value & y, AvlNode<Key,Value> * & t ) const;
    void remove(const Key & x, AvlNode<Key,Value> * & t ) const;

    AvlNode<Key,Value> * findMin( AvlNode<Key,Value> *t ) const;
    AvlNode<Key,Value> * findMax( AvlNode<Key,Value> *t ) const;
    AvlNode<Key,Value> * find( const Key & x, AvlNode<Key,Value> *t )const;
    void makeEmpty( AvlNode<Key,Value> * & t ) const;
    AvlNode<Key,Value> * clone( AvlNode<Key,Value> *t ) const;

    // Avl manipulations
    int height( AvlNode<Key,Value> *t ) const;
    void rotateWithLeftChild( AvlNode<Key,Value> * & k2 ) const;
    void rotateWithRightChild( AvlNode<Key,Value> * & k1 ) const;
    void doubleWithLeftChild( AvlNode<Key,Value> * & k3 ) const;
    void doubleWithRightChild( AvlNode<Key,Value> * & k1 ) const;
    void printTree(AvlNode<Key,Value> * t)const;

public:
    AVLSearchTree();
    AVLSearchTree(const AVLSearchTree & rhs);
    ~AVLSearchTree( );

    void printTree()const;
    const Key & find( const Key & x ) const;
    Value & valueOf( Key key );
    bool isEmpty( ) const;
    const Key & findMin( ) const;
    const Key & findMax( ) const;


    void makeEmpty( );
    void insert( const Key & x , const Value & y);
    void remove( const Key & x );
};




#endif //CS300HW2_AVLSEARCHTREE_H
#include "AVLSearchTree.cpp"