#include "tidy.h"
#include "buffio.h"

#include "errno.h"

#include "Rinternals.h"
#include "Rdefines.h"
#include "R_ext/Memory.h"

void *
RTI_alloc(TidyAllocator *sel, size_t nBytes)
{
  return(R_alloc(1, nBytes));
}

void *
RTI_realloc(TidyAllocator *sel, void *block, size_t nBytes)
{
  void *ans;
  ans = RTI_alloc(sel, nBytes);
  if(block)
      memcpy(ans, block, nBytes);
  return(ans);
}
void
RTI_free( TidyAllocator *self, void *block)
{
}

void
RTI_panic( TidyAllocator *self, ctmbstr msg)
{
  PROBLEM msg
    ERROR;
}

static const TidyAllocatorVtbl allocatorFuns =  {
  RTI_alloc,
  RTI_realloc,
  RTI_free,
  RTI_panic
};

SEXP
R_tidy_html(SEXP r_doc, SEXP r_asXHTML, SEXP r_size)
{
    Bool ok;
    unsigned int len;
    int status;
    tmbstr buf;
    SEXP ans;

    TidyDoc tdoc;
    TidyBuffer errbuf;
    TidyAllocator allocator;
    /* We use our own allocator so that if there was an error, R would
     * clean up as it returns from the .Call(). */
    /* ???  Do we have to free the errbuf? and tdoc.
       Since our free() does nothing, no problem.
       If we are concerned about building up a lot of unfreed segments
       during the operation, a) we probably shouldn't be, and b)
       we could manage the memory ourselves and store the allocated
       pointers in our allocator and then  ensure that  we
       free these before returning from error.
     */
    allocator.vtbl = &allocatorFuns;
    tdoc = tidyCreateWithAllocator(&allocator); // tidyCreate(); // will use tidyCreateWithAllocator

    tidyBufInit(&errbuf);

    if(LOGICAL(r_asXHTML)[0])
	tidyOptSetBool(tdoc, TidyXhtmlOut, yes);

    tidySetErrorBuffer( tdoc, &errbuf );

    ok = tidyParseString(tdoc, CHAR(STRING_ELT(r_doc, 0)));
    if(!ok) {
      ans = ScalarString(mkChar((char *) errbuf.bp));
      tidyBufFree(&errbuf);
      return(ans);
      PROBLEM "problem parsing the HTML document"
	ERROR;
    }
    ok = tidyCleanAndRepair(tdoc);
    if(!ok) {
      PROBLEM "problem tidying the HTML document"
	ERROR;
    }
    ok = tidyRunDiagnostics(tdoc); 
    if(!ok) {
      PROBLEM "problem running the diagnostics on the HTML document"
	ERROR;
    }    

    len = INTEGER(r_size)[0];
    buf = (tmbstr) R_alloc(len, sizeof(tmbchar));
    memset(buf, '\0', len);
    status = tidySaveString(tdoc, buf, &len);

    if(status == - ENOMEM) {
        len++;
	buf = (tmbstr) S_alloc(len, sizeof(tmbchar));
	memset(buf, '\0', len);
	status = tidySaveString(tdoc, buf, &len);
    }

    PROTECT(ans = NEW_CHARACTER(2));
    SET_STRING_ELT(ans, 0, mkChar(buf));
    SET_STRING_ELT(ans, 1, mkChar((char *) errbuf.bp));
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
    UNPROTECT(1);

    return(ans);

}
