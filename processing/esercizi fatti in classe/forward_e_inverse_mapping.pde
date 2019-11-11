PImage im,ifm,ifr,iim,iir,sh;

void setup()
{
  size(780,512);
  im=loadImage("lena.png");
  im.resize(256,256);
  ifm=scalaf(im,2,2);
  ifr=rotatef(im,radians(20));
  iim=scalai(im,2,2);
  iir=rotatei(im,radians(20));
  sh=shearF(im,2,2);
  
  image(im,0,0);
  image(ifm,256,0);
  image(ifr,512,0);
  image(sh,0,256);
  image(iim,256,256);
  image(iir,512,256);
  
  
}

void draw()
{
 
}

PImage scalaf(PImage I, float sx, float sy)
{
 PImage R=createImage(I.width,I.height,RGB);//può capitare che parte dei pixel dopo la trasformazione finiscano fuori se li faccio della stessa dimensione
 
 R.loadPixels();
 for(int i=0;i<R.pixels.length;i++)
 R.pixels[i]=color(0);//colora di zero lo sfondo
 R.updatePixels();
 
 
 float x,y,u1,v1;
 
 for(int u=0;u<I.width;u++)
 {
  for(int v=0;v<I.height;v++)
  {
    u1=u-I.width/2;//trasliamo prima
    v1=v-I.height/2;//e usiamo i valori traslati
    
    x=sx*u1;
    y=sy*v1;
    
    x=x+I.width/2;
    y=y+I.height/2;
    
    R.set(round(x),round(y),I.get(u,v));
  }
 }
 
 return R;
}

PImage rotatef(PImage I, float rad) //scale è un'operazione di Processing
{
  PImage R = createImage(I.width, I.height, RGB);
  
  R.loadPixels();
  for(int i = 0; i < R.pixels.length; i++)
  {
    R.pixels[i]=color(0);
  }
  R.updatePixels();
  
  float x, y, u1, v1; // u1 e v1 sono le variabili traslate
  for(int u = 0; u < I.width; u++)
  {
    for(int v = 0; v < I.height; v++)
    {
      u1= u-I.width/2; //qui stiamo traslando
      v1= v-I.height/2;
     
      x=u1 * cos(rad)-v1*sin(rad); //qui stiamo facendo la rotazione
      y=u1 * sin(rad)+v1*cos(rad);
      
      x=x+I.width/2; //qui stiamo ritraslando x e y nel punto originale
      y=y+I.height/2;
      
      R.set(round(x), round(y), I.get(u, v)); //dobbiamo fare round perchè il set vuole degli interi
    }
  }
  return R;
}

PImage shearF(PImage I, float shx, float shy) //scale è un'operazione di Processing
{
  PImage R = createImage(I.width, I.height, RGB);
  
  R.loadPixels();
  for(int i = 0; i < R.pixels.length; i++)
  {
    R.pixels[i]=color(0);
  }
  R.updatePixels();
  
  float x, y, u1, v1; // u1 e v1 sono le variabili traslate
  for(int u = 0; u < I.width; u++)
  {
    for(int v = 0; v < I.height; v++)
    {
      u1= u-I.width/2; //qui stiamo traslando
      v1= v-I.height/2;
     
      x=u1+shx*v1; //qui stiamo facendo lo shearing
      y=u1*shy+v1;
      
      x=x+I.width/2; //qui stiamo ritraslando x e y nel punto originale
      y=y+I.height/2;
      
      R.set(round(x), round(y), I.get(u, v)); //dobbiamo fare round perchè il set vuole degli interi
    }
  }
  return R;
}

PImage scalai(PImage I, float sx, float sy)
{
 PImage R=createImage(I.width,I.height,RGB);//può capitare che parte dei pixel dopo la trasformazione finiscano fuori se li faccio della stessa dimensione
 
 R.loadPixels();
 for(int i=0;i<R.pixels.length;i++)
 R.pixels[i]=color(0);//colora di zero lo sfondo
 R.updatePixels();
 
 
 float x1,y1,u,v;
 
 for(int x=0;x<R.width;x++)
 {
  for(int y=0;y<R.height;y++)
  {
    x1=x-R.width/2;//trasliamo prima
    y1=y-R.height/2;//e usiamo i valori traslati
    
    u=x1*(1/sx);
    v=y1*(1/sy);
    
    u=u+I.width/2;
    v=v+I.height/2;
    
    R.set(x,y,I.get(round(u),round(v)));
  }
 }
 
 return R;
}

PImage rotatei(PImage I, float rad)//NON FUNZIONA
{
 PImage R=createImage(I.width,I.height,RGB);//può capitare che parte dei pixel dopo la trasformazione finiscano fuori se li faccio della stessa dimensione
 
 R.loadPixels();
 for(int i=0;i<R.pixels.length;i++)
 R.pixels[i]=color(0);//colora di zero lo sfondo
 R.updatePixels();
 
 float x1,y1,u,v;
 
 for(int x=0;x<I.width;x++)
 {
  for(int y=0;y<I.height;y++)
  {
    x1=x-I.width/2;//trasliamo prima
    y1=y-I.height/2;//e usiamo i valori traslati
    
    u=x1*cos(rad)-y1*sin(rad);//+I.width;
    v=x1*sin(rad)+y1*cos(rad);//+I.height;//se la vogliamo ruotata rispetto al centro
    
    u=u+I.width/2;
    v=v+I.height/2;
    
    R.set(x,y,I.get(round(u),round(v)));
  }
 }
 
 return R;
}

void stampa(float[] H)
{
 for(int i=0;i<50;i++)
  print(H[i]+" ");
  print("\n");
}
