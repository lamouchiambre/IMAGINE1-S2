public class Dart extends RecursiveListElt {
    /// static var for compute id
    static int count = 0;
    
    public Boolean marks = false;
    
    public void mark(){
        this.marks = true;
    }
    public void unmark(){
        this.marks = false;
    }

    /// string output of a dart
    public String  toString() {
        return this.getName()+"["+this.getPrev().getName()+";"+this.getNext().getName()+";"+this.getOpposite().getName()+"]<"+this.face.getName()+","+this.getStartVertex().getName()+"-"+this.getEndVertex().getName()+">";
    }

    public String getName(){
        final String sid = String.format("%02d", this.id);
        return "d"+sid;
    }
    /// id of dart; useful to identify uniquely each dart and facilitate description
    private final int id;
    
    // MARK: - Half-edge
    
    /// betas operators (prev, next, opposite)
    private Dart betas[];
    
    /// beta_i operator
    /// - Parameter i: dimension of operator, 0 means oposite to beta_1
    /// - Returns: dart that is linked to self according to dimension i
    public Dart beta(int i){
        return this.betas[i];
    }
    /// set value of beta_i operator
    /// - Parameters:
    ///   - i: dimension of operator, 0 means oposite to beta_1
    ///   - dart: dart that will become beta_i value of self
    void setBeta(int i, Dart dart){
        this.betas[i] = dart;
    }
    
    /// next edge in face, by default itsel: ß1 operator
    Dart getNext(){ return this.betas[1]; }
    void setNext(Dart newValue){ this.betas[1] = newValue; }
    
    /// previous edge in face, by default itsel: ß0 operator
    Dart getPrev() { return this.betas[0]; }
    void setPrev(Dart newValue) { this.betas[0] = newValue; }
    
    /// same edge but opposite face, by default itsel: ß2 operator
    Dart getOpposite() { return this.betas[2]; }
    void setOpposite(Dart newValue) { this.betas[2] = newValue; }
    
    /// origin vertex of this half-edge
    private Vertex vertex;
    /// start vertex of this edge, i.e. origin vertex of the dart
    public Vertex getStartVertex(){ return this.vertex; }
    void setStartVertex(Vertex newValue) { this.vertex = newValue; }
    
    /// end vertex of this edge, i.e origin vertex of the opposite dart
    public Vertex getEndVertex(){ return this.getOpposite().vertex; }
    void setEndVertex(Vertex newValue) { this.getOpposite().vertex = newValue; }
    
    /// Face of the dart
    Face face;
    
    /// has this dart another following dart (edge) in the face
    public Boolean isNextFree() {
        return this.betas[1] == this;
    }
    /// has this dart another preceding dart (edge) in the face
    public Boolean isPreFree() {
        return this.betas[0] == this;
    }
    /// has this dart another opposite dart (edge) in the opposite face
    public Boolean isOppositeFree() {
        return this.betas[2] == this;
    }
    
    /// initialize a dart
    /// - Parameters:
    ///   - vertex: vertex attached (origin) to dart
    ///   - face: face of the dart
    Dart(Vertex vertex, Face face){
        super();
        this.id      = Dart.count;
        this.face    = face;
        this.vertex  = vertex;
        this.betas = new Dart[] { this, this, this};
        if (vertex.refDart == null) { vertex.refDart = this; }
        if (face.refDart == null) { face.refDart = this;   }
        Dart.count += 1;
    }
    
    /// dart will become next of self, and self becomes previous of dart
    /// - Parameter dart: dart to be linked
    void linkNext(Dart dart){
        this.betas[1] = dart;
        dart.betas[0] = this;
    }
    /// this dart will no more have a next, and old next dart will no more have a previous
    Dart unlinkNext(){
        final Dart ret = this.betas[1];
        this.betas[1].betas[0] = this.betas[1]; // ß1 of self will becomes link to itself by ß0
        this.betas[1]    = this; // self is link to itself by ß1 => ß1 free
        return ret;
    }
    
    /// dart will become previous of self, and self becomes next of dart
    /// - Parameter dart: dart to be linked
    void linkPrev(Dart dart){
        this.betas[0] = dart;
        dart.betas[1] = this;
    }
    /// this dart will no more have a previous, and old previous dart will no more have a next
    Dart unlinkPrev(){
        final Dart ret = this.betas[0];
        this.betas[0].betas[1] = this.betas[0]; // ß0 of self will becomes link to itself by ß1
        this.betas[0]    = this; // self is link to itself by ß0 => ß0 free
        return ret;
    }

    /// dart will become opposite of self, and self becomes opposite of dart
    /// - Parameter dart: dart to be linked
    void linkOpposite(Dart dart){
        this.betas[2] = dart;
        dart.betas[2] = this;
    }
    /// this dart will no more have an opposite, and old previous dart will no more have an opposite
    Dart unlinkOpposite(){
        final Dart ret = this.betas[2];
        this.betas[2].betas[2] = this.betas[2]; // ß2 of self will becomes link to itself by ß2
        this.betas[2]    = this; // self is link to itself by ß2 => ß2 free
        return ret;
    }
    
    //    @discardableResult
    /// link self with dart as opposite and ensure consistence of map
    /// - Parameter dart: dart to be sewn
    void sewOpposite(Dart dart){
        this.linkOpposite(dart);
    }
    /// unlink self from it's opposite ensure consistence of map
    public void unsewOpposite(){
        this.unlinkOpposite();
    }
    
    /// sew dart as next of self: link dart as next to self and ensure consistence of map
    /// - Parameter dart: dart to be sewn
    void sewNext(Dart dart){
        final Dart dartprev  = dart.getPrev();
        this.linkNext(dart);
        this.getOpposite().linkPrev(dartprev);
    }
    
    /// unsew itself from next:  unlink itself from next and ensure consistence of map
    void unsewNext(){
        final Dart dartprev = this.getOpposite().getPrev();
        final Dart dartnext = this.getNext();
        dartprev.linkNext(dartnext);
        this.linkNext(this.getOpposite());
    }

    /// sew dart as prev of self: link dart as prev to self and ensure consistence of map
    /// - Parameter dart: dart to be sewn
    public void sewPrev(Dart dart){
        final Dart dartnext = dart.getNext();
        this.linkPrev(dart);
        this.getOpposite().linkNext(dartnext);
    }

    /// unsew itself from previous:  unlink itself from previous and ensure consistence of map
    public void unsewPrev(){
        final Dart dartprev = this.getPrev();
        final Dart dartnext = this.getPrev().getNext();
        dartprev.linkNext(dartnext);
        this.linkPrev(this.getOpposite());
    }

    // /// the two vertices of edge of this dart
    // public var edgeVertices : (start: Vertex, end: Vertex){
    //     return (start: self.vertex, end: self.opposite.vertex)
    // }
    
    // /// the two faces separated by the edge of this dart
    // public var edgeFaces: (face: Face, faceop: Face){
    //     return (face: self.face, faceop: self.opposite.face) // ma face, et celle de mon opposée
    // }
    
    
}
