public class Circle{
    private final double radius;
    private final Point  center;

    public double getRadius(){
        return this.radius;
    }
    public Point getCenter(){
        return this.center;
    }
    
    public Circle(Point center, double radius){
        this.center = center;
        this.radius = radius;
    }
}