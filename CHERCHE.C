#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <time.h>


struct square {

	char square,ligne,col,cpt_move;
	struct square *ps;
	struct square *pp;

		    };



/* VARIABLES GLOBALES : */
/*----------------------*/
struct square *p,	*pcomp,	*pdebut,	*pdestruct ;
char g_max,g_square,g_nb_ligne,g_nb_col,g_depart_ligne,g_depart_col;




char xytosquare(char ligne,char col)

{

 return( ((ligne-1)*g_nb_col) + col );

}

struct square *liberer(p)
	struct square *p;
{

 p->pp->ps=0;
 pdestruct=p;
 p=p->pp;

 free(pdestruct);

 return(p);
};



char *duree(long l_seconde,char *pheure)

{
 long heure,minute,seconde;
 char c_heure[3],c_minute[3],c_seconde[3],zone[3];


 strcpy(pheure,"\0");

 strcpy(c_heure,"\0");
 strcpy(c_minute,"\0");
 strcpy(c_seconde,"\0");

 for(heure=0,minute=0,seconde=0;l_seconde>0;)
 {

  if(l_seconde<60)
  {
   seconde += l_seconde;
   l_seconde=0;
  }

  if (l_seconde>59)
  {
   minute++;
   l_seconde -= 60;
  }

  if (seconde>59)
  {
   seconde=0;
   minute++;
  }

  if (minute>59)
  {
   minute=0;
   heure++;
  }

  if (heure>59) heure=0;
 }

 ltoa(heure,c_heure,10);
 ltoa(minute,c_minute,10);
 ltoa(seconde,c_seconde,10);


 if ( strlen(c_heure)   == 1)
 {
  strcpy(zone,"0\0");strcat(zone,c_heure);strcpy(c_heure,zone);
 }

 if ( strlen(c_minute)  == 1)
 {
 strcpy(zone,"0\0");strcat(zone,c_minute);strcpy(c_minute,zone);
 }

 if ( strlen(c_seconde) == 1)
 {
 strcpy(zone,"0\0");strcat(zone,c_seconde);strcpy(c_seconde,zone);
 }

 strcat(pheure,c_heure);
 strcat(pheure,":\0");
 strcat(pheure,c_minute);
 strcat(pheure,":\0");
 strcat(pheure,c_seconde);
 return(pheure);

};



void info(unsigned long cpt_tent,char cpt_max,char cpt_des_max,char nb_square,clock_t t_debut, struct square *pg)
{

 clock_t t_courant;
 long diff=0L;
 char *heure,tab_h[9];



 t_courant=clock();


 diff =( (t_courant-t_debut) / CLK_TCK ) ;

/* gotoxy(1,10);
 printf("%d",diff);
 printf("\n%d",t_courant);
 printf("\n%d",t_debut);
 exit(0);
 sleep(10);
*/

 heure = duree(diff,tab_h);



 clrscr();
 gotoxy(1,1);
 printf("TENTATIVES : %lu TEMPS: %s\n",cpt_tent,heure);
 printf("MONTEE   !!!! MAX     : %u\n",cpt_max);
 printf("COUPS : %i, Case :  %i\n",nb_square,pg->square);
 printf("DESCENTE !!!! MAX_DES : %u\n",cpt_des_max);



};





void main(int argc,	char *argv[])

