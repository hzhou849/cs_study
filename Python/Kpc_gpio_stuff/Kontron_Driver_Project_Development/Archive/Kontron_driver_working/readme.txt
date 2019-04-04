qnx specific headers

<sys/mman.h>
<sys/neutrino.h>
<sys/procmgr.h>

These files require the three qnx headers, but I'm not sure what they do and the linux equivalent are
MappedIoAddress.cpp

MappedIoDevice.cpp
MappedMemoryAddress.cpp


MappedIoDevice-inl.h line 67, 71, 75 in16, in8 cast called. linux c++ does not recognize in16,in8 can replace or just remove the cast all together?



