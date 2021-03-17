
public class Vertex {
	private HEdge edge;
	private static int nb = 0;
	private int name;
	private float x;
	private float y;
	private float z;

	public Vertex() {
		// TODO Auto-generated constructor stub
	}
	public Vertex(int x, int y, int z) {
		this.x = x;
		this.y = y;
		this.z = z;
		this.nb = nb+1;
		this.name = nb;
		
		
		this.edge = null;
	}
	public Vertex(int x, int y, int z, HEdge he) {
		this.x = x;
		this.y = y;
		this.z = z;
		
		this.edge = he;
	}
	public HEdge getEdge() {
		return edge;
	}
	public void setEdge(HEdge edge) {
		this.edge = edge;
	}
	public float getX() {
		return x;
	}
	public void setX(float x) {
		this.x = x;
	}
	public float getY() {
		return y;
	}
	public void setY(float y) {
		this.y = y;
	}
	public float getZ() {
		return z;
	}
	public void setZ(float z) {
		this.z = z;
	}
	@Override
	public String toString() {
		return "" + name+ "" ;
	}

}
