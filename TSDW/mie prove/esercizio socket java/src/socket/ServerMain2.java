package socket;


import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerMain2 {

	public static void main(String[] args) throws IOException {
		ServerSocket server = null;
		Socket connectsock = null;
		try {
			server = new ServerSocket(6666);
			//cosi ho già fatto la socket del server, bind e listen
		}catch(IOException e) {
			e.printStackTrace();
			System.out.println("errore I/O");
		}
		
		while(true) {
			connectsock = server.accept();//il server ora parla con il client appena l'accetta
			new CommunicationThread2(connectsock).start();
		}
		
	}

}
