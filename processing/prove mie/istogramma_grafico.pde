PImage im;

void setup()
{
  size(1024,256);
  im=loadImage("lena.png");
  im.resize(256,256);
  im.filter(GRAY);
  image(im,0,0);
  float[] f=istogramma(im);
  line(256,250,1024,250);//linea orizzontale
  for(int i=1;i<256;i++)
  {
    line(256+i*3,250,256+i*3,250-f[i]*20000);
    //i*3 per distanziare le linee    -f[i]*20000 per l'altezza
  }
  
}

void draw()
{

}

float[] istogramma(PImage I)
{
  I.loadPixels();
  float[] H=new float[256];
  for(int i=0;i<256;i++)//azzeriamo i contatori
  H[i]=0;
  
  for(int i=0;i<I.pixels.length;i++)
  {
    H[int(green(I.pixels[i]))]++;//aumentiamo il contatore apposito
  }
  
  for(int i=0;i<256;i++)
  {
    H[i]=H[i]/I.pixels.length;//e facciamo la media per ognuno
    //println("i= "+i+" "+H[i]);
  }
  
  return H;
}
