import java.util.ArrayList;

public class Face {
	
	private ArrayList<HEdge> faces;
	private static int nb = 0;
	private int name;
	
	public Face() {
		// TODO Auto-generated constructor stub
		this.nb = nb+1;
		this.name = nb;
	}
	public ArrayList<HEdge> getFaces() {
		faces = new ArrayList<HEdge>();
		return faces;
	}
	public void setFaces(ArrayList<HEdge> faces) {
		this.faces = faces;
	}
	public void setFaces(HEdge HEdge1, HEdge HEdge2, HEdge HEdge3 ) {
		this.faces = new ArrayList<HEdge>();
		faces.add(HEdge1);
		faces.add(HEdge2);
		faces.add(HEdge3);
	}
	@Override
	public String toString() {
		return "Face [faces=" + faces + "]";
	}


}
