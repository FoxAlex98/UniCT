BlackHole bh;//un buco nero
ArrayList<Asteroid> ast;//tanti asteroidi

void setup()
{
  size(512,512);//dimensione predefinita
  background(125,125,125);//sfondo grigio
  bh=new BlackHole(mouseX,mouseY,50);//buco nero che segue il puntatore del mouse
  ast=new ArrayList<Asteroid>();//array di asteroidi
}

void draw()
{
  background(125,125,125);//aggiorniamo lo sfondo
  bh.run(ast);//avviamo il buco nero
  
  for(Asteroid var:ast)//eseguiamo tutti gli asteroidi
  {
    var.run(bh);
  }
  
  appari();//appare probabilmente un asteroide
}

void appari()
{
  if(random(0,100)<15)//15% di probabilità
    ast.add(new Asteroid(random(0,512),random(0,512),random(5,25)));//se si, allora aggiungi un asteroide
}

void keyPressed()
{
  if((key=='r')||(key=='R'))//se preme r allora resetta lo sketch
    setup();
}
