# -*- coding: utf-8 -*-
"""
Created on Mon May 11 10:47:08 2020

@author: Lucian
"""

from ctypes import c_long, c_char_p, c_ulong, c_bool, c_int, c_double, POINTER
import sys

srcdir = "C:/Users/Lucian/Desktop/phrasedml/src/"
if len(sys.argv)>2:
    print("Unable to process arguments:  there should be a single argument that is the directory where the source code lives.")
    assert(False)

if len(sys.argv)==2:
    srcdir = sys.argv[1] + "/"

headerfiles = ["phrasedml_api.h"]#, "phrasedml_api_cpp.h"]

libfile = open("phrasedml.py", "w")
alib = "__phrasedLib"
iblock = "   "

def getCType(atype):
   if atype=="long":
      return c_long
   if atype=="const char*":
      return c_char_p
   if atype=="char*":
      return c_char_p
   if atype=="char**":
      return POINTER(c_char_p)
   if atype=="char***":
      return POINTER(POINTER(c_char_p))
   if atype=="unsigned long":
      return c_ulong
   if atype=="unsigned long*":
      return POINTER(c_ulong)
   if atype=="bool":
      return c_bool
   if atype=="int":
      return c_int
   if atype=="void":
      return None
   if "_type" in atype:
      return c_int #Enum
   if atype=="double":
      return c_double
   if atype=="double*":
      return POINTER(c_double)
   if atype=="double**":
      return POINTER(POINTER(c_double))

   print("Couldn't find type", atype)
   return atype


def getCTypeStr(ctype):
   if ctype == c_long:
      return "c_long"
   if ctype == c_char_p:
      return "c_char_p"
   if ctype == POINTER(c_char_p):
      return "POINTER(c_char_p)"
   if ctype == POINTER(POINTER(c_char_p)):
      return "POINTER(POINTER(c_char_p))"
   if ctype == c_ulong:
      return "c_ulong"
   if ctype == POINTER(c_ulong):
      return "POINTER(c_ulong)"
   if ctype == c_bool:
      return "c_bool"
   if ctype == c_int:
      return "c_int"
   if ctype == None:
      return "None"
   if ctype == c_int: #Enum
      return "c_int"
   if ctype == c_double:
      return "c_double"
   if ctype == POINTER(c_double):
      return "POINTER(c_double)"
   if ctype == POINTER(POINTER(c_double)):
      return "POINTER(POINTER(c_double))"

   print("Couldn't find ctype", str(ctype))
   return "atype"


def isPointer(ctype):
   return "POINTER" in getCTypeStr(ctype)

def parse_function(line, comment, functions):
   function = {}
   fvec = line.split('(')
   lastspace = fvec[0].rfind(" ")
   firstbit = fvec[0][0:lastspace]
   firstbit = firstbit.replace("LIB_EXTERN ", "")
   firstbit = firstbit.strip()
   function["ret"] = getCType(firstbit)
   if "_type" in firstbit:
      function["enum"] = firstbit;
   id = fvec[0][lastspace+1:]
   argvec = fvec[1].split(')')[0].split(',')
   args = []
   for onearg in argvec:
      onearg = onearg.strip()
      if len(onearg)==0:
         continue
      lastspace = onearg.rfind(" ")
      atype = onearg[0:lastspace]
      argid = onearg[lastspace+1:]
      argtype = getCType(atype)
      if "=false" in argid:
          argid = argid.replace("false", "False")
      args.append((argtype, argid))
   function["args"] = args
   function["comment"] = comment.strip()
   return id, function


def readHeaderFiles(headerfile):
   functions = {}
   defs = {}
   filecomment = ""
   for file in headerfiles:
      doxygen = False
      comment = "";
      for line in open(srcdir + file, "r"):
         line = line.strip()
         if line[0:2] == "//":
            continue
         if "/**" in line:
            if doxygen:
               comment = "" #Clear the old comment
            doxygen = True
         elif "/*" in line:
            #Skip normal comments.
            continue
         if doxygen:
            cline = line.strip();
            if "@name" in line:
               continue
            if "\{" in line:
               continue
            if "\}" in line:
               continue
            cline = cline.replace("/**", "")
            cline = cline.replace("*/", "")
            if len(cline) and cline[0] == "*":
                cline = cline[1:]
            comment += cline + "\n"
            if "*/" in line:
               doxygen = False
               continue
         elif "#define" in line:
            lvec = line.split(" ")
            if len(lvec)==3:
               defs[lvec[1]] = lvec[2]
            if len(comment):
               filecomment = comment
               comment = ""
            continue
         elif "LIB_EXTERN" in line:
            if line[-1] == ";":
               id, func = parse_function(line, comment, functions)
               comment = ""
               if "CellML" in id:
                  continue
               if "Stoichiometry" in id:
                  continue
               if "DNA" in id:
                  continue
               functions[id] = func
            else:
               print("Need to read multi-line function: ", line)
   return functions, defs, filecomment


