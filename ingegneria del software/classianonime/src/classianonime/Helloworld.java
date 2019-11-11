package classianonime;

public class Helloworld {
	private final String hello="Hello World!";
	
	//normale
	public void printHelloWord(PrintMode pm) {
		pm.print(hello);
		System.out.println(pm.count(hello));
	}

	//viene usato dalle funzioni lambda
	//faccio un overriding
	public void printHelloWord(PrintMode2 pm) {
		pm.print(hello);
	}
}
