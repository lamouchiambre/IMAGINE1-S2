package tp;

public class HalfEdge {
	//public vertex 
	public Vertex vertex;
	public HalfEdge next;
	public HalfEdge prev;
	public HalfEdge opposite;
	

	public HalfEdge() {
		// TODO Auto-generated constructor stub
	}
	public HalfEdge(Vertex vertex) {
		// TODO Auto-generated constructor stub
		this.vertex = vertex;
		this.opposite = this;
		this.prev = this;
		this.next = this;
	}
	@Override
	public String toString() {
		return "HalfEdge [" + vertex + " ==> " + this.opposite.vertex + "]";
	}
	

}
