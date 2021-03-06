#include "NMloader.h"
#include <array>
#include <glew.h>
#include <math.h>

const int HEADER_OFFSETS_SIZE = 4;
std::vector<float> NMloader::readFloatArray(std::ifstream& file, int offsets)
{
    std::vector<float> values;
    for (int j = 0; j < offsets; j++) {
        char bytes[sizeof(float)];
        for (int i = 0; i < sizeof(float); i++)
            bytes[i] = file.get();
        if (!isnan(*reinterpret_cast<float*>(bytes))) {
            values.push_back(*reinterpret_cast<float*>(bytes));
        }
    }

    return values;
}

std::vector<int> NMloader::readIntArray(std::ifstream& file, int offsets)
{
    std::vector<int> values;
    for (int j = 0; j < offsets; j++) {
        char bytes[sizeof(int)];
        for (int i = 0; i < sizeof(int); i++)
            bytes[i] = file.get();
        int potential_nbr = *reinterpret_cast<int*>(bytes);
        if (potential_nbr != -1) {
            values.push_back(*reinterpret_cast<int*>(bytes));
        }
    }
    return values;
}

std::vector<int> NMloader::parseHeaders(std::ifstream& file)
{
    std::vector<int> values;
    for (int j = 0; j < HEADER_OFFSETS_SIZE; j++) {
        char bytes[sizeof(int)];
        for (int i = 0; i < sizeof(int); i++)
            bytes[i] = file.get();

        int potential_nbr = *reinterpret_cast<int*>(bytes);


        if (potential_nbr != -1) {
            values.push_back(*reinterpret_cast<int*>(bytes));
        }
    }
    return values;
}

RawModel* NMloader::loadNMmodel(const char* filePath, Loader* loader)
{
    std::ifstream file;
    file.open(filePath, std::ifstream::in | std::ifstream::binary);
    std::vector<int> headers = parseHeaders(file);
    std::vector<float> positions = readFloatArray(file, headers.at(0));
    std::vector<float> UV = readFloatArray(file, headers.at(1));
    std::vector<int> indices = readIntArray(file, headers.at(2));
    std::vector<float> normals = readFloatArray(file, headers.at(3));

    file.close();

    return loader->loadToVAO(&positions, &UV, &normals, &indices);
}
