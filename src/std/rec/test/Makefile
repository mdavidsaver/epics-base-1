#*************************************************************************
# Copyright (c) 2012 UChicago Argonne LLC, as Operator of Argonne
#     National Laboratory.
# Copyright (c) 2002 The Regents of the University of California, as
#     Operator of Los Alamos National Laboratory.
# EPICS BASE is distributed subject to a Software License Agreement found
# in the file LICENSE that is included with this distribution. 
#*************************************************************************
TOP=../../../..

include $(TOP)/configure/CONFIG

PROD_LIBS = dbRecStd dbCore ca Com

TARGETS += $(COMMON_DIR)/recTestIoc.dbd
recTestIoc_DBD = base.dbd
TESTFILES += $(COMMON_DIR)/recTestIoc.dbd

testHarness_SRCS += recTestIoc_registerRecordDeviceDriver.cpp

TESTPROD_HOST += arrayOpTest
arrayOpTest_SRCS += arrayOpTest.c
arrayOpTest_SRCS += recTestIoc_registerRecordDeviceDriver.cpp
testHarness_SRCS += arrayOpTest.c
TESTFILES += ../arrayOpTest.db
TESTS += arrayOpTest

TARGETS += $(COMMON_DIR)/analogMonitorTest.dbd
analogMonitorTest_DBD += base.dbd
TESTPROD_HOST += analogMonitorTest
analogMonitorTest_SRCS += analogMonitorTest.c
analogMonitorTest_SRCS += analogMonitorTest_registerRecordDeviceDriver.cpp
testHarness_SRCS += analogMonitorTest.c
testHarness_SRCS += analogMonitorTest_registerRecordDeviceDriver.cpp
TESTFILES += $(COMMON_DIR)/analogMonitorTest.dbd ../analogMonitorTest.db
TESTS += analogMonitorTest

# epicsRunRecordTests runs all the test programs in a known working order.
testHarness_SRCS += epicsRunRecordTests.c

recordTestHarness_SRCS += $(testHarness_SRCS)
recordTestHarness_SRCS_RTEMS += rtemsTestHarness.c

PROD_vxWorks = recordTestHarness
PROD_RTEMS = recordTestHarness

TESTSPEC_vxWorks = recordTestHarness.munch; epicsRunRecordTests
TESTSPEC_RTEMS = recordTestHarness.boot; epicsRunRecordTests

TESTSCRIPTS_HOST += $(TESTS:%=%.t)

include $(TOP)/configure/RULES
