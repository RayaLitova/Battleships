#include "defines.h"

void play(){
	struct tile_t **map_A=create_empty_map();
	struct tile_t **map_B=create_empty_map();

}

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


void load_template(int player){
	struct tile_t  **map=create_empty_map();
	//load from {player} file
}
void random_map(){
	struct tile_t **map=create_empty_map();
}

void choose_map(int player){
	printf("Player %d:\n", player);
	printf("Create map(1)\nLoad template(2)\nRandom map(3)\n");
	int map;
	scanf("%d", &map);
	if(map==1){
		create_map(player);
	}else if(map==2){
		load_template(player);
	}else{
		random_map(player);
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