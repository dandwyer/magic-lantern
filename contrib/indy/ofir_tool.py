# ofir_tool.py 
# Copyright (C) 2010 Arm.Indy, arm.indiana at google mail
# decode fir updates for 5D, 30D and 400D

# based on eos_tools_v11\dissect_fw2_5d and eos_tools_v11\dissect_fw2
# see eos_tools_v11.tar, http://chdk.setepontos.com/index.php/topic,111.msg11400.html#msg11400
"""
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor,
Boston, MA  02110-1301, USA.
"""
import os
import sys
import array
from struct import unpack
import ctypes
from binascii import hexlify, unhexlify
from optparse import OptionParser

version_id = "0.6 for 5D/30D/400D (11Nov2010)"
# based on a previous tool in C, dec 2009

# for 300D and 10D, see :
# - Alex Berstein 300d: http://wiki.alexbernstein.com/FirmwareDecrypterUnpacker  
# - module_list.cpp, to extract files from 300d firmware (http://iiepwie.narod.ru/) 

# decoding tables for 20D, 20Da, 350D, 30D, 5D and 400D
# found by Alex Berstein (30May2005): http://tech.groups.yahoo.com/group/canondigicamhacking/message/5712
# taken from eos_tools_v11/decrypt_fw1/20D_table.h
t512 = [ 0x53, 0xca, 0x81, 0x0a, 0x4d, 0xe1, 0xb2, 0x7f, 0x43, 0xf1, 0x95, 0xf6, 0xe9, 0x0d, 0x6c, 0x3c,
 0xb8, 0xaa, 0x79, 0xd8, 0x40, 0xcd, 0xb2, 0xed,  0x00, 0xf9, 0xd1, 0xd0, 0x14, 0x1c, 0x9a, 0x2c,
 0xf0, 0xf4, 0xf3, 0x1f, 0xb8, 0x0d, 0x99, 0xc7,  0x8c, 0xd8, 0xf3, 0x67, 0xe4, 0xf5, 0x2c, 0x32,
 0x5e, 0xd8, 0xe2, 0x72, 0xd4, 0x8f, 0x1d, 0x95, 0x00, 0x8d, 0xdc, 0x58, 0xf6, 0xde, 0xa5, 0x3c,
 0x7e, 0xe8, 0x46, 0xc7, 0x77, 0x20, 0x45, 0x18, 0x32, 0x33, 0xc7, 0xd5, 0x46, 0x3f, 0x50, 0x06,
 0x2d, 0xb8, 0xc4, 0x80, 0xa3, 0x4a, 0xed, 0x3f, 0xbf, 0x38, 0xad, 0xd2, 0x0c, 0xc3, 0x8e, 0xa4,
 0x29, 0x69, 0x90, 0xbe, 0xdb, 0x1c, 0x21, 0x75, 0x36, 0x93, 0x0b, 0xaf, 0xc7, 0xad, 0x97, 0xc5,
 0xd7, 0xa2, 0x30, 0x12, 0xfd, 0x40, 0x30, 0x9f, 0xa6, 0x18, 0xff, 0xdb, 0xbd, 0xfa, 0x9d, 0xbc,
 0x97, 0x09, 0x94, 0x53, 0x80, 0x86, 0x81, 0xb8, 0x2a, 0xdd, 0x6a, 0x31, 0x32, 0x8e, 0x7e, 0xe5,
 0xe3, 0x84, 0x13, 0x5e, 0x6e, 0xc7, 0x06, 0x1d, 0x0b, 0xff, 0x83, 0x75, 0x2d, 0xa4, 0xa3, 0xfb,
 0xc4, 0x34, 0x06, 0xdc, 0xd4, 0x2b, 0x65, 0xee, 0xa7, 0x79, 0x50, 0xf6, 0xbc, 0x32, 0xe1, 0x3c,
 0x39, 0x41, 0x0c, 0xc0, 0x48, 0x90, 0x42, 0x3c, 0xa7, 0xb6, 0x74, 0x3c, 0xdd, 0x6a, 0x5c, 0x8c,
 0x17, 0xf6, 0x84, 0x73, 0x01, 0x0c, 0x05, 0xa2, 0xdf, 0x1d, 0x40, 0xa2, 0xbd, 0xe9, 0x63, 0xaf,
 0xd4, 0xee, 0xcd, 0xf9, 0x18, 0x01, 0x95, 0x89, 0xdd, 0x8a, 0xac, 0x79, 0x26, 0x78, 0xed, 0x63,
 0xd0, 0x11, 0x60, 0xc9, 0xea, 0xd7, 0x16, 0xce, 0x79, 0x83, 0x2c, 0xb1, 0x5b, 0xf8, 0xf3, 0x98,
 0x97, 0x61, 0x88, 0x02, 0x2b, 0xe9, 0x90, 0xeb, 0xf5, 0x15, 0x10, 0x0b, 0xf9, 0x11, 0x3c, 0x31,
 0x2b, 0x44, 0x27, 0x1f, 0xdd, 0x26, 0x7b, 0x8e, 0x84, 0x97, 0x6b, 0x72, 0x8d, 0x0a, 0xc0, 0x35,
 0xac, 0x75, 0x4d, 0x81, 0xad, 0x4f, 0x4c, 0xa1, 0x89, 0x72, 0x2d, 0xa0, 0xa6, 0x10, 0x23, 0x10,
 0x99, 0xd7, 0x10, 0x46, 0x9a, 0x63, 0xed, 0x71, 0x8a, 0x5b, 0x46, 0x7e, 0x09, 0x82, 0x29, 0x4b,
 0x6d, 0x44, 0x1b, 0x2b, 0xed, 0x21, 0x48, 0xff, 0xdf, 0x17, 0xbf, 0x69, 0x95, 0xd8, 0x9f, 0x7f,
 0x4a, 0x11, 0x29, 0x65, 0x4e, 0x9d, 0xdf, 0x8f, 0x31, 0x84, 0x21, 0x04, 0xbf, 0xe7, 0x31, 0xaf,
 0x51, 0x9a, 0x94, 0x9b, 0x0c, 0x70, 0xaf, 0x48, 0xc0, 0x1f, 0x3e, 0x41, 0xbb, 0x66, 0xe7, 0xcf,
 0x37, 0xc5, 0x96, 0x35, 0xb2, 0x32, 0x5e, 0x9e, 0xfc, 0xb1, 0x0f, 0xcc, 0xc1, 0x06, 0xfe, 0xcb,
 0x91, 0xe4, 0xc9, 0x6e, 0xcc, 0x17, 0x79, 0x29, 0x40, 0x20, 0x60, 0x3f, 0xe5, 0x45, 0x4d, 0x30,
 0x53, 0x29, 0x45, 0x5f, 0x47, 0x23, 0xb0, 0x12, 0xd2, 0xbb, 0x7f, 0x2b, 0x0a, 0x51, 0xa5, 0xe0,
 0x46, 0x97, 0xff, 0x60, 0x9e, 0x30, 0x36, 0x22, 0xf5, 0x8b, 0x63, 0xdb, 0xeb, 0xae, 0xe7, 0x08,
 0xb0, 0x0d, 0xd0, 0x76, 0x85, 0x72, 0xdf, 0x0b, 0xd9, 0x10, 0xc6, 0x81, 0x89, 0x35, 0x5b, 0xa6,
 0xf5, 0x9d, 0x56, 0xc8, 0x3b, 0xf8, 0x1e, 0x62, 0xcd, 0x4d, 0x8b, 0xa7, 0x74, 0xeb, 0x8d, 0x56,
 0xfa, 0x5c, 0xa3, 0x94, 0x39, 0xfc, 0x70, 0xc7, 0xc0, 0x80, 0x14, 0xad, 0x33, 0xb6, 0x08, 0x6f,
 0x63, 0x8b, 0x9c, 0x8f, 0x24, 0x4c, 0x91, 0xf6, 0x01, 0x0e, 0x50, 0xe2, 0x14, 0x37, 0x8a, 0xa2,
 0x18, 0x2c, 0x3b, 0x93, 0x96, 0x0d, 0xe2, 0xdf, 0xa0, 0x61, 0x65, 0x4d, 0x1b, 0xb6, 0x02, 0x6d,
 0x04, 0x08, 0x31, 0x58, 0x7d, 0xa6, 0x76, 0xb5, 0x61, 0x05, 0xb5, 0xc5, 0xdd, 0x06, 0xa7, 0x30  ]
