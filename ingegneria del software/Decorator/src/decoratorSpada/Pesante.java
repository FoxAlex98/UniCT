package decoratorSpada;

public class Pesante extends Incantesimo {

	public Pesante(Spada s) {
		super(s);
	}
	
	public String getNome() {
		return super.getNome() + "Pesante";
	}

}
