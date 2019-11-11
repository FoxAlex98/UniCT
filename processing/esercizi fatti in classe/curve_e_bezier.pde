void setup()
{
  size(500,500);
}

void draw()
{
 background(255);
 fill(255,0,0);
 strokeWeight(5);
 beginShape();//inizia il disegno di un poligono con tot lati
 vertex(50,100);//metodo per disegnare un vertice
 vertex(200,100);
 bezierVertex(220,120,220,180,200,200);//prende due punti di controllo e uno di ancoraggio
 vertex(150,150);
 vertex(100,200);
 //endShape();//finisce il disegno del poligono
 endShape(CLOSE);//se mettiamo close l'ultimo punto si collega al primo
 
 //curva di BEZIER, ci permette di disegnare una curva usando 4 punti, 2 di ancoraggio (punti importanti della curva) e ,2 di controllo
 //in pratica si forma con un trapezio dividendo sempre a metà i lati superiori e collegandoli fra loro
 noFill();
 //bezier(100,400,150,300,250,300, mouseX, mouseY);//il primo e l'ultimo punto sono punti di ancoraggio, gli altri sono di controllo
 //bezier(100,400,mouseX, mouseY,250,300,300,400);
 //per fare petali o gocce fare coincidere i punti di ancoraggio
}
