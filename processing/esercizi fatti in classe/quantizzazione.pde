PImage im,qua;
int K=8;

//questa non è una quantizzazione ma una riquantizzazzione in quanto l'immagine è già stata quantizzata di default

void setup()
{
 im=loadImage("lena.png");
 im.filter(GRAY);//lavoriamo su scala di grigi
 im.resize(256,256);
 size(512,256);
 image(im,0,0);
 qua=quantizza(im,K);
 image(qua,256,0);
 
 
}

void draw()
{

}

PImage quantizza(PImage I, int k)//quantizziamo normalmente l'immagine quindi con  (L*K)/N dove K è il numero dei nuovi livelli, N numero di quelli vecchi, L vecchio livello
{
  PImage R=I.copy();//lavorando su una copia
  
  R.loadPixels();
  
  int q;
  for(int i=0;i<R.pixels.length;i++)
  {
    q=floor((blue(R.pixels[i])*k)/256);  //round arrotondamento  floor e seed
    
    //q=int((float(q)/(k-1))*255);
    //oppure
    q=int(lerp(0,255,float(q)/(k-1)));
    
    R.pixels[i]=color(q);
  }
  R.updatePixels();
  
  return R;
}

void keyPressed()
{
 if((key=='+') && (K<256))
 {
  K++;
  qua=quantizza(im,K);
  image(qua,256,0);
 }
 
 if((key=='-') && (K>0))
 {
  K--;
  qua=quantizza(im,K);
  image(qua,256,0);
 }
}