{
 char nb_square,v_ligne,v_col,v_square,touche,cpt_aff,cpt_max,cpt_des,cpt_des_max;

 char *paff,tab_heure[9];

 char tab_aff[1000];

 unsigned long cpt_tent;

 clock_t t_debut,t_courant;

 long t_diff=0L;

 if (argc!=5) {
  clrscr();
  gotoxy(1,1);
  printf("cherche <nb_ligne> <nb_col> <ligne_depart> <col_depart>\n");
  exit(1);

 }

 t_debut=clock();



 g_nb_ligne=*(argv[1])-48;
 g_nb_col=*(argv[2])-48;
 g_max=g_nb_ligne*g_nb_col;

 g_depart_ligne=*(argv[3])-48;
 g_depart_col=*(argv[4])-48;
 g_square=xytosquare(g_depart_ligne,g_depart_col);





 p=(struct square *)malloc(sizeof(struct square));
 pdebut=p;

 p->pp=0;
 p->ps=0;
 p->square=g_square;
 p->ligne=g_depart_ligne;
 p->col=g_depart_col;
 p->cpt_move=0;
 v_square = g_square;

 for(nb_square=(g_max+1);nb_square>0;nb_square--) tab_aff[nb_square]=00;

 clrscr();
 for(nb_square=1,cpt_tent=0,	v_ligne=v_col=cpt_max=cpt_des=cpt_des_max=0;(nb_square < g_max)||(p->square!=v_square);	 ) {

	if (kbhit())
	{

	 touche=getch();
	 if (touche==65) break ;

	 if (touche==73) info(cpt_tent,cpt_max,cpt_des_max,nb_square,t_debut,p);

	 if (touche==69) clrscr();

	}

	p->cpt_move++;
	cpt_tent++;

	v_ligne = p->ligne;
	v_col   = p->col;

	if (p->cpt_move==9)
	{

	 if (p->pp>0)
	 {
		p=liberer(p);
		nb_square--;
		cpt_des++;
	 }
	else
	{
	 p->col++;
	 if (p->col>g_nb_col)
	 {
	  p->ligne++;
	  if (p->ligne>g_nb_ligne)
	  {
	   t_courant = clock();

	   t_diff = ( (t_courant-t_debut) / CLK_TCK);

	   clrscr();
	   gotoxy(1,1);

	   printf("RESULTAT   :\n");
	   printf("TENTATIVES : %lu TEMPS : %s\n",cpt_tent,duree(t_diff,tab_heure));
	   printf("MAX        : %u\n",cpt_max);
	   printf("DES_MAX    : %u\n\n",cpt_des_max);
	   printf("\n PAS DE SOLUTION TROUVE !!");
	   exit(1);
	  }
	  p->col=1;
	 }
	 p->square=xytosquare(p->ligne,p->col);
	 p->cpt_move=0;
	 gotoxy(1,20);
	 printf("n_col %u  n_lig %u",v_col,v_ligne);

	}

	if (cpt_des>cpt_des_max)
	{
	 cpt_des_max=cpt_des;

	}
    }
   else
   {
    if (p->cpt_move==1) { 	v_ligne+=2;	v_col++ ;	}
    if (p->cpt_move==2) { 	v_ligne++ ;	v_col+=2;	}
    if (p->cpt_move==3) { 	v_ligne-- ;	v_col+=2;	}
    if (p->cpt_move==4) { 	v_ligne-=2;	v_col++ ;	}
    if (p->cpt_move==5) { 	v_ligne-=2;	v_col-- ;	}
    if (p->cpt_move==6) { 	v_ligne-- ;	v_col-=2;	}
    if (p->cpt_move==7) { 	v_ligne++ ;	v_col-=2;	}
    if (p->cpt_move==8) { 	v_ligne+=2;	v_col-- ;	}

    if ( (v_ligne>0) && (v_ligne<g_nb_ligne+1) && (v_col>0)
	  && (v_col<g_nb_col+1))
    {
	v_square=xytosquare(v_ligne,v_col);

	for(pcomp=p ;	(pcomp!=pdebut) && (pcomp->square != v_square);  )
	{

	 pcomp=pcomp->pp;
	}

	if (pcomp->square != v_square)
	{

	 p->ps=(struct square *) malloc(sizeof(struct square));

	 p->ps->pp=p;

	 p=p->ps;

	 p->ps=0;
	 p->square=v_square;
	 p->ligne=v_ligne;
	 p->col=v_col;
	 p->cpt_move=0;
	 nb_square++;
	 cpt_des=0;

	 if (nb_square>cpt_max)
	 {
	  cpt_max=nb_square;

	  for(nb_square=(g_max+1);nb_square>0;nb_square--)
		 tab_aff[nb_square]=00;

	  for(pcomp=pdebut,nb_square=0;pcomp->ps!=0;pcomp=pcomp->ps)
	  {
	   nb_square++;
	   tab_aff[pcomp->square]=nb_square;
	  }
	  nb_square++;
	  tab_aff[pcomp->square]=nb_square;
	  nb_square=cpt_max;

	 }
	}
    }
   }
  }

  t_courant = clock();

  t_diff = ( (t_courant-t_debut) / CLK_TCK);

  clrscr();
  gotoxy(1,1);

  printf("RESULTAT   :\n");
  printf("TENTATIVES : %lu TEMPS : %s\n",cpt_tent,duree(t_diff,tab_heure));
  printf("MAX        : %u\n",cpt_max);
  printf("DES_MAX    : %u\n\n",cpt_des_max);


  for(nb_square=1 ;nb_square<cpt_max+1;nb_square++)
  {


   for(cpt_aff=1;tab_aff[cpt_aff]!=nb_square && cpt_aff < g_max+1 ; )
	  cpt_aff++;

   if(!(nb_square%10))
   {
    printf("\n");
   }


   printf("%2d)%2d  ",nb_square,cpt_aff);

  }


  printf("\n\n     ");

  for(cpt_aff=1;cpt_aff<(g_nb_col+1);cpt_aff++) printf("%c  ",cpt_aff+96);

  printf("\n   ");

  for(cpt_aff=1;cpt_aff<(g_nb_col+1);cpt_aff++) printf("___",cpt_aff+96);

  printf("\n%2d| ",g_nb_ligne);

  for(cpt_aff=1, v_ligne=g_nb_ligne,v_col=1;(v_ligne>0) && ( v_col>0);)
  {
   nb_square=xytosquare(v_ligne,v_col);

   printf("%2d ",tab_aff[nb_square]);

   v_col++;


   cpt_aff++;

   if(cpt_aff>g_nb_col) {

   cpt_aff=1;

   v_ligne--;

   v_col=1;

   printf("\n");

   if (v_ligne>0 ) printf("%2d| ",v_ligne);

  }

 }


}