t513 = [ 0xdb, 0x87, 0x6c, 0xb6, 0xcf, 0x08, 0x5b, 0x3c, 0x2c, 0x16, 0x42, 0x6c, 0x5b, 0x58, 0x20, 0x6e,
 0xfc, 0xbb, 0x25, 0xa9, 0xd3, 0x1f, 0x45, 0x12, 0x0e, 0xa9, 0xd7, 0x2b, 0xdd, 0x5f, 0xf5, 0xcd,
 0xad, 0x00, 0xeb, 0xa1, 0xf9, 0x00, 0x2a, 0x3c, 0x8c, 0xda, 0x7c, 0xdb, 0x25, 0x05, 0xfb, 0x90,
 0xf6, 0xda, 0xdc, 0xd9, 0x76, 0x24, 0x35, 0x59, 0x13, 0xeb, 0x69, 0xee, 0x43, 0x5f, 0x4d, 0x79,
 0x15, 0xbd, 0x8b, 0xd5, 0xf9, 0x06, 0x08, 0xbb, 0xf0, 0x92, 0x36, 0xa6, 0x06, 0xc4, 0xf4, 0x90,
 0xa4, 0x20, 0x4d, 0x8e, 0xc6, 0x7a, 0xe3, 0xd7, 0x9d, 0x5a, 0x61, 0xb1, 0xbd, 0x94, 0x2e, 0x52,
 0x02, 0x73, 0xa3, 0x26, 0x45, 0xfe, 0x54, 0xf7, 0x4f, 0x7a, 0xc4, 0xa4, 0x79, 0xcf, 0xbb, 0x8f,
 0x99, 0xfe, 0x4d, 0x7b, 0x98, 0xed, 0x45, 0x46, 0xce, 0x20, 0xa3, 0x3a, 0x58, 0x0d, 0x36, 0x99,
 0x44, 0x7b, 0x42, 0x8e, 0x55, 0x37, 0x67, 0xda, 0xf8, 0x37, 0x3d, 0x71, 0x52, 0xfd, 0xe5, 0xdf,
 0xb5, 0x19, 0x37, 0x91, 0x61, 0xe8, 0x5a, 0xa2, 0x29, 0xce, 0x5e, 0x59, 0x71, 0x39, 0xf3, 0x5e,
 0xb6, 0x0c, 0x2d, 0x53, 0x86, 0x9f, 0xcc, 0x16, 0x73, 0xd1, 0x6d, 0x81, 0xe9, 0xfc, 0x25, 0x48,
 0x57, 0x89, 0xe4, 0x10, 0xd4, 0x5a, 0x32, 0xf8, 0xc8, 0x01, 0x44, 0xcb, 0x92, 0xb4, 0x84, 0x91,
 0x80, 0xcd, 0xfc, 0x42, 0xec, 0xec, 0x13, 0x6e, 0x28, 0x6e, 0x18, 0x46, 0x9f, 0xaa, 0xef, 0x95,
 0xb6, 0x42, 0xa2, 0xab, 0x9a, 0x16, 0xce, 0x84, 0xc4, 0xd0, 0x96, 0x52, 0xd2, 0x95, 0x05, 0x18,
 0xa9, 0x57, 0xb9, 0xae, 0x54, 0xc8, 0xe3, 0x27, 0x4c, 0x7f, 0x38, 0xb0, 0x66, 0xf7, 0x06, 0xa4,
 0xbf, 0xa0, 0xe1, 0xcc, 0xec, 0xc5, 0x35, 0x01, 0x4b, 0x37, 0x1d, 0x9b, 0x8d, 0x2a, 0x1b, 0xba,
 0x28, 0xcb, 0xe2, 0xbe, 0x58, 0x12, 0xb1, 0x55, 0xda, 0x7b, 0xaa, 0x4e, 0xb4, 0x1b, 0x9e, 0x05,
 0x84, 0xe6, 0x91, 0x6c, 0x9f, 0x88, 0xe8, 0xf0, 0x15, 0x2b, 0x30, 0x9b, 0x66, 0xf7, 0xf0, 0xcf,
 0x0b, 0x81, 0x59, 0xd1, 0x87, 0x06, 0xe8, 0x24, 0x16, 0x2a, 0x97, 0x3c, 0x3a, 0x07, 0x39, 0x75,
 0x58, 0xd1, 0xd4, 0x54, 0x33, 0xc0, 0xd9, 0x28, 0xd7, 0x85, 0xcc, 0xf9, 0xa4, 0x0d, 0x76, 0x32,
 0xeb, 0xd6, 0x83, 0x99, 0x6a, 0xd7, 0xf3, 0x24, 0xbe, 0x5e, 0xe5, 0xf3, 0xca, 0x71, 0x53, 0x4c,
 0x1a, 0xe0, 0xbc, 0x92, 0xcb, 0x4e, 0xaa, 0xdf, 0x98, 0xde, 0x02, 0xf0, 0x5c, 0x7b, 0xda, 0x5b,
 0x3f, 0xa9, 0x43, 0x3b, 0x58, 0x7f, 0x90, 0xba, 0x35, 0xdd, 0x3c, 0x79, 0x5d, 0x6c, 0x7b, 0xb6,
 0x92, 0xc1, 0x9e, 0xe8, 0xd3, 0x44, 0x04, 0x6c, 0xdb, 0x2e, 0x32, 0x88, 0xe8, 0x4f, 0x33, 0x77,
 0xbf, 0xb1, 0xce, 0x1d, 0x65, 0x9d, 0x09, 0x2e, 0x45, 0x5b, 0x54, 0xfd, 0x14, 0x75, 0xdc, 0xd7,
 0xc3, 0x9a, 0x69, 0x07, 0x6d, 0x1c, 0xb3, 0x97, 0x86, 0x11, 0xe1, 0x11, 0xab, 0x19, 0xd4, 0x8f,
 0xee, 0x30, 0x77, 0x4e, 0xc6, 0xfb, 0xce, 0xdd, 0x74, 0xe0, 0x21, 0xb7, 0xa7, 0x67, 0x84, 0xa1,
 0x2e, 0x43, 0x66, 0xbd, 0xc9, 0x8b, 0x6a, 0x84, 0x26, 0x76, 0x17, 0x8c, 0x1c, 0x0d, 0x5b, 0x15,
 0xc9, 0x38, 0x27, 0xaf, 0x9e, 0xe1, 0x71, 0x95, 0xb9, 0x50, 0xe7, 0x69, 0x09, 0x38, 0x57, 0x84,
 0xfd, 0x41, 0x73, 0x96, 0xef, 0xc3, 0xa9, 0xf1, 0x3b, 0xc2, 0xb3, 0x25, 0x24, 0xb9, 0x95, 0x20,
 0x5f, 0x92, 0x74, 0xec, 0x33, 0x87, 0x9e, 0x50, 0xde, 0x25, 0xe0, 0x22, 0x6d, 0xb6, 0x44, 0x6e,
 0xd1, 0xe4, 0xe5, 0x75, 0xe1, 0x7e, 0xbe, 0x84, 0x82, 0x8c, 0x4a, 0x3e, 0x2b, 0x97, 0x9f, 0x91,
 0x7e ]            

