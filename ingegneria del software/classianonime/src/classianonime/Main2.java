package classianonime;

public class Main2 {

	public static void main(String[] args) {
		Helloworld hw=new Helloworld();
		
		//implemento mentre chiamo
		
		//UpperCase
		hw.printHelloWord(new PrintMode() {
			@Override
			public void print(String message) {
				System.out.println(message.toLowerCase());
			}
			
			@Override
			public int count(String message) {
				return message.length();
			}
		});
		
		//LowerCase
		hw.printHelloWord(new PrintMode() {	
			
			@Override
			public void print(String message) {
				System.out.println(message.toUpperCase());
			}
			
			@Override
			public int count(String message) {
				return message.length()*2;
			}
		});
	
	}

}

//main con classi anonime
//utili quando bisogna implementare tante classi da un'interfaccia