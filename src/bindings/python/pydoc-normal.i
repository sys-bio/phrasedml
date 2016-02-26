%feature("docstring") convertFile "
Convert a file from phraSEDML to SEDML, or visa versa.  If None is
returned, an error occurred, which can be retrieved with
getLastError()'.

Returns The converted file, as a string.

Parameter 'filename' is the filename as a character string.  May be
either absolute or relative to the directory the executable is being
run from.

See also getLastError().
";


%feature("docstring") convertString "
Convert a model string from phraSEDML to SEDML, or visa versa.  If
None is returned, an error occurred, which can be retrieved with
getLastError().

Returns The converted model, as a string.

Parameter 'model' is the model as a character string.  May be either
SED-ML or phraSED-ML.

See also getLastError().
";


%feature("docstring") getLastPhrasedError "
When any function returns an error condition, a longer description of
the problem is stored in memory, and is obtainable with this function.
In most cases, this means that a call that returns a pointer returned
'None' (or 0).
";


%feature("docstring") getLastPhrasedErrorLine "
Returns the line number of the file where the last error was obtained,
if the last error was obtained when parsing a phraSED-ML file.
Otherwise, returns 0.
";


%feature("docstring") getPhrasedWarnings "
When translating some other format to phraSEDML, elements that are
unable to be translated are saved as warnings, retrievable with this
function (returns None if no warnings present).
";


%feature("docstring") getLastSEDML "
If a previous 'convert' call was successful, the library retains an
internal representation of the SEDML and the PhraSEDML.  This call
converts that representation to SEDML and returns the value, returning
an empty string if no such model exists.
";


%feature("docstring") getLastPhraSEDML "
If a previous 'convert' call was successful, the library retains an
internal representation of the SEDML and the PhraSEDML.  This call
converts that representation to PhraSEDML and returns the value,
returning an empty string if no such model exists.
";


%feature("docstring") setWorkingDirectory "
Sets the working directory for phraSED-ML to look for referenced
files.

Parameter 'directory' is the directory as a character string.  May be
either absolute or relative to the directory the executable is being
run from.
";


%feature("docstring") setReferencedSBML "
Allows phrasedml to use the given SBML document as the filename,
instead of looking for the file on disk.  If the document is invalid
SBML, 'false' is returned, but the document is still saved.

Parameter 'URI' is the string that, when used in phrasedml, should
reference the 'sbmlstring'. Parameter 'sbmlstring' is the SBML
document string to use when the 'URI' is encountered.

Returns a boolean indicating whether the document is valid SBML or
not.  Either way, the document is saved as the reference document for
the given filename string.
";


%feature("docstring") clearReferencedSBML "
Clears and removes all referenced SBML documents.
";


%feature("docstring") freeAllPhrased "
Frees all pointers handed to you by libphraSEDML. All libphraSEDML
functions above that return pointers return malloc'ed pointers that
you now own.  If you wish, you can ignore this and never free
anything, as long as you call 'freeAllPhrased' at the very end of your
program.  If you free *anything* yourself, however, calling this
function will cause the program to crash!  It won't know that you
already freed that pointer, and will attempt to free it again.  So
either keep track of all memory management yourself, or use this
function after you're completely done.

Note that this function only frees pointers handed to you by other
phrasedml_api functions.  The models themselves are still in memory
and are available.  (To clear that memory, use clearPreviousLoads() )
";


