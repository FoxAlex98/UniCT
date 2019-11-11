class BlackHole
{
  int posX,posY;//posizione
  int D;//dimensione
  
  BlackHole(int posX, int posY , int D)//inizializzazione
  {
    this.posX=posX;
    this.posY=posY;
    this.D=D;
  }
  
  void disegna()
  {
    fill(0);//una palla nera
    ellipse(posX,posY,D,D);
  }
  
  void muovi()//continuiamo a seguire il mouse
  {
    posX=mouseX;
    posY=mouseY;
  }
  
  void attrai(ArrayList<Asteroid> arr)
  {
    for(int i=0; i<arr.size() ;i++)//controlliamo tutto l'array di asteroidi
    {
      float dis=dist(posX,posY,arr.get(i).posX,arr.get(i).posY);//controlliamo la distanza tra il buco nero e l'asteroide
      if(dis<=D/2)//distanza abbastanza vicina da dare l'effetto di assorbimento
      {
        arr.remove(i);//rimuoviamo l'asteroide
        D++;// e aumentiamo la dimensione del buco nero
      }
    }
  }
  
  void run(ArrayList<Asteroid> arr)
  {
    attrai(arr);
    muovi();
    disegna();
  }
  

}
