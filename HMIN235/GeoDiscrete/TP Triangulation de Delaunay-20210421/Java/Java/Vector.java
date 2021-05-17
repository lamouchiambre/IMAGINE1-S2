

public class Vector {
    /// x corrdinate of point
    private double x;
    /// y corrdinate of point
    private double y;
    /// z corrdinate of point
    private double z;
    
    private Point initial;
    private Point terminal;
    
    


    public double getX() {
        return x;
    }
    public double getY() {
        return y;
    }
    public double getZ() {
        return z;
    }
    public Point getInitial() {
        return initial;
    }
    public Point getTerminal() {
        return terminal;
    }

    public String toString() {
        return "("+x+","+y+","+z+")";
    }
    
    /// initialize point from coordinates
    /// - Parameters:
    ///   - x: x coordinate
    ///   - y: y coordinate
    ///   - z: z coordinate
    public Vector(double x, double y, double z){
        this.x = x;
        this.y = y;
        this.z = z;
        this.initial  = new Point(0,0,0);
        this.terminal = new Point(x,y,z);
    }
    
    public Vector(Point p, Point q){
        this.x = q.getX() - p.getX();
        this.y = q.getY() - p.getY();
        this.z = q.getZ() - p.getZ();
        this.initial  = new Point(p);
        this.terminal = new Point(q);
    }

    public static double cross(Vector left, Vector right){
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }
    public static Vector opp(Vector vector) {
        return new Vector(-vector.x, -vector.y, -vector.z);
    }

    public static double determinant(Vector u, Vector v){
        return u.x * v.y - v.x * u.y;
    }

    public static double mixproduct(Vector u, Vector v, Vector w){
        return u.x * v.y * w.z + v.x * w.y * u.z + w.x * u.y * v.z - u.x * w.y * v.z - u.x * w.y * v.z - v.x * u.y * w.z - w.x * v.y * u.z;
    }
    
    Point getCenter() {
        return new Point( (initial.getX() + terminal.getX()) / 2.0 , (initial.getY() + terminal.getY()) / 2.0 , (initial.getZ() + terminal.getZ()) / 2.0 );
    }
    
    double getNorm() {
        double sqrt = Math.sqrt(x * x + y * y + z * z);
        return sqrt;
    }

}    
