set(MY_SOURCES ${MY_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/abstractsceneview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/mainwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/pointtablewidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/pointwidget.cpp
    )

# Rem: set here the headers related to the Qt MOC (i.e., with associated *.ui)
set(MY_HEADERS ${MY_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/abstractsceneview.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/mainwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/pointtablewidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/pointwidget.h
    )

set(MY_FORMS ${MY_FORMS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/mainwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/pointtablewidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/pointwidget.ui
    )
