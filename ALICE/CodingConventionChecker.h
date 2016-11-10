// ALICE O2 coding conventions
// Shyam Kumar; shyam.kumar@cern.ch


#ifndef SAS_CHECKERS_CODINGCONVENTIONCHECKER_H
#define SAS_CHECKERS_CODINGCONVENTIONCHECKER_H

// If USE_BUGTYPE is defined, reporting is done using the method
// `BugReporter.emitReport`. Otherwise, reporting uses the method
// `BugReporter.EmitBasicReport` (which in turn calls `BugReporter.emitReport`).
// The first method may be faster as it only defines `BugType` object once.
// Both possibilities are implemented in `CodingConventionChecker` for demonstration
// purpose.
#define USE_BUGTYPE

#include <clang/StaticAnalyzer/Core/Checker.h>
// clang::ento::Checker
// clang::ento::check::ASTDecl

#include <clang/AST/Decl.h>
// clang::VarDecl

#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
// clang::ento::AnalysisManager

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
// clang::ento::BugReporter

#ifdef USE_BUGTYPE
#include <clang/StaticAnalyzer/Core/BugReporter/BugType.h>
#endif // USE_BUGTYPE
#include "SasChecker.h"

namespace sas
{
   namespace ALICE {
      class CodenameTraits : public CommonCheckerTraits{
	  public:
		 static constexpr const char* Name="sas.ALICE.Code";
         static constexpr const char* Description="Checks whether the names of the variable start with an uppercase letter.";
      };
      class CodingConventionChecker:
                    public SasChecker<CodenameTraits, clang::ento::check::ASTDecl<clang::VarDecl>, clang::ento::check::ASTDecl<clang::FunctionDecl>,clang::ento::check::ASTDecl<clang::EnumDecl>,clang::ento::check::ASTDecl<clang::FieldDecl>,
clang::ento::check::ASTDecl<clang::UsingDirectiveDecl>, clang::ento::check::ASTDecl<clang::UsingDecl>, clang::ento::check::PreStmt<clang::CallExpr >>
      {
      public:
         void checkASTDecl(const clang::VarDecl* D, clang::ento::AnalysisManager& Mgr, clang::ento::BugReporter& BR) const; // Variable name checker
         void checkASTDecl(const clang::FunctionDecl* D, clang::ento::AnalysisManager &Mgr, clang::ento::BugReporter &BR) const; //function name checker
         void checkASTDecl(const clang::EnumDecl* D, clang::ento::AnalysisManager &Mgr, clang::ento::BugReporter &BR) const; //Enumeration name checker
         void checkASTDecl(const clang::FieldDecl* D, clang::ento::AnalysisManager &Mgr, clang::ento::BugReporter &BR) const; //field name checker
         void checkASTDecl(const clang::UsingDirectiveDecl *D, clang::ento::AnalysisManager &Mgr, clang::ento::BugReporter &BR) const;
         void checkASTDecl(const clang::CXXConstructorDecl* D, clang::ento::AnalysisManager& Mgr, clang::ento::BugReporter& BR) const; //default constructor checker
         void checkASTDecl(const clang::NamespaceDecl* D, clang::ento::AnalysisManager& Mgr, clang::ento::BugReporter& BR) const; //NameSpace declaration
         void checkASTDecl(const clang::CXXDestructorDecl* D, clang::ento::AnalysisManager& Mgr, clang::ento::BugReporter& BR) const; //destructor checker
         void checkASTDecl(const clang::UsingDecl *D, clang::ento::AnalysisManager &Mgr, clang::ento::BugReporter &BR) const;
         void checkPreStmt(const clang::CallExpr *, clang::ento::CheckerContext &) const;
         bool isDeclOK(const clang::NamedDecl *D, clang::ento::BugReporter &BR) const;
#ifdef USE_BUGTYPE
      private:
         mutable std::unique_ptr<clang::ento::BugType> BT;
#endif // USE_BUGTYPE
      private:
         static const char* const checkerName;
      };
   } // end namespace Example
}

#endif
