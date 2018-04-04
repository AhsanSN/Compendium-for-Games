#ifndef LIST_H
#define LIST_H
#include "Node.h"

class List
{
public:
    List();         //Constructor

    ~List();            //Destructor, deallocates all the nodes, consequently removing the entities at the nodes too

    List(const List&);          //Copy constructor for the list

    List& operator = (const List&);     //assignment operator

    int size() const; //simply returns an int representing the length of the list, does so by incrementing a local variable on discovering each node and returning the result

    bool append(Entity*);           //Adds the given entity to the list and returns if it was a success or not

    void clean();           //deletes the first nodes whose alive has been set to 0

    bool removeNodeAtInd(int);          //returns 1 if the node is found and removed, 0 otherwise

    int getNodeInd(Node*);          //returns index of the given node if found in the list, -1 if not found

    int getEntInd(Entity*);         //returns index of the given entity if found in one of the nodes of the list, -1 otherwise

    Entity* getEntAtInd(int) const;         //returns the entity at the given index

    void empty();               //Force empties current list, deletes all nodes and sets the list to initial condition

    void render(SDL_Renderer*);         //THE render function. Renders all the entities stored in the list onto the board, via calling their renders

    Node* getNodeAtInd(int);            //returns node at the specified index of the list, NULL if index is out of range

    void resetEntities();       //resets entities to their default states

    Node* getStart();           //returns the start of the list

    friend class Game;          //The game has access to the start and end

    void move(List* = NULL);        //THE move function. Moves the movable entities by calling their move functions

    int getBrickCount();            //returns the number of bricks in the list

private:

    Node* start;            //Starting node

    Node* end;              //Ending node
};

#endif // LIST_H
