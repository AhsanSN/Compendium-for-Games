#ifndef NODE_H
#define NODE_H
#include "Entity.h"
struct Node             //The very basic link of our list
{

    Node()              //Constructor, starts off the attributes
    {
        ent=NULL;
        next=NULL;
        prev=NULL;
    }
    ~Node()         //When called (in the list's destructor or node remover), will delete the entity stored at this node
    {
        delete ent;
    }
    Entity* ent;            //The entity
    Node* next;            //The next and previous nodes in the list
    Node* prev;
};

#endif // NODE_H
