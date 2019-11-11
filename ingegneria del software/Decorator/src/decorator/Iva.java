package decorator;

public class Iva extends Tariffa {

	public Iva(Prodotto prod) {
		super(prod);
	}
	
	public double getCost() {
		return super.getCost()*1.2;
	}
	
}
