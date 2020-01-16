#include <stdio.h>
#include <stdlib.h>

  FILE* fp = NULL;
  char line[50];
  size_t len = 0;
  int size = 0, turn = 0, coordX = 0, coordY = 0, memSize = 0;
  char prevTurn[3], nextTurn[3];
  char prevTurnRes;
  int rule=0;
  int handX=0, handY=0;
  int speedX=0, speedY=0;
  int range=0;
  int RuleWasZero=0;
  int x,y; 
  int level=1;
  int i=0,j=0;
  int alg=1;
  int up=-1,left=-1;
  int nope = 0;
  
//Читамем входные данные.
int input(char *argv[])   
{
	
  fp = fopen(argv[1], "r");

  if (!fp)
    return 1;

  if (fgets(line, 50, fp) != NULL)
  {
    sscanf(line, "%d", &size);
    printf("Size: %d\n", size);
  }

  if (fgets(line, 50, fp) != NULL)
  {
    sscanf(line, "%d", &turn);
    printf("Turn: %d\n", turn);
  }

  if (fgets(line, 50, fp) != NULL)
  {
    sscanf(line, "%d %d", &coordX, &coordY);
    printf("Coords: %d %d\n", coordX, coordY);
  }

  if (fgets(line, 50, fp) != NULL)
  {
    prevTurn[0] = line[0];
    prevTurn[1] = line[1];
    prevTurn[2] = '\0';
    printf("Prev turn: %s\n", prevTurn);
  }

  if (fgets(line, 50, fp) != NULL)
  {
    prevTurnRes = line[0];
    printf("Prev turn res: %c\n", prevTurnRes);
  }

  if (fgets(line, 50, fp) != NULL)
  {
    sscanf(line, "%d", &memSize);
    printf("MemSize: %d\n", memSize);
  }	
  	return 0;
}

//Записываем память робота.
void write_memory(int field[size+2][size+2])
{
 fprintf(fp, "%d\n", size+6);
  for(y=0;y<size+2;y++)
   {
	for(x=0;x<size+2;x++)
	 {
	  fprintf(fp,"%d ",field[x][y]);
     }
    fprintf(fp,"\n");
   }
  fprintf(fp,"%d\n",alg);
  fprintf(fp,"%d\n",rule);
  fprintf(fp,"%d\n",coordX);
  fprintf(fp,"%d\n",coordY); 
  fclose(fp);
	
}

//Читаем память робота.
void read_memory(int field[size+2][size+2])
{
	
  if (memSize > 0)
 { 
   for(y=0;y<size+2;y++)
    {
	 for(x=0;x<size+2;x++)
	  {
	   fscanf(fp,"%d",&field[x][y]);
      }
     fscanf(fp,"\n");
    }
   fscanf(fp,"%d",&alg); 
   fscanf(fp,"%d",&rule);
   fscanf(fp,"%d",&coordX);
   fscanf(fp,"%d",&coordY);   
   	
 
  }
  else
  {
 for(y=1;y<size+1;y++)
    {
	 for(x=1;x<size+1;x++)
	  {
	   field[x][y]=0;
      }
    }  
 for(x=0;x<size+2;x++) 
    {
	   field[x][0]=5;
	   field[x][size+1]=5;
	   field[0][x]=5;
	   field[size+1][x]=5;
    }
  }
	 fclose(fp);  
}

//Вспоминаем направление.
void trans_vect()
{
 if(prevTurn[0] == '-')
  {
   speedX = -1;
   return;
  }
 if(prevTurn[0] == '+')
  {
   speedX = 1;
   return;
  }
 if(prevTurn[1] == '-')
  {
   speedY = -1;
   return;
  }
 if(prevTurn[1] == '+')
  {
   speedY = 1;
   return;
  }
	
}

//Переносим результат предыдущего хода в память.
void check_prevTurnRes(int field[size+2][size+2])
{
 if((prevTurnRes == 'a')||(prevTurnRes == 'e'))
  {
	  if((size/2*2 != size)&&((coordX-speedX+coordY-speedY)/2*2 != (coordX-speedX+coordY-speedY))&&(turn == 1))
	   {
		return;
       }
      field[coordX-speedX][coordY-speedY] = 9;
      field[coordX][coordY] = 9;
  }
	
}

