library(RGCCTranslationUnit)
tu = parseTU("tidy.c.tu")
r = getRoutines(tu, "tidy")

enums = getEnumerations(tu, "tidy")

