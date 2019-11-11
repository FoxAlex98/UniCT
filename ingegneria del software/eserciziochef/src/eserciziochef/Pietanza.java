package eserciziochef;

public abstract class Pietanza {

	public Pietanza add(){
		return this;
	}
	
	public Pietanza remove() {
		return this;
	}
	
	public abstract void mostra(String indenta);
	
	public abstract int calcolaCalorie();
	
}
