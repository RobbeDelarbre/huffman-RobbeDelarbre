#ifndef TEST_BUILD

/*
*   This file is only active in non-test builds (i.e., builds where TEST_BUILD is not defined).
*/

#include <iostream>
#include <io/files.h>
#include <stdio.h>
#include <util.h>
#include <memory>
#include <io/memory-buffer.h>
#include <io/streams.h>
#include <encoding/encoding.h>
#include <encoding/eof-encoding.h>
#include <encoding/bit-grouper.h>
#include <encoding/encoding-combiner.h>
#include <io/binary-io.h>
#include <data/binary-tree.h>
#include <data/frequency-table.h>
#include <encoding/huffman/tree-encoding.h>
#include <encoding/huffman/huffman-encoding.h>
#include <algorithm>

/*
* This is the main entry point of your application.
* Note that it will only work in non-test builds.
*/
int main(int argc, char* argv[])
{
#ifdef NDEBUG
    std::cout << "You are running the release build" << std::endl;
    const std::string mode = argv[2];
    const std::string inputfile = argv[3];
    const std::string outputfile = argv[4];

    if (mode == "compress")
    {
        std::cout << "compressing " + inputfile << std::endl;

        encoding::Encoding<256, 257> eof = encoding::eof_encoding<256>();
        encoding::Encoding<257, 2> huffman = encoding::huffman::huffman_encoding<257>();
        encoding::Encoding<2, 256> grouper = encoding::bit_grouper<8>();

        auto combiner = eof | huffman | grouper;

        encode(io::create_file_data_source(inputfile), combiner, io::create_file_data_destination(outputfile));


        std::cout << "done" << std::endl;
    }
    else if (mode == "decompress")
    {
        std::cout << "compressing " + inputfile << std::endl;

        encoding::Encoding<256, 257> eof = encoding::eof_encoding<256>();
        encoding::Encoding<257, 2> huffman = encoding::huffman::huffman_encoding<257>();
        encoding::Encoding<2, 256> grouper = encoding::bit_grouper<8>();

        auto combiner = eof | huffman | grouper;

        decode(io::create_file_data_source(inputfile), combiner, io::create_file_data_destination(outputfile));

        std::cout << "done" << std::endl;
    }
    return 0; 
#else
    std::cout << "You are running the debug build" << std::endl;
#endif
}

#endif