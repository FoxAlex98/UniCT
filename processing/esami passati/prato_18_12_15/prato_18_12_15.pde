tagliaerba t;

void setup()
{
 size(500,500);//dimensione di default
 background(0,255,0);//sfodo verde
 t=new tagliaerba(5);//istanziamo il tagliaerba con velocità 5 di default
}

void draw()
{
 t.run();//eseguiamo
}

void keyPressed()
{
  if(key=='r' || key=='R')//con r o R si resetta il prato
  {
    background(0,255,0);
  }
  
  if(key=='+')
  {
    t.aumentavel();//aumenta la velocità
  }
  if(key=='-')
  {
    t.diminuiscivel();//diminuisce la velocità
  }
  
}
