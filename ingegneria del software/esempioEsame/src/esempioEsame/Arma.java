package esempioEsame;

public class Arma {
	
	String nome;
	int danno;
	public Arma(String nome, int danno) {
		this.nome = nome;
		this.danno = danno;
	}
	
	// Di default il metodo toString() stampa il tipo dell'oggetto ed un hash che identifica l'oggetto,
	// con l'ovverride ridefiniamo il comportamento di default e stampiamo altro
	
	@Override
	public String toString() {
		return "Nome Arma: "+nome+" Danno: "+danno;
	}
	
	
	
	
}
