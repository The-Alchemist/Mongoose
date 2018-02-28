/* ========================================================================== */
/* === Include/Mongoose_Options.hpp ========================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library  Copyright (C) 2017-2018,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * -------------------------------------------------------------------------- */

#pragma once

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

struct Options
{
    Int randomSeed;

    /** Coarsening Options ***************************************************/
    Int coarsenLimit;
    MatchingStrategy matchingStrategy;
    bool doCommunityMatching;
    double davisBrotherlyThreshold;

    /** Guess Partitioning Options *******************************************/
    GuessCutType guessCutType; /* The guess cut type to use */

    /** Waterdance Options ***************************************************/
    Int numDances; /* The number of interplays between FM and QP
                      at any one coarsening level. */

    /**** Fidducia-Mattheyes Options *****************************************/
    bool useFM;              /* Flag governing the use of FM               */
    Int fmSearchDepth;       /* The # of non-positive gain move to make    */
    Int fmConsiderCount;     /* The # of heap entries to consider          */
    Int fmMaxNumRefinements; /* Max # of times to run Fiduccia-Mattheyses  */

    /**** Quadratic Programming Options **************************************/
    bool useQPGradProj;         /* Flag governing the use of gradproj       */
    double gradProjTolerance;   /* Convergence tol for projected gradient   */
    Int gradprojIterationLimit; /* Max # of iterations for gradproj         */

    /** Final Partition Target Metrics ***************************************/
    double targetSplit;        /* The desired split ratio (default 50/50)  */
    double softSplitTolerance; /* The allowable soft split tolerance.      */
                               /* Cuts within this tolerance are treated   */
                               /* equally.                                 */

    /* Constructor & Destructor */
    static Options *Create();
    ~Options();
};

} // end namespace Mongoose
