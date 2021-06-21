#include "defines.h"
#include <stdio.h>


extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;


//FILE *fp;



void save_files(){

	FILE *fp;


	fp=fopen("templateA.txt", "w+");

	int a=0;

	a = fwrite(map_A_base, sizeof(map_A_base) , 1, fp);
	
	if(a != 0){
		printf("y");
	}	
	else{
		printf("n");
	}

	fclose(fp);



}
