import java.util.ArrayList;
import java.util.Iterator;

public class Vertex extends RecursiveListElt implements Iterable<Dart>{
    
    /// class property to count number of darts created and compute an index
    private static int count = 0; //numeroter les sommets
    
    /// return a comprehensible description string of the dart
    public String toString() {
        return this.getName()+":("+this.getX()+","+this.getY()+","+this.getZ()+")";
    }
    String getName(){
        final String vid = String.format("%02d", this.id);
        return "v"+vid;
    }

    /// unique number associated to the dart - allows to identify it uniquely
    private final int id;

    /// one reference dart that has this vertex as origin
    Dart refDart; //demis arrete de reference

    /// point coordinates
    Point point;

    /// x coordinate of point
    double getX() { return this.point.x; }
    void setX(double newValue){ this.point.x = newValue; }
    
    /// y coordinate of point
    double getY() { return this.point.y ; }
    void setY(double newValue) { this.point.y = newValue; }
    
    /// z coordinate of point
    double getZ() { return this.point.z; }
    void setZ(double newValue) { this.point.z = newValue; }
    
    /// initialize Vertex from a point
    /// - Parameter p: point corrdinates of vertex
    Vertex(Point p){
        super();
        this.id    = Vertex.count;
        this.point = p;
        this.refDart  = null;
        Vertex.count += 1;
    }
    
    /// initialize Vertex from coordinates
    /// - Parameters:
    ///   - x: x coordinate of vertex
    ///   - y: y coordinate of vertex
    ///   - z: z coordinate of vertex
    Vertex(double x, double y, double z){
        this(new Point(x, y, z));
    }

    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<Dart> iterator(){
        return( new OrbitDartVertexIterator(this.refDart));
    }    

    // /// make an iterator to iterate over darts of vertex: darts that have this vertex as origin
    // /// - Returns: an iterator of darts of vertex
    public OrbitDartVertexIterator makeIterator(){
        return(new OrbitDartVertexIterator(this.refDart));
    }
    
    // /// make an iterator to iterate over darts of vertex: darts that have this vertex as origin
    // /// - Returns: an iterator of darts of vertex
    public OrbitDartVertex makeOrbitDartVertex() {
        return( new OrbitDartVertex(this));
    }
    
    // /// make an iterator to iterate over faces of vertex
    // /// - Returns: an iterator of faces of vertex
    public OrbitFaceVertex makeOrbitFaceVertex() {
        return( new OrbitFaceVertex(this) );
    }

    /// find dart  located on a particular face that has vertex as origin
    /// - Parameters:
    ///   - vertex: vertex we want to find a dart
    ///   - face: face where the dart must be located
    /// - Returns: dart found or nil if no dart having vertex as origin  is located on face
    public Dart findVertexStartingDart(Face face){
        Dart found = null;
        final OrbitDartVertex orbit = makeOrbitDartVertex();
        for (Dart d : orbit){
            if (d.face == face){
                found = d;
                break;
            }
        }
        return(found);
    }

    /// find dart  located on a particular face that has vertex as end
    /// - Parameters:
    ///   - vertex: vertex we want to find a dart
    ///   - face: face where the dart must be located
    /// - Returns: dart found or nil if no dart having vertex as end  is located on face
    public Dart findVertexEndingDart(Face face){
        Dart found = null;
        final OrbitDartVertex  orbit = makeOrbitDartVertex();
        for( Dart d : orbit){
            if(d.getOpposite().face == face){
                found = d.getOpposite();
                break;
            }
        }
        return(found);
    }
    
    /// darts of vertex, i.e. darts that have this vertex as origin
    /// - Returns: an array of darts
    public ArrayList<Dart> darts(){
        ArrayList<Dart> ret = new ArrayList<Dart>();
        final OrbitDartVertex orbit = makeOrbitDartVertex();
        for(Dart dart : orbit){
            ret.add(dart);
        }
        return(ret);
    }
    /// faces of vertex
    /// - Returns: an array of faces
    ArrayList<Face> faces(){
        ArrayList<Face> ret = new ArrayList<Face>();
        final  OrbitFaceVertex orbit = makeOrbitFaceVertex();
        for(Face face : orbit){
            if(!ret.contains(face)){
                ret.add(face);
            }
        }
        return(ret);
    }

}

