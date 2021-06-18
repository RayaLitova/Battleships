#include "defines.h"

 
extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;

int print_map(struct tile_t** map){
	printf("   |");
	for(int i=0;i<sqrt(map_size);i++){
		printf(" %c |", 'A'+i);
		
	}
	for(int i=0;i<sqrt(map_size);i++){
		printf("\n    --- --- --- --- --- --- --- --- --- ---\n");
		if(i+1!=10){
			printf(" %d |", i+1);
		}else{
			printf("%d |", i+1);
		}
		for(int j=0;j<sqrt(map_size);j++){
			printf(" %c |", map[i][j].symbol);
		}
	}
	printf("\n");
}

void choose_difficulty(){
	printf("Easy(1)\nHard(2)\nInsane(3)\nRandom(4)\n");
	int diff;
	scanf("%d", &diff);
}


struct tile_t** load_template(int player){
	struct tile_t  **map=create_empty_map();
	//load from {player} file
}
struct tile_t** random_map(){
	struct tile_t **map=create_empty_map();
}

void choose_map(int player){
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
	}else{
		if(player==1) map_A_base=random_map();
		else map_B_base=random_map();
	};
}

void game_start(){
	printf("Singleplayer(1)\nMultyplayer(2)\n");
	int mode;
	scanf("%d", &mode);
	if(mode==1){
		choose_difficulty();
	}
	choose_map(1);
	if(mode==2){
		choose_map(2);
	}else{
		random_map(2);
	}
	play();
}

int main(){
	struct tile_t** map=create_empty_map();
	game_start();
}