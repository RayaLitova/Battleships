#include "defines.h"

 
extern struct tile_t **map_A_base;
extern struct tile_t **map_B_base;
extern struct ship_t *ships_A;
extern struct ship_t *ships_B;
extern int pl;

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
	if(diff>4 || diff<1){
		choose_difficulty();
	}
}


struct tile_t** load_template(int player){
	struct tile_t  **map=create_empty_map();
	//load from {player} file
}
struct tile_t** random_map(player){
	pl = player;
	ships_A=malloc(10*sizeof(struct ship_t));
	ships_B=malloc(10*sizeof(struct ship_t));
	struct tile_t **map=create_empty_map();
	printf("Generating random map, please wait\n");
	int x, y, dir, shipcount = 10, currship = 9, emergency_reset = 0;
	char directions_help [5] = {'l', 'r', 'u', 'd'};
	int ships[10] = {2, 2, 2, 2, 3, 3, 3, 4, 4, 6};
	while (shipcount>0){
		x = rand() % 10;
		y = rand() % 10;
		dir = rand() % 4;
		printf("x=%d y=%d dir=%c\n", x, y, directions_help[dir]);
		if(is_suitable(x, y, directions_help[dir], ships[currship], map)==1){
			place_ship(x, y, directions_help[dir], ships[currship], map);
			shipcount --;
			currship--;
			}
		if(emergency_reset > 5000){break;}
		emergency_reset ++;
	}
	if (emergency_reset>5000){
		return random_map(player);}
	print_map(map);
	return map;
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