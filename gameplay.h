#ifndef GAMEPLAY_H
#define GAMEPLAY_H

struct tile_t** surround_ship(int x, int y, char direction, int type, struct tile_t** map);

int check_ship(int x, int y);

struct ship_t *find_ship(int x, int y);

void play();

void fire_last();

void fire();

void spec_pos();

void hard_mode();

void easy_mode();

#endif
