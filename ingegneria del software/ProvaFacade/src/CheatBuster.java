
public class CheatBuster {

	public boolean check(Giocatore g) {
		for(String equip : g.getEquip()) {
			if(equip.equals("spara-coccodrilli"));
				return false;
		}
		return true;
	}
	
}
