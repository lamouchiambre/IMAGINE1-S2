import java.util.ArrayList;

public class Maillage {
	ArrayList<HEdge> hedges;
	ArrayList<Face> faces;
	ArrayList<Vertex> vertex;

	public Maillage() {
		// TODO Auto-generated constructor stub
		faces = new ArrayList<Face>();
		hedges = new ArrayList<HEdge>();
		vertex = new ArrayList<Vertex>();
	}
	
	void addFace3p(Vertex v1, Vertex v2, Vertex v3) {
		/*
		 * si v1 n'est pas dansla list 
		 * 	ajouter v1
		 * faire les reste pour v2 v3
		 * 
		 * */
		HEdge he_12 = new HEdge(v2, null, null, null, null);
		HEdge he_23 = new HEdge(v3, null, he_12,  null, null);
		HEdge he_31 = new HEdge(v1, he_12, he_23, null, null);
		
		HEdge he_21 = new HEdge(v1, null, null, he_12, null);
		HEdge he_13 = new HEdge(v3, null, he_21,  he_31, null);
		HEdge he_32 = new HEdge(v2, he_21, he_13, he_23, null);
		
		Face face123 = new Face();
		
		he_12.setFace(face123);
		he_23.setFace(face123);
		he_31.setFace(face123);
		
		he_23.setNext(he_31);
		he_23.setOpposite(he_32);
		
		he_13.setNext(he_32);
		
		he_21.setNext(he_13);
		he_21.setPrec(he_32);
		
		he_31.setOpposite(he_13);
		
		
		he_12.setNext(he_23);
		he_12.setPrec(he_31);
		he_12.setOpposite(he_21);
		
		v1.setEdge(he_31);
		v2.setEdge(he_12);
		v3.setEdge(he_23);
		
		face123.setFaces(he_12, he_23, he_31);
		
		faces.add(face123);
		
		hedges.add(he_12);
		hedges.add(he_23);
		hedges.add(he_31);
		
		hedges.add(he_21);
		hedges.add(he_32);
		hedges.add(he_13);
		
		vertex.add(v1);
		vertex.add(v2);
		vertex.add(v3);
	}
	
	public void addFace3p(HEdge h12, Vertex v3) {
		
		HEdge h23  = new HEdge(v3, null, h12,null, null);
		HEdge h31 = new HEdge(h12.getOpposite().getVhead(), h12, h23, null, null);
		
		HEdge h32 = new HEdge(h12.getVhead(), null, h12.getOpposite(),h23, null);
		HEdge h13 = new HEdge(v3, h32, h12.getOpposite(), h23, null);
		
		h23.setNext(h31);
		h23.setOpposite(h32);
		
		h31.setOpposite(h13);
		
		h32.setPrec(h13);
		
		Face f = new Face();
		f.setFaces(h12,h23,h31);
		
		h12.setFace(f);
		h23.setFace(f);
		h31.setFace(f);
		
	}
	
	public ArrayList<HEdge> insidence(Vertex s){
		ArrayList<HEdge> list  = new ArrayList<HEdge>();
		HEdge eh = s.getEdge();
		while (eh.getOpposite() != null) {
			list.add(eh);
			list.add(eh.getOpposite());
			eh = eh.getOpposite();
			for(int i = 0; i <2; i++) {
				eh = eh.getNext();
			}
		}
		return list;
	}
	
	public ArrayList<Vertex> getSommetFace(Face f){
		ArrayList<Vertex> sommets = new ArrayList<Vertex>();
		for(HEdge he : f.getFaces()) {
			sommets.add(he.getVhead());
		}
		return sommets;
	}
	
	public ArrayList<Vertex> getSommetEgde(HEdge he){
		ArrayList<Vertex> sommets = new ArrayList<Vertex>();
		sommets.add(he.getVhead());
		sommets.add(he.getOpposite().getVhead());
		return sommets;
	}
	
	public ArrayList<Face> getfacesAdjacentes(HEdge he){
		ArrayList<Face> l_face = new ArrayList<Face>();
		l_face.add(he.getFace());
		l_face.add(he.getOpposite().getFace());
		return l_face;
	}
	public ArrayList<ArrayList<Vertex>> getEdgeface(Face f){
		ArrayList<ArrayList<Vertex>> arretes = new ArrayList<ArrayList<Vertex>>();
		for(HEdge v : f.getFaces()) {
			arretes.add(this.getSommetEgde(v));
		}
		return arretes;
	}
	
	//void add

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Maillage m = new Maillage();
		
		Vertex v1 = new Vertex(0,0,0);
		Vertex v2 = new Vertex(1,1,1);
		Vertex v3 = new Vertex(2,2,2);
		
		m.addFace3p(v1, v2, v3);
		
		System.out.println(m.getHedges().get(3));
		System.out.println(m.getHedges().get(3).getNext());
		System.out.println(m.getHedges().get(3).getNext().getNext());
		
		
	}

	public ArrayList<HEdge> getHedges() {
		return hedges;
	}

	public void setHedges(ArrayList<HEdge> hedges) {
		this.hedges = hedges;
	}

	public ArrayList<Face> getFaces() {
		return faces;
	}

	public void setFaces(ArrayList<Face> faces) {
		this.faces = faces;
	}

	public ArrayList<Vertex> getVertex() {
		return vertex;
	}

	public void setVertex(ArrayList<Vertex> vertex) {
		this.vertex = vertex;
	}

}
