import java.util.ArrayList;

class Try{

    void testSimplexFromVerticesPrint(){
        final MeshMap map = new MeshMap();
        // make the four vertices
        final Vertex v0 = map.newVertex(new Point(1, -1, 0));
        System.out.println("----SimplexFromVertices----------------------------------------------------------------------");
        System.out.println(map);
        System.out.println("---------------------------------------------------------------------------------------------");
        final Vertex v1 = map.newVertex(new Point(-1, -1, 0));
        final Vertex v2 = map.newVertex(new Point(0, 1, 0));
        // // makes edges
        map.newSimplex(v0, v1, v2);
        System.out.println("----SimplexFromVertices----------------------------------------------------------------------");
        System.out.println(map);
        System.out.println("---------------------------------------------------------------------------------------------");
    }

	void testSimplexFromEdgeAndVertexPrint(){
        final MeshMap map = new MeshMap();
        // make the four vertices
        final Vertex v0 = map.newVertex(new Point( 1, -1, 0));
        final Vertex v1 = map.newVertex(new Point(-1, -1, 0));
        final Vertex v2 = map.newVertex(new Point( 0,  1, 0));
        final Vertex v3 = map.newVertex(new Point( 0,  0, 1));
        // makes edges
        final Dart e0 = map.newSimplex(v0, v1, v2);// ; let e1 = e0.opposite
        map.newSimplex(e0.getOpposite(), v3);
        System.out.println("----SimplexFromEdgeAndVertex-----------------------------------------------------------------");
        System.out.println(map);
        System.out.println("---------------------------------------------------------------------------------------------");
    }

	void testTetraPrint() {
        final MeshMap map = new MeshMap();
        map.addTetra(new Point(1, -1, 0), new Point(-1, -1, 0), new Point(0, 1, 0), new Point(0, 0, 1));
        System.out.println("---------------------------------------------------------------------------------------------");
        System.out.println(map);
        System.out.println("---------------------------------------------------------------------------------------------");
    }

	void testMakeMesh(){
        final Point p0 = new Point(0, 0, 0);
        final Point p1 = new Point(1, 5, 0);
        final Point p2 = new Point(2, 2, 0);
        final Point p3 = new Point(2, 4, 0);
        final Point p4 = new Point(3, 8, 0);
        final Point p5 = new Point(4, 4, 0);
        final Point p6 = new Point(5, 3, 0);
        final Point p7 = new Point(5, 6, 0);
        final Point p8 = new Point(7, 2, 0);
        final Point p9 = new Point(8, 6, 0);
        //  ------------------------------
        ArrayList<Point> points = new ArrayList<Point>();
		points.add(p0); points.add(p1); points.add(p2); points.add(p3); points.add(p4);
		points.add(p5); points.add(p6); points.add(p7); points.add(p8); points.add(p9);
        final MeshMap map = MeshMap.makeMesh(points);
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        System.out.println(map);
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        System.out.println("convex hull");
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        final OrbitVertexFace orbitVertex = map.infinite.makeOrbitVertexFace();
        for(Vertex v : orbitVertex){
            System.out.println(v);
        }
    }
    
    void testDelaunayTriangulate(){
        final Point p0 = new Point(0, 0, 0);
        final Point p1 = new Point(1, 5, 0);
        final Point p2 = new Point(2, 2, 0);
        final Point p3 = new Point(2, 4, 0);
        final Point p4 = new Point(3, 8, 0);
        final Point p5 = new Point(4, 4, 0);
        final Point p6 = new Point(5, 3, 0);
        final Point p7 = new Point(5, 6, 0);
        final Point p8 = new Point(7, 2, 0);
        final Point p9 = new Point(8, 6, 0);
        //  ------------------------------
        ArrayList<Point> points = new ArrayList<Point>();
		points.add(p0); points.add(p1); points.add(p2); points.add(p3); points.add(p4);
		points.add(p5); points.add(p6); points.add(p7); points.add(p8); points.add(p9);
        final MeshMap map = MeshMap.makeMesh(points);
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        System.out.println(map);
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        map.delaunayTriangulate();
        System.out.println("---TRIANGULATION-------------------------------------------------------------------------------------------------");
        System.out.println("map 1");
        System.out.println(map);
        System.out.println("map 2");
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        System.out.println("darts");
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        for(Dart d : map){
            System.out.println(d);
        }
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        System.out.println("vertices");
        System.out.println("-----------------------------------------------------------------------------------------------------------------");
        for(Vertex v : map.vertices){
            System.out.println(v);
        }
    }

    void testTriangleCirconsrit(){
        Point a = new Point(1, 4, 0);
        Point b = new Point(2, 8, 0);
        Point c = new Point(3, 6, 0);
        Circle cercle =  a.circumcircle(a, b, c);
        System.out.println(cercle.getCenter());
        System.out.println(cercle.getRadius());

    }

	Try(){}

	public static void main (String arg[])
	{
		System.out.println("Youpi!");
		Try t = new Try();
		// t.testSimplexFromVerticesPrint();
		// t.testSimplexFromEdgeAndVertexPrint();
		// t.testTetraPrint();
		// t.testMakeMesh();
		t.testDelaunayTriangulate();
        //t.testTriangleCirconsrit();
	}
}

