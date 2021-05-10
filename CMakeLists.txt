cmake_minimum_required(VERSION 3.16)
project(236lab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 main.cpp Lexer.h Lexer.cpp Automaton.h Token.h MatcherAutomaton.h Id.h StringRec.h UndefinedString.h Comment.h UndefinedComment.h EndOfFile.h Parser.h Parameter.h Predicate.h Rules.h StringParameter.h ExpressionParameter.h IdParameter.h relation.h Tuple.h Header.h Interpreter.h Database.h)