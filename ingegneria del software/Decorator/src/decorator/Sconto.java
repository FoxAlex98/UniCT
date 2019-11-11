package decorator;

//ConcreteDecorator
public class Sconto extends Tariffa {

	public Sconto(Prodotto prod) {
		super(prod);
	}

	public void printName() {
		System.out.println("Biglietto scontato");
	}
	
	public double getCost() {
		return super.getCost()*0.95;
	}
}
