#include "defines.h"

 
extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;



void choose_difficulty(){
	printf("Easy(1)\nHard(2)\nInsane(3)\nRandom(4)\n");
	int diff;
	scanf("%d", &diff);
	if(diff>4 || diff<1){
		choose_difficulty();
	}
}


struct tile_t** load_template(int player){
	struct tile_t  **map=create_empty_map();
	//load from {player} file
}
struct tile_t** random_map(){
	struct tile_t **map=create_empty_map();
}

void choose_map(int player){
	system("clear");
	printf("Player %d:\n", player);
	printf("Create map(1)\nLoad template(2)\nRandom map(3)\n");
	int map;
	scanf("%d", &map);
	if(map==1){
		if(player==1) map_A_base=create_map(player);
		else map_B_base=create_map(player);
	}else if(map==2){
		if(player==1) map_A_base=load_template(1);
		else map_B_base=load_template(2);
	}else if(map==3){
		if(player==1) map_A_base=random_map();
		else map_B_base=random_map();
	}else{
		printf("Invalid option\n");
		choose_map(player);
	}
}

void game_start(){
	printf("Singleplayer(1)\nMultyplayer(2)\n");
	int mode;
	scanf("%d", &mode);
	if(mode!=1 && mode!=2){
		game_start();
		return;
	}
	if(mode==1){
		choose_difficulty();
	}
	choose_map(1);
	if(mode==2){
		choose_map(2);
	}else if(mode==1){
		random_map(2);
	}
	play();
}

int main(){
	game_start();
}