add_library(labellib STATIC)

set_target_properties(labellib PROPERTIES OUTPUT_NAME "label")

target_sources(
    labellib
    PRIVATE
        "Label.h"
        "SimpleLabel.h"
        "SimpleLabel.cpp"
        "RichLabel.h"
        "RichLabel.cpp"
)


# Executable target for the application
add_executable(application)

set_target_properties(application PROPERTIES OUTPUT_NAME "labelEditor")

target_link_libraries(
    application
    PRIVATE
        labellib
)

target_sources(
    application
    PRIVATE
        "application.cpp"
)