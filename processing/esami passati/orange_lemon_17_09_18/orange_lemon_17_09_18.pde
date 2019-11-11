//la seguente è una mia variante della prima parte dell'esame del 17/09/18

PImage im,im2,punt,bordo;
int N=101;//grandezza di default
int scelta;//serve per scegliere tra orange e lemon

void setup()
{
  size(512,512);//di default
  im=loadImage("lena.png");
  im.resize(512,512);
  image(im,0,0);
}

void draw()
{
  stroke(0);//bordo nero del blocco in alto a sinistra
  strokeWeight(5);//bordo del blocco
  bordo=im.get(0,0,N+6,N+6);//blocco in alto a sinistra grande poco più del riquadro con relativo bordo, in modo da riincollarlo se diminuiamo N senza lasciare il bordo nero
  image(bordo,0,0);//e lo stampiamo sempre per primo, cosi verrà coperto dal resto sopra
  rect(1, 1, N, N);//bordo del quadrato in alto a sinistra
  punt=puntatore(im,mouseX,mouseY,N);//richiama la funzione puntatore
  image(punt,0,0);//e lo stampa in alto a sinistra
}



PImage puntatore(PImage I,int x, int y, int d)//funzione che restituisce il blocco che sta attualmente scorrendo sotto il mouse
{
  PImage R=I.copy();
  int off=d/2;
  R=R.get(x-off,y-off,d,d);
  return R;
}

PImage lemonFilter(PImage I)//filtro "al limone"
{
  PImage R=I.copy();
  R.loadPixels();
  float r,g,b;
  for(int i=0;i<R.pixels.length;i++)
  {
    r=red(R.pixels[i]);
    g=green(R.pixels[i]);
    b=blue(R.pixels[i]);
    R.pixels[i]=color(r-(b/8),g+b,0);//cambiamo i colori in questo modo
  }
  R.updatePixels();
  return R;
}

PImage orangeFilter(PImage I)//filtro "all'arancia"
{
  PImage R=I.copy();
  R.loadPixels();
  float r,g,b;
  for(int i=0;i<R.pixels.length;i++)
  {
    r=red(R.pixels[i]);
    g=green(R.pixels[i]);
    b=blue(R.pixels[i]);
    R.pixels[i]=color(r+b,g,0);//cambiamo i colori in questo modo
  }
  R.updatePixels();
  return R;
}

PImage applyArea(PImage I,int x, int y, int d, int f)//applica il filtro al limone o all'arancia in base al valore di f in una parte dell'immagine
{
  PImage R=I.copy();
  int off=d/2;
  R=R.get(x-off,y-off,d,d);
  if(f%2==1)//se f è dispari
    return lemonFilter(R);//applica limone
  else
    return orangeFilter(R);//applica arancia
}

void mousePressed()//qui in base al bottone premuto del mouse si chiama la funzione applyArea con scelta che condizionerà quale filtro usare
{
  if(mouseButton==LEFT)//bottone destro del mouse
  {
    scelta=0;//scelta è pari quindi si sceglie limone
  }
  if(mouseButton==RIGHT)//bottone sinistro del mouse
  {
    scelta=1;//scelta è dispari quindi si sceglie arancia
  }
  im2=applyArea(im,mouseX,mouseY,N,scelta);//applichiamo il filtro alla sottoimmagine
  image(im2,mouseX-N/2, mouseY-N/2);//e stampiamola li dove stava con le relative attenzioni all'offset dentro la funzione
}

void keyPressed()
{
  if(key=='r' || key=='R')//con la r o R si resetta
  {
    setup();
  }
  
  if(key=='+')//aumentiamo la dim del quadrato selettore
    {
      if(N<151)
        N+=2;
    }
    
  if(key=='-')//diminuiamo la dim del quadrato selettore
    {
      if(N>51)
        N-=2;
    }
}
