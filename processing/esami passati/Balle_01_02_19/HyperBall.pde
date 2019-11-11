class HyperBall extends Ball//estendiamo la classe figlia
{
  color c;
  
  HyperBall(int x, int y, int raggio) 
  {
    super(x,y,raggio);//richiama il costruttore della classe madre
    c=color(0,0,255);//colore di default blu
  }
  
  void disegna()
  {
    noStroke();//niente contorni
    fill(c);//riempi del colore che cambia
    ellipse(x,y,raggio*2,raggio*2);//disegnamo il cerchio
  }
  
  //non c'è il muovi perchè l'ha ereditato dalla classe madre e siccome è rimasto invariato allora non c'è bisogno di riscriverlo
  
  void controlla()//controlliamo se il puntatore del mouse sta dentro il cerchio e se ci sta allora cambia il colore dell'hyperball
  {
    //possiamo controllarlo in due modi
    //if(mouseX>x-raggio && mouseX<x+raggio && mouseY>y-raggio && mouseY<y+raggio) //o cosi
     if(dist(mouseX,mouseY,x,y)<raggio)  //o cosi, in questo modo controlliamo se la distanza dal mouse e dal centro (x,y) è minore del raggio
      c=color((random(0,255)),(random(0,255)),(random(0,255)));//cambiamo il colore dell' hyperball in uno casuale
  }
  
  void run()
  {
    disegna();
    muovi();
    controlla();
  }

}
