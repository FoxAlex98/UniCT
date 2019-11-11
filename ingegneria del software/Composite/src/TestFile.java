
public class TestFile {

	public static void main(String[] args) {
		Folder f=Creator.getFolder("Otto");
		Image i=Creator.getImage("LENA", 256, 256);
		
		f.add(i);
		
		i.show();
		
		f.show();
	}

}
