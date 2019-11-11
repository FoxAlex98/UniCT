
enum TipoEroe{GUERRIERO,MAGO,LADRO,ASSASSINO,SUPPORT}

public class Eroe {

	private String nome;
	private TipoEroe tipo;
	
	public Eroe(String nome, TipoEroe tipo)
	{
		this.nome=nome;
		this.tipo=tipo;
	}
	
	public String getNome() {
		return nome;
	}
	
	public TipoEroe getTipo() {
		return tipo;
	}
	
	@Override
	public String toString() {
		return "Nome "+nome+" Appartenenza: "+tipo;
	}
}
