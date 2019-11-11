
public class Libro {

	static enum Categoria {// metto statico cosi non devo creare un istanza, insomma motivi di visibilità
		FANTASY, 
		CYBERPUNK,
		STORICO,
		DISPERAZIONE,
		THRILLER;
	}

	String titolo;
	Categoria categoria;
	int prezzo;

	public Libro(String titolo, Categoria categoria, int prezzo) {
		this.titolo = titolo;
		this.categoria = categoria;
		this.prezzo = prezzo;
	}

	private static Libro[] prodPool = new Libro[] { 
			new Libro("Leviathan", Categoria.FANTASY, 20),
			new Libro("Trono di Spade", Categoria.FANTASY, 40),
			new Libro("Signore degli anelli", Categoria.FANTASY, 25),

			new Libro("Necromante", Categoria.CYBERPUNK, 15), 
			new Libro("Monnalisa Cyberpunk", Categoria.CYBERPUNK, 12),
			new Libro("Mirrorshades", Categoria.CYBERPUNK, 10),

			new Libro("Profondo Blu", Categoria.THRILLER, 0), 
			new Libro("Invasion", Categoria.THRILLER, 12),
			new Libro("La Torre Nera", Categoria.THRILLER, 10) };

	public static Libro gen() {
		int i = (int) (Math.random() * prodPool.length);// ritorna da 0 a 1, per questo bisogna moltiplicarlo
		return prodPool[i];
	}

	@Override
	public String toString() {
		return "Libro [titolo=" + titolo + ", categoria=" + categoria + ", prezzo=" + prezzo + "]";//generato automaticamente con Eclipse
	}

	//ctrl shift F indenta il codice

	
	
	public String getTitolo() {
		return titolo;
	}

	public void setTitolo(String titolo) {
		this.titolo = titolo;
	}

	public Categoria getCategoria() {
		return categoria;
	}

	public void setCategoria(Categoria categoria) {
		this.categoria = categoria;
	}

	public int getPrezzo() {
		return prezzo;
	}

	public void setPrezzo(int prezzo) {
		this.prezzo = prezzo;
	}

}
