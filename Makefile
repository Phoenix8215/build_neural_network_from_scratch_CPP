CONFIG_LOCAL  :=  ./config/Makefile.config

include $(CONFIG_LOCAL)

BUILD_PATH    :=  build
SRC_PATH      :=  src
INC_PATH      :=  include

CXX_SRC       :=  $(wildcard $(SRC_PATH)/*.cpp)

APP_OBJS      :=  $(patsubst $(SRC_PATH)%, $(BUILD_PATH)%, $(CXX_SRC:.cpp=.cpp.o))

APP_MKS       :=  $(APP_OBJS:.o=.mk)

APP_DEPS      :=  $(CXX_SRC)

# -----------------------------------------------------

CXXFLAGS      :=  -std=c++17 -pthread -fPIC


INCS          :=  -I $(INC_PATH) \
					`pkg-config --cflags eigen3`

LIBS          :=  -lstdc++fs 


ifeq ($(DEBUG),1)

CXXFLAGS      +=  -g -O0
else

CXXFLAGS      +=  -O3 
endif

ifeq ($(SHOW_WARNING),1)
CXXFLAGS      +=  -Wall -Wunused-function -Wunused-variable -Wfatal-errors
else
CXXFLAGS      +=  -w
endif

.PHONY: all update show clean $(APP) 
all: 
	$(MAKE) $(APP)

update: $(APP)
	@echo finished updating 😎😎😎$<

$(APP): $(APP_DEPS) $(APP_OBJS)
	@$(CXX) $(APP_OBJS) -o $@ $(LIBS) $(INCS)
	@echo finished building $@. Have fun!!🥰🥰🥰

show: 
	@echo $(BUILD_PATH)
	@echo $(APP_DEPS)
	@echo $(INCS)
	@echo $(APP_OBJS)
	@echo $(APP_MKS)

clean:
	-rm -rf $(APP) 😭
	-rm -rf build 😭


ifneq ($(MAKECMDGOALS), clean)
-include $(APP_MKS)
endif

# Compile CXX
$(BUILD_PATH)/%.cpp.o: $(SRC_PATH)/%.cpp 
	@echo Compile CXX $@
	@mkdir -p $(BUILD_PATH)
	@$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCS)
$(BUILD_PATH)/%.cpp.mk: $(SRC_PATH)/%.cpp
	@echo Compile Dependence CXX $@
	@mkdir -p $(BUILD_PATH)
	@$(CXX) -M $< -MF $@ -MT $(@:.cpp.mk=.cpp.o) $(CXXFLAGS) $(INCS) 



