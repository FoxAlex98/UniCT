Block b;
AmazingBlock ab;

void setup()
{
  size(256,512);
  background(255);
  b=new Block(int(random(0,width)),int(random(0,height/2)),40,60);
  ab=new AmazingBlock(int(random(0,width)),int(random(height/2,height)),40,60,random(0,360));
}

void draw()
{
  background(255);
  b.run();
  ab.run();
}

void keyPressed()
{
  if(key=='r' || key=='R')
    setup();
}
