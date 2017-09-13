/**
 * @fileoverview
 * @enhanceable
 * @public
 */
// GENERATED CODE -- DO NOT EDIT!

goog.provide('proto.PDB_Base.DBGameClub');

goog.require('jspb.Message');
goog.require('jspb.BinaryReader');
goog.require('jspb.BinaryWriter');


/**
 * Generated by JsPbCodeGenerator.
 * @param {Array=} opt_data Optional initial data array, typically from a
 * server response, or constructed directly in Javascript. The array is used
 * in place and becomes part of the constructed object. It is not cloned.
 * If no data is provided, the constructed object will be empty, but still
 * valid.
 * @extends {jspb.Message}
 * @constructor
 */
proto.PDB_Base.DBGameClub = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, null, null);
};
goog.inherits(proto.PDB_Base.DBGameClub, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  proto.PDB_Base.DBGameClub.displayName = 'proto.PDB_Base.DBGameClub';
}


if (jspb.Message.GENERATE_TO_OBJECT) {
/**
 * Creates an object representation of this proto suitable for use in Soy templates.
 * Field names that are reserved in JavaScript and will be renamed to pb_name.
 * To access a reserved field use, foo.pb_<name>, eg, foo.pb_default.
 * For the list of reserved names please see:
 *     com.google.apps.jspb.JsClassTemplate.JS_RESERVED_WORDS.
 * @param {boolean=} opt_includeInstance Whether to include the JSPB instance
 *     for transitional soy proto support: http://goto/soy-param-migration
 * @return {!Object}
 */
proto.PDB_Base.DBGameClub.prototype.toObject = function(opt_includeInstance) {
  return proto.PDB_Base.DBGameClub.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Whether to include the JSPB
 *     instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.PDB_Base.DBGameClub} msg The msg instance to transform.
 * @return {!Object}
 */
proto.PDB_Base.DBGameClub.toObject = function(includeInstance, msg) {
  var f, obj = {
    ulid: jspb.Message.getFieldWithDefault(msg, 1, 0),
    charnickname: jspb.Message.getFieldWithDefault(msg, 2, ""),
    ulcaptain: jspb.Message.getFieldWithDefault(msg, 3, 0),
    uilogoindex: jspb.Message.getFieldWithDefault(msg, 4, 0),
    uimaxmember: jspb.Message.getFieldWithDefault(msg, 5, 0),
    sapplicants: msg.getSapplicants_asB64(),
    snotice: msg.getSnotice_asB64(),
    uistatus: jspb.Message.getFieldWithDefault(msg, 8, 0),
    sdynamicinfo: msg.getSdynamicinfo_asB64(),
    ulcaptainreward: jspb.Message.getFieldWithDefault(msg, 10, 0)
  };

  if (includeInstance) {
    obj.$jspbMessageInstance = msg;
  }
  return obj;
};
}


/**
 * Deserializes binary data (in protobuf wire format).
 * @param {jspb.ByteSource} bytes The bytes to deserialize.
 * @return {!proto.PDB_Base.DBGameClub}
 */
proto.PDB_Base.DBGameClub.deserializeBinary = function(bytes) {
  var reader = new jspb.BinaryReader(bytes);
  var msg = new proto.PDB_Base.DBGameClub;
  return proto.PDB_Base.DBGameClub.deserializeBinaryFromReader(msg, reader);
};


/**
 * Deserializes binary data (in protobuf wire format) from the
 * given reader into the given message object.
 * @param {!proto.PDB_Base.DBGameClub} msg The message object to deserialize into.
 * @param {!jspb.BinaryReader} reader The BinaryReader to use.
 * @return {!proto.PDB_Base.DBGameClub}
 */
