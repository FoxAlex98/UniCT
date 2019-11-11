//leaf
public class Image extends Resource{

	private String id;
	private int x,y;
	
	public Image(String id, int x, int y) {
		this.id=id;
		this.x=x;
		this.y=y;
	}
	
	@Override
	public void show() {
		System.out.println("sono l'image "+id + " e ho dimensioni x: "+x+" y: "+y);
	}

}
