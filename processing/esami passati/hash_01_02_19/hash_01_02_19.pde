PImage im,ih,ih2;

void setup()
{
  size(768,256);
  im=loadImage("lena.png");//carichiamo l'immagine di lena
  im.resize(256,256);//ridimensioniamola
  im.filter(GRAY);//portiamola in grigio
  image(im,0,0);//stampiamola
  ih=hash(im,int(random(1,256)),int(random(1,256)));//immagine a cui è stato applicato l'hash
  image(ih,256,0);
  ih2=hash(im,int(random(1,256)),int(random(1,256)),int(random(3,11)));
  image(ih2,512,0);//immmagine a cui è stato applicato l'hash dopo l'operatore massimo
}

void draw()
{
  
}

PImage hash(PImage I,int h, int k)//colora tutte le righe e colonne con indice h e k
{
  PImage R=I.copy();//facciamo la copia dell'immagine
  color nero=color(0,0,0);
  for(int i=0;i<I.width;i++)//ciclo per colorare le righe
    {
      R.set(i,h,nero);//coloriamo tutta la riga che ha h come indice della riga scorrendo tra le colonne
      R.set(i,k,nero);//stessa cosa per k
    }
    
  for(int j=0;j<I.height;j++)//ciclo per colorare le colonne
        {
          R.set(h,j,nero);//coloriamo tutta la colonna che ha h come indice della colonna scorrendo tra le righe
          R.set(k,j,nero);//stessa cosa per k
        }
    
  return R;
}


PImage hash(PImage I,int h, int k, int n)
{
  PImage R=massimo(I,n);//effettuiamo il massimo dell'immagine con kernel n
  R=hash(R,h,k);//e facciamo l'hash normalmente
  return R;
}

PImage massimo(PImage I, int N)//operatore di massimo
{
  PImage R=createImage(I.width,I.height,RGB);
  
  PImage tmp;
  int off=N/2;
  float[] tmpF=new float[N*N];
  float res;
  
  for(int i=0;i<I.width;i++)
      {
       for(int j=0;j<I.height;j++)
       {
         tmp=I.get(i-off,j-off,N,N);
         tmp.loadPixels();
         
         for(int k=0;k<tmp.pixels.length;k++)
         {
          tmpF[k]=green(tmp.pixels[k]);
         }
         res=max(tmpF);
         R.set(i,j,color(res));
       }
      }
  
  
  return R;

}

void keyPressed()//alla pressione di r o R resettiamo lo sketch
{
  if(key=='r' || key=='R')
    setup();
}