//Уходим из плохой клетки.
void goAwayFromBadPlace(int field[size+2][size+2])
{
	
	if(field[coordX][coordY-1] == 0)
      {
	   nextTurn[0] = '0';
       nextTurn[1] = '-';
       nextTurn[2] = '\0';  
       return;
      }
     if(field[coordX+1][coordY] == 0)
      {
	   nextTurn[0] = '+';
       nextTurn[1] = '0';
       nextTurn[2] = '\0';  
       return;
      }
     if(field[coordX][coordY+1] == 0)
      {
	   nextTurn[0] = '0';
       nextTurn[1] = '+';
       nextTurn[2] = '\0';  
       return;
      }
     if(field[coordX-1][coordY] == 0)
      {
	   nextTurn[0] = '-';
       nextTurn[1] = '0';
       nextTurn[2] = '\0';  
       return;
      }
}

//Поменять правило.
int change_rule()
{
	
 if(size/2*2 == size)
 {
  if(coordY == 1)
   {
    if(coordX/2*2 == coordX)
     {
      return(1);
     }
    else
     {
      return(2);
     }
   }
   
  if(coordY == size)
   {
    if(coordX/2*2 == coordX)
     {
	  return(2);
	 }
	else
	 {
	  return(1);
     }
   }
   
  if(coordX == 1)
   {
    if(coordY/2*2 == coordY)
	 {
	  return(2);
	 }
	else
	 {
      return(1);
     }
   }
   
   if(coordX == size)
    {
	 if(coordY/2*2 == coordY)
	  {
	   return(1);
	  }
	 else
	  {
	   return(2);
      }
    }
}

 if(coordY == 1)
 {
	if(coordX - 1 < size - coordX)
	{
		if(coordX/2*2 == coordX)
		{
		return 1;
	    }
		return 2;
	}
	else
	{
		if(coordX/2*2 == coordX)
		{
		return 2;
	    }
	    return 1;
	}
 }

 if(coordY == size)
 {
	if(coordX - 1 < size - coordX)
	{
		if(coordX/2*2 == coordX)
		{		
		return 2;
	    }
	    return 1; 
	}
	else
	{
		if(coordX/2*2 == coordX)
		{		
		return 1;
	    }
	    return 2;
	}
 }	
 if(coordX == 1)
 {
	if(coordY - 1 < size - coordY)
	{
		if(coordY/2*2 == coordY)
		{		
		return 2;
	    }
	    return 1;
	}
	else
	{
		if(coordY/2*2 == coordY)
		{		
		return 1;
	    }
	    return 2;
	}
 }
 if(coordX == size)
 {
	if(coordY - 1 < size - coordY)
	{
		if(coordY/2*2 == coordY)
		{		
		return 1;
	    }
	    return 2;
	}
	else
	{
		if(coordY/2*2 == coordY)
		{		
		return 2;
	    }
	    return 1;
	}
 }		 
	 return 99;
 }

//Попытаться сделать шаг по правилу 0.
int tryStep_0(int field[size+2][size+2])
{
	if((turn == 0)||((size/2*2 != size)&&((coordX-speedX+coordY-speedY)/2*2 != (coordX-speedX+coordY-speedY))&&(turn == 1)))
	{
		if(coordX - 1 < size - coordX)
	 { 
		range = coordX - 1;
		speedY = 0;
		speedX = -1;
	 }
    else
     {
		range = size - coordX;
		speedY = 0;
		speedX = 1;
	 }
	if(range > coordY - 1)
	 {
		range = coordY - 1;
		speedY = -1;
		speedX = 0;	
	 }
	if(range > size - coordY)
	 {
		range = size - coordY;
		speedY = 1;
		speedX = 0;	
	 }
    }
    
    if((turn ==0)&&(coordY == (size+1)/2)&&(coordY/2*2 == coordY))
    {
		speedY = -1;
		speedX = 0;
	}
    if((turn ==0)&&(coordX == (size+1)/2)&&(coordX/2*2 == coordX))
    {
		speedX = -1;
		speedY = 0;
	}	
	    if(field[coordX+speedX][coordY+speedY] == 0)
         {
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return(1);
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return(1);
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return(1);
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return(1);
              }
	     }
	     return(0);
}

//Определить где право.
void calc_RightHand()
{
	if(speedY == 1)
	 {
	  handY = 0;
	  handX = -1;
	  return;
     }
	if(speedX == 1)
	 {
	  handY = 1;
	  handX = 0;
	  return;
	 }
	if(speedY == -1)
	 {
	  handY = 0;
	  handX = 1;
	  return;
	 }
    if(speedX == -1)
	 {
	  handY = -1;
	  handX = 0;
	  return;
	 }
}

//Определить где лево.
void calc_LeftHand()
{
	if(speedY == 1)
	 {
	  handY = 0;
	  handX = 1;
	  return;
     }
	if(speedX == 1)
	 {
	  handY = -1;
	  handX = 0;
	  return;
	 }
	if(speedY == -1)
	 {
	  handY = 0;
	  handX = -1;
	  return;
	 }
    if(speedX == -1)
	 {
	  handY = 1;
	  handX = 0;
	  return;
	 }
}

