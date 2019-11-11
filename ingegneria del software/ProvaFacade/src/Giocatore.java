public class Giocatore {
	private String id;
	private String[] equip = new String[] {"tirapolli","pistola"};
	
	public Giocatore(String id) {
		this.setId(id);
	}

	public String[] getEquip() {
		return equip;
	}

	public void setEquip(String[] equip) {
		this.equip = equip;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}





}
