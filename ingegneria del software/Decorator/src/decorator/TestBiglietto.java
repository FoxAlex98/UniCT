package decorator;

//client
public class TestBiglietto {

	public static void main(String[] args) {
		Prodotto prod;
		prod = Configurazione.getBigliettoScontato();
		prod.printName();
		System.out.println(" Costo: " + prod.getCost());
		prod = Configurazione.getBiglietto();
		prod.printName();
		System.out.println(" Costo: " + prod.getCost());
		prod = Configurazione.getBigliettoScontatissimo();
		prod.printName();
		System.out.println(" Costo: " + prod.getCost());
	}

}
