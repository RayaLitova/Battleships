#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define map_size 100

struct tile_t{
	int value;
	char symbol;
};

int print_map(struct tile_t** map){
	printf("   ");
	for(int i=0;i<sqrt(map_size);i++){
		printf(" %d |", i);
	}
	for(int i=0;i<sqrt(map_size);i++){
		printf("\n   --- --- --- --- --- --- --- --- --- ---\n");
		printf("%c |", 'A'+i);
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

struct tile_t **create_empty_map(){
	struct tile_t **new_map=malloc(map_size*sizeof(struct tile_t*));
	for(int i=0;i<sqrt(map_size);i++){
		new_map[i]=malloc(sqrt(map_size)*sizeof(struct tile_t));
		for(int j=0;j<sqrt(map_size);j++){
			new_map[i][j].value=0;
			new_map[i][j].symbol=' ';
		}
		
	}
	return new_map;
}

void create_map(){
	struct tile_t **map=create_empty_map(map_size);
	int ships[10] = {2, 2, 2, 2, 3, 3, 3, 4, 4, 6};
	int shipcount = 10, currship = 0, flag = 0;
	for(int go=0;go!=4;){
		if(shipcount!=0){
			printf("Place ship - %d(1)\n", shipcount);
		}
		printf("Move ship(2)\nSee board(3)\nReady(4)\n");
		scanf("%d", &go);
		if(go==1 && shipcount!= 0){
			printf("Choose ship type(2,3,4,6)");
			scanf("%d",&currship);
			for(int i=0; i<shipcount-1;i++){
				if(currship==ships[i]){
					ships[i] = 0;
					flag = 1;
					break;
					
				}
			}
			if(flag==0){
				printf("You dont have any of that kind left\n");
			}else{
				flag=0;
				shipcount--;
			}
		}else if(go==2){

		}else if(go==3){
			print_map(map);
		}else if(go!=4){
			printf("Invalid command\n");
		}
	}
}

void load_template(int player){
	struct tile_t  **map=create_empty_map(map_size);
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
	struct tile_t** map=create_empty_map();
	game_start();
}