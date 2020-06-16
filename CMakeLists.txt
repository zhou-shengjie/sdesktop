cmake_minimum_required(VERSION 3.5)

project(sdesktop LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(cpprestsdk CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(sdesktop
  main.cpp
  loginout.h
  loginout.cpp
  globalconfig.h
  globalconfig.cpp
  captcha.cpp
  captcha.h
  httpclientmgr.cpp
  httpclientmgr.h
  qmlregister.h
  qmlregister.cpp
  imageprovider.h
  imageprovider.cpp
  imageproviderbridge.h
  imageproviderbridge.cpp
  userinfo.h
  userinfo.cpp
  errmsg.h
  errmsg.cpp
  sexception.h
  sexception.cpp
  crypto.h
  crypto.cpp
  sdesktop.qrc
)

target_compile_definitions(sdesktop
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(sdesktop
  PRIVATE Qt5::Core Qt5::Quick cpprestsdk::cpprest OpenSSL::SSL OpenSSL::Crypto)
