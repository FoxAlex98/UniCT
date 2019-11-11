// GnrPosizioni e' un Creator
import java.util.TreeSet;
public abstract class GnrPosizioni { // versione 1.1
	private final int maxPosti = 100;
	private TreeSet< String > pst = new TreeSet< >(); // lista ordinata di posti

  	// metodo che rimanda alla sottoclasse l'istanziazione della classe
	public Posto prendiNumero(int x) {
		if (pst.size() == maxPosti) return null;
		// il chiamante dovrebbe controllare se null
		Posto p;
		do {  				  // fino a quando non trova un posto libero
			p = getPosto(x); // chiama metodo della sottoclasse
		} while (pst.contains(p.getPosizione()));
		pst.add(p.getPosizione());
		return p; 
	}

	public void printPostiOccupati() {
		for (String s : pst)
			System.out.print(s + " ");
	}

	// il metodo factory e' dichiarato ma non implementato
	public abstract Posto getPosto(int tipo);
}