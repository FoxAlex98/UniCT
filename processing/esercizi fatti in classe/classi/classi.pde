Ball b;
Ball b2;
int K=15;

Ball[] B;//array di ball

ArrayList<Ball> balls;//struttura dinamica definita generamente(con i template)

void setup()
{
 size(500,500);
 B=new Ball[K];
 
 balls=new ArrayList<Ball>();
 /*for(int i=0;i<K;i++)
 {
  B[i]=new Ball(random(50,450),random(50,450),random(25,75),random(0.5,3.5),random(0.5,3.5));
 }*/
 
 for(int i=0;i<K;i++)
 {
  balls.add(new Ball(random(50,450),random(50,450),random(25,75),random(0.5,3.5),random(0.5,3.5)));
 }
 
 //b=new Ball(100,100,50,2,1);
 //b2=new Ball(100,100,100,4,0.5);
}

void draw()
{
  //background(255,0,255);
  
  fill(255,0,255,40);//l'ultimo valore è l'opacità dello sfondo che a ogni ciclo viene sovrascritto e da l'impressione della scia
  rect(-10,-10,width+10,height+10);
  /*
  for(int i=0;i<K;i++)
  {
    B[i].run();
  }*/
  
  for(int i=0;i<balls.size();i++)
  balls.get(i).run();
  
  
  
  /*
  for(Ball var: balls)//for each (alternativa al for e get)
  var.run();          // non usa riferimenti a questi oggetti
  */
  
  //b.run();
  //b2.run();
}

void keyPressed()
{
 if(key == 'n')
   balls.add(new Ball(random(50,450),random(50,450),random(25,75),random(0.5,3.5),random(0.5,3.5)));
}
