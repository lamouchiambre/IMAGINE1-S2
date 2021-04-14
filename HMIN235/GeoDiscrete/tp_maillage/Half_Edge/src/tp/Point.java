package tp;

public class Point {
	public int x;
	public int y;
	public int z;
	
	public Point(int x, int y, int z) {
		super();
		this.x = x;
		this.y = y;
		this.z = z;
	}

	@Override
	public String toString() {
		return " (" + x + ", " + y + ", " + z + ")";
	}

	public Point() {
		// TODO Auto-generated constructor stub

	}

}
