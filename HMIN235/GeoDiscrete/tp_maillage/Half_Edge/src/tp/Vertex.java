package tp;

public class Vertex {
	public HalfEdge he;
	public Point point;
	public Vertex() {
		// TODO Auto-generated constructor stub
		this.point = new Point(0,0,0);
		this.he = null;
				//new HalfEdge(this);
	}
	@Override
	public String toString() {
		return "[" + point + "]";
	}
	public Vertex(Point p) {
		// TODO Auto-generated constructor stub
		this.point = p;
		this.he = new HalfEdge(this);
	}

}
