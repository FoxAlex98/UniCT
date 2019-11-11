PImage Im, Is, Ie;
float[] H1, H2;

void setup()
{
  size(768, 256);
  Im=loadImage("lena.png");
  Im.resize(256,256);
  Im.filter(GRAY);
  
  Is=stretching(Im);
  Ie=equalizza(Im);
  H1=istogramma(Im);
  H2=istogramma(Is);
  
  println(H1[0]);
  println(H2[0]);
  image(Im, 0, 0);
  image(Is, 256, 0);
  image(Ie, 512, 0);
}

void draw()
{
  
}

float[] istogramma(PImage I) //in java si può scrivere così perchè le strutture dati vengono allocate dinamicamente di default
{
  float[] H = new float[256]; //il new è uguale al c++
  for(int i = 0; i < 256; i++) H[i]= 0;
  I.loadPixels();
  
  for(int i=0; i<I.pixels.length; i++) // I.pixels.length è il numero di pixels che contiene l'immagine
  {
    H[int(green(I.pixels[i]))]++; //in questo modo avremo un array che contiene i numeri da 1 a 255
  }
  
  for(int i = 0; i<256; i++)
  {
    H[i] = H[i]/I.pixels.length;
  }
  return H;
}

PImage stretching(PImage I)
{
  PImage R=I.copy();
  
  R.loadPixels();
  float Max, Min, tmp;
  Max = green(R.pixels[0]);//indifferente l'uso dei colori nel bianco e nero
  Min = red(R.pixels[0]);
  
  for(int i=1; i<R.pixels.length; i++)
  {
    tmp = blue(R.pixels[i]);
    if(tmp>Max) Max=tmp;
    else if(tmp<Min) Min = tmp;
  }
  
  if(Max == Min) return R;
  for(int i = 0; i < R.pixels.length; i++)
  {
    tmp=green(R.pixels[i]);
    R.pixels[i]=color(255*(tmp-Min)/(Max-Min)); //potremmo anche calcolare il valore della formula e mettere direttamente il risultato
    
  }
  R.updatePixels();
  
  return R;
}

PImage equalizza(PImage I)
{
  PImage R=createImage(I.width, I.height, RGB);
  float[] H=istogramma(I);
  
  I.loadPixels();
  R.loadPixels();
  
  for(int i = 1; i < 256; i++)
  {
    H[i] = H[i]+H[i-1]; //l'array conterrà le somme che ci serviranno per la formula dell'equalizzazione
  }
  for(int i = 0; i <I.pixels.length; i++)
  {
    R.pixels[i] = color(255*H[int(green(I.pixels[i]))]);
  }
  return R;
}
