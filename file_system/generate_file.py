
# Helper function to generate random data filled test file
from random import randrange
import numpy

array = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]

for x in array:

  fp = open("size%sM" % x, "w+")

  content = numpy.random.bytes(x*1024*1024)

  fp.write(content);
  fp.close()