include $(sort $(wildcard $(BR2_EXTERNAL_SUBMARINE_PATH)/package/*/*.mk))

# flash-my-board:
# 	$(BR2_EXTERNAL_SUBMARINE_PATH)/board/rudder/flash-image \
# 		--image $(BINARIES_DIR)/image.bin \
# 		--address $(SUBMARINE_FLASH_ADDR)
