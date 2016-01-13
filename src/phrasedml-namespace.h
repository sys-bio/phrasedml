/**
 * @file    phrasedml-namespace.h
 * @brief   Defines C++ namespace of libphraSEDML
 * @author  Lucian Smith, from Akiya Jouraku
 * 
 */

#ifndef PHRASEDML_NAMESPACE_H
#define PHRASEDML_NAMESPACE_H 1

/*
 *
 * The idea of the following marcors are borrowed from 
 * Xerces-C++ XML Parser (http://xerces.apache.org/xerces-c/).
 *
 */

/* Define to enable phrasedml C++ namespace */
/* #undef PHRASEDML_USE_CPP_NAMESPACE */


#if defined(__cplusplus) && !defined(SWIG)
  /* C++ namespace of PHRASEDML */
  #define PHRASEDML_CPP_NAMESPACE            phrasedml
  #define PHRASEDML_CPP_NAMESPACE_BEGIN      namespace PHRASEDML_CPP_NAMESPACE {
  #define PHRASEDML_CPP_NAMESPACE_END        }
  #define PHRASEDML_CPP_NAMESPACE_USE        using namespace PHRASEDML_CPP_NAMESPACE;
  #define PHRASEDML_CPP_NAMESPACE_QUALIFIER  PHRASEDML_CPP_NAMESPACE::

#else
  #define PHRASEDML_CPP_NAMESPACE 
  #define PHRASEDML_CPP_NAMESPACE_BEGIN
  #define PHRASEDML_CPP_NAMESPACE_END  
  #define PHRASEDML_CPP_NAMESPACE_USE 
  #define PHRASEDML_CPP_NAMESPACE_QUALIFIER 
#endif


#endif  /* PHRASEDML_NAMESPACE_H */

