#pragma once
#include <iostream>
#include <fstream>  
#include <vector>
#include "../model/RawModel.h"
#include "./Loader.h"
class NMloader
{
private:
	static std::vector<float> readFloatArray(std::ifstream& file, int offsets);
	static std::vector<int> readIntArray(std::ifstream& file, int offsets);
	static std::vector<int> parseModelHeaders(std::ifstream& file);
	static std::vector<int> parseNoxModelHeaders(std::ifstream& file);

public:
	static std::vector<RawModel*> loadNMmodel(const char* filePath, Loader *loader);
};

