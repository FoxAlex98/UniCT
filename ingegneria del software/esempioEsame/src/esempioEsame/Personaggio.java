package esempioEsame;

public class Personaggio {
	private int hp;
	
	private int forza;
	private int destrezza;
	private int intelligenza;
	
	private String nome;
	private Arma arma;
	
	public Personaggio(String nome, int hp) {
		this.nome = nome;
		this.hp = hp;
	}
	
	public void setStats(int forza, int destrezza, int intelligenza) {
		this.forza = forza;
		this.destrezza = destrezza;
		this.intelligenza = intelligenza;
	}
	
	void assegnaArma(Arma arma) {
		this.arma = arma;
	}
	
	@Override
	public String toString() {
		String stat = getStats();
		return "Nome: "+nome+"\n"
				+"HP: "+hp+"\n"
				+"STAT: \n"+stat+"\n"
				+"ARMA: "+arma+"\n";
	}

	private String getStats() {
		String stat = "FOR: "+forza+"\n"
					 +"DES: "+destrezza+"\n"
					 +"INT: "+intelligenza+"\n";
		return stat;
	}
}