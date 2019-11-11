package senzaThread;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class MiniChat {

	public static void main(String[] args) throws IOException {
		ServerSocket server = null;
		Socket connectionSocket = null;
		BufferedReader input = null;
		PrintWriter output = null;
		String string;
		try {
			server = new ServerSocket(9999);
		}catch(IOException e) {
			System.out.println("server");
		}
		
		System.out.println("Server in ascolto");
		
		while(true) {
			try {
				connectionSocket = server.accept();
				input = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
				output = new PrintWriter(connectionSocket.getOutputStream(), true);
				output.println("Server connesso e pronto a ricevere");
			}catch(IOException e) {
				System.out.println("connection_socket");
			}
			while(true) {
				string = input.readLine();
				if(string.equals("chiudi"))
					break;
				output.println("MAMMAMIA MARCELLO " + string);
				System.out.println("stringa ricevuta " + string);
			}
			output.println("chiusura richiesta dal client");
		}
	}

}
