#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>

#include "tag.h"
#include "../../util/structs/matrix.h"
#include "../../util/stringUtils.h"


using IDMapper = std::map<int, std::string>;
using MapSettings = std::function<void(int, std::vector<Tag>)>;
using TileLayer = std::function<void(IDMapper, float, Matrix<int>)>;
using FreeLayer = std::function<void(IDMapper, float, int, float, float, std::vector<Tag>)>;
using AreaLayer = std::function<void(float, float,  float, float, std::vector<Tag>)>;

void loadMap(const std::string& file, MapSettings mapSettings, TileLayer tileLayer, FreeLayer freeLayer, AreaLayer areaLayer);

#endif