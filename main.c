#include <stdio.h>
#include <stdlib.h>

#define map_size 100

void choose_difficulty(){
	printf("Easy(1)\nHard(2)\nInsane(3)\nRandom(4)\n");
	int diff;
	scanf("%d", &diff);
}

int **create_empty_map(int size){
	int **new_map=malloc(size*sizeof(int*));
	for(int i=0; i<size; i++){
		new_map[i]=0;
	}
	return new_map;
}

void create_map(){
	int **map=create_empty_map(map_size);
}
void load_template(player){
	int **map=create_empty_map(map_size);
	//load from {player} file
}
void random_map(){
	int **map=create_empty_map(map_size);
}

void choose_map(int player){
	printf("Player %d:\n", player);
	printf("Create map(1)\nLoad template(2)\nRandom map(3)\n");
	int map;
	scanf("%d", &map);
	if(map==1){
		create_map();
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
}

int main(){
	game_start();
}