cmake_minimum_required(VERSION 3.16)
project(SmartBankSystem LANGUAGES CXX)

add_executable(SmartBankSystem "src/SmartBank System & ATM.cpp")
target_compile_features(SmartBankSystem PRIVATE cxx_std_17)