models = [ [ 0x80000213, '5D'], [ 0x80000234, '30D'], [ 0x80000236, '400D / Rebel XTi'] ]

def getLongLE(d, a):
   return unpack('<L',(d)[a:a+4])[0]
def getLongSE(d, a):
   return unpack('<H',(d)[a:a+2])[0]

def getModel(id):
  for i in models:
    if i[0]==id:
      return i[1]
  return None

def xor_decode( start, len ):
  o512 = 0
  o513 = 0
  out = array.array('B', m[start:start+len] )
  for i in range(len):
    out[i] =  out[i] ^ t512[o512] ^ t513[o513] 
    o512 = (o512+1) % 512
    o513 = (o513+1) % 513
  return out

def check_xor_decoding( out):
  if (out[8:16].tostring() == 'Copyrigh') :
    return True
  else:
    return False

def decipher_updater( offset, len, filename):
  out = xor_decode( offset, len)
  print ' xor_decoding [0x%x-0x%x]...' % ( offset, offset+len),
  if check_xor_decoding( out[0x10:] ):
    print 'OK (%s)' % filename
    f = open(filename, 'wb')
    out.tofile(f)
    f.close()
  else:
    print 'KO'

def getData(firmware, offset, modelId):
  nFiles = getLongLE( m2, offset )
  print '0x%03x: number of files in the pack = %d' % (offset+0x20, nFiles)
  tableOffset = getLongLE( m2, offset+4 )
  print '0x%03x: offset to the file table = 0x%x (from 0x%x)' % (offset+0x20+4, tableOffset, firmware)
  headerSize = getLongLE( m2, offset+8 )
  print '0x%03x: header size = 0x%x (from 0x%x). end of header = 0x%x' % (offset+0x20+8, headerSize, firmware, firmware+headerSize)
  val = getLongLE( m2, offset+0xc )
  print '0x%03x: size of file table = 0x%x ' % (offset+0x20+0xc, val)
  val = getLongLE( m2, offset+0x10 )
  print '0x%03x: size after table = 0x%x' % (offset+0x20+0x10, val )
  return nFiles, tableOffset, headerSize

