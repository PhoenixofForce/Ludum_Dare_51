#include "maploader.h"

void loadTileLayer(IDMapper mapper, const std::string& line, TileLayer tileLayer);
void loadFreeLayer(IDMapper mapper, const std::string& line, FreeLayer freeLayer);
void loadAreaLayer(const std::string& line, AreaLayer areaLayer);
void splitAtSemicolon(std::vector<std::string>& out, const std::string& line);
Tag parseStringAsTag(const std::string& line);

void loadMap(const std::string& file, MapSettings mapSettings, TileLayer tileLayer, FreeLayer freeLayer, AreaLayer areaLayer) {
    std::ifstream f{};
    f.open(file);

    if(f.fail()) {
        std::cerr << "Map \"" << file << "\" could not be opened" << std::endl;
        return;
    }
    std::cout << "Loading map \"" << file << "\"" << std::endl;

    std::string line{};
    std::getline(f, line);

    //Load tileSize and mapTags
    std::cout << " 1/5 loading map settings" << std::endl;

    int tileSize{};
    std::vector<Tag> mapTags{};

    std::vector<std::string> lineContents{};
    splitAtSemicolon(lineContents, line);

    tileSize = std::stoi(lineContents.at(0));
    for(int i = 1; i < lineContents.size(); i++) {
        mapTags.push_back(parseStringAsTag(lineContents.at(i)));
    }
    mapSettings(tileSize, mapTags);

    //Load IDMapper
    std::cout << " 2/5 loading texture replacements" << std::endl;

    std::getline(f, line);
    IDMapper mapper{};

    while(line.find("#") == 0) {
        int id = std::stoi(line.substr(1, line.find(" - ") - 1));
        std::string textureName = line.substr(line.find(" - ") + 3);
        mapper[id] = textureName;

        std::getline(f, line);
    }

    //Tiles
    std::cout << " 3/5 loading tile layer" << std::endl;

    while(line.find("[layer") == 0) {
        loadTileLayer(mapper, line, tileLayer);
        std::getline(f, line);
    }

    //Objects
    std::cout << " 4/5 loading free layer" << std::endl;

    while(line.find("[put") == 0) {
        loadFreeLayer(mapper, line, freeLayer);
        std::getline(f, line);
    }

    //Areas
    std::cout << " 5/5 loading area layer" << std::endl;

    while(line.size() > 0 && line.find("[area") == 0) {
        loadAreaLayer(line, areaLayer);
        std::getline(f, line);
    }

    f.close();
}

void loadTileLayer(IDMapper mapper, const std::string& line, TileLayer tileLayer) {
    std::vector<std::string> lineContents{};
    splitAtSemicolon(lineContents, line.substr(1, line.length() - 2));

    float depth = std::stof(lineContents.at(1));
    int width = std::stoi(lineContents.at(2));
    int height = std::stoi(lineContents.at(3));

    Matrix_m<int> map(width, height);
    for(int x = 0; x < width; x++) {
        std::string& column{ lineContents.at(x + 4) };
        int y = 0;

        size_t pos = 0;
        std::string token;
        while((pos = column.find(",")) != std::string::npos) {
            token = trim(column.substr(0, pos));
            column.erase(0, pos + 1);

            map.set(x, y, std::stoi(token));

            y++;
        }
    }

    tileLayer(mapper, depth, map);
}

void loadFreeLayer(IDMapper mapper, const std::string& line, FreeLayer freeLayer) {
    std::vector<std::string> lineContents{};
    splitAtSemicolon(lineContents, line.substr(1, line.length() - 2));

    float depth = std::stof(lineContents.at(1));
    int texture = std::stoi(lineContents.at(2));
    float x = std::stof(lineContents.at(3));
    float y = std::stof(lineContents.at(4));

    std::vector<Tag> tags{};
    for(int i = 5; i < lineContents.size(); i++) {
        tags.push_back(parseStringAsTag(lineContents.at(i)));
    }

    freeLayer(mapper, depth, texture, x, y, tags);
}

void loadAreaLayer(const std::string& line, AreaLayer areaLayer) {
    std::vector<std::string> lineContents{};
    splitAtSemicolon(lineContents, line.substr(1, line.length() - 2));

    float x1 = std::stof(lineContents.at(1));
    float y1 = std::stof(lineContents.at(2));
    float x2 = std::stof(lineContents.at(3));
    float y2 = std::stof(lineContents.at(4));

    std::vector<Tag> tags{};
    for(int i = 5; i < lineContents.size(); i++) {
        tags.push_back(parseStringAsTag(lineContents.at(i)));
    }

    areaLayer(x1, y1, x2, y2, tags);
}

void splitAtSemicolon(std::vector<std::string>& out, const std::string& line) {
    std::string currentString{""};
    int escapeLevel = 0;
    
    for(char c: line) {
        if(c == '[') escapeLevel++;
        if(c == ']') escapeLevel--;
        if(c == ';' && escapeLevel == 0) {
            out.push_back(trim(currentString));
            currentString = "";
            continue;
        }

        currentString += c;
    }
    
    currentString = trim(currentString);
    if(currentString.length() > 0) out.push_back(currentString);
}

Tag parseStringAsTag(const std::string& line) {
    std::vector<std::string> lineContent{};
    splitAtSemicolon(lineContent, line.substr(1, line.length() - 2));

    return {lineContent.at(1), lineContent.at(2)};
}