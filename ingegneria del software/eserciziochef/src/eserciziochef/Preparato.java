package eserciziochef;

import java.util.ArrayList;
import java.util.List;

public class Preparato extends Pietanza {

	String nome;
	List<Pietanza> lp;
	
	public Preparato(String nome) {
		this.nome=nome;
		lp=new ArrayList<>();
	}
	
	
	public void add(Pietanza p) {//usare il metodo per cui non ne inserisca altri uguali
		lp.add(p);
	}
	
	public void remove(Pietanza p) {
		lp.remove(p);
	}
	
	@Override
	public int calcolaCalorie() {
		int cont=0;
		for(Pietanza p: lp)
			cont+=p.calcolaCalorie();
		return cont;
	}

	@Override
	public void mostra(String indenta) {
		System.out.println("	"+nome);
		for(Pietanza p: lp)
		{
		 System.out.print("- ");
		 p.calcolaCalorie();
		}
		System.out.println("Calorie Totali " + calcolaCalorie());
	}

}
