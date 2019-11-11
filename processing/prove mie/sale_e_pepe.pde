/*
  questo programma mostra il rumore sale e pepe e le conseguenze dell'uso del filtro di media o mediano su di esso
  con la s di sporca l'immagine con il rumore sale e pepe
  con la r si resetta
  cliccando con il tasto destro si usa il filtro mediano all'interno del rettangolo
  cliccando con il tasto sinistro si usa il filtro media all'interno del rettangolo
  con + e - si aumenta o diminuisce la dimensione del kernel del filtro
  con la rotellina di aumenta o diminuisce la dimensione del quadrato verde
  con h si applica alla metà sinistra dell'immagine il filtro mediano e alla metà di destra il filtro di media
  con M si applica a tutta l'immagine il filtro mediano
  con m si applica a tutta l'immagine il filtro di media
*/
PImage im;
float prob=0.05;
int N=3;
int dim=50;

void setup()
{
  size(512,512);
  im=loadImage("lena.png");
  im.filter(GRAY);
  im.resize(512,512);
  image(im,0,0);
}

void draw()
{
  image(im,0,0);
  noFill();
  rectMode(CENTER);
  stroke(0,255,0);
  rect(mouseX,mouseY,dim,dim);
  textSize(20);
  text("N "+N,20,20);
}

PImage sporca(PImage I,float p)
{
  float s;
  PImage R=I.copy();
  R.loadPixels();
  for(int i=0;i<I.pixels.length;i++)
  {
    s=random(0,1);
    if(s<p)
      {
        if(s<p/2)
          R.pixels[i]=color(0);
        else
          R.pixels[i]=color(255);
      }
  }
  return R;
}


PImage media(PImage I, int N)
{
  PImage R=I.copy();
  float res=0;
  PImage tmp;
  int off=N/2;
  int xs,ys;
  
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      xs=i-off;
      ys=j-off;
      tmp=I.get(max(0,xs),max(0,ys),min(N,N+xs,I.width-xs),min(N,N+ys,I.height-ys));
      tmp.loadPixels();
      res=0;
      for(int k=0;k<tmp.pixels.length;k++)
        res+=green(tmp.pixels[k]);
      
      res=res/tmp.pixels.length;
      R.set(i,j,color(res));
    }
  }
  
  return R;
}



PImage mediano(PImage I, int N)
{
  PImage R=I.copy();
  
  float[] f;
  float res;
  int off=N/2;
  int xs,ys;
  PImage tmp;
  
  for(int i=0;i<I.width;i++)
  {
     for(int j=0;j<I.height;j++)
     {
       xs=i-off;
       ys=j-off;
       tmp=I.get(max(0,xs),max(0,ys),min(N,N+xs,I.width-xs),min(N,N+ys,I.height-ys));
       tmp.loadPixels();
       f=new float[tmp.pixels.length];
       for(int k=0;k<tmp.pixels.length;k++)
       {
         f[k]=red(tmp.pixels[k]);
       }
       f=sort(f);
       
       if(f.length%2==1)
         res=f[f.length/2];
       else
         res=(f[f.length/2]+f[f.length/2-1])/2;
       
       R.set(i,j,color(res));
     }
  }
  
  return R;
}


void mouseWheel(MouseEvent e)
{
  float r=e.getCount();
  if(dim<100 && r==1)
    dim++;
  else if(dim>0 && r==-1)
    dim--;
}


void mousePressed()
{
  PImage tmp;
  int off=dim/2;
  if(mouseButton==LEFT)
    {
      tmp=im.get(mouseX-off,mouseY-off,dim,dim);
      tmp=mediano(tmp,N);
      im.set(mouseX-off,mouseY-off,tmp);
    }
    
  if(mouseButton==RIGHT)
    {
      tmp=im.get(mouseX-off,mouseY-off,dim,dim);
      tmp=media(tmp,N);
      im.set(mouseX-off,mouseY-off,tmp);
    }
}


void keyPressed()
{
  if(key=='R' || key=='r')
    setup();
    
  if(key=='s' || key=='S')
    {
      im=sporca(im,prob);
      image(im,0,0);
    }  
  
  if(key=='M')
    {
      im=mediano(im,N);
      image(im,0,0);
    }
    
  if(key=='m')
    {
      im=media(im,N);
      image(im,0,0);
    }
    
  if(key=='h')
    {
      PImage i1,i2;
      i1=im.get(0,0,im.width/2,im.height);
      i2=im.get(im.width/2,0,im.width/2,im.height);
      im.set(0,0,mediano(i1,N));
      im.set(im.width/2,0,media(i2,N));
      image(im,0,0);
    }
    
  if(key=='+' && N<8)
  {
    N++;
  }
  if(key=='-' && N>1)
  {
    N--;
  }
  
}
