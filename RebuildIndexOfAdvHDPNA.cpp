#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

union binary_size {
    char hex[4];
    unsigned int dec;
};

using stdstr = std::string;
using fileway = std::ios_base;
namespace fs = std::experimental::filesystem;
using fpath = std::experimental::filesystem::v1::path;

void RebuildIndex(stdstr newfolder, fpath subfolder);
int readsize(char* buffer, unsigned int pos);
void writesize(char* buffer, unsigned int pos, int size);
int pnapack(stdstr newFolder);

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "usage: RIOAP [originFolder] [newFolder]" << std::endl;
        return -1;
    }

    for (auto& p : fs::recursive_directory_iterator(argv[1]))
        if (fs::is_directory(p))
            RebuildIndex(argv[2], p.path());
    std::cout << "Successfully Done!" << std::endl;
    getchar();
    return pnapack(argv[2]);
}

void RebuildIndex(stdstr newfolder, fpath subfolder)
{
    // Init loading Data
    char buffer[524288] = { 0 };
    fs::path i_cht = fs::path(subfolder.string() + '\\' + "_cht.bin");
    std::ifstream i_chtfile(i_cht.string() , fileway::binary | fileway::in);
    if (!i_chtfile.is_open())
        return;
    i_chtfile.read(buffer, fs::file_size(i_cht));
    i_chtfile.close();

    // 40bytes per file
    unsigned int pos = 0;
    unsigned int startpos = 0;
    bool fixed = false;
    int index = 0;

    // Load size and write
    int size = 0;
    fs::path newImage;
    binary_size hexsize;
    for (auto& p : fs::recursive_directory_iterator(subfolder))
    {
        // skip _cht.bin
        if (p.path().filename().string().length() > 7)
            continue;

        index = std::stoi(p.path().filename().string().substr(0, 3));
        if (!fixed) {
            while (fs::file_size(p) != readsize(buffer, pos))
            {
                hexsize.dec = readsize(buffer, pos);
                pos += 4;
            }
            startpos = pos - index * 40;
            fixed = true;
        }
        newImage = fs::path(newfolder + '\\' + subfolder.filename().string()
            + '\\' + p.path().filename().string());

        pos = startpos + 40 * index;
        writesize(buffer, pos, fs::file_size(newImage));
        std::cout << "-> Read: " << newImage
            << " size: " << readsize(buffer, pos) << std::endl;
    }
    // save the index
    fs::path o_cht = fs::path(newfolder + '\\' + subfolder.filename().string() + '\\' + "_cht.bin");
    std::ofstream o_chtfile(o_cht.string(), fileway::binary | fileway::out);
    o_chtfile.write(buffer, fs::file_size(i_cht));
    o_chtfile.close();
}

int readsize(char* buffer, unsigned int pos)
{
    binary_size hexsize;
    strncpy(hexsize.hex, buffer + pos, 4);
    return hexsize.dec;
}

void writesize(char* buffer, unsigned int pos, int size)
{
    binary_size hexsize;
    hexsize.dec = size;
    strncpy(buffer + pos, hexsize.hex, 4);
}

int pnapack(stdstr newFolder)
{
    char str[100];
    stdstr temp("ahdprc pna -r ");
    for (auto& p : fs::recursive_directory_iterator(newFolder))
        if (fs::is_directory(p))
        {
            system((temp + p.path().string()).c_str());
            std::cout << temp + p.path().string() << std::endl;
        }
    return 0;
}
