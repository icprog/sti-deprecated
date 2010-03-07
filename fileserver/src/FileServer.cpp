// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "FileServer.h"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_1;



void
Remote_File_Server::TFile::operator>>= (cdrStream &_n) const
{
  _n.marshalString(filename,0);
  _n.marshalBoolean(exists);
  _n.marshalBoolean(isDirectory);
  _n.marshalBoolean(isHidden);
  lastModified >>= _n;
  length >>= _n;

}

void
Remote_File_Server::TFile::operator<<= (cdrStream &_n)
{
  filename = _n.unmarshalString(0);
  exists = _n.unmarshalBoolean();
  isDirectory = _n.unmarshalBoolean();
  isHidden = _n.unmarshalBoolean();
  (::CORBA::ULong&)lastModified <<= _n;
  (::CORBA::ULong&)length <<= _n;

}

Remote_File_Server::FileServer_ptr Remote_File_Server::FileServer_Helper::_nil() {
  return ::Remote_File_Server::FileServer::_nil();
}

::CORBA::Boolean Remote_File_Server::FileServer_Helper::is_nil(::Remote_File_Server::FileServer_ptr p) {
  return ::CORBA::is_nil(p);

}

void Remote_File_Server::FileServer_Helper::release(::Remote_File_Server::FileServer_ptr p) {
  ::CORBA::release(p);
}

void Remote_File_Server::FileServer_Helper::marshalObjRef(::Remote_File_Server::FileServer_ptr obj, cdrStream& s) {
  ::Remote_File_Server::FileServer::_marshalObjRef(obj, s);
}

Remote_File_Server::FileServer_ptr Remote_File_Server::FileServer_Helper::unmarshalObjRef(cdrStream& s) {
  return ::Remote_File_Server::FileServer::_unmarshalObjRef(s);
}

void Remote_File_Server::FileServer_Helper::duplicate(::Remote_File_Server::FileServer_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
}

Remote_File_Server::FileServer_ptr
Remote_File_Server::FileServer::_duplicate(::Remote_File_Server::FileServer_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
  return obj;
}

Remote_File_Server::FileServer_ptr
Remote_File_Server::FileServer::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


Remote_File_Server::FileServer_ptr
Remote_File_Server::FileServer::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

Remote_File_Server::FileServer_ptr
Remote_File_Server::FileServer::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_FileServer _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_FileServer* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
    if( !_the_nil_ptr ) {
      _the_nil_ptr = new _objref_FileServer;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* Remote_File_Server::FileServer::_PD_repoId = "IDL:Remote_File_Server/FileServer:1.0";


Remote_File_Server::_objref_FileServer::~_objref_FileServer() {
  
}


Remote_File_Server::_objref_FileServer::_objref_FileServer(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::Remote_File_Server::FileServer::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
Remote_File_Server::_objref_FileServer::_ptrToObjRef(const char* id)
{
  if( id == ::Remote_File_Server::FileServer::_PD_repoId )
    return (::Remote_File_Server::FileServer_ptr) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::Remote_File_Server::FileServer::_PD_repoId) )
    return (::Remote_File_Server::FileServer_ptr) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}

// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_cstring
class _0RL_cd_384E6A89F0D7F454_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_00000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::String_var arg_0_;
  const char* arg_0;
  ::CORBA::Boolean result;
};

void _0RL_cd_384E6A89F0D7F454_00000000::marshalArguments(cdrStream& _n)
{
  _n.marshalString(arg_0,0);

}

void _0RL_cd_384E6A89F0D7F454_00000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();

}

void _0RL_cd_384E6A89F0D7F454_00000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);

}

void _0RL_cd_384E6A89F0D7F454_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();

}

