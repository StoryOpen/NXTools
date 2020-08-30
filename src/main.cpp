#include <iostream>
#include <string>
#include <nlnx/nx.hpp>
#include <nlnx/node.hpp>
#include <nlnx/bitmap.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdint.h>

void recurse(nl::node node, std::string nn)
{
    for (auto n = node.begin(); n != node.end(); n++)
    {
        if (n.data_type() == nl::node::type::bitmap)
        {
            auto bm = n.get_bitmap();
            auto data = reinterpret_cast<uint8_t *>(const_cast<void *>(bm.data()));
            int bytes = bm.width() * bm.height() * 4;
            for (int i = 0; i < bytes; i += 4)
            {
                uint8_t blue = data[i];
                data[i] = data[i + 2];
                data[i + 2] = blue;
            }

            stbi_write_png(
                (nn + std::string("-") + n.name() + std::string(".png")).c_str(),
                bm.width(), bm.height(), 4, data, bm.width() * 4);
        }
        recurse(n, nn + std::string("-") + node.name());
    }
}

int main(int argc, char const *argv[], char *envp[])
{
    nl::nx::load_all();
    std::string file(argv[1]);
    nl::node node;
    if (file == "map")
    {
        node = nl::nx::map;
    }
    else if (file == "ui")
    {
        node = nl::nx::ui;
    }
    else if (file == "mob")
    {
        node = nl::nx::mob;
    }
    else if (file == "skill")
    {
        node = nl::nx::skill;
    }
    else if (file == "npc")
    {
        node = nl::nx::npc;
    }
    else if (file == "quest")
    {
        node = nl::nx::quest;
    }
    else if (file == "morph")
    {
        node = nl::nx::morph;
    }
    else if (file == "effect")
    {
        node = nl::nx::effect;
    }
    else if (file == "character")
    {
        node = nl::nx::character;
    }
    else
    {
        std::cout << argv[1] << " is not a valid file." << std::endl;
        return 1;
    }

    nl::node searchnode = node.resolve(argv[2]);

    if(searchnode.size() == 0){
        std::cout << argv[2] << " in " << argv[1] << " not found." << std::endl;
        return 1;
    }

    recurse(searchnode, searchnode.name());
    return 0;
}