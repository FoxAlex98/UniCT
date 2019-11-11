/*
in questo programma sono presenti quasi tutti i filtri e le trasformazioni che sono stati trattati a lezione
tutti in una sola schermata
si possono modificare dimensioni del kernel dei filtri con + e - dove possibile
*/


PImage im,im2;
PImage iMAX,iMIN,iMED;
PImage iNEG,iLOG,iGAM,iQUA;
PImage isf,irf,isi,iri;
PImage irep,ibit,istr;

int N=3;

void setup()
{
  size(1280,1080);
  im=loadImage("lena.png");
  im.resize(256,256);
  fill(0,255,0);
  textSize(20);
  textAlign(CENTER);
  
  image(im,0,0);
  text("lena normale",128,20);
  
  im2=im.copy();
  
  
  im.filter(GRAY);
  image(im,256,0);
  text("lena a scala di grigi",128*3,20);
  
  iMAX=massimo(im,N); 
  image(iMAX,512,0);
  text("massimo con N="+N,128*5,20);
  
  iMIN=minimo(im,N); 
  image(iMIN,768,0);
  text("minimo con N="+N,128*7,20);
  
  iMED=mediano(im,N); 
  image(iMED,1024,0);
  text("mediano con N="+N,128*9,20);
  
  //seconda riga
  
  iNEG=negativo(im2); 
  image(iNEG,0,256);
  text("negativo da colori",128,256+20);
  
  iNEG=negativo(im); 
  image(iNEG,256,256);
  text("negativo da scala di grigi",128*3,256+20);
  
  iLOG=logaritmo(im2); 
  image(iLOG,512,256);
  text("operatore logaritmo",128*5,256+20);
  
  iGAM=gamma(im2,N); 
  image(iGAM,768,256);
  text("operatore gamma con N="+N,128*7,256+20);
 
  iQUA=quantizza(im,N); 
  image(iQUA,1024,256);
  text("quantizzazione con N="+N,128*9,256+20);
  
  //terza riga
  
  isf=scaleF(im,2,2); 
  image(isf,0,512);
  text("scale in FM di 2",128,512+20);
  
  irf=rotateF(im,radians(-45)); 
  image(irf,256,512);
  text("rotate in FM di -45°",128*3,512+20);
  
  ibit=bitPlanes(im,N);
  image(ibit,512,512);
  text("bitPlanes N="+N,128*5,512+20);
  
  irep=replication(im);
  image(irep,768,512);
  text("replication in immagine grande il doppio",128*8,512+20);
  
  //quarta riga
  
  isi=scaleI(im,2,2); 
  image(isi,0,768);
  text("scale in IM di 2",128,768+20);
  
  iri=rotateI(im,radians(45)); 
  image(iri,256,768);
  text("rotate in IM di 45°",128*3,768+20);
  
  istr=stretching(im);
  image(istr,512,768);
  text("stretching",128*5,768+20);
}

void draw()
{

}

void keyPressed()
{
  if(key=='+')
  {
    if(N<8)
    {
      N++;
      
      iMAX=massimo(im,N); 
      image(iMAX,512,0);
      text("massimo con N="+N,128*5,20);
      
      iMIN=minimo(im,N); 
      image(iMIN,768,0);
      text("minimo con N="+N,128*7,20);
      
      iMED=mediano(im,N); 
      image(iMED,1024,0);
      text("mediano con N="+N,128*9,20);
      
      iGAM=gamma(im2,N); 
      image(iGAM,768,256);
      text("operatore gamma con N="+N,128*7,256+20);
      
      iQUA=quantizza(im,N); 
      image(iQUA,1024,256);
      text("quantizzazione con N="+N,128*9,256+20);
      
      ibit=bitPlanes(im,N);
      image(ibit,512,512);
      text("bitPlanes N="+N,128*5,512+20);
    }
  }
  
  if(key=='-')
  {
    if(N>1)
    {
      N--;
      
      iMAX=massimo(im,N); 
      image(iMAX,512,0);
      text("massimo con N="+N,128*5,20);
      
      iMIN=minimo(im,N); 
      image(iMIN,768,0);
      text("minimo con N="+N,128*7,20);
      
      iMED=mediano(im,N); 
      image(iMED,1024,0);
      text("mediano con N="+N,128*9,20);
      
      iGAM=gamma(im2,N); 
      image(iGAM,768,256);
      text("operatore gamma con N="+N,128*7,256+20);
      
      iQUA=quantizza(im,N); 
      image(iQUA,1024,256);
      text("quantizzazione con N="+N,128*9,256+20);
      
      ibit=bitPlanes(im,N);
      image(ibit,512,512);
      text("bitPlanes N="+N,128*5,512+20);
    }
  }
}

