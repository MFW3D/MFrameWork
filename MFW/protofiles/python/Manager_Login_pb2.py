# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Manager_Login.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import Common_Base_pb2 as Common__Base__pb2
import DB_Base_pb2 as DB__Base__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='Manager_Login.proto',
  package='PManager_Login',
  syntax='proto3',
  serialized_pb=_b('\n\x13Manager_Login.proto\x12\x0ePManager_Login\x1a\x11\x43ommon_Base.proto\x1a\rDB_Base.proto\"\x1a\n\x06GetCfg\x12\x10\n\x08idstring\x18\x01 \x01(\tb\x06proto3')
  ,
  dependencies=[Common__Base__pb2.DESCRIPTOR,DB__Base__pb2.DESCRIPTOR,])




_GETCFG = _descriptor.Descriptor(
  name='GetCfg',
  full_name='PManager_Login.GetCfg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='idstring', full_name='PManager_Login.GetCfg.idstring', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
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
  serialized_start=73,
  serialized_end=99,
)

DESCRIPTOR.message_types_by_name['GetCfg'] = _GETCFG
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

GetCfg = _reflection.GeneratedProtocolMessageType('GetCfg', (_message.Message,), dict(
  DESCRIPTOR = _GETCFG,
  __module__ = 'Manager_Login_pb2'
  # @@protoc_insertion_point(class_scope:PManager_Login.GetCfg)
  ))
_sym_db.RegisterMessage(GetCfg)


# @@protoc_insertion_point(module_scope)