
public class Client {

	public static void main(String[] args) {
		Giocatore g=new Giocatore("FoxAlex");
		
		Partita p=new Partita();
		p.partecipa(g, "king-of-the-hill");
	}

}
