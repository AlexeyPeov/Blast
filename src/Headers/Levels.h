#ifndef LEVELS_H
#define LEVELS_H

const int level_1_width = 40;
const int level_1_height = 20;

const int level_2_width = 15;
const int level_2_height = 15;

const int level_3_width = 40;
const int level_3_height = 20;

const int dust_3_height = 50;
const int dust_3_width = 50;

const int dust_3_a_width = 31;
const int dust_3_a_height = 50;


const int level_1[800] = {
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,2,
        2,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,2,
        2,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,2,
        2,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,
        2,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,
        2,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,
        2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,2,
        2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,2,
        2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,


};
const int level_2[15 * 15] = {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2,
        2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 2,
        2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 2,
        2, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2,
        2, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2,
        2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        2, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        2, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 2,
        2, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

const int dust_3[50 * 50] = {
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,0,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,0,0,0,0,0,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,2,2,2,
        2,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,
        2,2,2,2,0,0,0,0,0,2,0,0,2,2,0,0,2,2,0,0,0,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,
        2,2,2,2,2,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,
        2,2,2,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,
        2,2,2,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,
        2,2,2,0,0,0,0,0,0,0,0,0,2,2,0,0,2,0,0,2,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,
        2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,0,2,2,
        2,2,2,0,0,0,0,0,0,0,2,0,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,
        2,2,2,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,
        2,2,2,2,2,0,2,2,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,
        2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,
        2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,0,0,2,2,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,
        2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,
        2,2,2,0,2,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,
        2,2,2,0,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,0,0,2,2,0,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,2,2,2,0,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,
        2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,
        2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,
        2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,0,2,2,2,0,0,0,2,0,2,0,0,0,2,2,2,
        2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,2,2,2,0,0,0,2,0,0,0,0,0,2,2,2,
        2,2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,2,2,2,
        2,2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,0,0,0,0,0,2,2,2,
        2,2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,0,0,0,0,0,2,2,2,
        2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,0,0,2,0,2,2,2,0,0,0,2,2,2,2,2,2,2,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,2,0,0,2,2,2,0,0,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,1,2,2,2,2,2,0,0,0,0,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,2,2,2,2,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,

};


const int dust_3_a[31 * 50] = {
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,0,0,2,2,2,0,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,0,0,2,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,2,2,2,
        2,2,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,
        2,0,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,
        2,0,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,
        2,0,0,0,0,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,
        2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,2,
        2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,
        2,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,
        2,2,0,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,0,2,2,
        2,2,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,
        2,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,
        2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,
        2,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,
        2,2,2,0,0,2,2,0,0,2,2,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,0,0,2,2,0,0,0,0,0,0,0,2,2,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,
        2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,0,2,2,2,0,0,0,2,0,2,0,0,0,2,2,2,
        2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,0,2,2,2,0,0,0,2,0,0,0,0,0,2,2,2,
        2,2,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,2,2,2,
        2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,0,0,0,0,0,2,2,2,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,0,0,0,0,0,2,2,2,
        2,0,0,0,2,2,2,2,2,2,0,0,0,0,2,0,2,2,2,0,0,0,2,2,2,2,2,2,2,3,3,
        2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,3,3,3,3,3,3,3,3,3,
        2,2,2,0,2,2,2,2,2,2,2,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,1,2,2,2,2,2,0,0,0,0,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,0,0,2,2,2,2,0,0,0,0,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,2,2,2,2,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        2,3,3,3,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,

};

//int level_2[800] = {
//        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
//        2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,
//        2,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0,0,2,
//        2,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,
//        2,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,2,
//        2,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,2,
//        2,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,2,
//        2,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,
//        2,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,2,
//        2,0,0,1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,2,
//        2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,2,
//        2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,0,2,
//        2,0,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,2,
//        2,0,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,0,1,0,2,
//        2,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,2,
//        2,1,0,1,0,1,1,1,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,2,
//        2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,0,0,1,1,0,0,0,0,1,0,2,
//        2,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
//        2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,2,
//        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
//
//
//};
const int level_3[800] = {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2,
        2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        1, 0, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2,


};
#endif