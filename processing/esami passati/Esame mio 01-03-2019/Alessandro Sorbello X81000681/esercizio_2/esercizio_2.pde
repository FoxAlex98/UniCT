PImage im,imlog,imlog2;

void setup()
{
  size(768,256);
  im=loadImage("lena.png");
  im.resize(256,256);
  im.filter(GRAY);
  image(im,0,0);
  imlog=logOp(im);
  image(imlog,256,0);
  imlog2=logOp(im,int(random(10,70)),int(random(10,70)));
  image(imlog2,512,0);
}

void draw()
{

}

PImage logOp(PImage I)
{
  PImage R=createImage(I.width,I.height,RGB);
  
  float c=255/(log(256)/log(10));
  R.loadPixels();
  float r,g,b;
  for(int i=0;i<R.pixels.length;i++)
    {
      r=c*log(1+red(I.pixels[i]))/log(10);
      g=c*log(1+green(I.pixels[i]))/log(10);
      b=c*log(1+blue(I.pixels[i]))/log(10);
      R.pixels[i]=color(r,g,b);
    }
  
  return R;
}

PImage logOp(PImage I, int h, int k)
{
  PImage R=I.copy();
  int posX=int(random(0,I.width));
  int posY=int(random(0,I.height));
  for(int x=posX-h/2;x<posX+h/2;x++)
  {
    for(int y=posY-k/2;y<posY+k/2;y++)
    {
      R.set(x,y,color(0));
    }
  }
  
  R=logOp(R);
  
  return R;
}

void keyPressed()
{
  if(key=='R' || key=='r')
    setup();
}
