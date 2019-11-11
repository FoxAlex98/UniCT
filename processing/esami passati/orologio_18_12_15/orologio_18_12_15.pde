int f=1;
orologio or;

void setup()
{
  size(500,500);//grandezza predefinita
  frameRate(f);//framerate iniziale a 1
  background(#FFFFFF);//sfondo bianco
  or=new orologio(width/2,height/2,int(random(1,59)),int(random(1,59)),int(random(1,11)));
}

void draw()
{
 background(255);//puliamo sempre il tutto
 or.run();//eseguiamo l'orologio
}

void keyPressed()
{
  if(key=='+')
    frameRate(f++);//aumenta il framerate di 1
    
  if(key=='-')
    {
      if(f>1)
      frameRate(f--);//diminuisce il framerate di 1
    }
  
}