proto.PDB_Base.DBGameClub.deserializeBinaryFromReader = function(msg, reader) {
  while (reader.nextField()) {
    if (reader.isEndGroup()) {
      break;
    }
    var field = reader.getFieldNumber();
    switch (field) {
    case 1:
      var value = /** @type {number} */ (reader.readUint64());
      msg.setUlid(value);
      break;
    case 2:
      var value = /** @type {string} */ (reader.readString());
      msg.setCharnickname(value);
      break;
    case 3:
      var value = /** @type {number} */ (reader.readUint64());
      msg.setUlcaptain(value);
      break;
    case 4:
      var value = /** @type {number} */ (reader.readUint32());
      msg.setUilogoindex(value);
      break;
    case 5:
      var value = /** @type {number} */ (reader.readUint32());
      msg.setUimaxmember(value);
      break;
    case 6:
      var value = /** @type {!Uint8Array} */ (reader.readBytes());
      msg.setSapplicants(value);
      break;
    case 7:
      var value = /** @type {!Uint8Array} */ (reader.readBytes());
      msg.setSnotice(value);
      break;
    case 8:
      var value = /** @type {number} */ (reader.readUint32());
      msg.setUistatus(value);
      break;
    case 9:
      var value = /** @type {!Uint8Array} */ (reader.readBytes());
      msg.setSdynamicinfo(value);
      break;
    case 10:
      var value = /** @type {number} */ (reader.readUint64());
      msg.setUlcaptainreward(value);
      break;
    default:
      reader.skipField();
      break;
    }
  }
  return msg;
};


/**
 * Serializes the message to binary data (in protobuf wire format).
 * @return {!Uint8Array}
 */
proto.PDB_Base.DBGameClub.prototype.serializeBinary = function() {
  var writer = new jspb.BinaryWriter();
  proto.PDB_Base.DBGameClub.serializeBinaryToWriter(this, writer);
  return writer.getResultBuffer();
};


/**
 * Serializes the given message to binary data (in protobuf wire
 * format), writing to the given BinaryWriter.
 * @param {!proto.PDB_Base.DBGameClub} message
 * @param {!jspb.BinaryWriter} writer
 */
proto.PDB_Base.DBGameClub.serializeBinaryToWriter = function(message, writer) {
  var f = undefined;
  f = message.getUlid();
  if (f !== 0) {
    writer.writeUint64(
      1,
      f
    );
  }
  f = message.getCharnickname();
  if (f.length > 0) {
    writer.writeString(
      2,
      f
    );
  }
  f = message.getUlcaptain();
  if (f !== 0) {
    writer.writeUint64(
      3,
      f
    );
  }
  f = message.getUilogoindex();
  if (f !== 0) {
    writer.writeUint32(
      4,
      f
    );
  }
  f = message.getUimaxmember();
  if (f !== 0) {
    writer.writeUint32(
      5,
      f
    );
  }
  f = message.getSapplicants_asU8();
  if (f.length > 0) {
    writer.writeBytes(
      6,
      f
    );
  }
  f = message.getSnotice_asU8();
  if (f.length > 0) {
    writer.writeBytes(
      7,
      f
    );
  }
  f = message.getUistatus();
  if (f !== 0) {
    writer.writeUint32(
      8,
      f
    );
  }
  f = message.getSdynamicinfo_asU8();
  if (f.length > 0) {
    writer.writeBytes(
      9,
      f
    );
  }
  f = message.getUlcaptainreward();
  if (f !== 0) {
    writer.writeUint64(
      10,
      f
    );
  }
};


/**
 * optional uint64 ulId = 1;
 * @return {number}
 */
proto.PDB_Base.DBGameClub.prototype.getUlid = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 1, 0));
};


/** @param {number} value */
proto.PDB_Base.DBGameClub.prototype.setUlid = function(value) {
  jspb.Message.setField(this, 1, value);
};


/**
 * optional string charNickName = 2;
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getCharnickname = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 2, ""));
};


/** @param {string} value */
proto.PDB_Base.DBGameClub.prototype.setCharnickname = function(value) {
  jspb.Message.setField(this, 2, value);
};


/**
 * optional uint64 ulCaptain = 3;
 * @return {number}
 */
proto.PDB_Base.DBGameClub.prototype.getUlcaptain = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 3, 0));
};


/** @param {number} value */
proto.PDB_Base.DBGameClub.prototype.setUlcaptain = function(value) {
  jspb.Message.setField(this, 3, value);
};


/**
 * optional uint32 uiLogoIndex = 4;
 * @return {number}
 */
proto.PDB_Base.DBGameClub.prototype.getUilogoindex = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 4, 0));
};


/** @param {number} value */
proto.PDB_Base.DBGameClub.prototype.setUilogoindex = function(value) {
  jspb.Message.setField(this, 4, value);
};


