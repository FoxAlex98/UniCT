class tagliaerba{
int vel;
int rot=0;
int posX,posY;
  
  
  tagliaerba(int vel)
  {
   this.vel=vel;
  }
  
  void taglia()
  {
    //qui non aumentiamo la velocità del tagliaerba
    pushMatrix();//per ruotare solo la parte interessata
    translate(posX,posY);//trasliamo in posX,posY che saranno i precedenti punti dove si trovava il mouse
    rotate(radians(rot));//ruotiamo anche qua per prendere la posizione del tagliaerba
    fill(200,128,0);//striscia marrone
    noStroke();//togliamo i bordi altrimenti l'effetto è brutto
    rectMode(CENTER);//è in modalità centro perchè il puntatore deve stare al centro
    rect(0,0,31,31);//stesso rettangolo ma un pochino più grande per coprire tutto
    popMatrix();
  }

  void disegna()
  {
    rot+=vel;//la rotazione aumenta sempre
    pushMatrix();//per ruotare solo la parte interessata
    translate(posX,posY);//trasliamo in posX,posY che sta volta saranno aggiornati con gli ultimi valori del mouse
    rotate(radians(rot));//ruotiamo ovviamente
    fill(125,125,125);//tagliaerba grigio
    rectMode(CENTER);
    rect(0,0,30,30);//tagliaerba
    
    fill(0,0,0);//punto nero
    ellipseMode(CENTER);
    ellipse(0,0,10,10);//punto nero al centro
    popMatrix();
  }
  
  void aumentavel()//aumentiamo la velocità con limite massimo di 15
  {
    if(vel<15)
      vel++;
  }
  
  void diminuiscivel()//diminuiamo la velocità con limite minimo di 3
  {
    if(vel>3)
      vel--;
  }
  
  void run()
  {
   taglia();//prima tagliamo
   posX=mouseX;//poi aggiorniamo i valori delle posizioni del mouse
   posY=mouseY;//cosi taglia è aggiornato con le posizioni precedenti
   disegna();//in questo modo solo disegna sarà aggiornato "in tempo reale"
  }
}
