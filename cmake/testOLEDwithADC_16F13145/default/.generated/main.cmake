include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(testOLEDwithADC_16F13145_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_assemble)
add_library(testOLEDwithADC_16F13145_default_default_XC8_assemble OBJECT ${testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_assemble})
    testOLEDwithADC_16F13145_default_default_XC8_assemble_rule(testOLEDwithADC_16F13145_default_default_XC8_assemble)
    list(APPEND testOLEDwithADC_16F13145_default_library_list "$<TARGET_OBJECTS:testOLEDwithADC_16F13145_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(testOLEDwithADC_16F13145_default_default_XC8_assemblePreprocess OBJECT ${testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_assemblePreprocess})
    testOLEDwithADC_16F13145_default_default_XC8_assemblePreprocess_rule(testOLEDwithADC_16F13145_default_default_XC8_assemblePreprocess)
    list(APPEND testOLEDwithADC_16F13145_default_library_list "$<TARGET_OBJECTS:testOLEDwithADC_16F13145_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_compile)
add_library(testOLEDwithADC_16F13145_default_default_XC8_compile OBJECT ${testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_compile})
    testOLEDwithADC_16F13145_default_default_XC8_compile_rule(testOLEDwithADC_16F13145_default_default_XC8_compile)
    list(APPEND testOLEDwithADC_16F13145_default_library_list "$<TARGET_OBJECTS:testOLEDwithADC_16F13145_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(testOLEDwithADC_16F13145_default_image_CgGcJHuz ${testOLEDwithADC_16F13145_default_library_list})

set_target_properties(testOLEDwithADC_16F13145_default_image_CgGcJHuz PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${testOLEDwithADC_16F13145_default_output_dir}")
target_link_libraries(testOLEDwithADC_16F13145_default_image_CgGcJHuz PRIVATE ${testOLEDwithADC_16F13145_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
testOLEDwithADC_16F13145_default_link_rule( testOLEDwithADC_16F13145_default_image_CgGcJHuz)


