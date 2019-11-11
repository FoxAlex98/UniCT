
public class Creator {

	public static Folder getFolder(String name) {
		return new Folder(name);
	}
	
	public static Image getImage(String id, int x, int y) {
		return new Image(id,x,y);
	}
}
