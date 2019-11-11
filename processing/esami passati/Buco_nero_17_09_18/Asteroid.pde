class Asteroid
{
  float posX, posY;//posizione
  float H;//dimensione
  
  Asteroid(float posX, float posY, float H)//inizializzazione
  {
    this.posX=posX;
    this.posY=posY;
    this.H=H;
  }
  
  void disegna()//disegnamo l'asteroide
  {
    fill(120,90,50);//marrone
    noStroke();//senza contorni
    ellipse(posX,posY,H,H);
  }
  
  void attira(BlackHole B)
  {
    float s=dist(posX,posY,B.posX,posY);//usiamo la distanza tra il buco nero e l'asteroide nelle prossime due righe
    float xs=(posX-B.posX)/s;//(x1-x2)/s
    float ys=(posY-B.posY)/s;//(y1-y2)/s    in pratica è un vettore di direzione
    posX-=xs*3;//sottraiamolo alla posizione moltiplicandolo prima per la velocità
    posY-=ys*3;
  }
  
  void run(BlackHole B)//esecuzione
  {
    attira(B);
    disegna();
  }
}
