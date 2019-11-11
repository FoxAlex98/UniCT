/*in questo file sono presenti tutti i piani di bit 
  il primo in alto a sinistra è l'immagine originale
  il primo in basso a sinistra è un piano che varia con + e - dal piano 0 al 7*/


PImage im,iml;
int N=4;

void setup()
{
  size(1280,512);
  fill(0,0,255);
  textSize(30);
  textAlign(CENTER);
  im=loadImage("lena.png");
  im.resize(256,256);
  im.filter(GRAY);
  image(im,0,0);
  text("lena in grigio",128,30);

  for(int i=0;i<4;i++)
  {
    iml=bitplane(im,i);
    image(iml,256*i+256,0);
    text("piano "+i,128*(i*2+1)+256,30);
  }
  for(int i=4;i<8;i++)
  {
    iml=bitplane(im,i);
    image(iml,256*(i-4)+256,256);
    text("piano "+i,128*((i-4)*2+1)+256,286);
  }
  
  iml=bitplane(im,N);
  image(iml,0,256);
  text("piano "+N,128,286);
}

void draw()
{

}

PImage bitplane(PImage I, int n)
{
  PImage R=I.copy();
  R.loadPixels();
  
  int k;
  int c;
  
  for(int i=0;i<R.pixels.length;i++)
  {
    k=int(green(R.pixels[i]));
    c=(k>>n)&1;
    R.pixels[i]=color(c*255);
  }
  R.updatePixels();
  return R;
}

void keyPressed()
{
  if(key=='+' && N<7)
  {
    N++;
    iml=bitplane(im,N);
    image(iml,0,256);
    text("piano "+N,128,286);
  }
  
  if(key=='-' && N>0)
  {
    N--;
    iml=bitplane(im,N);
    image(iml,0,256);
    text("piano "+N,128,286);
  }

}
