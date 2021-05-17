
import java.util.ArrayList;
import java.util.Iterator;

public class MeshMap implements Iterable<Dart>{
    
    /// circular list of darts
    RecursiveList<Dart> darts;
    /// circular list of vertices
    RecursiveList<Vertex> vertices;
    /// circular list of faces
    RecursiveList<Face> faces; // there is always at least one face
    /// outside face used for new isolated dart and for outside non close surface mesh
    Face infinite; // the face when mesh is not a closed surface, the one that exists at mesh initialization
       
    /// initialize a MeshMap
    ///
    /// map hold an infinate face by default; list of darts and vertices are empty
    public MeshMap(){
        this.infinite = new Face(); // outside face in case of non close surface mesh
        this.darts    = new RecursiveList<Dart>();
        this.vertices = new RecursiveList<Vertex>();
        this.faces    = new RecursiveList<Face>();
        this.faces.addFirst(this.infinite); // at start, only one face, the infinite one
    }
    
    /// return comprehensible string description of a map by printing all faces
    public String toString(){
        String output = "";
        for(Face face : this.faces){
            output += "- " + face + "\n";
        }
        return(output);
    }
    
    // -----------------------------------------------------------------------------------------------------------------------
    // MARK: - Add new elements to the map
    
    /// add a new vertex to the map
    /// - Parameter p: point coordinates of vertex
    /// - Returns: vertex created and added
    public Vertex newVertex(Point p){
        final Vertex v = new Vertex(p); // create a new vertex with point coordinates (no reference dart for the moment)
        this.vertices.append(v);
        return(v);
    }
    
    /// add a new vertex to the map - add also a new dart that will have this vertex as origin
    /// - Parameters:
    ///   - x: x coordinate of vertex
    ///   - y: y coordinate of vertex
    ///   - z: z coordinate of vertex
    /// - Returns: vertex created and added
    public Vertex newVertex(Double x, Double y, Double z){
        return(this.newVertex(new Point(x, y, z)));
    }
    
    /// create a new dart with vertex as origin and add it to the map
    /// - Parameter Vertex: origin vertex
    /// - Returns: Dart created and added
    private Dart newDart(Vertex vertex, Face face){
        final Face f = face;
        if( face == null) { face = this.infinite; }
        final Dart d = new Dart(vertex, f); // new dart, if vertex has no reference dart then e becomes its reference dart
        this.darts.append(d);
        return(d);
    }
    private Dart newDart(Vertex vertex){
        return(newDart(vertex, null));
    }
    
    
    /// adjust set of face according to new edge created
    ///
    /// check if the edge has split a face; if this is the case, creates a new face and add it to the list
    ///
    /// if the edge was created into infinite face and this one was closed (no dead-end edge), i.e. the case of an edge between two vertices on the border of a  surface and located outside,
    /// it could join the border of the surface making a close surface of a volume. If this is the case, no more edge of this surface is located in infinite face and so you have to correct this
    /// - Parameters:
    ///   - dart: one dart of edge just created
    ///   - intoInfiniteClosedFace: true if edge was created into infinite close face.
    void adjustFacesAfterMaking(Dart dart, Boolean intoInfiniteClosedFace){
        final Face face = Face.makeFace(dart);
        if(face != null){ // creating a face check if there is a cycle, if not init failed
            // when created a face register itself on all darts of cycle and change reference dart of old face if needed
            this.faces.append(face); // just have to add the new face to the list of faces
            // if we make an edge inside infinite closed face, we have perhaps join two faces and close surface
            if(intoInfiniteClosedFace) {
                final Face oppositeFace = Face.makeFace(dart.getOpposite());
                if(oppositeFace != null){ // if we can make a face with opposite dart (face is closed)
                    // that is that we join two faces
                    this.faces.append(oppositeFace);  // so add this new face to map
                    if( (this.infinite.refDart != null) && (this.infinite.refDart.face != this.infinite) ){ // if ref dart of infinite is now on another face
                        this.infinite.refDart = null; // it means we have closed a surface, infinite face has no more edges
                    }
                }
            }
        }
    }
    
