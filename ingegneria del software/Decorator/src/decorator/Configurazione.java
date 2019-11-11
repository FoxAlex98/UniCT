package decorator;

//metodo factory
public class Configurazione {

	public static Prodotto getBiglietto() {
		return new Iva(new Biglietto());
	}
	
	public static Prodotto getBigliettoScontato() {
		return new Iva(new Sconto(new Biglietto()));
	}

	public static Prodotto getBigliettoScontatissimo() {
		return new Iva(new Sconto(new Sconto(new Biglietto())));
	}

}