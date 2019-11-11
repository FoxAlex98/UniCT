
public class Berlina implements Auto {
	private Motore m;
	
	public Berlina(Motore x) {
		m = x;
	}

	@Override
	public String getTitolo() {
		return "Berlina";
	}

	@Override
	public int getPeso() {
		return 800;
	}

	@Override
	public float getDistance(int t) {
		return (float) t * t * m.getPotenza()/getPeso();
	}
	
	@Override
	public String toString(int t) {
		return getTitolo() + " = " + getDistance(t);
	}

}
