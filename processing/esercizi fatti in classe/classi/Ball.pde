class Ball
{
 float posX,posY,dim,sx,sy,pes;
 
 Ball(float x, float y, float d)
 {
  this(x,y,d,0,0);//this chiamata come funzione chiama il costruttore
 }
 
 Ball(float x, float y, float d, float sx, float sy)
 {
  this.posX=x;
  this.posY=y;
  this.dim=d;
  this.sx=sx;
  this.sy=sy;
  pes=0.1;
 }
 
 void display()//possiamo chiamarlo come vogliamo questo metodo
 {
   fill(0,0,255);
   noStroke();
   ellipse(posX,posY,dim,dim); 
 }
 
 void move()
 {
   posX+=sx;
   posY+=sy;
 }
  
 void run()//meglio fare un metodo che richiami tutto
 {
   display();
   gravity();
   move();
   bounce();
 }
 
 void gravity()
 {
   sy+=0.1;
   //sy+=pes;
   //pes+=5;
 }
 
 void bounce()
 {
  if((posX-dim/2<=0)||(posX+dim/2>width))
  {
    sx=-sx;
  }
  if((posY-dim/2<=0)||(posY+dim/2>height))
  {
    sy=-sy;
    //pes=0.1;
    //sy=sy/2;
  }
 }
  
  
}
