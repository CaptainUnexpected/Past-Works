
#include <stdio.h>

int n,m;
void horse(int x, int y, int field[n][m])
{
	if((x+2<m)&&(y+1<n))
	{
	field[y+1][x+2]++;
	horse(x+2,y+1,field);		
	}
	
	
	if((x+1<m)&&(y+2<n))
	{
	field[y+2][x+1]++;
	horse(x+1,y+2,field);	
	}

	return;
}
int main()
{

	 scanf("%d %d",&n,&m);	
	 int field[n][m];
	 int x,y;
	 for(y=0;y<n;y++)
    {
	 for(x=0;x<m;x++)
	  {
	   field[y][x] = 0;
      }
    }	 
horse(0,0,field);	 

printf("%d", field[n-1][m-1]); 
	return 0;
}