const char* const _0RL_cd_384E6A89F0D7F454_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_00000000* tcd = (_0RL_cd_384E6A89F0D7F454_00000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->exists(tcd->arg_0);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::exists(const char* file)
{
  _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_10000000, "exists", 7);
  _call_desc.arg_0 = file;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_20000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_00000000* tcd = (_0RL_cd_384E6A89F0D7F454_00000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->isFile(tcd->arg_0);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::isFile(const char* file)
{
  _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_20000000, "isFile", 7);
  _call_desc.arg_0 = file;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_30000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_00000000* tcd = (_0RL_cd_384E6A89F0D7F454_00000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->isDirectory(tcd->arg_0);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::isDirectory(const char* file)
{
  _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_30000000, "isDirectory", 12);
  _call_desc.arg_0 = file;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_40000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_00000000* tcd = (_0RL_cd_384E6A89F0D7F454_00000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->isAbsolute(tcd->arg_0);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::isAbsolute(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_40000000, "isAbsolute", 11);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_cstring_i_cstring
class _0RL_cd_384E6A89F0D7F454_50000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_50000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::String_var arg_0_;
  const char* arg_0;
  ::CORBA::String_var arg_1_;
  const char* arg_1;
  ::CORBA::Boolean result;
};

void _0RL_cd_384E6A89F0D7F454_50000000::marshalArguments(cdrStream& _n)
{
  _n.marshalString(arg_0,0);
  _n.marshalString(arg_1,0);

}

void _0RL_cd_384E6A89F0D7F454_50000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();
  arg_1_ = _n.unmarshalString(0);
  arg_1 = arg_1_.in();

}

void _0RL_cd_384E6A89F0D7F454_50000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);

}

void _0RL_cd_384E6A89F0D7F454_50000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();

}

const char* const _0RL_cd_384E6A89F0D7F454_50000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_60000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_50000000* tcd = (_0RL_cd_384E6A89F0D7F454_50000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->createNewFolder(tcd->arg_0, tcd->arg_1);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::createNewFolder(const char* containingDir, const char* filename)
{
  _0RL_cd_384E6A89F0D7F454_50000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_60000000, "createNewFolder", 16);
  _call_desc.arg_0 = containingDir;
  _call_desc.arg_1 = filename;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cRemote__File__Server_mTFileSeq_i_cstring
class _0RL_cd_384E6A89F0D7F454_70000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_70000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::String_var arg_0_;
  const char* arg_0;
  Remote_File_Server::TFileSeq_var result;
};

void _0RL_cd_384E6A89F0D7F454_70000000::marshalArguments(cdrStream& _n)
{
  _n.marshalString(arg_0,0);

}

void _0RL_cd_384E6A89F0D7F454_70000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();

}

void _0RL_cd_384E6A89F0D7F454_70000000::marshalReturnedValues(cdrStream& _n)
{
  (const Remote_File_Server::TFileSeq&) result >>= _n;

}

void _0RL_cd_384E6A89F0D7F454_70000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = new Remote_File_Server::TFileSeq;
  (Remote_File_Server::TFileSeq&)result <<= _n;

}

const char* const _0RL_cd_384E6A89F0D7F454_70000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_80000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_70000000* tcd = (_0RL_cd_384E6A89F0D7F454_70000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->getFiles(tcd->arg_0);


}

Remote_File_Server::TFileSeq* Remote_File_Server::_objref_FileServer::getFiles(const char* dir)
{
  _0RL_cd_384E6A89F0D7F454_70000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_80000000, "getFiles", 9);
  _call_desc.arg_0 = dir;

  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Proxy call descriptor class. Mangled signature:
//  _cRemote__File__Server_mTFile_i_cRemote__File__Server_mTFile
class _0RL_cd_384E6A89F0D7F454_90000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_90000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  Remote_File_Server::TFile_var arg_0_;
  const Remote_File_Server::TFile* arg_0;
  Remote_File_Server::TFile_var result;
};

void _0RL_cd_384E6A89F0D7F454_90000000::marshalArguments(cdrStream& _n)
{
  (const Remote_File_Server::TFile&) *arg_0 >>= _n;

}

void _0RL_cd_384E6A89F0D7F454_90000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = new Remote_File_Server::TFile;
  (Remote_File_Server::TFile&)arg_0_ <<= _n;
  arg_0 = &arg_0_.in();

}

void _0RL_cd_384E6A89F0D7F454_90000000::marshalReturnedValues(cdrStream& _n)
{
  (const Remote_File_Server::TFile&) result >>= _n;

}

void _0RL_cd_384E6A89F0D7F454_90000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = new Remote_File_Server::TFile;
  (Remote_File_Server::TFile&)result <<= _n;

}

const char* const _0RL_cd_384E6A89F0D7F454_90000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_a0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_90000000* tcd = (_0RL_cd_384E6A89F0D7F454_90000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->getParentFile(*tcd->arg_0);


}

