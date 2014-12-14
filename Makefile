BUILD_DIR = build

SRCS := src\data\grade.cc \
				src\data\assessment.cc \
				src\data\student.cc \
				src\data\course.cc \
				src\data\subscriber.cc \
				src\data\observer.cc \
				src\data\bbimporter.cc \
				src\data\config.cc \
				src\sql\gbsql.cc \
				src\gbapp.cc \
				src\gui\views\gbframeView.cc \
				src\gui\controllers\gbframeController.cc \
				src\gui\views\gbdialogassessmentView.cc \
				src\gui\controllers\gbdialogassessmentController.cc \
				src\gui\views\gbdialogcourseView.cc \
				src\gui\controllers\gbdialogcourseController.cc \
				src\gui\views\gbdialogstudentView.cc \
				src\gui\controllers\gbdialogstudentController.cc \
				src\gui\views\gbdialoguseroptionsView.cc \
				src\gui\controllers\gbdialoguseroptionsController.cc \
        src\gui\views\gbdialoggraphView.cc \
        src\gui\controllers\gbdialoggraphController.cc \
        

TEST_SRCS := 	tests\gbsqltest.cc \
							tests\gbtest.cc \
#        tests\bbimportertest.cc

OBJS := $(SRCS:%.cc=$(BUILD_DIR)/%.o)

TEST_OBJS := $(TEST_SRCS:%.cc=$(BUILD_DIR)/%.o)

BUILD = debug

WX_VER = 3.0.1
WX_DIR = lib\wxwidgets-$(WX_VER)
WX_MAKE_DIR = $(WX_DIR)\build\msw
WX_MAKE = makefile.gcc
WX_ARCH = wxwidgets-$(WX_VER).7z

WX_SQL_VER = 3.1.1
WX_SQL_DIR = lib\wxsqlite3-$(WX_SQL_VER)
WX_SQL_MAKE_DIR = $(WX_SQL_DIR)\build30
WX_SQL_MAKE = makefile.gcc
WX_SQL_ARCH = wxsqlite3-$(WX_SQL_VER).7z

SQL_DIR = $(WX_SQL_DIR)\sqlite3

GTEST_VER = 1.7.0
GTEST_DIR = lib\gtest-$(GTEST_VER)
GTEST_ARCH = gtest-$(GTEST_VER).7z

ARCH_TOOL = tools\7za.exe
SQL_TOOL = tools\sqlite3.exe

CPPFLAGS := -Iinclude \
						-Iinclude\data \
						-Iinclude\sql \
						-I$(WX_DIR)\include \
						-I$(WX_DIR)\lib\gcc_lib\mswud \
						-I$(WX_SQL_DIR)\include \
						-I$(GTEST_DIR)\include \
            -Ilib\wxmathplot-0.1.2
						-DBUILD=$(BUILD)

LDFLAGS := 	-L$(SQL_DIR)\lib \
						-L$(WX_SQL_DIR)\lib\gcc_lib	\
						-L$(WX_DIR)\lib\gcc_lib \
						-L$(GTEST_DIR)\make \
            -Llib\wxmathplot-0.1.2\build

LDLIBS :=	-lwxcode_msw30ud_wxsqlite3 -lsqlite3 -lwxmsw30ud_adv -lwxmsw30ud_core \
			-lwxbase30ud -luuid -lole32 -loleaut32 -lwxregexud -lcomctl32 \
			-lgdi32 -lwxpngd -lwxzlibd -lcomdlg32 -lwinspool -lmathplot 

build: setup gbapp

run: build
	$(BUILD_DIR)/gbapp

.PHONY: clean
clean:
	rmdir /Q /S $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cc
	if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))	
	$(CXX) -D__GUI__ -c -o $@ $(CPPFLAGS) $<

test: $(OBJS) $(TEST_OBJS)
	$(CXX) -o $(BUILD_DIR)\$@ $(LDFLAGS) $? $(LDLIBS) -lgtest
	$(BUILD_DIR)\$@

gbapp: $(OBJS)
	$(CXX) -o $(BUILD_DIR)\$@ $(LDFLAGS) $? $(LDLIBS)

setup: wxwidgets wxsqlite3 gtest wxmathplot

dummy:
	$(SQL_TOOL) $(BUILD_DIR)\gb.db < tests\data\gb.sql

wxwidgets:
ifeq (,$(wildcard $(WX_DIR)))
	$(ARCH_TOOL) x -olib lib\$(WX_ARCH)
	$(MAKE) -C $(WX_MAKE_DIR) -f $(WX_MAKE) BUILD=$(BUILD)
endif

wxsqlite3:
ifeq (,$(wildcard $(WX_SQL_DIR)))
	$(ARCH_TOOL) x -olib lib\$(WX_SQL_ARCH)
	$(MAKE) -C $(SQL_DIR)
	$(MAKE) -C $(WX_SQL_MAKE_DIR) -f $(WX_SQL_MAKE) WXWIN=$(CURDIR)\$(WX_DIR)
endif

gtest:
ifeq (,$(wildcard $(GTEST_DIR)))
	$(ARCH_TOOL) x -olib lib\$(GTEST_ARCH)
	$(MAKE) -C $(GTEST_DIR)\make gtest.a
	copy $(GTEST_DIR)\make\gtest.a $(GTEST_DIR)\make\libgtest.a
endif

wxmathplot:
ifeq (,$(wildcard lib\wxmathplot-0.1.2))
	$(ARCH_TOOL) x -olib lib\wxmathplot-0.1.2.7z
	$(MAKE) -C lib\wxmathplot-0.1.2 
endif
