package tp;

import java.util.ArrayList;

public class Mesh {
	ArrayList<HalfEdge> hedges;
	ArrayList<Vertex> vertex;

	public Mesh() {
		
	}
	
	public void coudreEdge(HalfEdge e1, HalfEdge e2) {
		e1.next = e2;
		e2.next = e1;
		
		e1.prev = e2;
		e2.prev = e1;
		
		e1.opposite = e2;
		e2.opposite = e1;
	}
	
	public Vertex[] sommets(HalfEdge he){
		Vertex [] som = { he.vertex, he.opposite.vertex };
		return som;
	}
	
	public HalfEdge addEdge3(Vertex v1, Vertex v2) {
		HalfEdge e1 = new HalfEdge(v1);
		this.coudreEdge(e1, v2.he);
		
		return e1;
	}
//	public void addEdge(Vertex v1, Vertex v2) {
//		HalfEdge e1 = new HalfEdge(v1);
//		HalfEdge e2 = new HalfEdge(v2);
//		v1.he = e1;
//		v2.he = e2;
//		this.coudreEdge(e1, e2);
//		hedges.add(e1);
//	}
	
//	public void addEdge2(Vertex v1, Vertex v2) {
//		this.coudreEdge(v1.he, v2.he);
//		//hedges.add(v1.he);
//	}
	
	public void addface(Vertex v1, Vertex v2, Vertex v3) {
		HalfEdge e0 = this.addEdge3(v1, v2);
		HalfEdge e2 = this.addEdge3(v2, v3);
		
		this.coudreNext(e0, e2);
		this.coudreNext(e2.opposite, e0.opposite);
		
		HalfEdge e4 = this.addEdge3(v3, v1);
		
		this.coudreNext(e2,e4);
		this.coudreNext(e4.opposite,e2.opposite);
		this.coudreNext(e4,e0);
		this.coudreNext(e0.opposite,e4.opposite);		
	}
	
	public void addface(HalfEdge h1, HalfEdge h2) {
		HalfEdge he1  = this.addEdge3(h1.vertex, h2.opposite.vertex);
		this.coudreNext(he1, h2.next);
		this.coudrePrec(he1, h1.prev);
		
		this.coudreNext(he1.opposite,h1);
		this.coudrePrec(he1.opposite, h2);
	}
	
	public void addface(HalfEdge he, Vertex v) {
		Vertex v1 = new Vertex(he.opposite.vertex.point);
		Vertex v2 = new Vertex(he.vertex.point);
		HalfEdge he2 = this.addEdge3(v, v2);
		HalfEdge he1 = this.addEdge3(v1, v);
		
		this.coudreNext(he1, he2);
		this.coudreNext(he2.opposite, he1.opposite);
	
		this.coudreNext(he.prev, he2.opposite);
		this.coudreNext(he1.opposite, he.next);
		
		this.coudreNext(he, he1);
		this.coudreNext(he2, he);
		
	}
	
//	public void addface2(HalfEdge he, Vertex v) {
//		HalfEdge he1 = this.addEdge3(he.opposite.vertex, v);
//		HalfEdge he2  = this.addEdge3(v, he.vertex);
//		
//		this.coudreNext(he1, he2);
//		this.coudreNext(he2.opposite, he1.opposite);
//		
//		this.coudreNext(he, he1);
//		this.coudreNext(he2, he);
//		
//		this.coudreNext(he.prev, he2.opposite);
//		this.coudreNext(he1.opposite, he.next);		
//		
//	}	
	
	
	public void coudreOpposite(HalfEdge e1, HalfEdge e2) {
		e1.opposite = e2;
		e2.opposite = e1;
	}
	public void coudreNext(HalfEdge e1, HalfEdge e2) {
		e1.next = e2;
		e2.prev = e1;
	}
	
	public void coudrePrec(HalfEdge e1, HalfEdge e2) {
		e1.prev = e2;
		e2.next = e1;
	}
	public static void main(String[] args){
		//constrution du tetraedre
		Point p0 = new Point(0, 0, 0);
		Point p1 = new Point(1, 1, 1);
		Point p2 = new Point(2, 2, 2);
		Point p3 = new Point(3, 3, 3);
		
		Vertex v0 = new Vertex(p0);
		Vertex v1 = new Vertex(p1);
		Vertex v2 = new Vertex(p2);
		Vertex v3 = new Vertex(p3);
		
		Mesh m = new Mesh();
		m.addface(v0, v1, v2);
		//m.addEdge2(v0, v1);
		
		
		System.out.println("------------");
		System.out.println(v0.he.opposite);
		System.out.println(v0.he.opposite.next);
		System.out.println(v0.he.opposite.next.next);
		System.out.println(v0.he.opposite.next.next.next);
		System.out.println("------------");
		
		m.addface(v0.he.opposite,v3);
		
		//iteration 
		IterVertex it = new IterVertex(v0.he);
		while(it.hasNext()) {
			System.out.println(it.next());
		}
		
		System.out.println(m.sommets(v0.he)[0] + " " + m.sommets(v0.he)[1]);
		
		m.addface(v2.he.opposite, v2.he.opposite.next);
		System.out.println("############");
		System.out.println("------------");
		System.out.println(v0.he);
		System.out.println(v0.he.next);
		System.out.println(v0.he.prev);
		System.out.println(v0.he.opposite);
		System.out.println("------------");
		System.out.println(v1.he);
		System.out.println(v1.he.next);
		System.out.println(v1.he.prev);
		System.out.println(v1.he.opposite);
		System.out.println("------------");
		System.out.println(v2.he);
		System.out.println(v2.he.next);
		System.out.println(v2.he.prev);
		System.out.println(v2.he.opposite);
		System.out.println("------------");
		System.out.println(v3.he);
		System.out.println(v3.he.next);
		System.out.println(v3.he.prev);
		System.out.println(v3.he.opposite);
		System.out.println("------------");
		System.out.println(v3.he);
		System.out.println(v3.he.next);
		System.out.println(v3.he.prev);
		System.out.println(v3.he.opposite);
		System.out.println("------------");
		System.out.println(v3.he.prev);
		System.out.println(v3.he.prev.next);
		System.out.println(v3.he.prev.prev);
		System.out.println(v3.he.prev.opposite);
		System.out.println("------------");
		System.out.println(v0.he.opposite.next);
		System.out.println(v3.he.opposite.next.next);
		System.out.println(v3.he.opposite.next.prev);
		System.out.println(v3.he.opposite.next.opposite);
		
		
		
//		//////////
//		System.out.println("------------");
//		System.out.println(v3.he);
//		System.out.println(v3.he.next);
//		System.out.println(v3.he.next.next);
//		System.out.println(v3.he.next.next.next);
//		System.out.println(v3.he.next.next.next.next);
//		System.out.println("------------");
//		System.out.println(v3.he.opposite);
//		System.out.println(v3.he.opposite.next);
//		System.out.println(v3.he.opposite.next.next);
//		System.out.println(v3.he.opposite.next.next.next);
//		System.out.println("------------");
//		System.out.println(v0.he.opposite);
//		System.out.println(v0.he.opposite.next);
//		System.out.println(v0.he.opposite.next.next);
//		System.out.println(v0.he.opposite.next.next.next);
//		System.out.println("------------");
//		m.addface(v2.he.opposite, v2.he.opposite.next);
//		System.out.println(v2.he.opposite);
//		System.out.println(v2.he.opposite.next);
//		System.out.println(v2.he.opposite.next.next);
//		System.out.println(v2.he.opposite.next.next.next);
//		System.out.println(v3.he.opposite.prev);
		
	}
	 

}
