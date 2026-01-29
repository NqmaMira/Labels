add_library(labellib STATIC)

set_target_properties(labellib PROPERTIES OUTPUT_NAME "label")

target_sources(
    labellib
    PRIVATE
        "Label.h"
        "SimpleLabel.h"
        "SimpleLabel.cpp"
        "RichLabelProperties.h"
        "RichLabel.h"
        "RichLabel.cpp"
        "TextTransformation.h"
        "CapitalizeTransformation.h"
        "CapitalizeTransformation.cpp"
        "LeftTrimTransformation.h"
        "LeftTrimTransformation.cpp"
        "RightTrimTransformation.h"
        "RightTrimTransformation.cpp"
        "NormalizeSpaceTransformation.h"
        "NormalizeSpaceTransformation.cpp"
        "DecorateTransformation.h"
        "DecorateTransformation.cpp"
        "CensorTransformation.h"
        "CensorTransformation.cpp"
        "ReplaceTransformation.h"
        "ReplaceTransformation.cpp"
        "LabelDecorator.h"
        "LabelDecorator.cpp"
        "RichLabelDecorator.h"
        "RichLabelDecorator.cpp"
        "RandomTransformDecorator.h"
        "RandomTransformDecorator.cpp"
        "CompositeTransformation.h"
        "CompositeTransformation.cpp"
        "CustomLabel.h"
        "CustomLabel.cpp"
        "HelpProvider.h"
        "SimpleHelpProvider.h"
        "SimpleHelpProvider.cpp"
        "HelpLabel.h"
        "HelpLabel.cpp"
        "RichHelpLabel.h"
        "RichHelpLabel.cpp"
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