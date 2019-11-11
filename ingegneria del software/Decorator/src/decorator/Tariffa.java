package decorator;

//Decorator
public class Tariffa implements Prodotto {

	private Prodotto prod;

	public Tariffa(Prodotto prod) {
		this.prod=prod;
	}

	@Override
	public void printName() {
		prod.printName();
	}

	@Override
	public double getCost() {
		return prod.getCost();		
	}

}
