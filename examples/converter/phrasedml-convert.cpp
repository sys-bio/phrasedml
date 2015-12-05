/**
 * @file    generateTestsFrom.cpp
 * @brief   Takes a test case model and generates the translated versions of the model plus the .m file.
 * @author  Lucian Smith
 * 
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <sstream>

#include <phrasedml_api.h>

using namespace std;

int
main (int argc, char* argv[])
{
  if (argc < 2)
  {
    cerr << endl << "Usage: phrasedml-convert file1 [file2] [...]" << endl << endl;
    return 1;
  }

  for (int f=1; f<argc; f++) {
    char* translated = convertFile(argv[f]);
    if (translated==NULL) {
      cerr << endl << "Unable to translate " << argv[f] << endl << endl;
      return 1;
    }
    string filename = argv[f];
    size_t xml = filename.find(".xml");
    int len = 4;
    if (xml == string::npos) {
      xml = filename.find(".sedml");
      len = 6;
    }
    size_t txt = filename.find(".txt");

    if (xml != string::npos) {
      filename.replace(xml, len, ".txt");
    }
    else if (txt != string::npos) {
      filename.replace(txt, 4, ".xml");
    }
    else {
      filename.append(".translated");
    }

    setlocale(LC_ALL, "C");
    ofstream afile(filename);
    if (!afile.good()) {
      cerr << "Unable to open file " << filename << " for writing.";
      return 1;
    }
    afile << translated;
    afile.close();

    free(translated);
  }
  return 0;
}
