if (CONFIG_OUR_DRIVER)
  target_sources(app PRIVATE our_driver.c our_driver_shell.c)

  target_include_directories(app PRIVATE ../../include)

  zephyr_syscall_header(../../include/our_driver/our_driver.h)
endif()


# I cannot use zephyr_library() because I'm not creating a module, so use target_sources instead

# if (CONFIG_OUR_DRIVER)
# zephyr_library()
# zephyr_syscall_header(${ZEPHYR_OUR_DRIVER_MODULE_DIR}/include/our_driver/our_driver.h)
# zephyr_include_directories(include)
# zephyr_library_sources(our_driver.c)
# endif (CONFIG_OUR_DRIVER)