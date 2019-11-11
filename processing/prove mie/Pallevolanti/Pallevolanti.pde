/*
palle di colore randomico che rimbalzano
se ne possono inserire massimo 10
con il tasto p si può mettere in pausa e riprendere
con + e - si aggiunge o si toglie una palla
con la rotellina si modifica la velocità
con r si resetta lo sketch
*/

Ball[] b;
int n;
boolean flag=true;

void setup()
{
 size(1000,1000);
 background(#AAFFAA);
 b=new Ball[10];
 n=0;
}

void draw()
{
  if(flag)
  {
    background(#AAFFAA);
    for(int i=0;i<n;i++)
          b[i].run();
  }
}

void add()
{
 int dirX=int(random(0,100));
 int dirY=int(random(0,100));
 b[n]=new Ball(dirX,dirY);
 n++;
}

void mouseWheel(MouseEvent event)
{
  int e=event.getCount();
  for(int i=0;i<n;i++)
    {
      b[i].velocita(e);
      //println(e);
    }
}

void keyPressed()
{
 if(key=='+')
   {
    if(n<10)
    add();
   }
 if(key=='-')
   {
     if(n>0)
     n--;
   } 
 if(key=='p')
   {
    if(flag)
       flag=false;
    else
       flag=true;
   }
   
  if(key=='r' || key=='R')
   {
     n=0;
     background(#AAFFAA);
   }
}
