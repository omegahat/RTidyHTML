\name{tidyHTML}
\alias{tidyHTML}
\title{Tidy HTML content}
\description{
This function processes an HTML document and 
tidys the malformed nodes so that they are legitimate
TML, i.e. with end nodes (</li>, </p>)
and attributes enclosed in quotes.
This also corrects the HTML in various ways.

The resulting document can then be used with a more
correct structure. This, for example,  makes processing it 
with the XML parsing facilities more straightforward.

This uses libtidy from \url{http://tidy.sourceforge.net} 
}
\usage{
tidyHTML(doc, asXHTML = FALSE, 
         asText = inherits(doc, "AsIs") ||
                    (!file.exists(doc) && length(grep("\\\\<", doc))),
         size = nchar(doc)*1.2, withErrors = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{doc}{the name of the file containing the HTML document or the contents of the HTML itself.}
  \item{asXHTML}{a logical value controlling whether the result is output as XHTML.}
  \item{asText}{a logical value indicating whether the value of \code{doc}
    is the HTML content or the name of a file.}
  \item{size}{an integer scalar giving a guess of the size of the resulting tidied document}
  \item{withErrors}{a logical value controlling whether a string giving the errors in the input document are also returned}
}
\value{
If \code{withErrors} is \code{TRUE}, a list with two elements
named \code{doc} and \code{errors}, both of which are scalar strings.

If \code{withErrors} is \code{FALSE}, a character string
containing the tidied document's contents.
}
\references{
 \url{http://tidy.sourceforge.net} 
}
\author{
Duncan Temple Lang
}

\seealso{
 \code{\link[XML]{htmlParse}}
}
\examples{
 doc = system.file("testData", "foo.html", package = "RTidyHTML")
 tidyHTML(doc)

 txt = readLines(url("http://www.omegahat.org"))
 tidyHTML(txt)
}
\keyword{IO}