#see eos_tools_v11\400D_pack\eospack.c for the 'pack structure'
def getTable(firmware, modelId, offset, nFiles, headerSize, n):
  pOffset=0
  pLength=0
  if modelId==0x80000213: #5D
    print '              +-flags-+-offset-+-length-+--name--------------------------+---??---'
  else:
    print '              +-flags-+-offset-+-length-+--name--------------------+'
  for i in range(nFiles):
    flag = getLongLE( m2, offset )
    print '0x%06x: 0x%02x 0x%04x ' % (offset+0x20, i+1, flag ),
    offset = offset+4
    val = getLongLE( m2, offset )
    if i+1==n:
      pOffset = val
    print '0x%06x' % (val ),
    val = getLongLE( m2, offset+4 )
    if i+1==n:
      pLength = val
    print '0x%06x' % (val ),
    end  = m2[ offset+8: ].find("\0")
    if modelId == 0x80000213:
      if flag == 1:
        print '%-32s' % ctypes.c_char_p(m2[ offset+8: offset+8+28]).value, #null terminated string
        val = getLongLE( m2, offset+36 )
        print '0x%02x' % (val ),
      else:
        print '%-32s' % ctypes.c_char_p(m2[ offset+8: offset+8+32]).value, 
      val = getLongLE( m2, offset+40 )
      print '0x%06x' % (val )
      offset = offset + 44
    else:
      print '%-32s' % ctypes.c_char_p(m2[ offset+8: offset+8+28]).value
      offset = offset + 36
  print '0x%06x: (+0x%x) end of table, first file' % (offset+0x20, headerSize)
  return pOffset, pLength
    
