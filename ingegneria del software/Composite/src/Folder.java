import java.util.ArrayList;
import java.util.List;

//composite
public class Folder extends Resource {

	private String name;
	private List<Resource> cList;
	
	public Folder(String name) {
		this.name=name;
		cList=new ArrayList<>();
	}
	
	@Override
	public void add(Resource c) {
		cList.add(c);
	}
	
	@Override
	public void remove(Resource c) {
		cList.remove(c);
	}
	
	@Override
	public void show() {
		System.out.println("io sono il folder: "+name);
		cList.forEach(x -> x.show());
	}

}
