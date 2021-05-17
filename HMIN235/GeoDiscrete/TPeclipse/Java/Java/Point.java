import java.util.ArrayList;
import java.util.Comparator;

public class Point {
    /// x corrdinate of point
    double x;
    /// y corrdinate of point
    double y;
    /// z corrdinate of point
    double z;

    public double getX(){
        return this.x;
    }
    public void setY(double y) {
        this.y = y;
    }
    public double getY() {
        return y;
    }
    public double getZ() {
        return z;
    }

    public Point(double x, double y, double z){
        this.x = x;
        this.setY(y);
        this.z = z;
    }

    public Point(Point p){
        this.x = p.x;
        this.setY(p.getY());
        this.z = p.z;
    }

    public String toString() {
        return "("+x+","+getY()+","+z+")";
    }
    
    public static Point circumcenter(Point A, Point B, Point C){
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        // TODO
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        return new Point(0, 0, 0);
    }

    public static Double circumradius(Point A, Point B, Point C){
        final Circle circle = circumcircle(A, B, C);
        return circle.getRadius();
    }

    public static Circle circumcircle(Point A, Point B, Point C){
        final Point O = circumcenter(A, B, C);
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        // TODO
        // -------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------
        final double radius = 0;
        return new Circle(O,radius);
    }

    public static Comparator<Point> PointComparator = new Comparator<Point>() {

        public int compare(Point p1, Point p2) {
           //ascending order
           if ( (p1.x < p2.x) || ( (p1.x == p2.x) && (p1.y < p1.y) ) ){
               return -1;
           }
           else {
               return 1;
           }
        }
    };

    public static int compare(Point p1, Point p2) {
        //ascending order
        if ( (p1.x < p2.x) || ( (p1.x == p2.x) && (p1.y < p1.y) ) ){
            return -1;
        }
        else {
            return 1;
        }
    }
}


class CenterOfGravity{
    Point center;
    private double weight;

    CenterOfGravity(ArrayList<Point> points){
        double sx = 0;
        double sy = 0;
        double sz = 0;
        for(Point p : points){
            sx += p.x;
            sy += p.y;
            sz += p.z;
        }
        final double w = points.size();
        this.center = new Point(sx/w, sy/w, sz/w);
        this.weight = w;
    }
    
    void add(Point p){
        final double w = this.weight + 1;
        this.center = new Point((this.center.x * this.weight + p.x)/w,
                                (this.center.y * this.weight + p.y)/w,
                                (this.center.z * this.weight + p.z)/w);
        this.weight = w;
    }
}