/// Orbit of darts vertex: set of darts that have vertex as origin
//l'enseble des demi arete incidente au sommet
class OrbitDartVertex implements Iterable<Dart>{
    /// vertex origin
    Vertex vertex;
    /// number of darts of vertex
    int getCount() {
        var i = 0;
        for (Dart d : this){
            i += 1;
        }
        return(i);
    }

    /// initialize orbit
    /// - Parameter v: vertex origin
    OrbitDartVertex(Vertex v){
        this.vertex  = v;
    }

    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<Dart> iterator(){
        return new OrbitDartVertexIterator(this.vertex.refDart);
    }    

    /// make an iterator over this set
    /// - Returns: an iterator
    OrbitDartVertexIterator makeIterator(){
        return( new OrbitDartVertexIterator(vertex.refDart) );
    }
}

/// iterator over set of dart of vertex
class OrbitDartVertexIterator implements Iterator<Dart> {
    /// starting dart for iterate
    private Dart start;
    /// current dart
    Dart current;
    
    /// initialize iterator from a starting dart
    /// - Parameter start: starting dart
    OrbitDartVertexIterator(Dart start){
        this.start   = start;
        this.current = start;
    }
    
    /// reinitialize iterator: iteration will restart from starting dart
    void reinit(){
        this.current = this.start;
    }
    /// return current dart and advance forward
    /// - Returns: current dart or nil if we reach end of set
    public Dart next(){
        if(this.current == null) { return null; }
        Dart ret = this.current;
        this.current = current.getOpposite().getNext();
        if(this.current == this.start) { this.current = null; }
        return(ret);
    }
    // returns false if next element does not exist
    public boolean hasNext(){
        return (this.current != null);
    }    
}
//parcour les face incidente au sommet
/// Orbit of faces vertex: set of faces of this vertex
class OrbitFaceVertex implements Iterable<Face> {
    /// vertex origin
    Vertex vertex;
    
    /// number of faces around vertex
    int getCount() {
        var i = 0;
        for (Face f : this){
            i += 1;
        }
        return(i);
    }
    
    /// initialize set of faces
    /// - Parameter v: vertex origin
    OrbitFaceVertex(Vertex v){
        this.vertex  = v;
    }

    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<Face> iterator(){
        return (new OrbitFaceVertexIterator(this.vertex.refDart));
    }    
    
    /// make an iterator to iterate over faces of this set
    /// - Returns: an iterator
    // public func makeIterator() -> OrbitFaceVertexIterator {
    //     return OrbitFaceVertexIterator(start: vertex.refDart)
    // }
}

/// Iterator over OrbitFace
class OrbitFaceVertexIterator implements Iterator<Face> {
    /// starting dart
    Dart start;
    /// current dart
    Dart currentdart;
    /// current face
    Face current() {
        if (this.currentdart == null) { return null; }
        return this.currentdart.face;
    }
    
    /// initialize iterator over faces of a vertex
    /// - Parameter start: starting dart of iterator: face if this dart is the starting face
    OrbitFaceVertexIterator(Dart start){
        this.start   = start;
        this.currentdart = start;
    }
    
    /// reinitialize iterator: iteration will restart from starting dart
    void reinit(){
        this.currentdart = this.start;
    }
    /// return current face and advance forward
    /// - Returns: current face or nil if we reach end of set
    public Face next() {
        if (this.currentdart == null) { return null; }
        Dart ret = this.currentdart;
        this.currentdart = currentdart.getOpposite().getNext();
        if (this.currentdart == this.start) { this.currentdart = null; }
        return(ret.face);
    }
    
    // returns false if next element does not exist
    public boolean hasNext(){
        return (this.currentdart != null);
    }

}