Remote_File_Server::TFile* Remote_File_Server::_objref_FileServer::getParentFile(const ::Remote_File_Server::TFile& child)
{
  _0RL_cd_384E6A89F0D7F454_90000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_a0000000, "getParentFile", 14);
  _call_desc.arg_0 = &(::Remote_File_Server::TFile&) child;

  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Proxy call descriptor class. Mangled signature:
//  _cstring_i_cstring
class _0RL_cd_384E6A89F0D7F454_b0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_b0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::String_var arg_0_;
  const char* arg_0;
  ::CORBA::String_var result;
};

void _0RL_cd_384E6A89F0D7F454_b0000000::marshalArguments(cdrStream& _n)
{
  _n.marshalString(arg_0,0);

}

void _0RL_cd_384E6A89F0D7F454_b0000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();

}

void _0RL_cd_384E6A89F0D7F454_b0000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalString(result,0);

}

void _0RL_cd_384E6A89F0D7F454_b0000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalString(0);

}

const char* const _0RL_cd_384E6A89F0D7F454_b0000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_c0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_b0000000* tcd = (_0RL_cd_384E6A89F0D7F454_b0000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->normalize(tcd->arg_0);


}

char* Remote_File_Server::_objref_FileServer::normalize(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_c0000000, "normalize", 10);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_d0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_b0000000* tcd = (_0RL_cd_384E6A89F0D7F454_b0000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->canonicalize(tcd->arg_0);


}

char* Remote_File_Server::_objref_FileServer::canonicalize(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_d0000000, "canonicalize", 13);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Proxy call descriptor class. Mangled signature:
//  _cstring
class _0RL_cd_384E6A89F0D7F454_e0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_e0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::String_var result;
};

void _0RL_cd_384E6A89F0D7F454_e0000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalString(result,0);

}

void _0RL_cd_384E6A89F0D7F454_e0000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalString(0);

}

const char* const _0RL_cd_384E6A89F0D7F454_e0000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_f0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_e0000000* tcd = (_0RL_cd_384E6A89F0D7F454_e0000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->getSeparator();


}

char* Remote_File_Server::_objref_FileServer::getSeparator()
{
  _0RL_cd_384E6A89F0D7F454_e0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_f0000000, "getSeparator", 13);


  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_01000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_b0000000* tcd = (_0RL_cd_384E6A89F0D7F454_b0000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->getAbsolutePath(tcd->arg_0);


}

char* Remote_File_Server::_objref_FileServer::getAbsolutePath(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_01000000, "getAbsolutePath", 16);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Proxy call descriptor class. Mangled signature:
//  _clonglong_i_cstring
class _0RL_cd_384E6A89F0D7F454_11000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_384E6A89F0D7F454_11000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::String_var arg_0_;
  const char* arg_0;
  ::CORBA::LongLong result;
};

void _0RL_cd_384E6A89F0D7F454_11000000::marshalArguments(cdrStream& _n)
{
  _n.marshalString(arg_0,0);

}

void _0RL_cd_384E6A89F0D7F454_11000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();

}

void _0RL_cd_384E6A89F0D7F454_11000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_384E6A89F0D7F454_11000000::unmarshalReturnedValues(cdrStream& _n)
{
  (::CORBA::LongLong&)result <<= _n;

}

const char* const _0RL_cd_384E6A89F0D7F454_11000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_21000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_11000000* tcd = (_0RL_cd_384E6A89F0D7F454_11000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->getFileLength(tcd->arg_0);


}

::CORBA::LongLong Remote_File_Server::_objref_FileServer::getFileLength(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_11000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_21000000, "getFileLength", 14);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_31000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_11000000* tcd = (_0RL_cd_384E6A89F0D7F454_11000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->getLastWriteTime(tcd->arg_0);


}

