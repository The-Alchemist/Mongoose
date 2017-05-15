/**
 * Graph data structure.
 *
 * Stores graph adjacency and weight information. Also used as a container for
 * storing information about matching, coarsening, and partitioning.
 */

#ifndef Mongoose_Graph_hpp
#define Mongoose_Graph_hpp

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

class Graph
{
public:
    /** CSparse3 Interoperability ********************************************/
    Int cs_n;                            /** # columns                       */
    Int cs_m;                            /** # rows                          */
    Int cs_nz;                           /** # triplet entries or -1         */
    Int cs_nzmax;                        /** max # nonzeros                  */

    /** Graph Data ***********************************************************/
    Int n;                               /** # vertices                      */
    Int nz;                              /** # edges                         */
    Int *p;                              /** Column pointers                 */
    Int *i;                              /** Row indices                     */
    double *x;                           /** Edge weight                     */
    double *w;                           /** Node weight                     */
    double X;                            /** Sum of edge weights             */
    double W;                            /** Sum of node weights             */

    double H;                            /** Heuristic max penalty to assess */

    /** Partition Data *******************************************************/
    bool *partition;                     /** T/F denoting partition side     */
    double *vertexGains;                 /** Gains for each vertex           */
    Int *externalDegree;                 /** # edges lying across the cut    */
    Int *bhIndex;                        /** Index+1 of a vertex in the heap */
    Int *bhHeap[2];                      /** Heap data structure organized by
                                            boundaryGains descending         */
    Int bhSize[2];                       /** Size of the boundary heap       */

    /** Cut Cost Metrics *****************************************************/
    double heuCost;                      /** cutCost + balance penalty       */
    double cutCost;                      /** Sum of edge weights in cut set  */
    double W0;                           /** Sum of partition 0 node weights */
    double W1;                           /** Sum of partition 1 node weights */
    double imbalance;                    /** Degree to which the partitioning
                                             is imbalanced, and this is
                                             computed as (0.5 - W0/W).       */

    /** Matching Data ********************************************************/
    Graph *parent;                       /** Link to the parent graph        */
    Int clevel;                          /** Coarsening level for this graph */
    Int cn;                              /** # vertices in coarse graph      */
    Int *matching;                       /** Linked List of matched vertices */
    Int *matchmap;                       /** Map from fine to coarse vertices */
    Int *invmatchmap;                    /** Map from coarse to fine vertices */
    Int *matchtype;                      /** Vertex's match classification
                                              0: Orphan
                                              1: Standard (random, hem, shem)
                                              2: Brotherly
                                              3: Community                   */

    /** Mark Data ************************************************************/
    Int *mark;                           /** O(n) mark array                 */
    Int markValue;                       /** Mark array can be cleared in O(k)
                                             by incrementing markValue.
                                             Implicitly, a mark value less than
                                             markValue is unmarked.          */

    /* Constructor & Destructor */
    Graph();
    static Graph *Create (const Int _n, const Int _nz);
    static Graph *Create (Graph *_parent);
    ~Graph();
};

void resetMarkArray(Int *mark, Int n);

} // end namespace Mongoose

/* Mongoose graph-related macros */
#ifndef MONGOOSE_MARKED
#define MONGOOSE_MARKED(a)   (mark[(a)] == markValue)
#endif

#ifndef MONGOOSE_MARK
#define MONGOOSE_MARK(a)     (mark[(a)] = markValue);
#endif

#ifndef MONGOOSE_CLEAR_ALL_MARKS
#define MONGOOSE_CLEAR_ALL_MARKS(n)    if (++markValue < 0) { markValue = 1; resetMarkArray(mark, (n)); }
#endif

#endif
