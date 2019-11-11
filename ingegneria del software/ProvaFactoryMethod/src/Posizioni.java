// Posizioni e' un ConcreteCreator con un metodo factory
public class Posizioni extends GnrPosizioni {
	// metodo factory che ritorna una istanza
	public Posto getPosto(int tipo) {
		// crea l'istanza di un ConcreteProduct 
		if (tipo == 1) return new Palco();
		return new Platea();
	}
}