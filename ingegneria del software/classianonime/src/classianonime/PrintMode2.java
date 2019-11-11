package classianonime;

//questa è un'altra interfaccia che differisce da PrintMode perchè è una functional interface
//viene usata solo dal Main3

@FunctionalInterface
public interface PrintMode2 {
	public void print(String message);
}
