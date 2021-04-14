package tp;

//import java.util.Iterator;

public class IterVertex { //implements Iterator<HalfEdge > 
	public HalfEdge start;
	public HalfEdge current;
	public int ite = 0; //le nombre d'iteration effectuée
	//public Vertex next;


	public boolean hasNext() {
		// TODO Auto-generated method stub
		if (!(current == start && ite != 0))
			return true;
		return false;
	}

	public IterVertex(HalfEdge start) {
		super();
		this.start = start;
		this.current = start;
	}

	public Vertex next() {
		// TODO Auto-generated method stub
		//this.current.opposite.vertex;
		Vertex s = this.current.opposite.vertex;
		this.current = this.current.opposite.next;
		ite++;
		return s;
	}
	public void clear() {
		this.ite = 0;
		this.current = this.start;
		
	}

}
