package socket;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Date;

public class CommunicationThread2 extends Thread {
	Socket sock;//connect_sock
	BufferedReader input;//per leggere su stream
	PrintWriter output;//per scrivere su stream
	
	public CommunicationThread2(Socket sock) throws IOException {
		this.sock = sock;
		input = new BufferedReader(new InputStreamReader(sock.getInputStream()));//abbiamo lo stream di input per leggere
		output = new PrintWriter(sock.getOutputStream(),true);
	}
	
	@Override
	public void run() {
		String message;
		
		while(true) {
			
		try {
			
				message = input.readLine();
				
				if(message.equals("TIME")) {
					System.out.println("il tempo");
					output.println(new Date().toString());
				}
				else {
					output.println("N/A");
				}
				
			}
			catch(IOException e) {
			System.out.println("MAMMAMIA MARCELLO, that's no way to use this software");
		}
		
		}
		
	}
}
