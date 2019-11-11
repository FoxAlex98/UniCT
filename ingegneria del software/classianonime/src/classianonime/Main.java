package classianonime;

class PrintUpperCase implements PrintMode{

	@Override
	public void print(String message) {
		System.out.println(message.toUpperCase());
	}

	@Override
	public int count(String message) {
		return message.length();
	}
	
	
}

class PrintLowerCase implements PrintMode{

	@Override
	public void print(String message) {
		System.out.println(message.toLowerCase());
		
	}

	@Override
	public int count(String message) {
		return message.length()*2;
	}
	
}

public class Main {

	public static void main(String[] args) {
		Helloworld hw=new Helloworld();
		hw.printHelloWord(new PrintUpperCase());
		hw.printHelloWord(new PrintLowerCase());
	}

}

//main senza classi anonime
