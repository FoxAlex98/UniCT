package eserciziochef;

public class Ingrediente extends Pietanza {

	private String nome;
	private int calorie;
	private int quantita;

	public Ingrediente(String nome, int calorie, int quantita) {
		this.nome=nome;
		this.calorie=calorie;
		this.quantita=quantita;		
	}
	
	@Override
	public int calcolaCalorie() {
		return calorie * quantita /100;
	}

	@Override
	public void mostra(String indenta) {
		System.out.format(indenta + "- %dg %s (%d kcal per 100g)\n",quantita,nome,calorie);
	}

}
