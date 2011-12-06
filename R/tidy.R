
tidyHTML = 
function(doc, asXHTML = FALSE, 
         asText = inherits(doc, "AsIs") || (!file.exists(doc) && length(grep("\\<", doc))),
         size = nchar(doc)*1.2, withErrors = FALSE)
{
   if(!asText)
     doc = paste( readLines(doc), collapse = "\n")
   else
     doc = paste(doc, collapse = "\n")

   ans = .Call("R_tidy_html", as.character(doc), as.logical(asXHTML), as.integer(size))

   if(length(ans) == 1)
      stop("problem with HTML document: ", ans)

   if(withErrors) 
     list(doc = ans[1], errors = ans[2])
   else
     ans[1]
}