//Поменять направление в соответствии с правилом правой руки.
void changeVect_RightHand()
{
	       if(speedY == 1)
		 {
			 speedY = 0;
			 speedX = 1;
			 return;
		 }
		   if(speedX == 1)
		 {
			 speedY = -1;
			 speedX = 0;
			 return;
		 }
		 if(speedY == -1)
		 {
			 speedY = 0;
			 speedX = -1;
			 return;
		 }
		  if(speedX == -1)
		 {
			 speedY = 1;
			 speedX = 0;
			 return;
		 }	
}	

//Поменять направление в соответствии с правилом левой руки.
void changeVect_LeftHand()
{
		    if(speedY == 1)
		 {
			 speedY = 0;
			 speedX = -1;
			 return;
		 }
		   if(speedX == 1)
		 {
			 speedY = 1;
			 speedX = 0;
			 return;
		 }
		 if(speedY == -1)
		 {
			 speedY = 0;
			 speedX = 1;
			 return;
		 }
		  if(speedX == -1)
		 {
			 speedY = -1;
			 speedX = 0;
			 return;
		 }	
	
}

//Попытаться сделать шаг по правилу правой руки.
void tryStep_RightHand(int field[size+2][size+2])
{
	for(x=0;x<4;x++)
	{
        if(field[coordX+speedX][coordY+speedY] == 0)
         {
	      if(field[coordX+handX][coordY+handY] != 0)
           {
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return;
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return;
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return;
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return;
              }
	       }
	      else
	       {
		    speedX = handX;
		    speedY = handY;
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return;
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return;
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return;
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return;
              }
	       }	 
        }
        changeVect_RightHand();
           
}

    for(x=0;x<4;x++)
	{
        if(field[coordX+speedX][coordY+speedY] == 2)
         {
	      if(field[coordX+handX][coordY+handY] != 2)
           {
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return;
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return;
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return;
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return;
              }
	       }
	      else
	       {
		    speedX = handX;
		    speedY = handY;
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return;
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return;
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return;
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return;
              }
	       }	 
        }
        changeVect_RightHand();
           
    }
     nope = 1;
}
//Попытаться сделать шаг по правилу левой руки.
void tryStep_LeftHand(int field[size+2][size+2])
{
	for(x=0;x<4;x++)
	{
		 
        if(field[coordX+speedX][coordY+speedY] == 0)
         {
	      if((field[coordX+handX][coordY+handY] != 0)||(RuleWasZero == 1))
           {
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return;
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return;
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return;
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return;
              }
	       }
	      else
	       {
		    speedX = handX;
		    speedY = handY;
		     if(speedX == -1)
		      {
               nextTurn[0] = '-';
               return;
              }
             if(speedX == 1)
		      {
               nextTurn[0] = '+';
               return;
              }
             if(speedY == -1)
		      {
               nextTurn[1] = '-';
               return;
              }
             if(speedY == 1)
		      {
               nextTurn[1] = '+';
               return;
              }
	       }	 
        }
      changeVect_LeftHand();
	}	
}

//Для уровня А
void level_1(int field[size+2][size+2])
{
	if((size/2*2 != size)&&((coordX+coordY)/2*2 != (coordX+coordY))&&(turn == 0))
	 {
      goAwayFromBadPlace(field);
      return;
	 }	
	 
	 check_prevTurnRes(field);

	  
    if(rule == 0)
     {
	  RuleWasZero = 1;	  
	  if(tryStep_0(field) == 1)
	  {
		  return;
	  }
	  rule = change_rule();
      }
     if(rule == 1)
      {
	   calc_RightHand();
	   tryStep_RightHand(field);
	   return;
      }     
     if(rule == 2)
      {
	   calc_LeftHand();
	   tryStep_LeftHand(field);
	   return;
      }		 
	
	
}

//Идем в угол
void alg_1(int field[size+2][size+2])
{
	if(coordX == -1)
	{
      coordX = size;
      coordY = size;
    }
    
    if(prevTurnRes == 'w')
    {
		if(coordY != 1)
	  {	
		  for(i=coordY;i<=size;i++)
		  {
		   for(j=1;j<=size;j++)
			{
			field[j][i-coordY+1] = field[j][i];
		    }
		  }
		  for(i=size-coordY+2;i<=size;i++)
		   {
		    for(j=1;j<=size;j++)
			 {  
			 field[j][i] = 0;
		     }
		   }		  	  
	  coordY = 1;
	  }
	  else
	  {
		  for(i=coordX;i<=size;i++)
		  {
		   for(j=1;j<=size;j++)
			{
			 field[i-coordX+1][j] = field[i][j];
		    }
		  }
		  for(i=size-coordX+2;i<=size;i++)
		   {
		    for(j=1;j<=size;j++)
			 {  
			 field[i][j] = 0;
		     }
		   }
			  coordX = 1; 
			  alg = 2; 
			  rule = 1;
	  }
      }

	if(coordY != 1)
	{
	 nextTurn[0] = '0';
     nextTurn[1] = '-';
     nextTurn[2] = '\0';  
    }
    else
    {
	 nextTurn[0] = '-';
     nextTurn[1] = '0';
     nextTurn[2] = '\0';  		
	}
    




	
}