::CORBA::LongLong Remote_File_Server::_objref_FileServer::getLastWriteTime(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_11000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_31000000, "getLastWriteTime", 17);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_41000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_00000000* tcd = (_0RL_cd_384E6A89F0D7F454_00000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->isReadOnly(tcd->arg_0);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::isReadOnly(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_41000000, "isReadOnly", 11);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_51000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_b0000000* tcd = (_0RL_cd_384E6A89F0D7F454_b0000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->readData(tcd->arg_0);


}

char* Remote_File_Server::_objref_FileServer::readData(const char* path)
{
  _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_51000000, "readData", 9);
  _call_desc.arg_0 = path;

  _invoke(_call_desc);
  return _call_desc.result._retn();


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_61000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_50000000* tcd = (_0RL_cd_384E6A89F0D7F454_50000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->writeData(tcd->arg_0, tcd->arg_1);


}

::CORBA::Boolean Remote_File_Server::_objref_FileServer::writeData(const char* path, const char* data)
{
  _0RL_cd_384E6A89F0D7F454_50000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_61000000, "writeData", 10);
  _call_desc.arg_0 = path;
  _call_desc.arg_1 = data;

  _invoke(_call_desc);
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_384E6A89F0D7F454_71000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_384E6A89F0D7F454_e0000000* tcd = (_0RL_cd_384E6A89F0D7F454_e0000000*)cd;
  Remote_File_Server::_impl_FileServer* impl = (Remote_File_Server::_impl_FileServer*) svnt->_ptrToInterface(Remote_File_Server::FileServer::_PD_repoId);
  tcd->result = impl->homeDirectory();


}

char* Remote_File_Server::_objref_FileServer::homeDirectory()
{
  _0RL_cd_384E6A89F0D7F454_e0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_71000000, "_get_homeDirectory", 19);


  _invoke(_call_desc);
  return _call_desc.result._retn();


}
Remote_File_Server::_pof_FileServer::~_pof_FileServer() {}


omniObjRef*
Remote_File_Server::_pof_FileServer::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::Remote_File_Server::_objref_FileServer(ior, id);
}


::CORBA::Boolean
Remote_File_Server::_pof_FileServer::is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::Remote_File_Server::FileServer::_PD_repoId) )
    return 1;
  
  return 0;
}

const Remote_File_Server::_pof_FileServer _the_pof_Remote__File__Server_mFileServer;

Remote_File_Server::_impl_FileServer::~_impl_FileServer() {}


::CORBA::Boolean
Remote_File_Server::_impl_FileServer::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if( omni::strMatch(op, "exists") ) {

    _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_10000000, "exists", 7, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "isFile") ) {

    _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_20000000, "isFile", 7, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "isDirectory") ) {

    _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_30000000, "isDirectory", 12, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "isAbsolute") ) {

    _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_40000000, "isAbsolute", 11, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "createNewFolder") ) {

    _0RL_cd_384E6A89F0D7F454_50000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_60000000, "createNewFolder", 16, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getFiles") ) {

    _0RL_cd_384E6A89F0D7F454_70000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_80000000, "getFiles", 9, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getParentFile") ) {

    _0RL_cd_384E6A89F0D7F454_90000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_a0000000, "getParentFile", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "normalize") ) {

    _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_c0000000, "normalize", 10, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "canonicalize") ) {

    _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_d0000000, "canonicalize", 13, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getSeparator") ) {

    _0RL_cd_384E6A89F0D7F454_e0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_f0000000, "getSeparator", 13, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getAbsolutePath") ) {

    _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_01000000, "getAbsolutePath", 16, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getFileLength") ) {

    _0RL_cd_384E6A89F0D7F454_11000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_21000000, "getFileLength", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getLastWriteTime") ) {

    _0RL_cd_384E6A89F0D7F454_11000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_31000000, "getLastWriteTime", 17, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "isReadOnly") ) {

    _0RL_cd_384E6A89F0D7F454_00000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_41000000, "isReadOnly", 11, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "readData") ) {

    _0RL_cd_384E6A89F0D7F454_b0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_51000000, "readData", 9, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "writeData") ) {

    _0RL_cd_384E6A89F0D7F454_50000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_61000000, "writeData", 10, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "_get_homeDirectory") ) {

    _0RL_cd_384E6A89F0D7F454_e0000000 _call_desc(_0RL_lcfn_384E6A89F0D7F454_71000000, "_get_homeDirectory", 19, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
Remote_File_Server::_impl_FileServer::_ptrToInterface(const char* id)
{
  if( id == ::Remote_File_Server::FileServer::_PD_repoId )
    return (::Remote_File_Server::_impl_FileServer*) this;
  
  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::Remote_File_Server::FileServer::_PD_repoId) )
    return (::Remote_File_Server::_impl_FileServer*) this;
  
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}

const char*
Remote_File_Server::_impl_FileServer::_mostDerivedRepoId()
{
  return ::Remote_File_Server::FileServer::_PD_repoId;
}

POA_Remote_File_Server::FileServer::~FileServer() {}

