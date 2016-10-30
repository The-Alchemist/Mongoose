#include <string>
#include "Mongoose_IO.hpp"
#include "Mongoose_Conditioning.hpp"
#include "Mongoose_EdgeSeparator.hpp"
#include <cassert>
#include "Mongoose_Test.hpp"
#include <iostream>
#include <fstream>

using namespace Mongoose;

void runEdgeSeparatorTest(const std::string inputFile)
{
    Logger::log(Test, "Running Edge Separator Test on " + inputFile);
        
    // Given a symmetric matrix...
    Options *options;
    Graph *G;
    
    options = Options::Create();
    if (!options)
    {
        // Ran out of memory
        Logger::log(Test, "Error creating Options struct in Edge Separator Test");
        SuiteSparse_free(options);
        assert(false);
    }
    
    // Read graph from file
    G = readGraph(inputFile);

    if (!G)
    {
        // Ran out of memory
        Logger::log(Test, "Error reading Graph from file in Edge Separator Test");
        SuiteSparse_free(options);
        SuiteSparse_free(G);
        assert(false);
    }

    // An edge separator should be computed with default options
    int error = ComputeEdgeSeparator(G, options);

    if (error)
    {
        // Error occurred
        Logger::log(Test, "Error computing edge separator in Edge Separator Test");
        assert(false);
    }
    else
    {
        // The graph should be partitioned
        assert (G->partition != NULL);
        for (int i = 0; i < G->n; i++)
        {
            bool equals_0 = (G->partition[i] == 0);
            bool equals_1 = (G->partition[i] == 1);
            assert(equals_0 != equals_1);
        }
    }

    G->~Graph();
    SuiteSparse_free(G);
    SuiteSparse_free(options);

    Logger::log(Test, "Edge Separator Test Completed Successfully");
}