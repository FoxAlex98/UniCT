import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

//import Libro.Categoria;

public class MainLibro {

	public static void main(String args[]) {
		query0();//stampare 10 libri
		query1();//contare tutti i libri cyberpunk
		query2();//lista dei titoli dei libri cyberpunk o fantasy
		query3();//somma dei costi di tutti i libri
		query4();//somma in dollari dei costi di tutti i libri (controlla valuta)  1 euro = 1.12 USD
		query5();//stampa tutti i libri con prezzo compreso tra 10 e 15
		query6();//titolo del libro meno caro (ma a partire da 12 euro)
		query7();//stampa la lista dei libri ordinati per prezzo
		query8();//stampare totale vendite per ogni libro venduto
		query9();//libro cyberpunk più venduto
		//query10();//Creare una lista di libri fantasy da "Harry Potter 1" a "Harry Potter 7" tutti da 15 euro
		//query11();//Sfruttando il metodo precedente, ottenere la lista di libri e mescolarla in ordine casuale
		//query12();//Data una lista di libri, stampare il primo che ha un prezzo maggiore del precedente
		//query13();//Data una lista di libri, stampare il primo che ha un prezzo minore del precedente
		//query14();//Data una lista di libri, applicare ad ogni libro uno sconto...
	}
	
	//ricordare l'importanza di equals
	//il == fa un confronto fra le istanze
	
	//libri raggruppati per categoria
	public static void querybonus() {
		System.out.println("\n# Query bonus");
		//Senza grouping by
		List<Libro> list = Stream.generate(Libro::gen)
						.limit(10)
						.collect(Collectors.toList());
		
		list.stream()
			.map(Libro::getCategoria)
			.distinct()
			.peek(c -> System.out.println("Categoria: " + c))
			.forEach(c -> list.stream()
					.filter(x-> x.getCategoria() == c)
					.map(Libro::getTitolo)
					.forEach(t -> System.out.println("- "+t)));
		
	}
	
	//stampare 10 libri
	public static void query0() {
		System.out.println("\n# Query 0");
		
		Stream.generate(Libro::gen)
			.limit(10)
			.forEach(System.out::println);
		
		
		/*//cosi possiamo stampare tutti i libri dello stream
		Stream.of(new Libro("Harry Potter", Libro.Categoria.FANTASY, 60),
					new Libro("Storia di una capinera", Libro.Categoria.STORICO, 5),
				new Libro("Design Pattern", Libro.Categoria.DISPERAZIONE, 1))
			.forEach(System.out::println);*/
	}
	
	//Contare tutti i libri CYBERPUNK
	public static void query1() {
		System.out.println("\n# Query 1");
		long cnt = Stream.generate(Libro::gen)
				.limit(10)
				.filter(x -> x.getCategoria() == Libro.Categoria.CYBERPUNK)
				.peek(System.out::println)//prende l'elemento dallo Stream, fa l'operazione tra parentesi e lo rimette nello stream (peek = sbirciare)
				.count();
		
		System.out.println(cnt);
	}
	
	
	public static void query2() {
		System.out.println("\n# Query 2");
		List<String> list = Stream.generate(Libro::gen)
				.limit(10)//lo mettiamo prima per generarne 10 indiscriminatamente
				.filter(x -> x.getCategoria() == Libro.Categoria.CYBERPUNK || x.getCategoria() == Libro.Categoria.FANTASY)
				.map(x->x.getTitolo()+":"+x.getPrezzo())
				.collect(Collectors.toList());
		//cosi non lo stampa ancora
		
		for(String x: list)
			System.out.println(x);
	}
	
	public static void query3() {
		System.out.println("\n# Query 3");
		long sum = Stream.generate(Libro::gen)
				.limit(10)
				.peek(System.out::println)
				.map(x->x.getPrezzo())
				.reduce(0, (acc,x)->acc+x);
		
		
		System.out.println(sum);
	}
	
	
	public static void query4() {
		System.out.println("\n# Query 4");
		double sum = Stream.generate(Libro::gen)
				.limit(10)
				.peek(System.out::println)
				.map(x->x.getPrezzo()*1.12)
				.reduce(0.0, Double::sum);//funziona anche con  (acc,x)->acc+x al posto di Double::sum
		
		
		System.out.println(sum);
	}
	
	
	public static void query5() {
		System.out.println("\n# Query 5");
		List<String> list = Stream.generate(Libro::gen)
				.limit(10)//lo mettiamo prima per generarne 10 indiscriminatamente
				//.filter(x -> x.getPrezzo() >= 10 && x.getPrezzo() <=15) va bene anche cosi
				.filter(x -> x.getPrezzo() >= 10)
				.filter(x -> x.getPrezzo() <=15)
				.map(x->x.getTitolo()+":"+x.getCategoria()+":"+x.getPrezzo())
				.collect(Collectors.toList());
		
		for(String x: list)
			System.out.println(x);
	}
	
