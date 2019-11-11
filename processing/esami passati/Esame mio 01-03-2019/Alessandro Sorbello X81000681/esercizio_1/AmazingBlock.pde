class AmazingBlock extends Block
{
  float angle;
  color c;
  
  AmazingBlock(int posX, int posY, int w, int h, float angle)
  {
    super(posX,posY,w,h);
    this.angle=angle;
  }
  
  void disegna()
  {
    c=color(angle%256,255-angle%256,255);
    fill(c);
    rectMode(CENTER);
    pushMatrix();
    translate(posX,posY);
    rotate(radians(angle));
    rect(0,0,w,h);
    popMatrix();
    angle+=5;
  }
  
  void run()
  {
    disegna();
    sposta();
  }
}
