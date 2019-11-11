public class TokenProvider {

	final int SIZE=5;
	final String charSet = "123ABC";
	
	public String getToken() {
		String token = "";
		for(int i=0;i<SIZE;i++)
			token+=charSet.charAt(i % SIZE);//se SIZE è più lungo della lunghezza di charSet
		return token;
	}

}
