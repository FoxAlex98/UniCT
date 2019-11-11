void setup()
{
  size(500,500);
}

void draw()
{
 background(255);
 
 
 //rect(width/2-50, height/2-50,100,100);//per averlo al centro togliere la metà della sua dimensione
 
 stroke(0,255,0);
 strokeWeight(4);
 //rectMode(CORNER);//modalità di partenza
 //rectMode(CENTER);//rect mode cambia il modo in cui disegnare il rettangolo
 //rect(width/2, height/2,50,50);//adesso lo disegna dal centro
 //rectMode(CORNERS);//modo per disegnare un rettangolo usando i vertici opposti
 //rect(width/2, height/2,mouseX, mouseY);
 
 //point(width/2, height/2);
 fill(255,0,0);
 noStroke();
 //ellipse(width/2, height/2,100,100);//ellisse cotruito con l'indicazione degli assi
 //ellipseMode(RADIUS);//cambia il modo facendo in modo di usare il raggio
 //ellipse(width/2, height/2,100,100);
 //ellipseMode(CENTER);//modalità di default
 //ellipseMode(CORNER);//modo per usare un rettangolo e inscriverci dentro un ellisse
 //ellipseMode(CORNERS);//modo per usare un rettangolo e inscriverci dentro un ellisse
}
