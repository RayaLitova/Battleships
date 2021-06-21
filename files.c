#include "defines.h"
#include <stdio.h>


extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;


void save_template(int player){

	FILE *fp;


	if(player == 1){
	
		
		fp=fopen("templateA.txt", "w+");
		for(int i=0; i<sqrt(map_size); i++){
			for(int j=0; j<sqrt(map_size); j++){
				fprintf(fp, "%d ", map_A_base[i][j].value);	
			}
			fprintf(fp, "\n");
		}
	}
	else{
	
		
		fp=fopen("templateB.txt", "w+");
		for(int i=0; i<sqrt(map_size); i++){
			for(int j=0; j<sqrt(map_size); j++){
				fprintf(fp, "%d ", map_B_base[i][j].value);	
			}
			fprintf(fp, "\n");
		}
	}
	
	fclose(fp);
}

void call_sf(int player){
	char ans;
	printf("Do you want to save this as a template?");
	scanf(" %c", &ans);
	if(ans == 'y'){
		save_template(player);
	}
}



struct tile_t** load_template(int player){
	struct tile_t  **map=create_empty_map();
	//load from {player} file
	
	FILE *fp;
	

	if(player == 1){
	
		fp=fopen("templateA.txt", "r");
		if(feof(fp)==0){
			printf("You don't have a template.");
			return 0;
		}
		for(int i=0; i<sqrt(map_size); i++){
			for(int j=0; j<sqrt(map_size); j++){
				fscanf(fp, "%d ", &map[i][j].value);	
				if(map[i][j].value!=0){
					map[i][j].symbol = 'X';
				}
				else if(map[i][j].value==0){
					map[i][j].symbol = ' ';
				}
			}
		}
	}
	else{
	
		fp=fopen("templateB.txt", "r");
		if(feof(fp)!=0){
			printf("You don't have a template.");
			return 0;
		}
		for(int i=0; i<sqrt(map_size); i++){
			for(int j=0; j<sqrt(map_size); j++){
				fscanf(fp, "%d ", &map[i][j].value);	
				if(map[i][j].value!=0){
					map[i][j].symbol = 'X';
				}
				else if(map[i][j].value==0){
					map[i][j].symbol = ' ';
				}
			}
		}
	}
	
	fclose(fp);
	return map;	
}

