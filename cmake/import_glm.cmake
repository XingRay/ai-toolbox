# glm
# https://github.com/g-truc/glm
function(import_glm glm_install_dir)
    message("import_glm: glm_install_dir:${glm_install_dir}")
    add_library(glm INTERFACE)

    target_include_directories(glm
            INTERFACE ${glm_install_dir}
    )
endfunction()