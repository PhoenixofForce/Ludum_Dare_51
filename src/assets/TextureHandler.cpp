#include "TextureHandler.h"

namespace texture {

	std::map<std::string, SDL_Texture*> textureImages{};
	std::map<std::string, Rect> imageRects{};
	std::map<std::string, std::string> imageSheets{};

	void loadImagePng(SDL_Renderer* renderer, const std::string& fileName, const std::string& internTextureName) {
		SDL_Surface* tmpSurface{ IMG_Load(("res/" + fileName + ".png").c_str()) };
		SDL_Texture* tex{ SDL_CreateTextureFromSurface(renderer, tmpSurface) };
		SDL_FreeSurface(tmpSurface);

		textureImages[internTextureName] = tex;
	}

	void loadSpriteSheetPng(SDL_Renderer* renderer, const std::string& fileName, const std::string& internSheetName) {
		std::cout << "loading " << fileName << std::endl;
		loadImagePng(renderer, fileName, internSheetName);

		std::ifstream f{};
		f.open("res/" + fileName + ".text");
		std::string line{};

		int lineCount = 0;
		while (std::getline(f, line)) {
			if (lineCount > 0) {
				std::string textureName{};
				int x = 0,
					y = 0, 
					w = 0, 
					h = 0;

				int splitCounter = 0;
				std::string linePart{};

				std::istringstream iss(line);
				while (std::getline(iss, linePart, ' ')) {
					if (splitCounter == 0) {
						textureName = internSheetName + "_" + linePart;
					} 
					else if (splitCounter == 1) {
						x = std::stoi(linePart);
					}
					else if (splitCounter == 2) {
						y = std::stoi(linePart);
					}
					else if (splitCounter == 3) {
						w = std::stoi(linePart);
					}
					else if (splitCounter == 4) {
						h = std::stoi(linePart);
					}

					splitCounter++;
				}

				imageSheets[textureName] = internSheetName;
				imageRects[textureName] = Rect{ x, y, w, h };
			}
			
			lineCount++;
		}
	}

	const Rect& getSpriteSheetBounds(const std::string& textureName) {
		return imageRects[textureName];
	}

	SDL_Texture* getSpriteSheet(const std::string& textureName) {
		if (imageSheets.find(textureName) != imageSheets.end()) {
			return textureImages[imageSheets[textureName]];
		}
		return textureImages[textureName];
	}

	void deleteAll() {
		for(std::map<std::string, SDL_Texture*>::iterator iter = textureImages.begin(); iter != textureImages.end(); ++iter) {
			SDL_Texture* texture = iter->second;
			SDL_DestroyTexture(texture);
		}
		textureImages.clear();
		imageRects.clear();
		imageSheets.clear();
	}

	void deleteSheet(const std::string& sheetName) {
		std::cout << "unloading " << sheetName << std::endl;

		SDL_DestroyTexture(textureImages[sheetName]);
		textureImages.erase(sheetName);

		for(std::map<std::string, std::string>::iterator iter = imageSheets.begin(); iter != imageSheets.end(); ++iter) {
			if(iter->second == sheetName) {
				imageSheets.erase(iter->first);
				imageRects.erase(iter->first);
			}	
		}
	}

	int getTextureCount(const std::string& substring) {
		int out = 0;
		for(std::map<std::string, std::string>::iterator iter = imageSheets.begin(); iter != imageSheets.end(); ++iter) {
			if(iter->first.find(substring) != std::string::npos) out++;
		}
		return out;
	}
}