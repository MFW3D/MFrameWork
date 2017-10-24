# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: DB_Logic.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import DB_Base_pb2 as DB__Base__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='DB_Logic.proto',
  package='PDB_Logic',
  syntax='proto3',
  serialized_pb=_b('\n\x0e\x44\x42_Logic.proto\x12\tPDB_Logic\x1a\rDB_Base.proto\"\x12\n\x10LDIdentification\"\x12\n\x10\x44LIdentification*\x1b\n\x07\x45\x44G_CMD\x12\x10\n\x0c\x45\x44G_CMD_None\x10\x00\x62\x06proto3')
  ,
  dependencies=[DB__Base__pb2.DESCRIPTOR,])

_EDG_CMD = _descriptor.EnumDescriptor(
  name='EDG_CMD',
  full_name='PDB_Logic.EDG_CMD',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='EDG_CMD_None', index=0, number=0,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=84,
  serialized_end=111,
)
_sym_db.RegisterEnumDescriptor(_EDG_CMD)

EDG_CMD = enum_type_wrapper.EnumTypeWrapper(_EDG_CMD)
EDG_CMD_None = 0



_LDIDENTIFICATION = _descriptor.Descriptor(
  name='LDIdentification',
  full_name='PDB_Logic.LDIdentification',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=44,
  serialized_end=62,
)


_DLIDENTIFICATION = _descriptor.Descriptor(
  name='DLIdentification',
  full_name='PDB_Logic.DLIdentification',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=64,
  serialized_end=82,
)

DESCRIPTOR.message_types_by_name['LDIdentification'] = _LDIDENTIFICATION
DESCRIPTOR.message_types_by_name['DLIdentification'] = _DLIDENTIFICATION
DESCRIPTOR.enum_types_by_name['EDG_CMD'] = _EDG_CMD
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

LDIdentification = _reflection.GeneratedProtocolMessageType('LDIdentification', (_message.Message,), dict(
  DESCRIPTOR = _LDIDENTIFICATION,
  __module__ = 'DB_Logic_pb2'
  # @@protoc_insertion_point(class_scope:PDB_Logic.LDIdentification)
  ))
_sym_db.RegisterMessage(LDIdentification)

DLIdentification = _reflection.GeneratedProtocolMessageType('DLIdentification', (_message.Message,), dict(
  DESCRIPTOR = _DLIDENTIFICATION,
  __module__ = 'DB_Logic_pb2'
  # @@protoc_insertion_point(class_scope:PDB_Logic.DLIdentification)
  ))
_sym_db.RegisterMessage(DLIdentification)


# @@protoc_insertion_point(module_scope)