/**
 * optional uint32 uiMaxMember = 5;
 * @return {number}
 */
proto.PDB_Base.DBGameClub.prototype.getUimaxmember = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 5, 0));
};


/** @param {number} value */
proto.PDB_Base.DBGameClub.prototype.setUimaxmember = function(value) {
  jspb.Message.setField(this, 5, value);
};


/**
 * optional bytes sApplicants = 6;
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getSapplicants = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 6, ""));
};


/**
 * optional bytes sApplicants = 6;
 * This is a type-conversion wrapper around `getSapplicants()`
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getSapplicants_asB64 = function() {
  return /** @type {string} */ (jspb.Message.bytesAsB64(
      this.getSapplicants()));
};


/**
 * optional bytes sApplicants = 6;
 * Note that Uint8Array is not supported on all browsers.
 * @see http://caniuse.com/Uint8Array
 * This is a type-conversion wrapper around `getSapplicants()`
 * @return {!Uint8Array}
 */
proto.PDB_Base.DBGameClub.prototype.getSapplicants_asU8 = function() {
  return /** @type {!Uint8Array} */ (jspb.Message.bytesAsU8(
      this.getSapplicants()));
};


/** @param {!(string|Uint8Array)} value */
proto.PDB_Base.DBGameClub.prototype.setSapplicants = function(value) {
  jspb.Message.setField(this, 6, value);
};


/**
 * optional bytes sNotice = 7;
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getSnotice = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 7, ""));
};


/**
 * optional bytes sNotice = 7;
 * This is a type-conversion wrapper around `getSnotice()`
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getSnotice_asB64 = function() {
  return /** @type {string} */ (jspb.Message.bytesAsB64(
      this.getSnotice()));
};


/**
 * optional bytes sNotice = 7;
 * Note that Uint8Array is not supported on all browsers.
 * @see http://caniuse.com/Uint8Array
 * This is a type-conversion wrapper around `getSnotice()`
 * @return {!Uint8Array}
 */
proto.PDB_Base.DBGameClub.prototype.getSnotice_asU8 = function() {
  return /** @type {!Uint8Array} */ (jspb.Message.bytesAsU8(
      this.getSnotice()));
};


/** @param {!(string|Uint8Array)} value */
proto.PDB_Base.DBGameClub.prototype.setSnotice = function(value) {
  jspb.Message.setField(this, 7, value);
};


/**
 * optional uint32 uiStatus = 8;
 * @return {number}
 */
proto.PDB_Base.DBGameClub.prototype.getUistatus = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 8, 0));
};


/** @param {number} value */
proto.PDB_Base.DBGameClub.prototype.setUistatus = function(value) {
  jspb.Message.setField(this, 8, value);
};


/**
 * optional bytes sDynamicInfo = 9;
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getSdynamicinfo = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 9, ""));
};


/**
 * optional bytes sDynamicInfo = 9;
 * This is a type-conversion wrapper around `getSdynamicinfo()`
 * @return {string}
 */
proto.PDB_Base.DBGameClub.prototype.getSdynamicinfo_asB64 = function() {
  return /** @type {string} */ (jspb.Message.bytesAsB64(
      this.getSdynamicinfo()));
};


/**
 * optional bytes sDynamicInfo = 9;
 * Note that Uint8Array is not supported on all browsers.
 * @see http://caniuse.com/Uint8Array
 * This is a type-conversion wrapper around `getSdynamicinfo()`
 * @return {!Uint8Array}
 */
proto.PDB_Base.DBGameClub.prototype.getSdynamicinfo_asU8 = function() {
  return /** @type {!Uint8Array} */ (jspb.Message.bytesAsU8(
      this.getSdynamicinfo()));
};


/** @param {!(string|Uint8Array)} value */
proto.PDB_Base.DBGameClub.prototype.setSdynamicinfo = function(value) {
  jspb.Message.setField(this, 9, value);
};


/**
 * optional uint64 ulCaptainReward = 10;
 * @return {number}
 */
proto.PDB_Base.DBGameClub.prototype.getUlcaptainreward = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 10, 0));
};


/** @param {number} value */
proto.PDB_Base.DBGameClub.prototype.setUlcaptainreward = function(value) {
  jspb.Message.setField(this, 10, value);
};

