#include "LexerTest.h"
#include <clang/Basic/LangOptions.h>
#include <clang/Basic/LangStandard.h>
#include <clang/Basic/TokenKinds.h>
#include <clang/Lex/Lexer.h>
#include <clang/Lex/Token.h>
#include <iostream>
#include <string>
#include <vector>

namespace clang::playground {
clang::LangOptions genericLangOpts() {
  clang::LangOptions Opts;
  std::vector<std::string> UnusedIncludes;
  LangOptions::setLangDefaults(Opts, clang::Language::CXX, llvm::Triple(),
                               UnusedIncludes, clang::LangStandard::lang_c17);

  // Some options are "on by default", but e.g. at the driver level.
  if (Opts.CPlusPlus)
    Opts.CXXOperatorNames = true;
  if (Opts.CPlusPlus20)
    Opts.Coroutines = true;

  // Some options are off by default, but define keywords we want to tolerate.
  if (Opts.CPlusPlus)
    Opts.MicrosoftExt = true;  // kw__try, kw__finally
  Opts.DeclSpecKeyword = true; // __declspec
  Opts.WChar = true;

  return Opts;
}

void LexerTest::run() {
  auto Code = std::string("// Comment\n /*Multiline\nComment\nHere*/");
  auto Start = clang::SourceLocation();
  auto Opts = genericLangOpts();
  auto Lexer = clang::Lexer(Start, Opts, Code.data(), Code.data(),
                            Code.data() + Code.size());
                            
  Lexer.SetCommentRetentionState(true);

  auto Result = std::vector<clang::Token>();
  auto CT = clang::Token();

  do
  {
    Lexer.LexFromRawLexer(CT);
    Result.push_back(CT);
  }
  while(!CT.is(tok::eof));

  for (const auto& T : Result)
  {
    std::cout << T.getKind() << " ";
  }
}
} // namespace clang::playground