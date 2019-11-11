package decorator;

//ConcreteComponent
public class Biglietto implements Prodotto {

	@Override
	public void printName() {
		System.out.println("Biglietto n. 123123");
	}

	@Override
	public double getCost() {
		return 100.0;
	}
	
}
