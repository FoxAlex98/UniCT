
public class Client {

	public static void main(String[] args) {

		Taverna t=new Taverna();
		SpiaDellaGilda s=new SpiaDellaGilda(t,TipoEroe.GUERRIERO);
		t.inviaSpia(s);
		SpiaDellaGilda s2=new SpiaDellaGilda(t,TipoEroe.ASSASSINO);
		t.inviaSpia(s2);
		SpiaDeiMercanti sm=new SpiaDeiMercanti(t);
		t.inviaSpia(sm);
		t.entra(new Eroe("Frodo",TipoEroe.GUERRIERO));
		t.entra(new Eroe("Garrus",TipoEroe.GUERRIERO));
		t.entra(new Eroe("EZIO",TipoEroe.ASSASSINO));
		t.entra(new Eroe("HARRY",TipoEroe.MAGO));
		t.entra(new Eroe("Gandalf",TipoEroe.MAGO));
		t.entra(new Eroe("Silente",TipoEroe.MAGO));
		t.entra(new Eroe("Lupin",TipoEroe.LADRO));
		t.entra(new Eroe("ARNO",TipoEroe.ASSASSINO));
		t.entra(new Eroe("MAG",TipoEroe.GUERRIERO));
		t.entra(new Eroe("RHINO",TipoEroe.GUERRIERO));
		s.elenca();
		s2.elenca();
		sm.elenca();
	}

}