    Boolean thereIsAndEdge(Dart ante, Dart post){
        final Vertex v = post.getStartVertex();
        for( Dart d : ante.getEndVertex()){
            if (d.getEndVertex() == v) { return true; }
        }
        return false;
    }
    
    /// make an edge between two vertices designated by darts that allows to precisely locate the futur edge
    /// - Parameters:
    ///   - ante: dart from where new edge will start; the edge will start next this dart
    ///   - post: dart where edge finishes: this dart will we next of edge
    /// - Returns: dart created between start and end
    public Dart makeEdgeBetween(Dart ante, Dart post) {
        if (ante.getNext() == post){ throw new AssertionError("makeEdge(dart,dart): only one vertex here, cannont make an edge"); }
        if (thereIsAndEdge(ante, post)) { throw new AssertionError("makeEdge(dart,dart): there is already an edge here"); }
        // check if face of ante is infinite && infinite is closed (a loop)
        final Boolean isEdgeMadeIntoInfiniteClosedFace = (ante.face == this.infinite) && Face.checkClosed(ante);
        // first, make an isolated edge between the two vertices
        final Dart dart = makeEdgeDoubleDeadEnd(ante.getEndVertex(), post.getStartVertex(), ante.face);
        // sew edge to ante and post edge
        dart.sewPrev(ante) ; dart.sewNext(post);
        // now we have to check if a new face has been created by closing a cycle
        this.adjustFacesAfterMaking(dart, isEdgeMadeIntoInfiniteClosedFace);
        return(dart); // return dart of edge attached to first vertex
    }

    /// make an edge between one vertex designated by a dart that gives in the same time face where drawn edge, and a vertex as end of edge
    /// - Parameters:
    ///   - ante: dart from where new edge will start; the edge will start next this dart
    ///   - post: vertex that is end of edge
    /// - Returns: dart created between start and end
    public Dart makeEdgeBetween(Dart ante, Vertex vertex){
        if (vertex.refDart != null) { // if vertex has at least one dart, then find dart of this edge located in face of ante
            final Dart post = vertex.findVertexStartingDart(ante.face);
            if(post == null) { throw new AssertionError("makeEdge(dart,vertex) end vertex is not a vertex of face of dart"); }
            return(this.makeEdgeBetween(ante, post) );
        }
        // check if face of ante is infinite && infinite is closed (a loop)
        final Boolean isEdgeMadeIntoInfiniteClosedFace = (ante.face == this.infinite) && Face.checkClosed(ante);
        // first, make an isolated edge between the two vertices
        final Dart dart = makeEdgeDoubleDeadEnd(ante.getEndVertex(), vertex, ante.face);
        // sew edge to ante
        dart.sewPrev(ante);
        // now we have to check if a new face has been created by closing a cycle
        this.adjustFacesAfterMaking(dart,isEdgeMadeIntoInfiniteClosedFace);
        return(dart);
    }
    /// make an edge between one vertex designated by a dart that gives in the same time face where drawn edge, and a vertex as start of edge
    /// - Parameters:
    ///   - ante: vertex that is start of edge
    ///   - post: dart where the edge will fall, vertex of this dart is the end of edge
    /// - Returns: dart created between start and end
    public Dart makeEdgeBetween(Vertex vertex, Dart post){
        // first, make an isolated edge between the two vertices
        if(vertex.refDart != null) {
            final Dart ante = vertex.findVertexEndingDart(post.face);
            if(ante == null) { throw new AssertionError("makeEdge(vertex:dart:) start vertex is not a vertex of face of dart"); }
            return(this.makeEdgeBetween(ante, post));
        }
        // check if face of ante is infinite && infinite is closed (a loop)
        final Boolean isEdgeMadeIntoInfiniteClosedFace = (post.face == this.infinite) && Face.checkClosed(post);
        //
        final Dart dart = makeEdgeDoubleDeadEnd(vertex, post.getStartVertex(), post.face);
        // sew edge to post
        dart.sewNext(post);
        // now we have to check if a new face has been created by closing a cycle
        this.adjustFacesAfterMaking(dart, isEdgeMadeIntoInfiniteClosedFace);
        return(dart);
    }
    
