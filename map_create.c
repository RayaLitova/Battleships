#include "defines.h"

struct ship_t *ships_A;
struct ship_t *ships_B;
int sizeA=0, sizeB=0;
int pl;
const int ship_count=10;


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
		if(*direction!='d' && *direction!='u' && *direction!='l' && *direction!='r') printf("No such direction\n");
	}while(*direction!='d' && *direction!='u' && *direction!='l' && *direction!='r');
}

void ships_change(int x, int y, int type, int endx, int endy, char direction){
    if(pl==1){
        ships_A[sizeA].startx=x;
        ships_A[sizeA].starty=y;
        ships_A[sizeA].endx=endx;
        ships_A[sizeA].endy=endy;
        ships_A[sizeA].type=type;
        ships_A[sizeA].hit=0;
        ships_A[sizeA].direction=direction;
        sizeA++;
    }else{
        ships_B[sizeB].startx=x;
        ships_B[sizeB].starty=y;
        ships_B[sizeB].endx=endx;
        ships_B[sizeB].endy=endy;
        ships_B[sizeB].type=type;
        ships_B[sizeB].hit=0;
        ships_B[sizeB].direction=direction;
        sizeB++;
    }

}

int is_suitable(int x, int y, char direction, int type, struct tile_t** map ){
	int chy, chx, maxY, maxX;
	if((direction=='r'&& x>9-type+1)||(direction=='l'&& x<0+type-1)||(direction=='u'&& y<0+type-1)||(direction=='d'&& y>9-type+1)) {
		printf("You going out of course! Redirect the ship!\n");
		return 0;
	}
	if(direction=='r'){
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
					printf("Ships too close to each other, they might crash. Please redirect. \n");
					return 0;
				}
			}
			if(y==0||y==9)chy=y;
			else chy=y-1;
		}
	}
	if(direction=='l'){
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
					printf("Ships too close to each other, they might crash. Please redirect. \n");
					return 0;
				}
			}
			if(y==0)chy=y;
			else chy=y-1;
		}
	}
	if(direction=='d'){
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
					printf("Ships too close to each other, they might crash. Please redirect. \n");
					return 0;
				}
			}
			if(y==0)chy=y;
			else chy=y-1;
		}
	}
	if(direction=='u'){
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
					printf("Ships too close to each other, they might crash. Please redirect. \n");
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
    if(direction=='r'){
        for(int chx=x;chx<x+type;chx++){
            map[y][chx].value=type;
            map[y][chx].symbol='X';
        }
        ships_change(x,y,type,x+type-1,y,direction);
    }
    if(direction=='l'){
        for(int chx=x;chx>x-type;chx--){
            map[y][chx].value=type;
            map[y][chx].symbol='X';
        }
        ships_change(x,y,type,x-type-1,y,direction);
    }
    if(direction=='d'){
        for(int chy=y;chy<y+type;chy++){
            map[chy][x].value=type;
            map[chy][x].symbol='X';
        }
        ships_change(x,y,type,x,y+type-1,direction);
    }
    if(direction=='u'){
        for(int chy=y;chy>y-type;chy--){
            map[chy][x].value=type;
            map[chy][x].symbol='X';
        }
        ships_change(x,y,type,x,y-type-1,direction);
    }
}

void delete_ship(int x, int y, struct tile_t** map){
	int type = map[y][x].value;
	if(x!=9){
		if(map[y][x+1].value!=0){
			for(int hx=x;hx<x+type;hx++){
				map[y][hx].value = 0;
				map[y][hx].symbol=' ';
			}
		}
	}
	if(x!=0){
		if(map[y][x-1].value!=0){
			for(int hx=x;hx>x-type;hx--){
				map[y][hx].value = 0;
				map[y][hx].symbol=' ';
			}
		}
	}
	if(y!=9){
		if(map[y+1][x].value!=0){
			for(int hy=y;hy<y+type;hy++){
				map[hy][x].value = 0;
				map[hy][x].symbol=' ';
			}
		}
	}
	if(y!=0){
		if(map[y-1][x].value!=0){
			for(int hy=y;hy>y-type;hy--){
				map[hy][x].value = 0;
				map[hy][x].symbol=' ';
			}
		}
	}
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
	ships_A=malloc(ship_count*sizeof(struct ship_t));
	ships_B=malloc(ship_count*sizeof(struct ship_t));
	struct tile_t **map=create_empty_map();
	int ships[10] = {2, 2, 2, 2, 3, 3, 3, 4, 4, 6};
	int shipcount = 10, currship = 0, flag = 0, x=0, y=0, deffence=0;
	char direction;
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
				if(currship==ships[i]){
					flag = 1;
					break;
				}
			}
			if(flag==0||currship==0){
				printf("You dont have any of that kind left!\n");
			}else{
				position_ship(&x,&y,&direction);
				if(is_suitable(x,y,direction,currship,map)== 0) goto reposition;
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
			if(is_suitable(trX,trY,direction,map[y][x].value,map)== 0) goto reposition;
			else place_ship(trX,trY,direction,map[y][x].value,map);
			delete_ship(x,y,map);

		}else if(go==3){
			print_map(map);
		}else if(go!=4){
			printf("Invalid command!\n");
		}
	}
	
	return map;
}
