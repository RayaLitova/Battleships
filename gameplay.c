#include "defines.h"

struct tile_t **map_A_base;
struct tile_t **map_B_base;

struct tile_t **map_A;
struct tile_t **map_B;
int turn=1;

int last_fire_Bx=0;
int last_fire_By=0;
int last_fire_Ax=0;
int last_fire_Ay=0;

void play(){
	int ships_left_A=10, ships_left_B=10;
	struct tile_t **map_A=create_empty_map();
	struct tile_t **map_B=create_empty_map();
	fire();
}

void fire(){
	int x,y;
	do{
		printf("\nPlayer %d:\n", turn);
		printf("Choose position(A1,B2,..)\n");
		char help_c;
		scanf(" %c", &help_c);
		if(help_c>'a') x = help_c-'a';
		else x = help_c-'A';
		scanf("%d", &y);
		y-=1;
		if(x<0||x>9) printf("No such x\n");
		if(y<0||y>9) printf("No such y\n");
	}
	while(y<0||y>9||x<0||x>9);
	if(turn==1){
		if(map_A_base[x][y].value>1){
			printf("A ship was hit!\n");
		}else{
			printf("No ships were hit! :(\n");
			turn=2;
		}
		last_fire_Ax=x;
		last_fire_Ay=y;
	}else if(turn==2){
		if(map_B_base[x][y].value>1){
			printf("A ship was hit!\n");
		}else{
			printf("No ships were hit! :(\n");
			turn=1;
		}
		last_fire_Bx=x;
		last_fire_By=y;
	}
	fire();
}