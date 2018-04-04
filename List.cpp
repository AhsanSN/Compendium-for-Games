#include "List.h"

List::List()            //The constructor
{
    start=NULL;
    end=NULL;
}

List::~List()           //The destructor, to deallocate all dynamically created objects in the list
{
    while(start)
    {
        Node* tmp=start;
        start=start->next;
        delete tmp;
    }
    start=NULL;
    end=NULL;
}
List::List(const List& toCopy): start(NULL),end(NULL)           //Copy constructor
{
    for (int i=0; i<toCopy.size(); i++) //loop will iterate from 0 to size of toCopy and will append each element to the list being constructed
    {
        this->append(toCopy.getEntAtInd(i));
    }
}
int List::size() const          //Returns the size of the list
{
    int len=0;
    Node* tmp = start;
    while(tmp)
    {
        len++;
        tmp=tmp->next;
    }
    return len;
}
bool List::append(Entity* ent)      //Adds the given entity address to the list
{

    if (start==NULL && end ==NULL)      //if there are no elements in the queue
    {
        Node* p= new Node;
        if(p==NULL) return 0;
        p->ent=ent;
        start=p;
        end=p;
        return 1;
    }
    else
    {
        Node* p = new Node;
        if(p==NULL) return 0;
        p->ent=ent;
        end->next=p;
        p->prev=end;
        end=p;
        return 1;
    }
}

void List::clean()          //deletes the first node whose alive has been set to 0
{
    Node* tmp=start;
    while(tmp)
    {
        if( !(tmp->ent->getAlive()) )
        {
            removeNodeAtInd(getNodeInd(tmp));
            break;
        }
        else
        {
            tmp=tmp->next;
        }
    }
}


bool List::removeNodeAtInd(int ind)     //returns 1 if the node is found and removed, 0 otherwise
{
    if(ind<0 || ind>=this->size())
    {
        cerr<<"Invalid index passed  to removeNodeAtInd()"<<endl;
        return 0;
    }
    Node *behind = start;
    if(ind==0) //special case, if the ind to remove is 0
    {
        if(size()>1)
        {
            start = start->next;
            start->prev=NULL;
            delete behind;
            return 1;
        }
        else
        {
            delete start;
            start=NULL;
            end=NULL;
            return 1;
        }

    }
    else if(ind==size()-1)
    {
        Node* tmp = end;
        end=end->prev;
        end->next=NULL;
        delete tmp;
        return 1;
    }
    else        //general case, if the ind is > 0
    {
        //now go to the appropriate location
        Node* ahead  = behind->next;
        for (int i=1; i<ind; i++)
        {
            behind = ahead;
            ahead  = ahead->next;//at end of loop ahead will be storing the node at the given index
        }
        behind->next = ahead->next;
        ahead->next->prev=behind;
        delete ahead;
        return 1;
    }
}

int List::getNodeInd(Node* toFind)      //Returns the index of a node that is to be found
{
    int ind=0;
    Node* tmp=start;
    while(tmp)
    {
        if(tmp==toFind)
        {
            return ind;
        }
        else
        {
            ind++;
        }
        tmp=tmp->next;

    }
    return -1;
}
void List::empty()      //Force empties current list, deletes all nodes and sets the list to initial condition
{
    for(int i=0; i<size(); i++)
    {
        this->removeNodeAtInd(0);
    }
    start=NULL;
    end=NULL;
}
void List::render(SDL_Renderer* gRenderer)              //The renderer, iterates through the list, calling each entity's render
{
    Node* tmp=start;
    while(tmp)
    {
        tmp->ent->render(gRenderer);
        tmp=tmp->next;
    }
}

Entity* List::getEntAtInd(int ind) const            //Returns the entity address stored at the given index
{
    if(ind<0 || ind >=size()) return NULL;
    int i=0;
    Node*tmp=start;
    while(tmp)
    {
        if(i==ind)
        {
            return tmp->ent;
        }
        tmp=tmp->next;
        i++;
    }
    return NULL;
}
void List::move(List* worldEnt)             //Iterates through the list, checks for movable objects and calls their move functions
{
    Node* tmp=start;
    while(tmp)
    {
        if(tmp->ent->getType()==tmp->ent->MOBILEBRICKX || tmp->ent->getType()==tmp->ent->MOBILEBRICKY
                || tmp->ent->getType()==tmp->ent->PADDLE || tmp->ent->getType()==tmp->ent->BALL ||
                tmp->ent->getType() == tmp->ent->NORMBULLET || tmp->ent->getType()==tmp->ent->POWERUP
                || tmp->ent->getType()==tmp->ent->BOSSBRICK || tmp->ent->getType()==tmp->ent->RESISTANTBULLET)//check if the entity is movable
            tmp->ent->move(this);
        else if (tmp->ent->getType()==tmp->ent->MISSILE && worldEnt != NULL)
        {
            tmp->ent->move(worldEnt);
        }
        tmp=tmp->next;
    }
}

int List::getEntInd(Entity* toFind)     //returns index of the given entity if found in one of the nodes of the list, -1 otherwise
{
    Node* tmp=start;
    int i=0;
    while(tmp)
    {
        if (tmp->ent == toFind)
        {
            return i;
        }
        else
        {
            tmp=tmp->next;
            i++;
        }
    }
    return -1;
}


Node* List::getNodeAtInd(int ind)               //Returns the node at the given index
{
    if(ind<0 || ind >=size()) return NULL;
    int i=0;
    Node*tmp=start;
    while(tmp)
    {
        if(i==ind)
        {
            return tmp;
        }
        tmp=tmp->next;
        i++;
    }
    return NULL;
}

void List::resetEntities()          //Resetting the entities via calling their reset methods
{
    Node* tmp=start;
    while(tmp)
    {
        tmp->ent->reset();
        tmp=tmp->next;
    }
}

int List::getBrickCount()           //Returns the count of the alive bricks currently in the list
{
    int numBricks=0;//INVISIBLE and STEEL Bricks don't count, they're instead part of the level
    Node* tmp=start;
    while(tmp)
    {
        if(tmp->ent->getAlive())
        {
            if(tmp->ent->getType()==Entity::ONEHITBRICK)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==Entity::TWOHITBRICK)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==Entity::THREEHITBRICK)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==Entity::MOBILEBRICKX)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==Entity::MOBILEBRICKY)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==Entity::BOSSBRICK)
            {
                numBricks++;
            }
        }
        tmp=tmp->next;
    }
    return numBricks;
}

Node* List::getStart()      //returns the start of the list
{
    return start;
}
