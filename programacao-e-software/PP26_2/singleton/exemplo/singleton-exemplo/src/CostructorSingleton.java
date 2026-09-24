public class CostructorSingleton {

    private static volatile CostructorSingleton instance;

    private CostructorSingleton() {
        
    }
    
    public static CostructorSingleton getInstance() {
        if (instance == null) {
            // Funciona como um bloqueio de sincronização para garantir que apenas uma instância seja criada em um ambiente multithread - apenas uma thread pode acessar o bloco de código dentro do synchronized por vez.
            synchronized (CostructorSingleton.class) {
                // Dupla verificacao da instancia para garantir que apenas uma instância seja criada
                if (instance == null) { 
                    instance = new CostructorSingleton();
                }
            }
        }
        return instance;
    }

    public void showMessage() {
        System.out.println("Instancia do CostructorSingleton criada com sucesso!");
    }
}
