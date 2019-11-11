int s,m,o;

class orologio{

  int posX;//width/2
  int posY;//heigth/2
  
  orologio(int posX, int posY, int secondi, int minuti, int ore)
  {
    this.posX=posX;//qui possiamo usare il this perchè sono posX e posY sono dentro la classe
    this.posY=posY;
    s=secondi;//qui non possimo usare il this perchè s,m,o sono globali
    m=minuti;
    o=ore;
  }
  
  void sposta()
  {
   s++;//i secondi aumentano sempre
   if(s>=60)//se superiamo i 60
     {
           s=0;//resettiamo i secondi
           m++;//aumentiamo i minuti
             if(m>=60)//controlliamo a cascata i minuti e se superano i 60
             {
              m=0;//si azzerano i minuti
              o++;//aumentiamo le ore
                  if(o>=12)//controlliamo a cascata le ore e se superiamo le 12
                    {
                      o=0;//resettiamo le ore
                    }
             }
     }
  }
     
  void run()
  {
   sposta();//prima spostiamo 
   disegna();//poi disegnamo il cambiamento
  }   
  
  void disegna()
  {
    float Rs=radians(6*s);//angolo di rotazione moltiplicato per un determinato fattore
    float Rm=radians(6*m);//secondi e minuti ruotano con lo stesso angolo
    float Ro=radians(30*o);//le ore ruotano con un angolo più ampio
  
     stroke(0,255,0);//contorno verde dell'orologio
     strokeWeight(15);//spessore del contorno
     ellipse(posX,posY,120,120);//orologio vero e proprio
     
     pushMatrix();//ogni volta usiamo i push e il pop per cambiare solo i diretti interessati
     translate(posX,posY);//trasliamo (come di consueto prima di ruotare, per ruotare solo la lancetta e non il piano) al centro
     rotate(Rs);//ruotiamo
     stroke(0,0,0);//lancetta nera dei secondi
     strokeWeight(1);//spessore 1
     line(0,0,0,-50);//di lunghezza 50
     popMatrix();//fine spostamento dei secondi
     
     pushMatrix();
     translate(posX,posY);
     rotate(Rm);
     stroke(255,0,0);//lancetta rossa dei minuti
     strokeWeight(2);//spessore 2
     line(0,0,0,-40);//lunghezza 40
     popMatrix();//fine spostamento dei minuti
     
     pushMatrix();
     translate(posX,posY);
     rotate(Ro);
     stroke(0,0,255);//lancetta blu delle ore
     strokeWeight(3);//spessore 3
     line(0,0,0,-30);//lunghezza 30
     popMatrix();//fine spostamento delle ore
  }
  
  
  }
