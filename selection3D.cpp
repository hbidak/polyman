#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "selection3D.h"

#define BUFSIZE 512


int selection3D::processHits (GLint hits, GLuint buffer[])
{
	int nom;

	bool trouve=false;
		cout<<"se rend dans processhits"<<endl;
	unsigned int i, j;
	GLuint names, *ptr;

	printf("hits = %d\n", hits);
	ptr=(GLuint *) buffer;
	cout<<"se rend ici9"<<endl;
	for (i=0;i < hits;i++)
	{
		names=*ptr;
		printf("nombre de noms pour hit= %d\n", names); ptr++;
		printf(" z1 egale %g;", (float) *ptr/0x7fffffff); ptr++;
		printf(" z2 egale %g\n", (float) *ptr/0x7fffffff); ptr++;
		printf(" le nom est ");
		for(j=0;j<names;j++)
		{
			printf("%d ", *ptr);
			if(trouve==false)
			{	
				nom=*ptr;
				trouve=true;
			}

			 ptr++;
		}
		printf("\n");
	}

	cout<<"le nom est"<<nom<<endl;
	return nom;
}