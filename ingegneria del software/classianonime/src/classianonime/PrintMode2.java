package classianonime;

//questa � un'altra interfaccia che differisce da PrintMode perch� � una functional interface
//viene usata solo dal Main3

@FunctionalInterface
public interface PrintMode2 {
	public void print(String message);
}
