CXX      := -c++
MOC      := moc
UIC      := uic
CXXFLAGS := -fPIC
LDFLAGS  := -L/usr/lib/x86_64-linux-gnu -lQt5Widgets -lQt5Gui -lQt5Core -lQt5Charts -lparted
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/src
INC_DIR  := $(BUILD)/include
MOC_DIR  := $(BUILD)/moc
TARGET   := PrintParted
INCLUDE  := 			\
	-Iinclude/ \
	-I$(INC_DIR) \
	-I/usr/include/x86_64-linux-gnu/qt5 \
	-I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
	-I/usr/include/x86_64-linux-gnu/qt5/QtCore \
	-I/usr/include/x86_64-linux-gnu/qt5/QtGui \
	-I/usr/include/x86_64-linux-gnu/qt5/QtCharts \
	
SRC      :=                      \
	$(wildcard src/*.cpp)         \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

# generate ui_widget.h
$(INC_DIR)/ui_widget.h: src/widget.ui
	$(UIC) $< -o $@

# compile all cpp source files
$(OBJ_DIR)/%.o: %.cpp $(INC_DIR)/ui_widget.h
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# process moc header with Qt's moc utility
$(MOC_DIR)/moc_widget.cpp: include/widget.h
	$(MOC) $(INCLUDE) $< -o $@
	
$(MOC_DIR)/moc_chart.cpp: include/chart.h
	$(MOC) $(INCLUDE) $< -o $@
	
$(MOC_DIR)/moc_disk.cpp: include/disk.h
	$(MOC) $(INCLUDE) $< -o $@	
	
$(MOC_DIR)/moc_comboboxmodel.cpp: include/comboboxmodel.h
	$(MOC) $(INCLUDE) $< -o $@
	
$(MOC_DIR)/moc_dialog.cpp: include/dialog.h
	$(MOC) $(INCLUDE) $< -o $@	
	
$(MOC_DIR)/moc_disktablemodel.cpp: include/disktablemodel.h
	$(MOC) $(INCLUDE) $< -o $@	
	
$(MOC_DIR)/moc_freespace.cpp: include/freespace.h
	$(MOC) $(INCLUDE) $< -o $@	
	
$(MOC_DIR)/moc_freespacemodel.cpp: include/freespacemodel.h
	$(MOC) $(INCLUDE) $< -o $@	
	
$(MOC_DIR)/moc_part.cpp: include/part.h
	$(MOC) $(INCLUDE) $< -o $@		
	
$(MOC_DIR)/moc_parttablemodel.cpp: include/parttablemodel.h
	$(MOC) $(INCLUDE) $< -o $@
			
# compile the output of Qt's moc utility
$(OBJ_DIR)/src/moc_widget.o: $(MOC_DIR)/moc_widget.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_chart.o: $(MOC_DIR)/moc_chart.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_disk.o: $(MOC_DIR)/moc_disk.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_comboboxmodel.o: $(MOC_DIR)/moc_comboboxmodel.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_dialog.o: $(MOC_DIR)/moc_dialog.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_disktablemodel.o: $(MOC_DIR)/moc_disktablemodel.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_freespace.o: $(MOC_DIR)/moc_freespace.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_freespacemodel.o: $(MOC_DIR)/moc_freespacemodel.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_part.o: $(MOC_DIR)/moc_part.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(OBJ_DIR)/src/moc_parttablemodel.o: $(MOC_DIR)/moc_parttablemodel.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# linking libraries must follow the executable and not precede it
$(APP_DIR)/$(TARGET): $(OBJ_DIR)/src/moc_widget.o \
			$(OBJ_DIR)/src/moc_chart.o \
			$(OBJ_DIR)/src/moc_disk.o \
			$(OBJ_DIR)/src/moc_comboboxmodel.o \
			$(OBJ_DIR)/src/moc_dialog.o \
			$(OBJ_DIR)/src/moc_disktablemodel.o \
			$(OBJ_DIR)/src/moc_freespace.o \
			$(OBJ_DIR)/src/moc_freespacemodel.o \
			$(OBJ_DIR)/src/moc_part.o \
			$(OBJ_DIR)/src/moc_parttablemodel.o $(OBJECTS)
			
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(INC_DIR)
	@mkdir -p $(MOC_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(INC_DIR)/*
	-@rm -rvf $(MOC_DIR)/*
