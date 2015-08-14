/**
 * \file    TestUtil.h
 * \brief   Test phraSEDML's basic constructs.
 * \author  Lucian Smith
 * ---------------------------------------------------------------------- -->*/

#include <string>

BEGIN_C_DECLS

void compareStringAndFileTranslation(const std::string& phrasedml, const std::string& base);
void compareFileTranslation(const std::string& base);
void compareStringTranslation(const std::string& phrasedml, const std::string& sedml);
void compareOriginalXMLTranslations(const std::string& base);


END_C_DECLS
