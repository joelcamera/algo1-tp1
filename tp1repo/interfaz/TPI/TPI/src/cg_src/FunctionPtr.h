#pragma once
#include <utility>

template< class T >
class FunctionPtr
{
  typedef void* InstancePtr;
  typedef void (*InternalFunction)(InstancePtr, T);
  typedef std::pair<InstancePtr, InternalFunction> Stub;
 
  // turns a free function into our internal function stub
  template <void (*Function)(T)>
  static inline void FunctionStub(InstancePtr, T ARG0)
  {
    // we don't need the instance pointer because we're dealing with free functions
    return (Function)(ARG0);
  }
 
  // turns a member function into our internal function stub
  template <class C, void (C::*Function)(T)>
  static inline void ClassMethodStub(InstancePtr instance, T ARG0)
  {
    // cast the instance pointer back into the original class instance
    return (static_cast<C*>(instance)->*Function)(ARG0);
  }
 

  
public:

	FunctionPtr(void)
    : m_stub(nullptr, nullptr)
	  {
	  }
  static FunctionPtr<T>* GetInstance()
  {
	  FunctionPtr<T> p1;
	  return &p1;
  }
 
  /// Binds a free function
  template <void (*Function)(T)>
  void Bind(void)
  {
    m_stub.first = nullptr;
    m_stub.second = &FunctionStub<Function>;
  }
 
  /// Binds a class method
  template <class C, void (C::*Function)(T)>
  void Bind(C* instance)
  {
    m_stub.first = instance;
    m_stub.second = &ClassMethodStub<C, Function>;
  }
 
  /// Invokes the delegate
  void Invoke(T ARG0) const
  {
	  //(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.")();
    return m_stub.second(m_stub.first, ARG0);
  }
 
private:
  Stub m_stub;
};

