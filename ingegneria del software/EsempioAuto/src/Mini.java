
public class Mini extends Berlina {
	Motore m;
	
	public Mini(Motore x) {
		super(x);
	}

	@Override
	public String getTitolo() {
		return "Mini";
	}

	@Override
	public int getPeso() {
		return 600;	
	}
	
	@Override
	public String toString(int t) {
		return getTitolo() + " = " + getDistance(t);
	}


}

