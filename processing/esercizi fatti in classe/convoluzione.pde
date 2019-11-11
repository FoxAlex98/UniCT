//La convoluzione restituisce in output una matrice che ha i valori di un segnale
//Ricordiamo che PImage usa le coordinate invertite rispetto alle normali matrici

float n3=1/9.0; //bisogna mettere 9.0 perchè altrimenti viene fatta una divisione a interi
float[][] nbox3={{n3, n3, n3},
                 {n3, n3, n3},
                 {n3, n3, n3}};
                 
float n5=1.0/25;              
float[][] nbox5={{n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5},
                 {n5,n5,n5,n5,n5}};

float[][] sharp={{-1,0,-1},
                 {0,5,0},
                 {-1,0,-1}};
                 
float[][] sobX={{-1, -2, -1},
                { 0,  0,  0},
                {-1, -2, -1}};
                
float[][] lapl={{-1, 0, -1},
                { 0, 4,  0},
                {-1, 0, -1}};
                
PImage Im, In3, In5, Is, IsX, Ir, Il;
void setup()
{
  size(512, 512);
  Im=loadImage("lena.png");
  Im.resize(256, 256);
  Im.filter(GRAY);
  In3=converti(Convoluzione(Im, nbox3));
  In5=converti(Convoluzione(Im, nbox5));
  //Is=converti(Convoluzione(Im, sharp));
  IsX=converti(Convoluzione(Im, sobX));
  Il=converti(Convoluzione(Im, lapl));
  
  image(Im, 0, 0);
  image(In3, 256, 0);
  image(Il, 0, 256);
  image(In5, 256, 256);
  
  
}

void draw()
{
 
}

float[][] Convoluzione(PImage I, float[][] K)//non funziona, sistemare
{
 //print(K[1][1]);
 float[][] R=new float[I.height][I.width];//le dimensioni sono invertite
 
 float res;
 //tipicamente il kernel è quadrato ma può essere anche rettangolare
 
 int N=K[0].length;//numero di colonne del kernel
 int M=K.length;//numero di righe del kernel
 
 int offx=N/2;
 int offy=N/2;
 PImage tmp;
 
 for(int x=0;x<I.width;x++)
 {
  for(int y=0;y<I.height;y++)
  {
   tmp=I.get(x-offx,y-offy,N,M);//non stiamo attenti ai bordi, in quanto anche non fare niente è una soluzione
   
   res=0;
   
   for(int i=0;i<tmp.width;i++)
   {
    for(int j=0;j<tmp.height;j++)
    {
     res=res+red(tmp.get(i,j))*K[j][i];
    }
   }
   
   R[y][x]=res;
  }
 }
 
 
 return R;
}



//ma noi vogliamo un immagine quindi la convertiamo
PImage converti(float[][] F)//converte una matrice in un'immagine
{
 PImage R=createImage(F[0].length,F.length,RGB);
 float res=0;
 
 for(int x=0;x<R.width;x++)
 {
  for(int y=0;y<R.height;y++)
  {
   res=constrain(abs(F[y][x]),0,255);//constrain prende il valore e se supera i limiti riporta il valore nel range es se è 258 diventa 255
   R.set(x,y,color(res));
  }
 }
 return R;
}
