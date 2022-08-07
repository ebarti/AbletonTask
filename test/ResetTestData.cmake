# Clean test out directory
file(REMOVE_RECURSE ${TEST_OUTPUT_ROOT_DIR}/resources)
file(REMOVE_RECURSE ${TEST_OUTPUT_ROOT_DIR}/output)
# Create fresh directory
file(MAKE_DIRECTORY ${TEST_OUTPUT_ROOT_DIR}/output)
file(COPY ${TEST_INPUT_ROOT_DIR}/resources DESTINATION ${TEST_OUTPUT_ROOT_DIR})