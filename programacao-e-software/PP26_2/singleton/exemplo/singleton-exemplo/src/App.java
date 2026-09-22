public class App {
    public static void main(String[] args) throws Exception {
        CostructorSingleton singleton = CostructorSingleton.getInstance();
        CostructorSingleton singleton1 = CostructorSingleton.getInstance();
        singleton.showMessage();
        singleton1.showMessage();

        System.out.println("São a mesma instância? " + (singleton == singleton1));
    }
}
