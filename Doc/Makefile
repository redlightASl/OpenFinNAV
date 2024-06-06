#######################################
# Generate Documents
#######################################
# include $(FINNAV_BUILD_DIR)/utils.mk


doxygen:
	@echo "=============== generate Documents ==============="
	@cd $(FINNAV_DOC_DIR)
	@doxygen Doxyfile
	@echo "=============== generate Done! ==============="

clean:
	@echo "=============== clean Documents ==============="
	rm -rf $(FINNAV_DOC_DIR)/DoxygenOut
	@echo "=============== clean Done! ==============="

.PHONY: doxygen clean_
# *** EOF ***
