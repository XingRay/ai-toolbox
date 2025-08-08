# https://github.com/XingRay/vklite
function(import_vklite vklite_install_dir)
    message("import_vklite: vklite_install_dir:${vklite_install_dir}")
    set(Vklite_DIR ${Vklite_INSTALL_DIR})
    find_package(Vklite)
    if (NOT TARGET vklite)
        message(FATAL_ERROR "vklite is not a target !")
    endif ()
endfunction()