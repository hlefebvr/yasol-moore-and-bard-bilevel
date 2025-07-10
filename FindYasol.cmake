set(YASOL_DIR "/home/henri/Research/yasol/Yasol_4.0.1.5_b_linux")

find_path(YASOL_INCLUDE_DIR
        NAMES Algorithms
        PATHS
        ${YASOL_DIR}/Solver/include
        /usr/local/include
        /usr/include
)

find_library(YASOL_LIBRARY
        NAMES Solver.a
        PATHS
        ${YASOL_DIR}/Solver
        /usr/local/lib
        /usr/lib
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Yasol
        REQUIRED_VARS YASOL_LIBRARY YASOL_INCLUDE_DIR
        VERSION_VAR YASOL_VERSION
)

if(YASOL_FOUND)
    add_library(Yasol::Yasol UNKNOWN IMPORTED)
    set_target_properties(Yasol::Yasol PROPERTIES
            IMPORTED_LOCATION "${YASOL_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${YASOL_INCLUDE_DIR}"
    )
endif()