import java.util.ArrayList;
import java.util.Iterator;

/// Recursive element for recursive list
///
/// Recursive element handle next and prev links. You should derive it to add your own properties
class RecursiveListElt{
    /// next list element after this one in the list; initialized by default to self
    RecursiveListElt listnext;
    /// previous list element before this one in the list; initialized by default to self
    RecursiveListElt listprev;
    
    RecursiveListElt(){
        this.listnext = this;
        this.listprev = this;
    }

    /// add another recursive list element after this one
    /// - Parameter elt: element to be inserted in the list after this one
    /// - Returns: itself to allow chaining operation
    RecursiveListElt pushAfter(RecursiveListElt elt){
        elt.listnext          = this.listnext;
        elt.listnext.listprev = elt;
        elt.listprev          = this;
        this.listnext         = elt;
        return this;
    }
    /// add another recursive list element before this one
    /// - Parameter elt: element to be inserted in the list before this one
    /// - Returns: itself to allow chaining operation
    RecursiveListElt pushBefore(RecursiveListElt elt){
        elt.listprev          = this.listprev;
        elt.listprev.listnext = elt;
        elt.listnext          = this;
        this.listprev         = elt;
        return this.listprev;
    }
    
    /// remove this element of the list
    /// - Returns: return the next of element or nil if it was alone in the list
    RecursiveListElt remove(){
        // if self is the only one elt of the list (next and prev are link to self), then return nil
        if ( (this.listnext == this) && (this.listprev == this) ) {
            this.listnext = null; // remove reference to itself to allow deallocate
            this.listprev = null; // remove reference to itself to allow deallocate
            return null; // no more element
        }
        this.listprev.listnext = this.listnext; // previous has now as next the next element of self
        this.listnext.listprev = this.listprev; // next has now as previous the previous element of self
        final RecursiveListElt ret = this.listnext; // next of self becomes the new element
        this.listnext = null; // remove reference to itself to allow deallocate
        this.listprev = null; // remove reference to itself to allow deallocate
        return ret; // return as new element the element that was the next of self
    }
    
    /// remove element after this one
    /// - Returns: itself except if this element is isolated, then no more element so return nil
    RecursiveListElt removeNext(){
        // if self is the only one elt of the list (next and prev are link to self), then return nil
        if ( this.listnext.remove() == null ) {
            this.listnext = null ; this.listprev = null; // to allow deallocate (reference to itself prevent from deallocation)
            return null;
        }
        return this;
    }

    /// remove element before this one
    /// - Returns: itself except if this element is isolated, then no more element so return nil
    RecursiveListElt removePrev(){
        // if self is the only one elt of the list (next and prev are link to self), then return nil
        if (this.listprev.remove() == null) {
            this.listnext = null ; this.listprev = null;// to allow deallocate (reference to itself prevent from deallocation)
            return null;
        }
        return this;
    }
}


/// Iterator on recursive list
class RecursiveListIterator<ListElt extends RecursiveListElt> implements Iterator<ListElt>{
    
    // /// list we iterate on
    RecursiveList<ListElt> list;
    /// current element of iterator
    ListElt current;
    
    // /// initialize iterator over a recursive list
    // /// - Parameter list: list we will iterate on
    RecursiveListIterator(RecursiveList<ListElt> list){
        this.list    = list;
        this.current = list.head;
    }
    
    // /// get current element and advance forward to next element
    // /// - Returns: current element or nil if we reach end of the list
    public ListElt next(){
        if (this.current == null) { return null; } // loop is finished
        final ListElt elt = current;
        this.current = this.current.listnext == this.list.head ? null : (ListElt) this.current.listnext;
        return elt;
    }

    public boolean hasNext() {
        return this.current != null;
    }
}



/// Recursive list class
///
/// Generic list based on recursive elements that old next and prev links: allow to delete an element from it without looking for it into the list
///
/// You should derive RercursiveListElt to add your own properties and define you list of elements
class RecursiveList<ListElt extends RecursiveListElt> implements Iterable<ListElt>{
    
    /// head of the list : first element of the list or nil if list is empty
    ListElt head;
    
    /// number of elements of the list
    int count;

    RecursiveList(){
        this.head = null;
        this.count = 0;
    }
    /// first element of the list if there is one, nil if list is empty
    ListElt getFirst(){
        if(this.isEmpty()){ return null; }
        return (ListElt) this.head.listnext;
    }
    /// last element of the list if there is one, nil if list is empty
    ListElt getLast(){
        if (this.isEmpty()) { return null; }
        return (ListElt) this.head.listprev;
    }
    /// true if list is empty, i.e. no element in the list
    Boolean isEmpty(){
        return this.head == null;
    }
    
    /// add an element in front of the list, this element becomes the first element of the list
    /// - Parameter elt: element to be insersted
    /// - Returns: list modified
    void addFirst(ListElt elt){
        if (this.head != null){ // if there is already a first elt
            this.head = (ListElt) this.head.pushBefore(elt); // pushes new element in front of the former first
        }
        else{ // list is empty
            this.head = elt; // new element become the firt one
        }
        this.count += 1;
    }
    
    /// add an element at the end of the list, this element becomes the first element of the list
    /// - Parameter elt: element to be insersted
    /// - Returns: list modified
    void append(ListElt elt){
        if (this.head != null) { // if there is already a first elt
            // previous element of first element is the last element
            this.head.listprev.pushAfter(elt); // so pushes new element afther this last element
        }
        else{ // list is empty
            this.head = elt; // new element become the firt and so last one since only one element in the list
        }
        this.count += 1;
    }
    
    /// insert an element after one eleent
    /// - Parameters:
    ///   - newElt: new element to be inserted
    ///   - elt: element after the one we want to insert new element
    void insertAfter(ListElt newElt,  ListElt elt){
        elt.pushAfter(newElt);
        this.count += 1;
    }

    /// insert an element before one element
    /// - Parameters:
    ///   - newElt: new element to be inserted
    ///   - elt: element before the one we want to insert new element
    void insertBefore(ListElt newElt, ListElt elt){
        elt.pushBefore(newElt);
        this.count += 1;
    }
    
    /// remove first element of the list; if list is empty do  nothing
    void removeFirst(){
        if( this.head != null ) {  // list is not empty
            this.head = (ListElt) this.head.remove();
            this.count -= 1;
        }
    }
    
    /// remove last element of the list; if list is empty do  nothing
    void removeLast(){
        if (this.head != null) {
            // previous of head is the last element, so remove previous element of head
            if (this.head.removePrev() == null){ // head was in fact the last element
                this.head = null;
            }
        }
        this.count -= 1;
    }
    /// remove an element of the list
    /// - Parameter elt: element to remove from the list
    void remove(ListElt elt){
        if (elt.remove() == null){ // in fact elt was the only one
            this.head = null; // so list is empty
        }
        this.count -= 1;
    }
    
    // /// make an iterator on the list
    // /// - Returns: an iterator
    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<ListElt> iterator(){
        return(new RecursiveListIterator<ListElt>(this));
    }    

    public RecursiveListIterator<ListElt> makeIterator(){
        return( new RecursiveListIterator<ListElt>(this) );
    }
    
    
    // /// get an array of all values of the list
    // /// - Returns: array of list elements
    public ArrayList<ListElt> getAllValues(){
        ArrayList<ListElt> ret = new ArrayList<ListElt>();
        for( ListElt elt : this){
            ret.add(elt);
        }
        return(ret);
    }

}
