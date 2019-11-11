
public class Main {

    public static void main(String[] args) {
        Auto a1 = Garage.getAuto(10000);
        Auto a2 = Garage.getAuto(100);

        int t=10;

        System.out.println(a1.toString(t));
        System.out.println(a2.toString(t));
    }
}