    /// make an edge between two vertices and linked it to other edges attached to these vertices
    /// - Parameters:
    ///   - v1: first vertex of edge
    ///   - v2: second vertex of edge
    ///   - f: face where drawing edge between the two vertices
    /// - Returns: dart of edge having v1 as origin
    public Dart makeEdgeBetween(Vertex v1, Vertex v2, Face f){
        // if vertices has no reference dart, we just have to make an edge between this vertices
        if( (v1.refDart == null) && (v2.refDart == null) ){
            final Dart dart = makeEdgeDoubleDeadEnd(v1, v2);
            final Dart oppo = dart.getOpposite();
            dart.face = this.infinite ; oppo.face = this.infinite;
            return(dart);
        }
        // if only one vertex has no reference dart
        if( (v1.refDart == null) || (v2.refDart == null) ){
            if( v1.refDart == null) { // it is v1 that has no reference dart
                final Dart post = v2.findVertexStartingDart(this.infinite);
                if( post == null) {
                    throw new AssertionError("makeEdgeLinked(vertex, vertex, face): the post vertex is not in the infinite face while the ante vertex is only in the infinite face"); 
                }
                return(this.makeEdgeBetween(v1, post));
            }
            if( v2.refDart == null) { // it is v2 that has no reference dart
                final Dart ante = v1.findVertexStartingDart(this.infinite);
                if( ante == null ) {
                    throw new AssertionError("makeEdgeLinked(vertex, vertex, face): the ante vertex is not in the infinite face while the post vertex is only in the infinite face");
                 }
                return( this.makeEdgeBetween(ante, v2) );
            }
        }
        // the two vertices have one reference dart
        Face face; // face where to draw edge between the two vertices
        if(f == null) { // if no face given, find a common face
            final Face commonface = this.findSingleCommonFace(v1, v2);
            if (commonface == null) { throw new AssertionError("makeEdgeLinked(vertex,vertex): no face given and no common face"); }
            face = commonface;
        }
        else{ // else keep face given in parameter
            face = f;
        }
        // else vertices have some edges attached
        // must be one dart around each vertices that is located in face asked
        final Dart antenext = v1.findVertexStartingDart(face);
        final Dart post = v2.findVertexStartingDart(face);
        if( antenext == null ) { throw new AssertionError("makeEdgeLinked(vertex, vertex, face): ante vertex is not a vertex of face"); }
        if( post == null ) { throw new AssertionError("makeEdgeLinked(vertex, vertex, face): post vertex is not a vertex of face"); }
        final Dart ante = antenext.getPrev();
        // these dart must be dart of edges, so must have an opposite
        if(ante.isOppositeFree()) { throw new AssertionError("makeEdge: inconsistent mesh, dart of ante vertex has no opposite"); }
        if(post.isOppositeFree()) { throw new AssertionError("makeEdge: inconsistent mesh, dart of post vertex has no opposite"); }
        // existing darts of vertices can be start and end of edge, so we can call makeEdge function
        return( makeEdgeBetween(ante, post) );
    }

    public Dart makeEdgeBetween(Vertex v1, Vertex v2){
        return makeEdgeBetween(v1, v2, null);
    }
    
    /// get dart of  edge between origin and end vertices that is located at origin vertex
    /// - Parameters:
    ///   - v1: first vertex
    ///   - v2: second vertext
    /// - Returns: dart of  edge between origin and end vertices that is located at origin vertex, nil if there is no edge
    public Dart edgeDartOrigin(Vertex origin, Vertex end){
        if(origin.refDart != null){
            Dart found  = null;
            Dart dart = origin.refDart;
            if(dart.getEndVertex() == end) { found = dart; }
            dart = dart.getOpposite().getNext();
            while( (found == null) && (dart!=null) && (dart != origin.refDart) ){
                if(dart.getEndVertex() == end) { found = dart; }
                dart = dart.getOpposite().getNext();
            }
            return(found);
        }
        else{
            return(null);
        }
    }
    
