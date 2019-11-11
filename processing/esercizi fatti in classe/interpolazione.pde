PImage im,ip,ir,rp;
float mse0,mse1,mse2,psnr;

void setup()
{
 im=loadImage("lena.png");
 im.filter(GRAY);//lavoriamo su scala di grigi
 im.resize(256,256);
 
 size(760,256);
 background(255,0,0);
 ip=im.copy();
 ip.resize(128,128);//rimpiccioliamo
 ip.resize(256,256);//riportiamo alla normalità, cosi si perde un pò di qualità
 
 ir=im.copy();
 ir.resize(128,128);
 rp=replication(ir);
 
 
 image(im,0,0);
 image(ip,256,0);
 image(rp,512,0);
 
 mse0=MSE(im,im);// MSE dell'immagine con se stessa è 0
 println("MSE se stessa: "+mse0);
 mse1=MSE(im,ip);
 println("MSE rimpicciolita e ingrandita: "+mse1);
 mse2=MSE(im,rp);
 println("MSE replication: "+mse2);
 
 psnr=PSNR(im,im);// PSNR con se stessa tende a infinito e restituisce infinito
 println("PSNR se stessa: "+psnr);
 psnr=PSNR(im,ip);
 println("PSNR rimpicciolita e ingrandita: "+psnr);
 psnr=PSNR(im,rp);
 println("PSNR replication: "+psnr);
}

void draw()
{

}

PImage replication(PImage I)
{
 PImage R=createImage(2*I.width, 2*I.height, RGB);
 
 for(int x=0;x<I.width;x++)
 {
   for(int y=0;y<I.width;y++)
   {
     R.set(2*x,2*y,I.get(x,y));//il punto stesso e i punti vicini
     R.set(2*x+1,2*y,I.get(x,y));
     R.set(2*x,2*y+1,I.get(x,y));
     R.set(2*x+1,2*y+1,I.get(x,y));
   }
 }
 
 return R;
}

float MSE(PImage i1, PImage i2)
{
 //bisognerebbe fare il controllo sulle dimensioni uguali
 float mse=0;
 
 i1.loadPixels();
 i2.loadPixels();
 
 for(int i=0;i<i1.pixels.length;i++)
 {
  mse+=pow(green(i1.pixels[i])-green(i2.pixels[i]),2);//colore a caso quindi prendiamo uno a caso
 }
 return mse/(i1.width*i1.height);//oppure usare I1.pixels.length
}


float PSNR(PImage I1, PImage I2)
{
  float res;
  float mse=MSE(I1,I2);
  res=10*(log((255*255)/mse))/log(10);
  return res;
}
