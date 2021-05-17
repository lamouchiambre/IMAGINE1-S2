import java.util.ArrayList;
import java.util.Iterator;

public class Face extends RecursiveListElt implements Iterable<Dart>{

    /// class property to count number of darts created and compute an index
    static int count = 0;
    
    public String getName() {
        final String fid = String.format("%02d", this.id);
        return "f"+fid;
    }
    
    /// return a comprehensible description string of face by given list of darts of face
    public String toString() {
        String edges = "";
        if (this.refDart != null) {
            OrbitDartFace orbit = this.makeOrbitDartFace();
            for(Dart d : orbit){
                edges += "\n - " + d.getStartVertex().getName() +" -> " + d;
            }
            edges += " -> " + this.refDart; // to display restart and show complete loop with vertices
        }
        return this.getName()+":"+ edges;
    }

    /// unique number associated to the dart - allows to identify it uniquely
    final int id;

    /// one reference dart that has this vertex as origin
    Dart refDart;

    /// array of darts of the face
    ArrayList<Dart> getDarts() {
        ArrayList<Dart> ret = new ArrayList<Dart>();
        if (this.refDart == null) { return ret; }
        final OrbitDartFace face = this.makeOrbitDartFace();
        for (Dart d : face){
            ret.add(d);
        }
        return ret;
    }

    /// array of vertices of the face
    ArrayList<Vertex> getVertices() { // tableau des sommets (pointeurs) de la face
        ArrayList<Vertex> ret = new ArrayList<Vertex>();
        if(this.refDart == null) { return ret; }
        final OrbitVertexFace orbit = makeOrbitVertexFace();
        for (Vertex v : orbit){
            ret.add(v);
        }
        return ret;
    }
    
    /// initialize a face without reference dart
    Face(){
        super();
        this.id = Face.count;
        this.refDart = null;
        Face.count += 1;
    }
    
    /// check if face is closed
    ///
    /// verifiy that following ß1 we come back to starting dart without deadend edge
    /// - Parameter start: starting dart
    /// - Returns: true if face is closed
    static Boolean checkClosed(Dart start){
        Dart current = start.getNext();
        // if next is start
        while( (current != start) && (current.getNext() != current.getOpposite()) && (current.getNext() != current) ){
            current = current.getNext();
        } // stop loop if next == start (we have a cycle) or if next == current.opposite (dead end edge) or if next == current (isolated dart)
        return (current == start) && (current.getNext() != current.getOpposite()) && (current.getNext() != current);// we have a cycle only if we go back to start
    }

    /// initialize of face from a reference dart
    ///
    /// check if dart given is well a dart of a face, i.e we got a cycle when going next
    /// - Parameter dart: reference dart for the face
    static Face makeFace(Dart dart){
        if (!Face.checkClosed(dart)) { return null; }
        var face = new Face();
        face.refDart = dart; // dart becomes reference dart of the new face
        // new face should become face of this dart and all darts of cycle
        final Dart newRefOldFace = dart.getOpposite();
        final OrbitDartFace orbit = face.makeOrbitDartFace();
        for (Dart d : orbit){
            // if d was the reference of old face, the opposite of dart has to becomes its reference dart
            // since the edge of dart should have split old face
            if (d.face.refDart == d) {
                d.face.refDart = newRefOldFace;
            }
            // face of current is the new face
            d.face = face;
        }
        return face;
    }
    
    
    /// make an iterator over darts of face
    /// - Returns: an iterator
    public Iterator<Dart> iterator(){
        return(new OrbitDartFaceIterator(this.refDart));
    }    

    /// make an iterator over darts of face
    /// - Returns: an iterator
    public OrbitDartFaceIterator makeIterator(){
        return(new OrbitDartFaceIterator(this.refDart));
    }

    /// make an iterator over darts of face
    /// - Returns: an iterator
    public OrbitDartFace makeOrbitDartFace() {
        return(new OrbitDartFace(this));
    }
    // /// make an iterator over vertices of face
    // /// - Returns: an iterator
    public OrbitVertexFace makeOrbitVertexFace() {
        return(new OrbitVertexFace(this));
    }
        
}

/// set of darts of face
///
/// - Tag: OrbitDartFace
class OrbitDartFace implements Iterable<Dart>{
    /// face reference
    Face face;
    
