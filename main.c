#include "defines.h"

 
extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;
extern struct ship_t *ships_A;
extern struct ship_t *ships_B;
extern int pl;


int choose_difficulty(){
	printf("Easy(1)\nHard(2)\n");
	int diff;
	do{scanf("%d", &diff);}
	while(diff>2 || diff<1);
	return diff;
}


struct tile_t** load_template(int player){
	struct tile_t  **map=create_empty_map();
	//load from {player} file
}


void choose_map(int player){
	//system("clear");
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
		if(player==1) map_A_base=random_map(1);
		else map_B_base=random_map(2);
	}else{
		printf("Invalid option\n");
		choose_map(player);
	};
}

void game_start(){
	printf("Singleplayer(1)\nMultyplayer(2)\n");
	int mode;
	scanf("%d", &mode);
	if(mode!=1 && mode!=2){
		game_start();
		return;
	}
	choose_map(1);
	if(mode==2){
		choose_map(2);
		play();
	}else{
		map_B_base=random_map(2);
		if(choose_difficulty()==2){hard_mode();}
		else{easy_mode();}
		
		
	}

}

int main(){
	struct tile_t** map=create_empty_map();
	game_start();
}
