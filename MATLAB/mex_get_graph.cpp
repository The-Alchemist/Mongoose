#include "mongoose_mex.hpp"

namespace Mongoose
{

Graph *mex_get_graph
(
    const mxArray *Gmatlab, /* The sparse matrix            */
    const mxArray *Amatlab  /* The real-valued node weights */
)
{
    // Check for valid sparse matrix
    cs_mex_check (0, -1, -1, 1, 1, 1, Gmatlab) ;

    Graph *returner = (Graph*) SuiteSparse_calloc(1, sizeof(Graph));
    if(!returner) return NULL;

    Int n = returner->n = mxGetN(Gmatlab);
    Int *Gp = returner->p = (Int*) mxGetJc(Gmatlab);
    Int *Gi = returner->i = (Int*) mxGetIr(Gmatlab);
    double *Gx = returner->x = (double*) mxGetPr(Gmatlab);
    Int nz = returner->nz = Gp[n];

    /* Read node weights from matlab into the problem. */
    if(Amatlab != NULL)
    {
        returner->w = (double*) mxGetPr(Amatlab);
    }
    else
    {
        returner->w = (double*) SuiteSparse_malloc(n, sizeof(double));
        for(Int k=0; k<n; k++) returner->w[k] = 1.0;
    }

    return returner;
}

}
