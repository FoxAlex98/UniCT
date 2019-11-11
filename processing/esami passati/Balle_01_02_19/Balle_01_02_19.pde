Ball b;//classe madre
HyperBall hb;//classe figlia

void setup()
{
 size(512,256);//dimensione predefinite
 background(255,255,255);//sfondo bianco
 b=new Ball(int(random(1,width/2)),int(random(1,height)),40);//definizione classe madre
 hb=new HyperBall(int(random(width/2,width)),int(random(1,height)),40);//definizione classe figlia
}

void draw()
{
 b.run();//esecuzione classe madre
 hb.run();//esecuzione classe figlia
}

void keyPressed()
{
  if(key=='r' || key=='R')//resettiamo lo sketch
    {
      setup();//usando lo stesso setup
    }
}