parser = OptionParser(usage="usage: %prog [options] filename")
parser.add_option("-c", "--checksum", action="store_true", dest="checksum", default=False, help="verify checksum(s)")
parser.add_option("-v", "--verbose", action="store_true", dest="verbose", default=False, help="verbose mode")
parser.add_option("-x", "--extract", type="int", dest="extract", default=-1, help="extract part")
(options, args) = parser.parse_args()
  
f = open(args[0], 'rb')
m = f.read()
fileLen = f.tell()
f.close()

print 'Fir_tool %s\n' % version_id
print 'fileLen = 0x%x' % fileLen
print '---.fir header---'
modelId = getLongLE( m, 0 )
print '0x000: modelId = 0x%08x,' % modelId,
modelName = getModel( modelId )
if (modelName!=None):
  print '(%s, VxWorks)' % (modelName)
else:
  print 'not supported'
  sys.exit()
print '0x010: version = %s' % ( m[0x10:0x10+5] )

print '---ciphered part (xor)---'

prefix = '{0:04x}'.format(modelId & 0xffff) + "_" + m[0x10]+m[0x12]+m[0x14] 
decipher_updater( 0x20, fileLen-0x20, prefix+'_firmware.bin')

f = open(prefix+'_firmware.bin', 'rb')
m2 = f.read()
f.close()

