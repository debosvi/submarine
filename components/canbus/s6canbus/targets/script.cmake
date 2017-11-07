
## generation profile name.
## mandatory (generates library profile)
set(COMP_SRC_PROFILE "install")

message (STATUS "comp dir: ${LOCAL_COMP_ROOTDIR}")
BOZ_INSTALL_SCRIPT(${LOCAL_COMP_ROOTDIR}/files/scripts/execline.script)
