package esempioEsame;

public class Main {

	public static void main(String[] args) {
		Arma spada = new Arma("spada", 100);
		Arma arco = new Arma("arco", 20);
		Personaggio conan = new Personaggio("Conan", 100);
		
		System.out.println(conan);
		System.out.println(spada);
		System.out.println(arco);

	}

}
