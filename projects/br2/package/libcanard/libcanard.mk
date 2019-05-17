################################################################################
#
# libcanard
#
################################################################################

LIBCANARD_VERSION = 0.0.1
LIBCANARD_SITE = $(call github,debosvi,libcanard,$(LIBCANARD_VERSION))
LIBCANARD_LICENSE = ISC
# LIBCANARD_LICENSE_FILES = COPYING
# LIBCANARD_CONF_OPTS = \
# 	--disable-tests \
# 	--disable-examples \
# 	--disable-man-pages \
# 	--disable-html-docs

LIBCANARD_INSTALL_STAGING = YES

# Also has CMake support, but that forces shared+static libs and static
# lib has a different name.
$(eval $(cmake-package))
 