    /// get dart of  edge between origin and end vertices that is located at end vertex
    /// - Parameters:
    ///   - v1: first vertex
    ///   - v2: second vertext
    /// - Returns: dart of  edge between origin and end vertices that is located at end vertex, nil if there is no edge
    public Dart edgeDartEnd(Vertex origin, Vertex end){
        final Dart ret = edgeDartOrigin(origin, end);
        if( ret == null ) { return(null); }
        return( ret.getOpposite() );
    }
    
    /// check if an edge exists between these two vertices
    /// - Parameters:
    ///   - v1: first vertex
    ///   - v2: second vertext
    /// - Returns: true if there is already an edge between these to vertex, else returns false
    public Boolean checkEdge(Vertex origin, Vertex end){
        return (edgeDartOrigin(origin, end) != null );
    }
    
    /// create a simplex (triangle) to the map between three vertices
    /// - Parameters:
    ///   - v0: first vertex
    ///   - v1: second vertex
    ///   - v2: third vertex
    /// - Returns: dart of the simplex that has v0 as origin and is located inside.
    public Dart newSimplex(Vertex v0, Vertex v1, Vertex v2){
        Dart dart = this.edgeDartOrigin(v0, v1);
        final Dart dart0 =  dart == null ? this.makeEdgeBetween(v0, v1) : dart;
        dart = this.edgeDartOrigin(v1, v2);
        final Dart  dart1 = dart == null ? this.makeEdgeBetween(dart0, v2) : dart;
        if(dart0.getNext() != dart1) { throw new AssertionError("addSimplex(v1,v2,v3): problem edge1 not linked to edge2"); }
        final Dart dart2 = this.makeEdgeBetween(v2, v0);
        if( (dart1.getNext() != dart2) || (dart2.getNext() != dart0) ) { 
            throw new AssertionError("addSimplex(v1,v2,v3): problem edges not correctly linked"); }
        return(dart0);
    }
    
    /// create a simplex (triangle) to the map between an edge and a vertex
    /// - Parameters:
    ///   - edge: base of the simple: the two vertices of the edge will be two vertices of the simplex
    ///   - vertex: third vertex of the simplex
    /// - Returns: dart of the simplex that has second vertex of edge as origin and is located inside.
    public Dart newSimplex(Dart edge, Vertex vertex){
        if( edge.getOpposite() == edge) { throw new AssertionError("addSimplex(edge,vertex): edge is a single dart, not an edge!"); }
        final Vertex startvertex = edge.getStartVertex();
        final Vertex endvertex   = edge.getEndVertex();
        Dart dart = this.edgeDartOrigin(endvertex, vertex);
        final Dart dart1 = dart == null ? this.makeEdgeBetween(edge, vertex) : dart;
        if( edge.getNext() != dart1) { throw new AssertionError("addSimplex(edge,vertex): problem edge is not linked to dart that ends on vertex"); }
        dart = this.edgeDartOrigin(vertex, startvertex);
        final Dart dart2  = dart == null ? this.makeEdgeBetween(vertex, edge) : dart;
        if( (dart2.getNext() != edge) || (dart1.getNext() != dart2) ) { 
            throw new AssertionError("addSimplex(edge,vertex): problem edges not correctly linked"); }
        return(dart1);
    }

    
    /// make a tetraedre between the four vertices
    /// - Parameters:
    ///   - p0: first vertex
    ///   - p1: second vertex
    ///   - p2: third vertex
    ///   - p3: fourth vertex
    public void addTetra(Point p0, Point p1, Point p2, Point p3){
        // make the four vertices
        final Vertex v0 = this.newVertex(p0);
        final Vertex v1 = this.newVertex(p1);
        final Vertex v2 = this.newVertex(p2);
        final Vertex v3 = this.newVertex(p3);
        // makes edges
        final Dart e0  = this.newSimplex(v0, v1, v2);
        final Dart e3  = this.newSimplex(e0.getOpposite(), v3);
        final Dart e3p = e3.getOpposite();
        final Dart e2p = e3p.getNext();
        this.makeEdgeBetween(e2p, e3p);
    }
    
    
    public Boolean illegalDelaunay(Vertex r1, Vertex s, Vertex t, Vertex r2){
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        // TODO
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        return false;
    }