fsum = getLongLE( m2, 0 )
print '0x020: checksum = 0x%08x' %  fsum 
if options.checksum:
  csum = sum( array.array('B', m[ 0:0x20 ]) ) + sum( array.array('B', m2[ 4:fileLen-4 ]) )
  if fsum != ctypes.c_uint32(~csum).value:
    print " checksum error csum=0x%x" % (csum)
  else:
    print " checksum computing [0x%x-0x%x] is OK!" % (0x0 , fileLen)

updater1 = getLongLE( m2, 4 )
print '0x024: updater offset = 0x%x' % ( updater1 )
firmware = getLongLE( m2, 8 )
print '0x028: firmware pack offset = 0x%x' % firmware
val = getLongLE( m, 0xc )
print '0x02c:  = 0x%x' % val
print '0x030: ---updater---'

print '0x%03x: ---firmware---' % (firmware)
fsum2 = getLongLE( m2, firmware-0x20 )
print '0x%03x: (+0x000) firmware checksum = 0x%x' % (firmware, fsum2)
if options.checksum:
  csum = sum( array.array('B', m2[ firmware-0x20+4:fileLen-0x20 ]) )
  if fsum2 != ctypes.c_uint32(~csum).value:
    print " checksum error csum=0x%x" % (csum)
  else:
    print " checksum computing [0x%x-0x%x] is OK!" % (firmware+4 , fileLen)
if modelId==0x80000213:
  val = getLongLE( m2, firmware-0x20+4 )
  print '0x%03x: 0x%x (only with 5D)' % (firmware+4, val)
  nFiles, tableOffset, headerSize = getData(firmware, firmware-0x20+8, modelId)
  val = getLongLE( m2, firmware-0x20+tableOffset-4 )
  print '0x%03x: 0x%x (only with 5D)' % (firmware-0x20+tableOffset-4, val) #dissect_fw2_d5.c is buggy on this!
else:
  nFiles, tableOffset, headerSize  = getData(firmware, firmware-0x20+4, modelId)

print '0x%03x: (+0x%03x) files table' % (firmware-0x20+tableOffset, tableOffset)
pOffset, pLength = getTable(firmware, modelId, firmware-0x20+tableOffset, nFiles, headerSize, options.extract)

if options.extract != -1 and pLength!=0:
  name = prefix+'_'+'{0:02x}'.format(options.extract)+'.bin'
  print '\nwriting %s [0x%x-0x%x]. size=0x%x/%d' % (name, pOffset, pOffset+pLength, pLength, pLength)
  f = open(name, 'wb')
  f.write( m2[ firmware+pOffset-0x20: firmware+pOffset-0x20+pLength ] )
  f.close()