PImage massimo(PImage I, int n)
{
  PImage R=createImage(I.width,I.height,RGB);
  PImage sub;
  
  int off=n/2;
  float m;
  
  float f[]=new float[n*n];
  
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      sub=I.get(i-off,j-off,n,n);
      
      sub.loadPixels();
      
      for(int k=0;k<sub.pixels.length;k++)
      {
       f[k]=red(sub.pixels[k]);
      }
      
      m=max(f);
      R.set(i,j,color(m));
    }
  }
  return R;  
}

PImage minimo(PImage I, int n)
{
  PImage R=createImage(I.width,I.height,RGB);
  
  PImage sub;
  int off=n/2;
  int xs,ys;
  float m;
  float[] f;//non è detto che sia grande N*N
  
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      xs=i-off;
      ys=j-off;
      sub=I.get(max(0,xs),max(0,ys),min(n,n+xs,I.width-xs),min(n,n+ys,I.height-ys));
      sub.loadPixels();
      
      f=new float[sub.pixels.length];
      
      for(int k=0;k<sub.pixels.length;k++)
      {
        f[k]=red(sub.pixels[k]);
      }
      
      m=min(f);
      R.set(i,j,color(m));
    }
  }
  
  return R;
}


PImage mediano(PImage I, int N)
{
  PImage R=createImage(I.width,I.height,RGB);
  float med;
  float[] f;
  int off=N/2;
  PImage tmp;
  int xs,ys;
  
  for(int x=0;x<I.width;x++)
  {
    for(int y=0;y<I.height;y++)
    {
      xs=x-off;
      ys=y-off;
      tmp=I.get(max(0,xs),max(0,ys),min(N,N+xs,I.width-xs),min(N,N+ys,I.height-ys));
      tmp.loadPixels();
      f=new float[tmp.pixels.length];
      for(int k=0;k<tmp.pixels.length;k++)
      {
        f[k]=green(tmp.pixels[k]);
      }
      f=sort(f);
      if(f.length%2==1)
        med=f[f.length/2];
      else
        med=(f[f.length/2-1]+f[f.length/2])/2;
          
      R.set(x,y,color(med));
    }
  }
  
  return R;
}

PImage negativo(PImage I)
{
  PImage R=I.copy();
  R.loadPixels();
  for(int i=0;i<R.pixels.length;i++)
  {
      R.pixels[i]=color(255-red(R.pixels[i]),255-green(R.pixels[i]),255-blue(R.pixels[i]));
  }
  R.updatePixels();
  return R;
}

//se l'immagine su cui applichiamo il filtro logaritmo è a scala di grigi non c'è bisogno di r,g,b, ma solo di uno di essi
PImage logaritmo(PImage I)
{
   PImage R=I.copy();
   R.loadPixels();
   
   float c=255/(log(255)/log(10));
   //float c=255/log(256);
   float r,g,b;
   for(int i=0;i<R.pixels.length;i++)
   {
       r=c*log(red(R.pixels[i])+1)/log(10);
       g=c*log(green(R.pixels[i])+1)/log(10);
       b=c*log(blue(R.pixels[i])+1)/log(10);
       R.pixels[i]=color(r,g,b);
   }
   
   return R;
}

//se l'immagine su cui applichiamo il filtro gamma è a scala di grigi non c'è bisogno di r,g,b, ma solo di uno di essi
PImage gamma(PImage I, float gm)
{
  PImage R=I.copy();
  R.loadPixels();
  
  float c=1/(pow(255,gm-1));
  float r,g,b;
  
  for(int i=0;i<R.pixels.length;i++)
  {
    r=c*pow(red(R.pixels[i]),gm);
    g=c*pow(green(R.pixels[i]),gm);
    b=c*pow(blue(R.pixels[i]),gm);
    R.pixels[i]=color(r,g,b);
  }
  
  R.updatePixels();
  
  return R;
}

PImage quantizza(PImage I, float k)
{
  PImage R=I.copy();
  R.loadPixels();
  
  int q;
  
  for(int i=0;i<R.pixels.length;i++)
  {
    q=floor((red(R.pixels[i])*k)/256);
    
    q=int((float(q)/(k-1))*255);
    
    R.pixels[i]=color(q);
  }
  R.updatePixels();
  
  return R;
}

