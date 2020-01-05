cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 main.cpp Command.h OpenDataServer.cpp OpenDataServer.h ConnectControlClient.cpp ConnectControlClient.h DefineVarCommand.cpp DefineVarCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.h LoopCommand.cpp LoopCommand.h Info.h AssignVarCommand.cpp AssignVarCommand.h expressions/Expression.h expressions/Variable.cpp expressions/Variable.h expressions/Value.cpp expressions/Value.h expressions/UnaryExpression.cpp expressions/UnaryExpression.h expressions/UPlus.cpp expressions/UPlus.h expressions/UMinus.cpp expressions/UMinus.h expressions/BinaryOperator.cpp expressions/BinaryOperator.h expressions/Plus.cpp expressions/Plus.h expressions/Minus.cpp expressions/Minus.h expressions/Mul.cpp expressions/Mul.h expressions/Div.cpp expressions/Div.h expressions/Interpreter.cpp expressions/Interpreter.h ConditionCommand.cpp ConditionCommand.h Singleton.h expressions/BooleanOperator.cpp expressions/BooleanOperator.h expressions/IsEquals.cpp expressions/IsEquals.h expressions/IsNotEquals.cpp expressions/IsNotEquals.h expressions/IsSmaller.cpp expressions/IsSmaller.h expressions/IsSmallerEquals.cpp expressions/IsSmallerEquals.h expressions/IsBigger.cpp expressions/IsBigger.h expressions/IsBiggerEquals.cpp expressions/IsBiggerEquals.h Lexer.cpp Lexer.h MapCommands.h)
