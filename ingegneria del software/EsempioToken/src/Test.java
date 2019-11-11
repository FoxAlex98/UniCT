public class Test {

	TokenProvider tp;
	
	public static void main(String[] args) {
		Test t=new Test();
		t.testLunghezza();
		t.testSet();
	}
	
	private void testSet() {
		init();
		String token=tp.getToken();
		
		String charSet="123ABC";
		
		for(int i=0;i<token.length();i++) {
			if(! charSet.contains(token.charAt(i)+"")) {
				System.out.println("NO: test Set fallito");
				return;
			}
			else
			{
				System.out.println("OK: test Set superato");
			}
		}
			
	}

	public void init() {
		tp=new TokenProvider();
	}

	private void testLunghezza() {
		init();
		String s=tp.getToken();
		if(s.length()==5)
			System.out.println("OK: test Lunghezza riuscito");
		else
			System.out.println("NO: test Lunghezza fallito");
	}
	
	private void testDifferentNext() {
		
	}
	
	
}
