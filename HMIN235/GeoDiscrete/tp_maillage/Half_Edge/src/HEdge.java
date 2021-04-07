
public class HEdge {

	private Vertex vhead;
	private HEdge next;
	private HEdge prec;
	private HEdge opposite;
	private Face face;
	
	public HEdge() {
		// TODO Auto-generated constructor stub
	}
	public HEdge(Vertex vhead, HEdge next, HEdge prec, HEdge opposite, Face face) {
		super();
		this.vhead = vhead;
		this.next = next;
		this.prec = prec;
		this.opposite = opposite;
		this.face = face;
	}
	
	//Getter Setter

	public Vertex getVhead() {
		return vhead;
	}

	public void setVhead(Vertex vhead) {
		this.vhead = vhead;
	}

	public HEdge getNext() {
		return next;
	}

	public void setNext(HEdge next) {
		this.next = next;
	}

	public HEdge getPrec() {
		return prec;
	}

	public void setPrec(HEdge prec) {
		this.prec = prec;
	}

	public HEdge getOpposite() {
		return opposite;
	}

	public void setOpposite(HEdge opposite) {
		this.opposite = opposite;
	}

	public Face getFace() {
		return face;
	}

	public void setFace(Face face) {
		this.face = face;
	}
	public void afficheArretes() {
		System.out.println("(" + this.vhead + " -> " + this.opposite.getVhead() + ")" );
	}
	@Override
	public String toString() {
		//return "HEdge [vhead=" + vhead + "]";
		return " (" + this.opposite.getVhead()+ " -> " + this.vhead  + ") " ;
	}

}
