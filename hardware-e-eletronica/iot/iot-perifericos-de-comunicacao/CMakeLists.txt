idf_component_register(
    SRCS 
        "src/main.c" 
        "src/mpu6050.c" 
        "src/ssd1306.c" 
        "src/sdcard.c"
    INCLUDE_DIRS "src"
    REQUIRES driver fatfs vfs
)