    /// number of darts in the face
    int getCount() {
        int i = 0;
        if (face.refDart == null) { return 0; }
        else{
            for(Dart d : this){
                i += 1;
            }
        }
        return i;
    }
    
    /// initialize orbit from a face
    /// - Parameter f: face of which we want set of darts
    public OrbitDartFace(Face f){
        this.face  = f;
    }
    
    public OrbitDartFace(Dart dart){
        this(dart.face);
    }
    
    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<Dart> iterator(){
        return new OrbitDartFaceIterator(this.face.refDart);
    }    
    public OrbitDartFaceIterator makeIterator() {
        return new OrbitDartFaceIterator(this.face.refDart);
    }

}

/// Iterator over [OrbitDartFace](x-source-tag://OrbitDartFace)
class OrbitDartFaceIterator implements Iterator<Dart> {
    /// starting dart for iteration
    private Dart start;
    /// current dart
    Dart current;
    
    /// initialize an iterator from a starting dart
    /// - Parameter start: starting dart
    OrbitDartFaceIterator(Dart dart){
        this.start = dart;
        this.current = dart;
    }
    
    /// initialize an iterator from a face
    /// - Parameter face: face of which we want iterate
    OrbitDartFaceIterator(Face face){
        this(face.refDart);
    }
    
    /// get current dart and advance forward to next dart in the set
    /// - Returns: current dart or nil if we reach end of iteration
    public Dart next() {
        if (this.current == null) { return null; }
        Dart ret = this.current;
        this.current = current.getNext();
        if (this.current == this.start) { this.current = null; }
        return ret;
    }

    // returns false if next element does not exist
    public boolean hasNext(){
        return (this.current != null);
    }
    
    // /// get current dart and advance forward to next dart in the set
    // /// - Returns: current dart or nil if we reach end of iteration
    public Dart prev() {
        if (this.current == null)  { return null; }
        Dart ret = this.current;
        this.current = current.getPrev();
        if (this.current == this.start) { this.current = null;  }
        return ret;
    }
    

    /// reinitialize iterator so that futur call to next restart from beginning
    public void reinit(){
        this.current = this.start;
    }
    
}

// set of vertices of face
///
/// - Tag: OrbitVertexFace
class OrbitVertexFace  implements Iterable<Vertex>{
    /// face reference
    Face face;
    
    /// number of darts in the face
    int getCount() {
        int i = 0;
        for (Vertex v : this){
            i += 1;
        }
        return i;
    }

    /// initialize an iterator from a face
    /// - Parameter start: face of which we want the set of vertices
    OrbitVertexFace(Face f){
        this.face  = f;
    }

    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<Vertex> iterator(){
        return new OrbitVertexFaceIterator(this.face.refDart);
    }    

    /// make an iterator over vertices of this set
    /// - Returns: an iterator
    public OrbitVertexFaceIterator makeIterator(){
        return new OrbitVertexFaceIterator(face.refDart);
    }

}
/// Iterator over [OrbitVertexFace](x-source-tag://OrbitVertexFace)
class OrbitVertexFaceIterator implements Iterator<Vertex> {
    /// starting dart for iteration
    private Dart start;
    /// current dart
    Dart current;
    
    /// initialize an iterator from a starting dart
    /// - Parameter start: starting dart
    public OrbitVertexFaceIterator(Dart start){
        this.start = start;
        this.current = start;
    }

    /// initialize an iterator from a face
    /// - Parameter start: face of which we want the set of vertices
    public OrbitVertexFaceIterator(Face face){
        this(face.refDart);
    }

    /// get current vertex and advance forward to next vertex in the set
    /// - Returns: current vertex or nil if we reach end of iteration
    public Vertex next() {
        if( this.current == null) { return null; }
        Dart ret = this.current;
        this.current = current.getNext();
        if (this.current == this.start) { this.current = null; }
        return ret.getStartVertex();
    }

    // returns false if next element does not exist
    public boolean hasNext(){
        return (this.current != null);
    }
    
    /// get current vertex and advance forward to next vertex in the set
    /// - Returns: current vertex or nil if we reach end of iteration
    public Vertex prev() {
        if ( this.current == null) { return null; }
        Dart ret = this.current;
        this.current = current.getPrev();
        if (this.current == this.start) { this.current = null;  }
        return ret.getStartVertex();
    }
    
    /// reinitialize iterator so that futur call to next restart from beginning
    void reinit(){
        this.current = this.start;
    }
    
}
