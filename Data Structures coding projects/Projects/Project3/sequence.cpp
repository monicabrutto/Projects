/*Monica Brutto
* Project 3 - Sequence Object belongs to sequnce.h, creates constuctors, destructor, getters and setters 
*           and other methods used to modify the sequence and sequence nodes for the Sequence object. 
*/

#include "Sequence.h"

//----------------------------------------------------------------
// Sequence: constructor, if the sz is zero, set the head and tail to
//           null, if the sz is greater than zero, then create a new
//           sequence node for head, set head to tail. Then for all the
//           items in the sequence, add a new node, moving tail each time. 
//    Returns:
//    Parameters: sz - size of the sequence
//----------------------------------------------------------------
Sequence::Sequence(size_type sz)
{
    numElts = sz; 
    if(sz == 0){
        head = nullptr;
	    tail = nullptr; 
    } else {
        head = new SequenceNode();
        tail = head;

        for(int i = 0; i < sz-1; i++){
            tail->next = new SequenceNode();
            tail->next->prev = tail;
            tail = tail->next;  
        }
    }
 
}
//----------------------------------------------------------------
// Sequence: copy constructor, copies all of the elements from s to 
//           the current sequence
//    Returns:
//    Parameters: s - sequence to be copied, passed as reference
//----------------------------------------------------------------
Sequence::Sequence(const Sequence& s)
{
    SequenceNode* current = s.head;
    head = nullptr; 
    for(int i = 0; i < s.numElts; i++){
        push_back(current->elt);
        current = current->next; 
    }

    numElts = s.numElts;
}

//----------------------------------------------------------------
// ~Sequence: destrcutor, deletes all of the items in the sequence
//    Returns:
//    Parameters:
//----------------------------------------------------------------
Sequence::~Sequence()
{
    SequenceNode* current = head; 
    for(int i = 0; i < numElts; i++){
        SequenceNode* killed = current->next; 
        delete current; 
        current = killed; 
    }
}

//----------------------------------------------------------------
// operator=: clears and replaces the current sequence with a deep 
//            copy of the sequnce passed, returns a reference
//    Returns: a reference to this sequence
//    Parameters: s - sequence to be copied, passed as reference
//----------------------------------------------------------------
Sequence& Sequence::operator=(const Sequence& s)
{
    clear();        // clear out sequence
    
    SequenceNode* current = s.head;
    head = nullptr; 
    for(int i = 0; i < s.numElts; i++){
        push_back(current->elt);
        current = current->next; 
    }

    numElts = s.numElts;
    
    
    return *this;
}
//----------------------------------------------------------------
// operator[]: returns the item at the position in the sequence as a
//             reference. throws an exception if the position is 
//             outside the bounds of the sequence
//    Returns: reference to the element of the postiton
//    Parameters: postiton - place in the sequence to be changed
//----------------------------------------------------------------
Sequence::value_type& Sequence::operator[](size_type position)
{
    SequenceNode* current = head;

    if(position < 0 && position > numElts){
            throw exception(); 
    } else {
        for(int i = 0; i < position; i++)
        {
            current = current->next; 
        }
        return current->elt; 
    }
   
}

//----------------------------------------------------------------
// push_back: adds a new value to the end of the sequence, adds
//            one to the number of Elements
//    Returns:
//    Parameters: value - the element to be added onto the end
//----------------------------------------------------------------
void Sequence::push_back(const value_type& value)
{
    SequenceNode* node = new SequenceNode(); 
    //if the list is empty:
    if(head == nullptr || numElts < 0){
        node->elt = value;
        node->prev = nullptr; 
        node->next = nullptr; 
        head = node;
        tail = head; 
    } else {
        node->elt = value; 
        tail->next = node;
        node->next = nullptr; 
        node->prev = tail; 
        tail = node;   
    }
    numElts++;
    
}

//----------------------------------------------------------------
// pop_back: deletes the last element in the sequence. If there
//           are no elements, throws an exeception. Decrements
//          numElments
//    Returns:
//    Parameters:
//----------------------------------------------------------------
void Sequence::pop_back()
{
    if(numElts <= 0)
    {
        throw exception();
    } else {
        SequenceNode* current = tail; 
        tail = tail->prev; 
        delete current; 
        numElts--; 
        if(numElts < 1){
            tail = nullptr; 
            
        } else {
            
            tail->next = nullptr; 
        }
      
    }

}

