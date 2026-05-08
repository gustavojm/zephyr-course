if (CONFIG_OUR_DRIVER)
  target_sources(app PRIVATE our_driver.c)

  target_include_directories(app PRIVATE ../../include)

  zephyr_syscall_header(../../include/our_driver/our_driver.h)
endif()


# if (CONFIG_OUR_DRIVER)
# zephyr_library()
# zephyr_syscall_header(${ZEPHYR_OUR_DRIVER_MODULE_DIR}/include/our_driver/our_driver.h)
# zephyr_include_directories(include)
# zephyr_library_sources(our_driver.c)
# endif (CONFIG_OUR_DRIVER)