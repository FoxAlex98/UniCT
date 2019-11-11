package classianonime;

public class Main3 {
//per le funzioni lambda abbiamo bisogno di una functional interface
	public static void main(String[] args) {
		Helloworld hw=new Helloworld();
		hw.printHelloWord(s -> System.out.println(s.toUpperCase()));
		hw.printHelloWord(s -> System.out.println(s.toLowerCase()));
	}
}

//main con lambda expression
//tutti e tre i main sono equivalenti (ad eccezzione del count)