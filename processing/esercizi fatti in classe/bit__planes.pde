PImage im,ib;
int N=5;

void setup()
{
  size(1024,522);
  im=loadImage("lena.png");
  im.filter(GRAY);
  im.resize(256,256);
  image(im,0,0);
  ib=bitplane(im,N);
  image(ib,256,0);
  
}
//dobbiamo usare lo shift moltiplicando o dividendo i byte per 2       << shift verso sinistra   >> shift verso destra
//dobbiamo usare anche l'AND
void draw()
{
  
}

PImage bitplane(PImage I, int n)
{
 PImage R=I.copy();
 
 R.loadPixels();
 
 int k;//non usiamo i float perchè i numeri a virgola mobile sono "particolari"(sono complicati)
 int r;
 for(int i=0;i<R.pixels.length;i++)
 {
  k=(int(green(R.pixels[i])));
  
  r=(k>>n)&1;
  
  R.pixels[i]=color(r*255);
  
 }
 
 R.updatePixels();
 return R;
}

void keyPressed()
{
 if((key=='+') && (N<7))
   {
    N++;
    ib=bitplane(im,N);
    image(ib,256,0);
   }
   
   
   if((key=='-') && (N>0))
   {
    N--;
    ib=bitplane(im,N);
    image(ib,256,0);
   }
}
