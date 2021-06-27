#include "defines.h"


struct ship_t ships_A[10];
struct ship_t ships_B[10];
int sizeA=0, sizeB=0;
int pl;
const int ship_count=10;

void fill_ships(int player){
	pl=player;
	for(int i=0; i<10; i++){
		if(player==1) ships_A[i].type=1;
		else ships_B[i].type=1;
	}
}

void print_map(struct tile_t** map){
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

void position_ship(int* x, int* y, char* direction){
	do{
		printf("Choose position(A1,B2,..) ");
		char help_c;
		scanf(" %c", &help_c);
		if(help_c>96) *x = help_c-97;
		else *x = help_c-65;
		scanf("%d", y);
		*y-=1;
		if(*x<0||*x>9) printf("No such x\n");
		if(*y<0||*y>9) printf("No such y\n");
	}
	while(*y<0||*y>9||*x<0||*x>9);
	do{
		printf("Choose direction Up(u), Down(d), Left(l), Right(r) ");
		scanf(" %c", direction);
		if(*direction!='d' && *direction!='D'&& *direction!='u' && *direction!='U' && *direction!='l' && *direction!='L' && *direction!='r' && *direction!='R') printf("No such direction\n");
	}while(*direction!='d' && *direction!='D'&& *direction!='u' && *direction!='U' && *direction!='l' && *direction!='L' && *direction!='r' && *direction!='R');
}

void ships_change(int x, int y, int type, int endx, int endy, char direction){
    if(pl==1){
		for(int i=0; i<ship_count; i++ ){
			if(ships_A[i].type==1){
				ships_A[i].startx=x;
				ships_A[i].starty=y;
				ships_A[i].endx=endx;
				ships_A[i].endy=endy;
				ships_A[i].type=type;
				ships_A[i].check_type=type;
				ships_A[i].hit=0;
				ships_A[i].direction=direction;
				sizeA++;
				break;
			}
		}
    }else{
		for(int i=0; i<ship_count; i++ ){
			if(ships_B[i].type==1){
				ships_B[i].startx=x;
				ships_B[i].starty=y;
				ships_B[i].endx=endx;
				ships_B[i].endy=endy;
				ships_B[i].type=type;
				ships_B[i].check_type=type;
				ships_B[i].hit=0;
				ships_B[i].direction=direction;
				sizeB++;
				break;
			}
		}
    }

}

int is_suitable(int x, int y, char direction, int type, struct tile_t** map, int random_flag ){
	int chy, chx, maxY, maxX;
	if(((direction=='r'||direction == 'R')&& x>9-type+1)||((direction=='l'||direction=='L')&& x<0+type-1)||((direction=='u'||direction=='U')&& y<0+type-1)||((direction=='d'||direction=='D')&& y>9-type+1)) {
		if(random_flag==0){printf("You going out of course! Redirect the ship!\n");}
		return 0;
	}
	if(direction=='r'||direction == 'R'){
		if(x==0)chx=x;
		else chx=x-1;
		if(y==0)chy=y;
		else chy=y-1;
		if(x+type+1>10)maxX=10;
		else maxX = x+type+1;
		if(y+2>10)maxY=10;
		else maxY = y+2;
		for(;chx<maxX;chx++){
			for(;chy<maxY;chy++){
				if(map[chy][chx].value!=0){
					if(random_flag==0){printf("Ships too close to each other, they might crash. Please redirect. \n");}
					return 0;
				}
			}
			if(y==0)chy=y;
			else chy=y-1;
		}
	}
	if(direction=='l'||direction=='L'){
		if(x==9)chx=x;
		else chx=x+1;
		if(y==0)chy=y;
		else chy=y-1;
		if(x-type-1<-1)maxX=-1;
		else maxX = x-type-1;
		if(y+2>10)maxY=10;
		else maxY = y+2;
		for(;chx>maxX;chx--){
			for(;chy<maxY;chy++){
				if(map[chy][chx].value!=0){
					if(random_flag==0){printf("Ships too close to each other, they might crash. Please redirect. \n");}
					return 0;
				}
			}
			if(y==0)chy=y;
			else chy=y-1;
		}
	}
	if(direction=='d'||direction=='D'){
		if(x==0)chx=x;
		else chx=x-1;
		if(y==0)chy=y;
		else chy=y-1;
		if(x+2>10)maxX=10;
		else maxX = x+2;
		if(y+type+1>10)maxY=10;
		else maxY = y+type+1;
		for(;chx<maxX;chx++){
			for(;chy<maxY;chy++){
				if(map[chy][chx].value!=0){
					if(random_flag==0){printf("Ships too close to each other, they might crash. Please redirect. \n");}
					return 0;
				}
			}
			if(y==0)chy=y;
			else chy=y-1;
		}
	}
	if(direction=='u'||direction=='U'){
		if(x==0)chx=x;
		else chx=x-1;
		if(y==9)chy=y;
		else chy=y+1;
		if(x+2>10)maxX=10;
		else maxX = x+2;
		if(y-type-1<-1)maxY=-1;
		else maxY = y-type-1;
		for(;chx<maxX;chx++){
			for(;chy>maxY;chy--){
				if(map[chy][chx].value!=0){
					if(random_flag==0){printf("Ships too close to each other, they might crash. Please redirect. \n");}
					return 0;
				}
			}
			if(y==9)chy=y;
			else chy=y+1;
		}
	}
	return 1;
}

void place_ship(int x, int y, char direction, int type, struct tile_t** map){
    if(direction=='r'||direction == 'R'){
        for(int chx=x;chx<x+type;chx++){
            map[y][chx].value=type;
            map[y][chx].symbol='X';
        }
        ships_change(x,y,type,x+type-1,y,direction);
    }
    if(direction=='l'||direction=='L'){
        for(int chx=x;chx>x-type;chx--){
            map[y][chx].value=type;
            map[y][chx].symbol='X';
        }
        ships_change(x,y,type,x-type+1,y,direction);
    }
    if(direction=='d'||direction=='D'){
        for(int chy=y;chy<y+type;chy++){
            map[chy][x].value=type;
            map[chy][x].symbol='X';
        }
        ships_change(x,y,type,x,y+type-1,direction);
    }
    if(direction=='u'||direction=='U'){
        for(int chy=y;chy>y-type;chy--){
            map[chy][x].value=type;
            map[chy][x].symbol='X';
        }
        ships_change(x,y,type,x,y-type+1,direction);

    }
}

void delete_ship(struct ship_t* ship, struct tile_t** map){
	int type = ship->type;
	if(ship->startx!=9){
		if(map[ship->starty][ship->startx+1].value!=0){
			for(int hx=ship->startx;hx<ship->startx+type;hx++){
				map[ship->starty][hx].value = 0;
				map[ship->starty][hx].symbol=' ';
			}
		}
	}
	if(ship->startx!=0){
		if(map[ship->starty][ship->startx-1].value!=0){
			for(int hx=ship->startx;hx>ship->startx-type;hx--){
				map[ship->starty][hx].value = 0;
				map[ship->starty][hx].symbol=' ';
			}
		}
	}
	if(ship->starty!=9){
		if(map[ship->starty+1][ship->startx].value!=0){
			for(int hy=ship->starty;hy<ship->starty+type;hy++){
				map[hy][ship->startx].value = 0;
				map[hy][ship->startx].symbol=' ';
			}
		}
	}
	if(ship->starty!=0){
		if(map[ship->starty-1][ship->startx].value!=0){
			for(int hy=ship->starty;hy>ship->starty-type;hy--){
				map[hy][ship->startx].value = 0;
				map[hy][ship->startx].symbol=' ';
				
			}
		}
	}
	ship->type =1;
}

int check_ship_a(int x, int y, struct tile_t** map){
	int help=0;
	if(x!=9){
		if(map[y][x+1].value!=0) help++;
	}
	if(x!=0){
		if(map[y][x-1].value!=0) help++;
	}
	if(y!=9){
		if(map[y+1][x].value!=0) help++;
	}
	if(y!=0){
		if(map[y-1][x].value!=0) help++;
	}
	if(help>1) return 0;
	return 1;
}

struct tile_t** create_map(int player){
	pl=player;
	struct tile_t **map=create_empty_map();
	int ships[10] = {2, 2, 2, 2, 3, 3, 3, 4, 4, 6};
	int shipcount = 10, currship = 0, flag = 0, x=0, y=0, deffence=0;
	char direction;
	fill_ships(player);


	for(int go=0;go!=4;){
		reposition:
		if(shipcount!=0){
			printf("\nPlace ship - %d (1)\n", shipcount);
		}
		printf("Move ship(2)\nSee board(3)\n");
		if(shipcount==0){
			printf("Ready(4)\n");
			deffence = 1;
		}
		scanf("%d", &go);
		if(go==4 && deffence!=1){
			printf("The board is not ready yet\n");
			goto reposition;
		}
		if(go==1 && shipcount!= 0){
			printf("Choose ship type(2,3,4,6) ");
			scanf("%d",&currship);
			for(int i=0; i<10;i++){
				if(currship==ships[i]&&currship!=1){
					flag = 1;
					break;
				}
			}
			if(flag==0||currship==0){
				printf("You dont have any of that kind left!\n");
			}else{
				position_ship(&x,&y,&direction);
				if(is_suitable(x,y,direction,currship,map, 0)== 0) goto reposition;
				else place_ship(x,y,direction,currship,map);

				for(int i=0; i<10;i++){
					if(currship==ships[i]){
						ships[i] = 0;
						break;
					}
				}
				flag=0;
				shipcount--;
			}
		}else if(go==2){
			int trY, trX;
			printf("Choose ship to move\n");
			do{
				printf("Enter the starting or ending position of a ship(A1,B2,..) ");
				char help_c;
				scanf(" %c", &help_c);
				if(help_c>96) x = help_c-97;
				else x = help_c-65;
				scanf("%d", &y);
				y--;

				if(x<0||x>9) printf("No such x\n");
				if(y<0||y>9)printf("No such y\n");
			}
			while(y<0||y>9||x<0||x>9);
			if(map[y][x].value==0){
				printf("There is no ship at that position. Relocate the ship!\n");
				goto reposition;
			}
			if(check_ship_a(x,y,map)==0){
				printf("Can't maintain a conection with the ship. Reestablish the connection!\n");
				goto reposition;
			}
			printf("Move to: ");
			position_ship(&trX,&trY,&direction);
			struct ship_t* temp_sh = find_ship(x,y, 3-pl);
			
			delete_ship(temp_sh,map);
			
			if(is_suitable(trX,trY,direction,temp_sh->check_type,map, 0)== 0) {
			
				place_ship(x,y,temp_sh->direction,temp_sh->check_type,map);
				goto reposition;
			}
			else place_ship(trX,trY,direction,temp_sh->check_type,map);
			

		}else if(go==3){
			print_map(map);
			
		}else if(go!=4){
			printf("Invalid command!\n");
		}
	}

	return map;
}


struct tile_t** random_map(int player,int mode){
	pl = player;
	struct tile_t **map=create_empty_map();
	fill_ships(player);
	printf("Generating random map, please wait\n");
	int x, y, dir, shipcount = 10, currship = 9, emergency_reset = 0;
	char directions_help [5] = {'l', 'r', 'u', 'd'};
	int ships[10] = {2, 2, 2, 2, 3, 3, 3, 4, 4, 6};
	srand(time(NULL));
	while (shipcount>0){
		x = rand() % 10;
		y = rand() % 10;
		dir = rand() % 4;
		if(is_suitable(x, y, directions_help[dir], ships[currship], map, 1)==1){
			place_ship(x, y, directions_help[dir], ships[currship], map);
			shipcount --;
			currship--;
			}
		if(emergency_reset > 5000){break;}
		emergency_reset ++;
	}
	if (emergency_reset>5000){
		random_map(player, mode);
		return create_empty_map();
	}
	if(pl!=2 || mode!=1){print_map(map);}

	return map;
}
