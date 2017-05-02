TARGET = nic_stat_olas

LIBS += base net config timeout

SRC_CC += component.cc main.cc uplink.cc interface.cc

INC_DIR += $(PRG_DIR)