PImage media(PImage I, int N)
{
  PImage R=createImage(I.width,I.height,RGB);
  
  float res;
  int xs,ys;
  int off=N/2;
  PImage tmp;
  
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
      {
        res+=red(tmp.pixels[k]);
      }
      res=res/tmp.pixels.length;
      R.set(i,j,color(res));
    }
  }
  
  return R;
}

PImage scaleF(PImage I, float sx, float sy)
{
  PImage R=createImage(I.width,I.height,RGB);
  R.loadPixels();
  
  for(int i=0;i<R.pixels.length;i++)
    R.pixels[i]=color(0);
  
  float x,y,u,v;
  
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      u=i-I.width/2;
      v=j-I.height/2;
      
      x=u*sx;
      y=v*sy;
      
      x=x+I.width/2;
      y=y+I.height/2;
      
      R.set(round(x),round(y),I.get(i,j));
    }
  }
  
  return R;
}

PImage rotateF(PImage I, float rot)
{
  PImage R=createImage(I.width,I.height,RGB);
  R.loadPixels();
  
  for(int i=0;i<R.pixels.length;i++)
    R.pixels[i]=color(0);
    
  float x,y,u,v;
  
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      u=i-I.width/2;
      v=j-I.height/2;
      
      x=u*cos(rot)-v*sin(rot);
      y=u*sin(rot)+v*cos(rot);
      
      x=x+I.width/2;
      y=y+I.height/2;
      
      R.set(round(x),round(y),I.get(i,j));
    }
  }
  
  return R;
}

PImage scaleI(PImage I, float sx, float sy)
{
  PImage R=createImage(I.width,I.height,RGB);
  R.loadPixels();
  for(int i=0;i<R.pixels.length;i++)
    R.pixels[i]=color(0);
   
  float u,v,x,y;
   
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      u=i-I.width/2;
      v=j-I.height/2;
      
      x=u*(1/sx);
      y=v*(1/sy);
      
      x=x+I.width/2;
      y=y+I.height/2;
      
      R.set(i,j,I.get(round(x),round(y)));
    }
  }
  
  return R;
}

PImage rotateI(PImage I, float rot)
{
  PImage R=createImage(I.width,I.height,RGB);
  R.loadPixels();
  
  for(int i=0;i<R.pixels.length;i++)
      R.pixels[i]=color(0);
      
  float u,v,x,y;
  
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      u=i-I.width/2;
      v=j-I.height/2;
      
      x=u*cos(rot)-v*sin(rot);
      y=u*sin(rot)+v*cos(rot);
      
      x=x+I.width/2;
      y=y+I.height/2;
      
      R.set(i,j,I.get(round(x),round(y)));
    }
  }
  
  return R;
}

PImage replication(PImage I)
{
  PImage R=createImage(I.width*2,I.height*2,RGB);
  
  for(int i=0;i<I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      R.set(i*2,j*2,I.get(i,j));
      R.set(i*2+1,j*2,I.get(i,j));
      R.set(i*2,j*2+1,I.get(i,j));
      R.set(i*2+1,j*2+1,I.get(i,j));
    }
  }
  
  return R;
}

PImage bitPlanes(PImage I, int n)
{
  PImage R=I.copy();
  R.loadPixels();
  
  int k;
  int r;
  
  for(int i=0;i<R.pixels.length;i++)
  {
    k=int(green(R.pixels[i]));
    r=(k>>n)&1;
    R.pixels[i]=color(r*255);
  }
  
  return R;
}

float[] istogramma(PImage I)
{
  PImage R=I.copy();
  R.loadPixels();
  float[] H=new float[256];
  
  for(int i=0;i<256;i++)
      H[i]=0;
      
  for(int i=0;i<R.pixels.length;i++)
  {
    H[int(green(R.pixels[i]))]++;
  }
  
  for(int i=0;i<256;i++)
  {
    H[i]=H[i]/R.pixels.length;
  }
  
  return H;
}


PImage stretching(PImage I)
{
  PImage R=I.copy();
  R.loadPixels();
  
  float min,max,tmp;
  
  min=green(R.pixels[0]);
  max=green(R.pixels[0]);
  
  for(int i=1;i<R.pixels.length;i++)
    {
      tmp=green(R.pixels[i]);
      if(tmp<min)
        min=tmp;
      else if(tmp>max)
              max=tmp;
    }
    if(max==min)
      return R;
    
    for(int i=0;i<R.pixels.length;i++)
      {
        tmp=green(R.pixels[i]);
        R.pixels[i]=color(255*(tmp-min)/(max-min));
      }
      R.updatePixels();
  
  return R;
}