    public void flipEdge(Dart dart){
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        // TODO
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
    }
    
    private void push(Dart d, ArrayList<Dart> stack) {
        final Boolean isEdgeOfHull = ( (d.face == this.infinite) || (d.getOpposite().face == this.infinite) );
        if(!isEdgeOfHull && !d.marks && !d.getOpposite().marks) { // if edge not marked
            d.mark();
            stack.add(d);
        }
    };
    private Dart pop(ArrayList<Dart> stack) {
        final Dart ret = stack.remove(stack.size() - 1);
        ret.unmark();
        return ret;
    };
    public void delaunayTriangulate(){
        // initialize a stack
        ArrayList<Dart> stack = new ArrayList<Dart>();
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        // TODO
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
    }

    static Boolean visible(CenterOfGravity cog, Dart left, Dart right, Vertex vertex){
        final Point g = cog.center;
        final Point l = left.getStartVertex().point;
        final Point r = right.getStartVertex().point;
        final Point v = vertex.point;
        return( ( Vector.determinant(new Vector(g,r), new Vector(g,l)) * Vector.determinant(new Vector(v,r), new Vector(v,l)) ) < 0);
    }
    public static MeshMap makeMesh(ArrayList<Point> points){
        points.sort( (Point p1, Point p2) -> p1.x < p2.x ? -1 : ((p1.x > p2.x) ? 1 : ( p1.y < p2.y ? -1 : 1) ) );
        final MeshMap map = new MeshMap();
        ArrayList<Vertex> vertices = new ArrayList<Vertex>();
        for(Point p : points){
            vertices.add(map.newVertex(p));
        }
        map.newSimplex(vertices.get(1), vertices.get(2), vertices.get(3));
        // -------------------------------
        final ArrayList<Point> firstTriangle = new ArrayList<Point>();
        firstTriangle.add(vertices.get(1).point); firstTriangle.add(vertices.get(2).point); firstTriangle.add(vertices.get(3).point);
        var gc = new CenterOfGravity(firstTriangle);
        Dart last = vertices.get(3).findVertexStartingDart(map.infinite);
        if( last == null ) { throw new AssertionError("init first triangle fails"); }
        int i = 0;
        for( Vertex v : vertices){
            if( (i > 3) ){
                Dart right = last;
                Dart left  = last;
                // find right limit
                OrbitDartFaceIterator itright = new OrbitDartFaceIterator(right.getNext());
                Dart next = itright.current;
                while( itright.hasNext() && (next != left) && visible(gc, right, next, v) ){
                    right = next;
                    itright.next();
                    next = itright.current;
                }
                // find left limit
                OrbitDartFaceIterator itleft = new OrbitDartFaceIterator(left.getPrev());
                next = itleft.current;
                while( itleft.hasNext() && (next != right) && visible(gc, next, left, v) ){
                    left = next;
                    itleft.prev();
                    next = itleft.current;
                }
                // we found left and right limit
                last = map.makeEdgeBetween(v, right.getStartVertex());
                map.makeEdgeBetween(v, left.getStartVertex()); // map.makeEdgeBetween(ante: last.opposite, post: left.prev)
                // now let's make edges between v and vertices that are between left and right
                while( left.getEndVertex() != right.getStartVertex() ){
                    map.makeEdgeBetween(left, v);
                    left = left.getNext().getOpposite().getNext();                    
                }
                gc.add(v.point);
            }
            i += 1;
        }
        return(map);
    }
    
    

    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------

    
    // -----------------------------------------------------------------------------------------------------------------------
    // MARK: - Sequence and Iterator
    