//Смотрим в будущее. Планируем дальнейшие ходы.
void alg_2(int field[size+2][size+2],char *argv[])
{
int coordx = 1,coordy = 1,handx = 0,handy = 0,speedx = 0, speedy = 0;
	 nextTurn[0] = '0';
     nextTurn[1] = '0';
     nextTurn[2] = '\0';  
     
     for(x=1;x<=size;x++)
     {
		 if(field[x][1]==2)
		 {left++;}
		 else
		 {break;}
	 }
	 
     for(y=1;y<=size;y++)
     {
		 if(field[x-1][y]==2)
		 {up++;}
		 else
		 {break;}
	 }
	 coordx = coordX;
	 coordy = coordY;
	 handx = handX;
	 handy = handY;
	 speedx = speedX;
	 speedy = speedY;
	 
	 while(1)
	 {
	 coordX = coordx;
	 coordY = coordy;
	 handX = handx;
	 handY = handy;
	 speedX = speedx;
	 speedY = speedy;
	nextTurn[0] = '0';
	nextTurn[1] = '0';
	nextTurn[2] = '\0';	 
	 for(y=1;y<size+1;y++)
      {
	   for(x=1;x<size+1;x++)
	    {
	     field[x][y]=0;
        }
      }  
     for(x=0;x<size+2;x++) 
      {
	   field[x][0]=5;
	   field[x][size+1]=5;
	   field[0][x]=5;
	   field[size+1][x]=5;
      }
      
	 for(i=1;i<=left+1;i++)
	  {
	   field[i][1]=2;
	  }
	 for(j=1;j<=up+1;j++)
	  {
	   field[left+1][j]=2;
	  }
	  	if(nope == 1)
	  	{break;}
	  while(1)
	  {
	   calc_RightHand();
	   tryStep_RightHand(field); 
	   if(nope == 1)
	   {
	 for(y=1;y<size+1;y++)
      {
	   for(x=1;x<size+1;x++)
	    {
	     if(field[x][y] == 0)
	     {nope = 2;}
        }
      }  		   
	   }
	   if(nope != 0)
	   {break;}
	   
       coordX = coordX+speedX;
       coordY = coordY+speedY; 
       field[coordX][coordY] = 1;
        
 // output(argv);
 // write_memory(field);

	   
	  }
	  
	  if(nope == 2)
	  {		
	  if(up != 0)
	  {
		 nope = 0;
		 up--;
	  }
	  else
	  {
       if(left != 0)
		{
		 nope = 0;
	     left--;
	    }
		 else
		 {break;}
	  }
      } 
	  }
	 	 
	 alg = 3;


	
}

//Следуем плану
void alg_3(int field[size+2][size+2])
{
	   calc_RightHand();
	   tryStep_RightHand(field); 
}

//Основной алгоритм.
void perform_alg(int field[size+2][size+2],char *argv[])
{
    if((prevTurnRes == 'a')||(prevTurnRes == 'e'))
    {
    coordX = coordX+speedX;
    coordY = coordY+speedY;
    }
if(alg == 1)
{alg_1(field);}
   
if(alg == 2)
{alg_2(field,argv);}

if(alg == 3)
{alg_3(field);}

if(alg == 1)
{
    field[coordX][coordY] = 2;
}
else
{
field[coordX][coordY] = 1;
}
}

//Записыпаем данные хода.
int output(char *argv[])
{
 fp = fopen(argv[2], "a+");
 if (!fp)
 {
 return(1);
 }
 fprintf(fp, "%s\n", nextTurn);
 return 0;
}


int main(int argc, char *argv[])
{
    nextTurn[0] = '0';
	nextTurn[1] = '0';
	nextTurn[2] = '\0';
	
  if (argc != 3)
  {
    printf("Usage: %s input.txt output.txt\n", argv[0]);
    return 1;
  }
  
  if(input(argv) != 0) return 1;
  
  int field[size+2][size+2];
   	
  read_memory(field);
  
  
  trans_vect();
  
  perform_alg(field,argv);

 
  output(argv);

  write_memory(field);
  
  return(0);
}
