package classianonime;

//diciamo al compilatore che � una functional interface
//quindi dovrebbe avere un solo metodo
//@FunctionalInterface
public interface PrintMode {
	public void print(String message);
	public int count(String message);
}
