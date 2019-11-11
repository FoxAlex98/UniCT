//ConcreteSubject

import java.util.ArrayList;
import java.util.List;

public class Taverna extends Edificio{

	List<Eroe> le=new ArrayList<>();
	
	Eroe last;
	
	public void entra(Eroe e) {
		le.add(e);
		last=e;
		avvertiSpie();
	}
	
	public Eroe getEroe() {
		return last;
	}
	
	public List<Eroe> getEroi(){
		return le;
	}
	
}
