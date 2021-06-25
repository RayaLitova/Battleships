#include "defines.h"

extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;
extern struct ship_t ships_A[10];
extern struct ship_t ships_B[10];
extern int ship_count;


void save_template(int player){

	FILE *fp;


	if(player == 1){
	
		
		fp=fopen("templateA.txt", "w");
		for(int i=0; i<sqrt(map_size); i++){
			fprintf(fp, "%d ", ships_A[i].startx);
			fprintf(fp, "%d ", ships_A[i].starty);
			fprintf(fp, "%c ", ships_A[i].direction);
			fprintf(fp, "%d ", ships_A[i].type);	
			fprintf(fp, "\n");
		}
		
	}
	else{
	
		
		fp=fopen("templateB.txt", "w");
		for(int i=0; i<sqrt(map_size); i++){
			fprintf(fp, "%d ", ships_B[i].startx);
			fprintf(fp, "%d ", ships_B[i].starty);
			fprintf(fp, "%c ", ships_B[i].direction);
			fprintf(fp, "%d ", ships_B[i].type);
			fprintf(fp, "\n");
		}
	
	}
	
	fclose(fp);
}

void call_sf(int player){
	char ans;
	
	printf("Do you want to save this as a template?(y/n) ");
	scanf(" %c", &ans);
	while(ans!='y' && ans!='n'){
		printf("Invalid input. Choose y/n.\n");
		printf("Do you want to save this as a template?(y/n) ");
		scanf(" %c", &ans);
		if(ans == 'y'){
			save_template(player);
		}
		else if(ans == 'n'){
			break;
		}
	}
	if(ans == 'y'){
		save_template(player);
	}
	
}



struct tile_t** load_template(int player){
	struct tile_t  **map=create_empty_map();
	fill_ships(player);
	
	FILE *fp;
	

	if(player == 1){
	
		fp=fopen("templateA.txt", "r");
		if(feof(fp)!=0){
			printf("You don't have a template.\n\n");
			return 0;
		}
		int temp_x;
		int temp_y;
		char temp_dir;
		int temp_type;
		for(int i=0; i<sqrt(map_size); i++){
			fscanf(fp, "%d", &temp_x);
			fscanf(fp, "%d", &temp_y);
			fscanf(fp, " %c", &temp_dir);
			fscanf(fp, "%d", &temp_type);
			place_ship(temp_x, temp_y, temp_dir, temp_type, map);
		}
	}
	else{
	
		fp=fopen("templateB.txt", "r");
		if(feof(fp)!=0){
			printf("You don't have a template.\n\n");
			return 0;
		}
		int temp_x;
		int temp_y;
		char temp_dir;
		int temp_type;
		for(int i=0; i<sqrt(map_size); i++){
			fscanf(fp, "%d", &temp_x);
			fscanf(fp, "%d", &temp_y);
			fscanf(fp, " %c", &temp_dir);
			fscanf(fp, "%d", &temp_type);
			place_ship(temp_x, temp_y, temp_dir, temp_type, map);
		}
	}
	
	fclose(fp);
	return map;	
}