def writeLibIntro(libfile):
   text = """# -*- coding: utf-8 -*-
\"\"\"
Created November 2021

@author: Lucian Smith
\"\"\"


##@Module phrasedmlPython
#This module allows access to the phrasedml library from python
import os
from ctypes import c_long, c_int, c_char_p, c_ulong, c_bool, c_double, POINTER, cdll
import inspect
import platform

# Ctypes will only load the dll properly if the working directory is the same as 
# the directory where the dll is (at least on Windows).
__thisfile = inspect.getframeinfo(inspect.currentframe()).filename
__libdir = os.path.dirname(os.path.abspath(__thisfile))
#print(__thisfile)
#print(__libdir)

__oldir = os.getcwd()
os.chdir(__libdir)

__osname = platform.system()
if __osname == "Windows":
   __sharedLib = os.path.join(__libdir, 'libphrasedml.dll')
elif __osname == "Linux":
   __sharedLib = os.path.join(__libdir, "libphrasedml.so")
elif __osname == "Darwin":
   __sharedLib = os.path.join(__libdir, "libphrasedml.dylib")

if not os.path.isfile(__sharedLib):
    print('Unable to find shared library file', __sharedLib, "Exiting.")
    exit()
else:
    pass
    #print(__sharedLib, 'found.')
__phrasedLib = cdll.LoadLibrary(__sharedLib)

os.chdir(__oldir)

"""
   libfile.write(text)

def getPointerDetanglerFor(funcid):
    """
    NOTE:  never actually called for phraSED-ML; it was used in the Antimony version.
    """
    if funcid=="getModuleNames":
      return ("getNumModules()", "getNthModuleName(n)")
    if funcid=="getSymbolNamesInInterfaceOf":
      return ("getNumSymbolsInInterfaceOf(moduleName)", "getNthSymbolNameInInterfaceOf(moduleName, n)")
    
    print("Unhandled function ", funcid)
    return ("", "")
   

def createPointerBody(libfile, funcid, function):
   (nfunc, subfunc) = getPointerDetanglerFor(funcid)
   if nfunc=="":
      print("Improperly handled pointer for", funcid)
      libfile.write(iblock + "return None\n")
      return
   libfile.write(iblock + "ret = []\n")
   libfile.write(iblock + "for n in range(" + nfunc + "):\n")
   libfile.write(iblock + iblock + "ret.append(" + subfunc + ")\n")
   libfile.write(iblock + "return ret\n\n")
      

def writeDefs(libfile, defs):
   libfile.write("#Definitions\n")
   for onedef in defs:
      if "VERSION" in onedef:
         libfile.write("__version__ = \"" + defs[onedef][2:] + "\n")
      else:
         libfile.write(onedef +" " + defs[onedef] + "\n")
   libfile.write("\n")

def writeFunctions(libfile, functions):
   libfile.write("#Library functions\n")
   for funcid in functions:
      function = functions[funcid]

      #return value type
      libfile.write(alib + "." + funcid + ".restype = " + getCTypeStr(function["ret"]) + "\n")

      #argument types
      libfile.write(alib + "." + funcid + ".argtypes = (")
      for (argtype, argid) in function["args"]:
         libfile.write(getCTypeStr(argtype) + ", ")
      libfile.write(")\n")

      #Redefinition
      newid = funcid.replace("PhrasedError", "Error")
      libfile.write("\ndef " + newid + "(")
      first = True
      hasModuleName = False
      for (n, (argtype, argid)) in enumerate(function["args"]):
         if first:
            first = False
         else:
            libfile.write(", ")
         libfile.write(argid)
      libfile.write("):\n")
      libfile.write(iblock + '"""\n' + iblock)
      libfile.write(function["comment"].replace("\n ", "\n" + iblock))
      libfile.write("\n" + iblock + '"""\n')
      if hasModuleName:
         libfile.write(iblock + "if moduleName==None:\n")
         libfile.write(iblock + iblock + "moduleName = getMainModuleName()\n")
      for (argtype, argid) in function["args"]:
         if argtype==c_char_p:
            libfile.write(iblock + "if type(" + argid + ") == str:\n")
            libfile.write(iblock + iblock + argid + " = " + argid + ".encode('utf-8')\n")
                          
      if isPointer(function["ret"]):
         createPointerBody(libfile, funcid, function)
         continue
      hasret = function["ret"] == c_char_p
      if hasret:
         libfile.write(iblock + "ret = ")
      elif function["ret"] == None:
         libfile.write(iblock);
      else:
         libfile.write(iblock + "return ")
      libfile.write(alib + "." + funcid + "(")
      first = True
      for (argtype, argid) in function["args"]:
         if first:
            first = False
         else:
            libfile.write(", ")
         if "=False" in argid:
             argid = argid.replace("=False","")
         libfile.write(argid)
      libfile.write(")")
      if hasret:
         libfile.write("\n")
         libfile.write(iblock + "if ret==None:\n")
         libfile.write(iblock + iblock + "return ret\n")
         libfile.write(iblock + "return ret.decode('utf-8')\n")
      libfile.write("\n\n")




functions, defs, filecomment = readHeaderFiles(headerfiles)
writeLibIntro(libfile)
writeDefs(libfile, defs)
writeFunctions(libfile, functions)

libfile.close()
print("Successfully created phrasedml.py.")
