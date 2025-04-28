/*
#############################################################################
#
# Copyright  2024 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/
// RGB color arrays created using "I Want Hue" tool : 
// https://medialab.github.io/iwanthue/
//
#ifndef RGB_COLOR_ARRAYS_
#define RGB_COLOR_ARRAYS_
class rgbColorArrays
{
public :
static const std::vector<std::vector<double>> rgb10;
static const std::vector<std::vector<double>> rgb15;
static const std::vector<std::vector<double>> rgb20;
static const std::vector<std::vector<double>> rgb40;
};


const std::vector<std::vector<double>> rgbColorArrays::rgb10 =
{{129,63,58},{80,106,54},{92,102,163},{139,73,200},{189,65,136},
{213,88,63},{201,139,181},{94,173,168},{190,157,74},{102,184,79}};

const std::vector<std::vector<double>> rgbColorArrays::rgb15 =
{{193,149,103},{91,68,193},{92,189,67},{189,76,215},{214,78,161},
{104,190,141},{209,64,85},{212,86,46},{151,140,215},{204,147,49},
{118,55,129},{96,128,50},{69,80,132},{65,79,34},{74,132,106}};

const std::vector<std::vector<double>> rgbColorArrays::rgb20 =
{{38,47,0},  {103,0,1},    {1,48,158},   {97,0,161},   {0,96,45},
{166,0,119}, {0,103,86},   {58,125,0},   {1,121,191},  {222,57,0},
{255,0,63},  {128,143,0},  {255,60,131}, {195,168,0},  {0,209,83},
{255,160,57},{213,169,255},{100,208,255},{124,218,147},{251,184,136}};

const std::vector<std::vector<double>> rgbColorArrays::rgb40 =
{{101,39,47},{101,35,107},{73,37,153},{57,55,130},{45,72,30},
{102,67,35},{146,49,34},{96,47,202},{127,71,164},{169,53,149},
{83,113,33},{106,92,227},{59,124,108},{149,108,46},{171,64,218},
{212,57,84},{165,100,99},{99,126,78},{227,58,40},{97,117,221},
{80,131,168},{209,95,41},{228,67,138},{216,80,217},{154,127,202},
{182,115,224},{112,158,61},{205,118,173},{94,153,224},{73,183,69},
{78,184,116},{220,150,54},{88,182,205},{207,162,117},{156,179,117},
{186,173,56},{93,188,163},{180,165,217},{144,190,55},{83,209,49}};
#endif


