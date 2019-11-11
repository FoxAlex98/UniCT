class Ball
{
  int velx=5,vely=5;
  int direzioneX=1,direzioneY=1;
  float x,y,dim;
  color c;
  
 Ball(int dirX, int dirY)
 {
  dim=random(50,100);
  x=random(dim+100,1000-dim);
  y=random(dim+100,1000-dim);
  
  if(dirX%2==1)
  direzioneX=-1;
  
  if(dirY%2==1)
  direzioneY=-1;
  
  stroke(0,0,0);
  c=color(random(0,256),random(0,256),random(0,256));
  ellipse(x,y,dim,dim);
 }
 
 void disegna()
 {
  fill(c);
  ellipse(x,y,dim,dim);
 }
 
 void move()
 {
   x+=velx*direzioneX;
   y+=vely*direzioneY;
  if(x<=0+(dim/2) || x>=width-(dim/2))
  {
    direzioneX=-direzioneX;
  }
  if(y<=0+(dim/2) || y>=height-(dim/2))
  {
    direzioneY=-direzioneY;
  }
 }
 
 void velocita(int vel)
 {
   if(velx>0 && velx<20)
   {
     velx+=vel;
   }
   if(vely>0 && vely<20)
   {
     vely+=vel;
   }
   if(velx==0 || vely==0)
     velx=vely=1;
   
   if(velx==20 || vely==20)
     velx=vely=19;
     
 }
 
 void run()
 {
  disegna();
  move();
  //stampa();
 }

 void stampa()
 {
   println("dim="+dim+" x="+x+" y="+y);
 }
}
