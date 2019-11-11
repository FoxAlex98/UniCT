float a,sx,sy,tx,ty,shx,shy;

void setup()
{
  size(500,500);
  a=0;
  sx=0;
  sy=0;
  tx=ty=0;
  shx=shy=0;
}

void draw()
{
  background(255);
  
  strokeWeight(5);
  stroke(0,0,0);
  fill(255,0,0);
  rectMode(CENTER);
  rect(0,0,100,100);
  /*pushMatrix();//salva la trasformazione precedente al comando (si possono annidare)
  //translate(250,250);//modifica la posizione dell'origine del piano
  //rotate(PI/4);//ruota il piano con l'angolo espresso in radianti e ruota in senso orario se il grado è positivo   PI=costante di pigreco
  //ma cosi ruotiamo il piano, se vogliamo ruotare una figura allora trasliamo prima il piano, poi lo ruotiamo e infine disegnamo la figura nel punto (0,0)
  translate(width/2,height/2);
  rotate(radians(a));//con radians usiamo i numeri che vengono convertiti in radianti
  scale(2,2);//scala il piano, in questo caso lo raddoppia
  rect(0,0,75,75);
  popMatrix();//butta via tutto ciò che è stato salvato dopo pushMatrix()
  shearX(shx);//ruota l'asse X lasciando invariato l'asse Y e viceversa con shearY
  */
  
  pushMatrix();
  translate(tx,ty);
  //rotate(radians(a));
  shearX(shx);
  rect(0,0,75,75);
  popMatrix();
  
  pushMatrix();
  translate(width/2-100,height/2-100);
  //scale(sx,sy);
  shearX(shx);
  shearY(shy);
  
  rect(0,0,75,75);
  popMatrix();
  
  stroke(0,255,0);
  fill(0,255,255);
  
  pushMatrix();
  translate(width/2,height/2-100);
  //applyMatrix(cos(radians(a)), sin(radians(a)),0,-sin(radians(a)), cos(radians(a)),0);//trasformiamo in base ad una matrice che scriviamo manualmente noi
  /*applyMatrix( 1, shx, 0,
              shy, 1, 0);
              Se si vuole fare una rototraslazione e si conoscono la matrice della rotazione e quella dell traslazione, basta fare il prodotto riga colonna delle 
              due matrici 3x3 ed eliminare la terza riga.
              */
              
  rect(0,0,75,75);
  popMatrix();
  
  a++;
  sx+=0.01;
  sy+=0.01;
  tx+=2;
  ty+=2;
  shx+=0.01;
  shy+=0.01;
}