    /// make an iterator over darts of the map
    /// - Returns: an interator
    public RecursiveListIterator<Dart> makeDartIterator(){
        return( this.darts.makeIterator() );
    }

    /// make an iterator over darts of this set
    /// - Returns: an iterator
    public Iterator<Dart> iterator(){
        return( this.darts.makeIterator() );
    }    

 
    /// make an iterator over faces of the map
    /// - Returns: an iterato
    public RecursiveListIterator<Face> makeFaceIterator() {
        return this.faces.makeIterator();
    }
    
    /// make an iterator over vertices of the map
    /// - Returns: an iterator
    public RecursiveListIterator<Vertex> makeVertexIterator() {
        return this.vertices.makeIterator();
    }

    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------


    // -----------------------------------------------------------------------------------------------------------------------
    // MARK: - Helper methods
    
    /// make an isolated edge between two vertices
    ///
    /// edge is located in infinite face and has no other edges connected.
    /// - Attention: if vertex belongs to other edges, resulting map will be inconsistent; this should be temporary
    /// - Parameters:
    ///   - origin: first vertex of the edge
    ///   - end: second vertex of the edge
    /// - Returns: dart of the edge that has first vertex as origin
    Dart makeEdgeDoubleDeadEnd(Vertex origin, Vertex end, Face f){
        final Face face = f == null ? this.infinite : f;
        final Dart dart = this.newDart(origin, face);
        final Dart oppo = this.newDart(end,    face);
        dart.sewOpposite(oppo);
        dart.linkNext(oppo);
        oppo.linkNext(dart);
        return (dart);
    }
    Dart makeEdgeDoubleDeadEnd(Vertex origin, Vertex end){
        return makeEdgeDoubleDeadEnd(origin, end, null);
    }
    
   
    /// find common faces for v1 and v2
    /// - Parameters:
    ///   - v1: first vertex
    ///   - v2: second vertex
    /// - Returns: return all face in common for
    private ArrayList<Face> findCommonFaces(Vertex v1, Vertex v2){
        ArrayList<Face> commonfaces = new ArrayList<Face>();
        ArrayList<Face> faces1 = v1.faces();
        if(faces1.size() == 0) { faces1.add(this.infinite); } // if no faces, it means that vertex has no reference dart and so is located in infinite face
        ArrayList<Face> faces2 = v2.faces();
        if(faces2.size() == 0) { faces2.add(this.infinite); } // if no faces, it means that vertex has no reference dart and so is located in infinite face
        for(Face f : faces1){
            if(faces2.contains(f) && !commonfaces.contains(f)) {
                commonfaces.add(f);
            }
        }
        return(commonfaces);
    }

    /// check if vertices has a single common face and return it;
    /// by single common face we mean either infinite face if it is the single common face, or the non infinite face if there are exactly two common faces
    /// - Parameters:
    ///   - v1: first vertex
    ///   - v2: second vertex
    /// - Returns: the common face of v1 and v2;
    /// if no common face returns nil;
    /// if 3 or more common faces returns it;
    /// if 2 common faces and none of the two is the infinite face, returns it;
    /// at last if there are 1 common face, returns it, or if there are two including infinite face, returns the non infinite common face
    private Face findSingleCommonFace(Vertex v1, Vertex v2){
        Face face;
        final ArrayList<Face> commonfaces = this.findCommonFaces(v1, v2);
        if (commonfaces.size() == 0) { return(null); }
        if (commonfaces.size() >= 3) {
            throw new AssertionError("makeEdge: more than two faces in common, so impossible to choose, please provide one"); }
        if( (commonfaces.size() != 1) && (!commonfaces.contains(this.infinite)) ){
            throw new AssertionError("makeEdge: two faces in common but none is infinite face, so impossible to choose, please provide one"); }
        face = commonfaces.size() == 1 ? commonfaces.get(0) : (commonfaces.get(0) == this.infinite ? commonfaces.get(1) : commonfaces.get(0));
        return(face);
    }
    
}
