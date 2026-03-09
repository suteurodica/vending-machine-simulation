cmake_minimum_required(VERSION 3.30)
project(lab9)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab9 main.cpp
        produs.h
        produs.cpp
        repo.h
        repo.cpp
        teste.cpp
        teste.h
        service.h
        service.cpp
        ui.h
        ui.cpp
        tonomat.h
        tonomat.cpp
        collection.h
        repofile.h
        repofile.cpp
        cmake-build-debug/exceptii.h
        exceptii.h
        validator.h
)
