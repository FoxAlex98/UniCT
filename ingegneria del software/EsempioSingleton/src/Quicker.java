
public class Quicker {
	private String[] s={"pippo","pluto","topolino","paperino","minnie"};
    private int x;
    private static Quicker t=new Quicker();
    private Quicker(){
    	x=0;
    }
    
    public static Quicker getInstance() {
    	return t;
    }

    public String getNextValue()
    {
        if(x>s.length-1) x=0;
        return s[x++];
    }
}