//----------------------------------------------------------------
// insert: inserts the value at the postion given into the sequence, 
//         increment numElmnts and throws an execption if the postion
//         is out of bounds
//    Returns: 
//    Parameters: position - spot in the sequence where the vlaue is
//                to be inserted 
//                value - number to be added
//----------------------------------------------------------------
void Sequence::insert(size_type position, value_type value) {
    if(position >= 0 && position <= numElts) { // else create a previousNode to keep track of where to connect back
        SequenceNode* previousNode = head; 
        // if the position is 0 or the head of the sequence
        if(position == 0){
            //create a new node and set it as the head, increase the number of elements
            SequenceNode* newNode = new SequenceNode();
            newNode->elt = value; 
            head = newNode; 
            newNode->prev = nullptr;
            newNode->next = previousNode; 
            numElts++;
        } else if(position == numElts){ //if the element is the tail call push_back
            push_back(value); 
        }  else {
            //if it is in the middle of the sequence, traverse to find the postion before
            for(int i = 0; i < position-1; i++){
                previousNode = previousNode->next; 
            }
            //create a the nextNode which will come after the newNode
            SequenceNode* nextNode =  nextNode = previousNode->next;
            //Create a newNode, link the previousNode and nextNode
            SequenceNode* newNode = new SequenceNode();
            newNode->elt = value; 
            previousNode->next = newNode; 
            nextNode->prev = newNode; 

            //link the newNode
            newNode->next = nextNode; 
            newNode->prev = previousNode; 

            //increase number of Elemnts
            numElts++;
        }
       
    } else {
        throw exception();
    }
    
}

//----------------------------------------------------------------
// front: returns a reference of the first item in the sequence
//        if the size of the sequence is less than or equal to zero
//        throws an execption
//    Returns: reference to the first item
//    Parameters: 
//----------------------------------------------------------------
const Sequence::value_type& Sequence::front() const
{
    if(numElts <= 0){
        throw exception();
    } else {
        return head->elt; 
    }
    
}

//----------------------------------------------------------------
// back: returns a reference of the lst item in the sequence
//        if the size of the sequence is less than or equal to zero
//        throws an execption
//    Returns: reference to the last item
//    Parameters: 
//----------------------------------------------------------------
const Sequence::value_type& Sequence::back() const
{
    if(numElts <= 0){
        throw exception();
    } else {
        return tail->elt;
    }
    
}
//----------------------------------------------------------------
// empty: returns true if the sequence is empty, returns false if 
//        the sequence has size > 0
//    Returns: a boolean, true value indicates size of the sequence is zero.
//    Parameters: 
//----------------------------------------------------------------
bool Sequence::empty() const
{
    if(numElts > 0){
        return false;
    } else {
        return true; 
    }
    
}
//----------------------------------------------------------------
// size: returns that number of elements in the sequence
//    Returns: numElts - the number of elements
//    Parameters: 
//----------------------------------------------------------------
Sequence::size_type Sequence::size() const
{
    return numElts;
}

//----------------------------------------------------------------
// erase:  All items in the sequence deleted and the memory associated with 
//         the sequence is released.
//    Returns: 
//    Parameters:
//----------------------------------------------------------------
void Sequence::clear()
{
    SequenceNode* current = head; 
    for(int i = 0; i < numElts; i++){
        SequenceNode* killed = current->next; 
        delete current; 
        current = killed; 
    }
    head = nullptr; 
    tail = nullptr; 
    numElts = 0; 
}

//----------------------------------------------------------------
// erase: deletes items from the sequence from position to (position + count - 1)
//        if postion and count is out of bounds, throws execption.
//        sets head and tail of the altered sequence
//    Returns: 
//    Parameters: postition - starting postion
//                count - amount of items to delete
//----------------------------------------------------------------
void Sequence::erase(size_type position, size_type count) {
    //if position is less than 0 and number of items to be deleted is greater than the number of elements
    //in the sequence, throws an exception 
    if(position >= 0 && (position + count -1) <= numElts) {
        //move current to the postion to start deleting
        SequenceNode* start = head; 
        for(int i = 0; i < position; i++){
            start = start->next;
        }
        
        SequenceNode* end = start; 
        for(int i = position; i < (position + count)-1; i++)
        {
            end = end->next;  
        }

        if((position + count -1) == numElts){
            tail = start->prev;
            head->next = nullptr;
            tail->next = nullptr; 
        } else if(numElts == 1) {
            
        } else if(start == head){
            head = end->next;
            head->prev = nullptr; 
        } else if(end == tail){
            tail = start->prev;
            tail->next = nullptr; 
        } else{
            start->prev->next = end->next; 
            end->next->prev = start->prev; 
        }
        //delete all the items from postion to count, decrement numElts
        while(start != end){
            SequenceNode* deleteNext = start; 
            start = start->next; 
            delete deleteNext; 
            numElts--;
        }

        delete end;
        numElts--;
        
    } else {
        throw exception();
    }
}

//----------------------------------------------------------------
// print: takes in ostream as a reference and prints out every
//         value in the sequence
//    Returns:
//    Parameters: ostream - reference to ostream object used to perfrom 
//                         output
//----------------------------------------------------------------
void Sequence::print(ostream& os) const
{
    SequenceNode* current = new SequenceNode();
    current = head; 
    os << "<";
    for(int i = 0; i < numElts; i++){
        os << current->elt; 
        current = current->next; 
        if(current != nullptr){         //if it is not the last item in the sequence add "," in between
            os << ", ";
        }
    }
    os << ">" << endl; 
}

// Don't modify, do the output in the print() method
ostream& operator<<(ostream& os, const Sequence& s)
{
    s.print(os);
    return os;
}

