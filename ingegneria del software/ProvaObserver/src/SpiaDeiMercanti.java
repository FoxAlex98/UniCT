//ConcreteObserver

import java.util.ArrayList;
import java.util.List;

public class SpiaDeiMercanti  implements Spia{
Taverna t;
TipoEroe tipo;
List<Eroe> le=new ArrayList<>();

public SpiaDeiMercanti(Taverna t) {
	this.t=t;
}

@Override
public void nuovoEroe() {
	if(t.getEroi().size()==10)
	{
		System.out.println("Spia dei mercanti, scelgo te");
	}
}

@Override
public void elenca() {
	for(Eroe var: t.getEroi()) {
		System.out.println(var);
	}
}
	
}