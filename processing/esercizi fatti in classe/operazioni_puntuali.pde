PImage im, in, lo, gam;

void setup()
{
 im=loadImage("lena.png");
 im.resize(256,256);
 
 size(512,512);
 
 in=negativo(im);
 lo=logaritmo(im);
 gam=gamma(im,5);
 image(im,0,0);//immagine normale
 image(in,256,0);//negativo
 image(lo,0,256);//logaritmo
 image(gam,256,256);//gamma
 
 //per cambiare la base del log bisogna fare log in base A di B = log in base e di B/log in base e di A
 //di default il log è in base e
 
}

void draw()
{

}

PImage negativo(PImage I)//otteniamo il negativo dell'immagine
{
  PImage R=I.copy();//lavorando su una copia
  
  R.loadPixels();
  
  for(int i=0;i<R.pixels.length;i++)
  {
    R.pixels[i]=color(255-red(R.pixels[i]),255-green(R.pixels[i]),255-blue(R.pixels[i]));
  }
  
  return R;
}

PImage logaritmo(PImage I)//applichiamo l'operatore logaritmo    g(x,y)=c*log(1+f(x,y))
{
  PImage R=createImage(I.width,I.height,RGB);//creando una nuova immagine
  
  R.loadPixels();
  I.loadPixels();
  
  float r,g,b;
  float c=255/log(256);//costante di normalizzazione il log è in base e
  
  for(int i=0;i<I.pixels.length;i++)
  {
   r=c*log(1+red(I.pixels[i]));
   g=c*log(1+green(I.pixels[i]));
   b=c*log(1+blue(I.pixels[i]));
   R.pixels[i]=color(r,g,b);
  }
  return R;
}

PImage gamma(PImage I, float gm)//applichiamo l'operatore gamma che è g(x,y)= c*f(x,y)^gamma
{
  PImage R=createImage(I.width,I.height,RGB);//creando una nuova immagine
  
  R.loadPixels();
  I.loadPixels();
  
  float r,g,b;
  float c=1/pow(255,gm-1); //costante di normalizzazione che è 255/pow(255,gm) oppure 1/pow(255,gm-1)
  
  for(int i=0;i<I.pixels.length;i++)
  {
   r=c*pow(red(I.pixels[i]),gm);
   g=c*pow(green(I.pixels[i]),gm);
   b=c*pow(blue(I.pixels[i]),gm);
   R.pixels[i]=color(r,g,b);
  }
  return R;
}
