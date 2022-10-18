
if (CONFIG_URDF_PARSER)

zephyr_library_named(urdfparser)

zephyr_include_directories(include)

zephyr_sources(
  src/tinyxml.cpp
  src/tinyxmlerror.cpp
  src/tinyxmlparser.cpp
  src/common.cpp
  src/geometry.cpp
  src/joint.cpp
  src/link.cpp
  src/model.cpp
)

endif()