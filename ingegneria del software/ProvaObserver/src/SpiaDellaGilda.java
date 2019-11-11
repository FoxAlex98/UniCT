//ConcreteObserver

import java.util.ArrayList;
import java.util.List;

public class SpiaDellaGilda  implements Spia{
Taverna t;
TipoEroe tipo;
List<Eroe> le=new ArrayList<>();

public SpiaDellaGilda(Taverna t, TipoEroe tipo) {
	this.t=t;
	this.tipo=tipo;
}

@Override
public void nuovoEroe() {
	if(t.getEroe().getTipo()==tipo)
	le.add(t.getEroe());
}

@Override
public void elenca() {
	for(Eroe var: le) {
		System.out.println(var);
	}
}
	
}
