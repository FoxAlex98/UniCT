public class Server {

	private int capienza=10;
	private int capienzaMax=9;
	private String modalita;

	
	public String getMod() {
		return modalita;
	}
	
	public boolean isFull() {
		return capienza>=capienzaMax;
	}
	
	@Override
	public String toString() {
		return capienza+"/"+capienzaMax+" \tmodalità "+modalita;
	}
	
	
	
}
