// Platea e' un ConcreteProduct
public class Platea implements Posto {
	private String[] nomi = { "A", "B", "C", "D", "E", "F" };
	private int numero;
	private int riga;

	public Platea() {
		numero = (int) (Math.random() * 10);
		riga = (int) (Math.random() * 5);
	}

	@Override
	public int getCosto() {
		if (numero > 5 && rigaMax()) return 100;
		if (numero > 5 && rigaMin()) return 80;
		return 60;
	}

	@Override
	public String getPosizione() {
		return nomi[riga].concat(Integer.toString(numero));
	}

	@Override
	public String getSettore() {
		if (riga == 0) return "Riservato";
		return "Normale";
	}

	private boolean rigaMax() {
		if (riga >= 1 && riga <= 4) return true;
		return false;
	}

	private boolean rigaMin() {
		if (riga == 0 || riga == 5) return true;
		return false;
	}
}