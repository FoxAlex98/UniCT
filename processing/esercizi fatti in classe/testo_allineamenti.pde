int i=0;
String parola="";

void setup()
{
  size(500,500);
  background(0);
}

void draw()
{
 
 textSize(25);//i caratteri saranno alti 25 pixel
 fill(255,0,0);//specifica il colore del testo
 //si può cambiare anche il font, ma non lo facciamo e non lo chiede all'esame, si deve scaricare
 textAlign(RIGHT);//cambia l'allineamento del testo rispetto al punto
 //textAlign(LEFT);
 //textAlign(CENTER);
 //textAlign(CENTER,TOP);//allineamento anche in base alla Y quindi sopra sotto e centro
 //textAlign(CENTER,BOTTOM);
 //textAlign(CENTER,CENTER);
 text("ciao",100,100);//testo, posizione
 //il colore di default è il bianco
 //text("ciao ciao ciao ciao ciao ciao ciao ciao ciao",100,100,300,200);//gli ultimi due indicano un box dentro il quale sta il testo
 strokeWeight(5);
 stroke(0,255,0);
 point(100,100);//punto in cui comincia a scrivere
}

/*
void keyPressed()
{
  text(key,100,200+i);
  i+=10;
}
*/