	public static void query6() {
		System.out.println("\n# Query 6");
		
		//soluzione 1
		Optional<Libro> l = Stream.generate(Libro::gen)
				.limit(10)
				.filter(x->x.getPrezzo()>=12)//lasciamo tutti quei libri con prezzo >= 12
				.min(Comparator.comparing(Libro::getPrezzo));//e troviamo il minimo di loro
		
		if(l.isPresent())
			System.out.println("Libro: " + l.get());
		else
			System.out.println("Nessun libro rispetta i criteri");
				
		/*Optional<Libro> l = Stream.generate(Libro::gen)//soluzione 2
		.limit(10)
		.sorted(Comparator.comparing(Libro::getPrezzo))//ordiniamo in base al prezzo
		.filter(x -> x.getPrezzo() >= 12)//filtriamo in base al se è maggiore di 12
		.findFirst();//e ci facciamo stampare solo il primo
		*/
		
	}
	
	public static void query7() {
		System.out.println("\n# Query 7");
		List<String> lista = Stream.generate(Libro::gen)
				.limit(10)
				.sorted(Comparator.comparing(Libro::getPrezzo))//e ci facciamo stampare solo il primo
				.map(x->x.getTitolo()+":"+x.getCategoria()+":"+x.getPrezzo())
				.collect(Collectors.toList());
		
		//si può fare anche solo uno Stream usando il foreach che stampa, al posto di collect
		//e non si usa poi il for
		
		for(String x:lista)
			System.out.println(x);
	}
	
	//totale vendite per ogni libro venduto
	public static void query8() {
		System.out.println("\n# Query 8");
		/*
		long lista = Stream.generate(Libro::gen)
				.limit(10)
				.distinct()
				//.map(x->x.getTitolo()+" "+x.getPrezzo())
				
				.count();
				*/
		
		List<Libro> lista = Stream.generate(Libro::gen)
				.limit(10)
				.collect(Collectors.toList());
		
		lista.stream()
			 .map(x->x.getTitolo())//cambia lo stream con solo i titoli
			 .distinct()//tutti diversi
			 .peek(x->System.out.println("Titolo: "+ x + "Conteggio: "))
			 .forEach(x -> System.out.println(
					 	lista.stream()
					 	.filter(t -> t.getTitolo().equals(x))//la variabile lambda deve essere diversa
					 	.count()));
		
		
	}
	
	//diff tra range e rangeclosed
	//range esclude l'ultimo
	//rangeclosed non esclude l'ultimo
	
	
	//libro Cyberpunk più venduto
	public static void query9() {
		System.out.println("\n# Query 9");
		
		List<Libro> list=Stream.generate(Libro::gen)
				.limit(20)
				.filter(y -> y.getCategoria().equals(Libro.Categoria.CYBERPUNK))
				.peek(System.out::println)
				.collect(Collectors.toList());
		
		list.stream()
		 .map(x->x.getTitolo())//cambia lo stream con solo i titoli
		 .distinct()//tutti diversi
		 .peek(x->System.out.println("Titolo: "+ x + "Conteggio: "))
		 .forEach(x -> System.out.println(
				 	list.stream()
				 	.filter(t -> t.getTitolo().equals(x))//la variabile lambda deve essere diversa
				 	.count()));
		
		
		
		
		/*list.stream()
			
			.distinct()
			.peek(z -> list.stream()
					.filter(t -> t.getTitolo().equals(z))
					.count())
			.max(Comparator.naturalOrder());
			*/
	}
	
	
	
	public static List<Libro> query10() {
		System.out.println("\n# Query 10");
		
		List<Libro> hp = IntStream.rangeClosed(1,7)
				.mapToObj(i -> new Libro("Harry Potter "+i, Libro.Categoria.FANTASY, 15))
				.collect(Collectors.toList());
		
		hp.forEach(System.out::println);

		return hp;
	}
	
	public static void query11() {
		System.out.println("\n# Query 11");
		
		List<Libro> hp = query10();
		
		Stream.generate(Math::random)
			  .map(d -> (int) (d*hp.size()))
			  .distinct()
			  .limit(hp.size())
			  .map(c -> hp.get(c))
			  .forEach(System.out::println);
	}
	

	public static void query12() {
		System.out.println("\n# Query 12");
		
		List<Libro> list=Stream.generate(Libro::gen)
			  .limit(10)
			  .peek(System.out::println)
			  .collect(Collectors.toList());
		
		System.out.println();

		IntStream.range(1, list.size())
				 .filter(i -> list.get(i).getPrezzo()<=list.get(i+1).getPrezzo())
				 .mapToObj(i -> list.get(i))
				 .peek(System.out::println)
				 .findAny();
	}
	
}
