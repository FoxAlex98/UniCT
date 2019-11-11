class Ball{

  int sy=5;//velocità
  int x,y;//posizione di x e y
  int raggio;//raggio
  
  
  Ball(int x,int y,int raggio)
  {
   this.x=x;
   this.y=y;
   this.raggio=raggio;
  }
  
  
  void disegna()
  {
    background(255);//sfondo bianco
    noStroke();//palla senza bordi
    fill(255,0,0);//colorata di rosso
    ellipse(x,y,raggio*2,raggio*2);//visto che abbiamo il raggio allora moltiplichiamo per due per avere il diametro
  }
  
  void muovi()
  {
    y+=sy;//avanziamo sempre
       if(y>height)//separiamo il controllo di un lato da un altro
       {//se superiamo il lato in basso
         sy=-sy;//cambiamo il verso
         y=height;//e riportiamo la y ad un valore all'interno della finestra
       }
       
       if(y<0)//se superiamo il lato in alto
       {
         sy=-sy;//cambiamo il verso
         y=0;//e riportiamo la y ad un valore all'interno della finestra
       }
  }
  
  void run()
  {
    disegna();
    muovi();   
  }
  
  
}
