
public class Garage {
	
	public static int v=0;
	
	public static Auto getBerlina(int dollarazzi) {
		return new Berlina(seHaISordi(dollarazzi));
	}
	
	public static Auto getMini(int dollarazzi) {
		return new Mini(seHaISordi(dollarazzi));
	}
	
	public static Auto getAuto(int dollarazzi) {
		if(v==0) {
			v++;
			return getBerlina(dollarazzi);
		}
		else {
			v--;
			return getMini(dollarazzi);
		}
		
	}
	
	public static Motore seHaISordi(int dollarazzi) {
		if(dollarazzi > 10000) return new Fire();
		else return new CommonRail();
	}
	
	/*altro modo che posso usare al posto di v
	public static int numrandom(int n) {
		return (int)(Math.random()*n);
	}

	public static Auto getAuto(int dollarazzi) {
		if(numrandom(10)%2==0) return getBerlina(dollarazzi);
		return getMini(dollarazzi);
	}*/
}
