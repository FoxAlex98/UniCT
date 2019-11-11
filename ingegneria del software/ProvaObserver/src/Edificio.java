//Subject

import java.util.*;

public class Edificio {

private List<Spia> ls=new ArrayList<>();

//Attach
public void inviaSpia(Spia s) {
	if(!ls.contains(s))
		ls.add(s);
}
	
//Detach
public void ritiraSpia(Spia s) {
	if(ls.contains(s))
		ls.remove(s);	
}

//notify
public void avvertiSpie() {
	for(Spia var: ls) {
		var.nuovoEroe();
	}
}
	
}
