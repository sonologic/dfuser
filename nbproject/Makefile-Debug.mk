#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Attributes.o \
	${OBJECTDIR}/fuser.o \
	${OBJECTDIR}/dfuser.o \
	${OBJECTDIR}/DFuser.o \
	${OBJECTDIR}/Repository.o \
	${OBJECTDIR}/Logger.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs fuse`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dfuser

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dfuser: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dfuser ${OBJECTFILES} ${LDLIBSOPTIONS} 

test.sh: test.bash 
	@echo Performing Custom Build Step
	cp test.bash test.sh

${OBJECTDIR}/Attributes.o: Attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. `pkg-config --cflags fuse`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Attributes.o Attributes.cpp

${OBJECTDIR}/fuser.o: fuser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. `pkg-config --cflags fuse`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/fuser.o fuser.cpp

${OBJECTDIR}/dfuser.o: dfuser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I. `pkg-config --cflags fuse`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/dfuser.o dfuser.c

${OBJECTDIR}/DFuser.o: DFuser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. `pkg-config --cflags fuse`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/DFuser.o DFuser.cpp

${OBJECTDIR}/Repository.o: Repository.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. `pkg-config --cflags fuse`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Repository.o Repository.cpp

${OBJECTDIR}/Logger.o: Logger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. `pkg-config --cflags fuse`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Logger.o Logger.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dfuser
	${RM} test.sh

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
