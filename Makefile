CXX = g++
CXXFLAGS = -std=c++23 -O2 -g -Iinclude -Iexternal/imgui -Iexternal/glm -Iexternal/glad -Iexternal/stb -Iexternal/assimp -Iexternal/GLFW

SRC_DIR = src
EXTERNAL_IMGUI_DIR = external/imgui
EXTERNAL_GLAD_DIR  = external/glad

BUILD_DIR = build
DIST_DIR  = dist

# --- SOURCE LISTS ---
SRC_CPP := $(shell find $(SRC_DIR) -name '*.cpp')
SRC_C    := $(wildcard $(SRC_DIR)/*.c)
GLAD_C    := $(wildcard $(EXTERNAL_GLAD_DIR)/*.c)

# --- LINUX ---
LINUX_BUILD_DIR = $(BUILD_DIR)/linux

LINUX_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(LINUX_BUILD_DIR)/%.o,$(filter %.cpp, $(SRC_CPP)))
LINUX_OBJ += $(patsubst $(SRC_DIR)/%.c,$(LINUX_BUILD_DIR)/%.o,$(filter %.c, $(SRC_C)))
LINUX_OBJ += $(patsubst $(EXTERNAL_GLAD_DIR)/%.c,$(LINUX_BUILD_DIR)/external/glad/%.o,$(GLAD_C))

LINUX_LDFLAGS = -lglfw -ldl -lGL -lassimp
LINUX_OUT = $(LINUX_BUILD_DIR)/app
LINUX_DEP = $(LINUX_OBJ:.o=.d)

-include $(LINUX_DEP)

linux: $(LINUX_OUT)

$(LINUX_OUT): $(LINUX_OBJ)
	$(CXX) $(LINUX_OBJ) -o $@ $(LINUX_LDFLAGS)

$(LINUX_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(LINUX_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(LINUX_BUILD_DIR)/external/imgui/%.o: $(EXTERNAL_IMGUI_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(LINUX_BUILD_DIR)/external/glad/%.o: $(EXTERNAL_GLAD_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# --- WINDOWS ---
WIN_CXX = x86_64-w64-mingw32-g++
WIN_CXXFLAGS = -std=c++23 -O2 -g -Iinclude -Iexternal/imgui -Iexternal/glm -Iexternal/glad -Iexternal/stb -Iexternal/assimp/include -Iexternal/GLFW
WIN_LDFLAGS = -Llib/win -lglfw3 -lassimp -lopengl32 -lgdi32 -lkernel32 -luser32 -lz

WIN_BUILD_DIR = $(BUILD_DIR)/win

WIN_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(WIN_BUILD_DIR)/%.o,$(SRC_CPP))
WIN_OBJ += $(patsubst $(SRC_DIR)/%.c,$(WIN_BUILD_DIR)/%.o,$(SRC_C))
WIN_OBJ += $(patsubst $(SRC_DIR)/App/%.cpp,$(WIN_BUILD_DIR)/App/%.o,$(SRC_APP_CPP))
WIN_OBJ += $(patsubst $(EXTERNAL_GLAD_DIR)/%.c,$(WIN_BUILD_DIR)/external/glad/%.o,$(GLAD_C))

WIN_OUT = $(WIN_BUILD_DIR)/app.exe
WIN_DEP = $(WIN_OBJ:.o=.d)

-include $(WIN_DEP)

win: $(WIN_OUT)

$(WIN_OUT): $(WIN_OBJ)
	$(WIN_CXX) $(WIN_OBJ) -o $@ $(WIN_LDFLAGS)

$(WIN_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(WIN_CXX) $(WIN_CXXFLAGS) -MMD -MP -c $< -o $@

$(WIN_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(WIN_CXX) $(WIN_CXXFLAGS) -MMD -MP -c $< -o $@

$(WIN_BUILD_DIR)/external/imgui/%.o: $(EXTERNAL_IMGUI_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(WIN_CXX) $(WIN_CXXFLAGS) -MMD -MP -c $< -o $@

$(WIN_BUILD_DIR)/external/glad/%.o: $(EXTERNAL_GLAD_DIR)/%.c
	@mkdir -p $(dir $@)
	$(WIN_CXX) $(WIN_CXXFLAGS) -MMD -MP -c $< -o $@

# --- DISTRIBUTION ---
DIST_LINUX = $(DIST_DIR)/linux
DIST_WIN   = $(DIST_DIR)/win

dist-linux: linux
	@mkdir -p $(DIST_LINUX)
	cp $(LINUX_OUT) $(DIST_LINUX)/
	cp -r assets $(DIST_LINUX)/
	cp -r shaders $(DIST_LINUX)/

dist-win: win
	@mkdir -p $(DIST_WIN)
	cp $(WIN_OUT) $(DIST_WIN)/
	cp -r assets $(DIST_WIN)/
	cp -r shaders $(DIST_WIN)/
	cp -r lib/win/* $(DIST_WIN)/

dist: dist-linux dist-win

run: linux
	$(LINUX_OUT)

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)
