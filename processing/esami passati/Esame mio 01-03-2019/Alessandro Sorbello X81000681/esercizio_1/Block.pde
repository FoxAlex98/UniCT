class Block
{
  int posX,posY,w,h,sx;
  
  Block(int posX, int posY, int w, int h)
  {
    this.posX=posX;
    this.posY=posY;
    this.w=w;
    this.h=h;
    sx=4;
  }
  
  void disegna()
  {
    fill(0,255,0);
    noStroke();
    rectMode(CENTER);
    rect(posX,posY,w,h);
  }
  
  void sposta()
  {
    posX+=sx;
    if(posX<0)
    {
      posX=0;
      sx*=-1;
    }
    else if(posX>width)
    {
      posX=width;
      sx*=-1;
    }
  }
  
  void run()
  {
    disegna();
    sposta();
  }

}
